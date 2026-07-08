section .text.entry
global kernel_entry
extern kmain

kernel_entry:
	call kmain
.hang:
	hlt
	jmp .hang
