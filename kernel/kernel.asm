PIC1_CMD equ 0x20
PIC1_DATA equ 0x21

PIC2_CMD equ 0xa0
PIC2_DATA equ 0xa1

; generate ISRs that call irq<n>_handler defined in kernel/interrupt/irq.h
%macro gen_isr_irq 1
	extern irq %+ %1 %+ _handler
	global isr_irq %+ %1
	isr_irq %+ %1:
		call irq %+ %1 %+ _handler
		iretq
%endmacro

; generate ISRs for CPU interrupts that call C handlers defined in kernel/interrupt/cpuint.h
; arg 1: ISR id
; arg 2: C handler name
%macro gen_isr_cpuint 2
	extern %2
	global isr_cpuint %+ %1
	isr_cpuint %+ %1:
		call %2
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

gen_isr_irq 0
gen_isr_irq 1
gen_isr_irq 2
gen_isr_irq 3
gen_isr_irq 4
gen_isr_irq 5
gen_isr_irq 6
gen_isr_irq 7
gen_isr_irq 8
gen_isr_irq 9
gen_isr_irq 10
gen_isr_irq 11
gen_isr_irq 12
gen_isr_irq 13
gen_isr_irq 14
gen_isr_irq 15

gen_isr_cpuint 0, cpuint_divide_error
gen_isr_cpuint 1, cpuint_debug_exception
gen_isr_cpuint 2, cpuint_nmi
gen_isr_cpuint 3, cpuint_breakpoint
gen_isr_cpuint 4, cpuint_bound_range_exceeded
gen_isr_cpuint 5, cpuint_overflow
gen_isr_cpuint 6, cpuint_undef_opcode
gen_isr_cpuint 7, cpuint_no_math_coproc
gen_isr_cpuint 8, cpuint_double_fault
gen_isr_cpuint 9, cpuint_coproc_seg_overrun
gen_isr_cpuint 10, cpuint_invalid_tss
gen_isr_cpuint 11, cpuint_seg_not_present
gen_isr_cpuint 12, cpuint_stack_seg_fault
gen_isr_cpuint 13, cpuint_gen_prot
gen_isr_cpuint 14, cpuint_page_fault
; int 15 reserved
gen_isr_cpuint 16, cpuint_math_fault
gen_isr_cpuint 17, cpuint_align_check
gen_isr_cpuint 18, cpuint_machine_check
gen_isr_cpuint 19, cpuint_simd_fp_exception
gen_isr_cpuint 20, cpuint_virt_exception
gen_isr_cpuint 21, cpuint_control_prot_exception
