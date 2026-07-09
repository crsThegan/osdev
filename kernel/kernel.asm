PIC1_CMD equ 0x20
PIC1_DATA equ 0x21

PIC2_CMD equ 0xa0
PIC2_DATA equ 0xa1

; generate ISRs that call irq<n>_handler defined in kernel/interrupt/irq.h
%macro gen_isr 1
	extern irq %+ %1 %+ _handler
	global isr %+ %1
	isr %+ %1:
		call irq %+ %1 %+ _handler
		iretq
%endmacro

section .text.entry
global kernel_entry
extern kmain

kernel_entry:
	; initializing PICs
	mov al, 0x11
	out PIC1_CMD, al

	mov al, 0x11
	out PIC2_CMD, al
		
	; Remapping PIC interrupts to start from 0x20 for master, 0x28 for slave
	mov al, 0x20
	out PIC1_DATA, al

	mov al, 0x28
	out PIC2_DATA, al

	call kmain
.hang:
	hlt
	jmp .hang

gen_isr 0
gen_isr 1
gen_isr 2
gen_isr 3
gen_isr 4
gen_isr 5
gen_isr 6
gen_isr 7
gen_isr 8
gen_isr 9
gen_isr 10
gen_isr 11
gen_isr 12
gen_isr 13
gen_isr 14
gen_isr 15
