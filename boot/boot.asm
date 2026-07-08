org 0x7c00
bits 16

; Clearing the interrupt flag and setting up the stack
cli
xor ax, ax
mov ss, ax
mov sp, 0x1000
sti

; Reading disk sectors with BIOS for stage 2
mov ah, 0x02
mov al, 1			; number of sectors to read
xor ch, ch
mov cl, 2
xor dh, dh
xor bx, bx
mov es, bx
mov bx, 0x8000		; loaded data address at es:bx
int 0x13

mov ax, 0xb800
mov es, ax
xor di, di

mov ax, 0x0f41
stosw

jmp 0x0000:0x8000			; second stage

times 510 - ($ - $$) db 0
dw 0xaa55
