#ifndef INTERRUPT_CPUINT_H
#define INTERRUPT_CPUINT_H

// Not callable. Use only for getting the address of ISRs for CPU interrupts
// defined in kernel/kernel.asm.
void isr_cpuint0(void);
void isr_cpuint1(void);
void isr_cpuint2(void);
void isr_cpuint3(void);
void isr_cpuint4(void);
void isr_cpuint5(void);
void isr_cpuint6(void);
void isr_cpuint7(void);
void isr_cpuint8(void);
void isr_cpuint9(void);
void isr_cpuint10(void);
void isr_cpuint11(void);
void isr_cpuint12(void);
void isr_cpuint13(void);
void isr_cpuint14(void);
void isr_cpuint15(void);
void isr_cpuint16(void);
void isr_cpuint17(void);
void isr_cpuint18(void);
void isr_cpuint19(void);
void isr_cpuint20(void);
void isr_cpuint21(void);

// C handlers of CPU interrupts that are called inside of ISRs.
void cpuint_divide_error(void);
void cpuint_debug_exception(void);
void cpuint_nmi(void);
void cpuint_breakpoint(void);
void cpuint_bound_range_exceeded(void);
void cpuint_overflow(void);
void cpuint_undef_opcode(void);
void cpuint_no_math_coproc(void);
void cpuint_double_fault(void);
void cpuint_coproc_seg_overrun(void);
void cpuint_invalid_tss(void);
void cpuint_seg_not_present(void);
void cpuint_stack_seg_fault(void);
void cpuint_gen_prot(void);
void cpuint_page_fault(void);
void cpuint_math_fault(void);
void cpuint_align_check(void);
void cpuint_machine_check(void);
void cpuint_simd_fp_exception(void);
void cpuint_virt_exception(void);
void cpuint_control_prot_exception(void);

#endif
