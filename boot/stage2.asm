org 0x8000
bits 16

; load the kernel into RAM
xor ax, ax
mov ds, ax

mov ah, 0x02
mov al, 10
xor ch, ch
mov cl, 3
xor dh, dh
mov bx, 0x1000
mov es, bx
xor bx, bx
int 0x13

; enable A20
in al, 0x92
or al, 0b00000010
out 0x92, al

lgdt [gdt_desc]

; set PE bit
mov eax, cr0
or eax, 1
mov cr0, eax

jmp 0x08:prot_entry

bits 32
prot_entry:
	cli
	; setting up the 32-bit stack
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov esp, 0x1000


	; loading TSS at runtime
	mov eax, tss            ; low 32 bits of address

	mov word [tss_desc + 0], tss_end - tss - 1   ; limit
	mov word [tss_desc + 2], ax                  ; base 15:0

	shr eax, 16
	mov byte [tss_desc + 4], al                  ; base 23:16

	mov byte [tss_desc + 5], 0b10001001          ; type/P/DPL

	mov byte [tss_desc + 6], 0                   ; limit high + flags

	mov byte [tss_desc + 7], ah                  ; base 31:24

	xor eax, eax
	mov dword [tss_desc + 8], eax                ; base 63:32
	mov dword [tss_desc + 12], 0

	mov ax, tss_desc - gdt
	ltr ax

	; clear page tables pages
	mov edi, 0x100000
	mov ecx, 4096 * 3 / 4
	xor eax, eax
	rep stosd

	; PML4[0] -> PDPT
	mov dword [0x100000], 0x101000 | 0x03
	mov dword [0x100000 + 4], 0

	; PDPT[0] -> PD
	mov dword [0x101000], 0x102000 | 0x03
	mov dword [0x101000 + 4], 0

	; map first 1 GiB with 2 MiB pages
	mov edi, 0x102000
	mov eax, 0x00000083
	mov ecx, 512

	.map_pd:
		mov dword [edi], eax
		mov dword [edi + 4], 0
		add eax, 0x200000
		add edi, 8
		loop .map_pd
	
	; load CR3 with PML4
	mov eax, 0x100000
	mov cr3, eax

	; enable PAE
	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax

	mov ecx, 0xc0000080		; IA32_EFER
	rdmsr
	or eax, 1 << 8			; LME
	wrmsr

	; enable paging
	mov eax, cr0
	or eax, 1 << 31
	mov cr0, eax
	mov eax, cr0

	jmp 0x18:long_entry

bits 64
long_entry:
	mov ax, 0x20
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov rsp, 0x74000

	jmp 0x10000

.hang:
	hlt
	jmp .hang

gdt_desc:
	dw gdt_end - gdt - 1
	dd gdt
	
gdt:
	; null
	dq 0x0000000000000000
	; 32-bit code
	dq 0x00CF9A000000FFFF
	; 32-bit data
	dq 0x00CF92000000FFFF
	; kernel code
	dq 0x00209a0000000000
	; kernel data
	dq 0x0000920000000000
	; user code
	dq 0x0020fa0000000000
	; user data
	dq 0x0000f20000000000

tss_desc:
	dq 0
	dq 0
gdt_end:

tss:
	; reserved
	dd 0
	; rsp0 low
	dd 0x00074000
	; rsp0 high
	dd 0
	; rsp1 low
	dd 0
	; rsp1 high
	dd 0
	; rsp2 low
	dd 0
	; rsp2 high
	dd 0
	; reserved
	dq 0
	; ist1 low
	dd 0x00078000
	; ist1 high
	dd 0
	; ist2
	dq 0
	; ist3
	dq 0
	; ist4
	dq 0
	; ist5
	dq 0
	; ist6
	dq 0
	; ist7
	dq 0
	; reserved
	dq 0
	dd 0
	; iopb
	dd 0xffffffff
tss_end:
