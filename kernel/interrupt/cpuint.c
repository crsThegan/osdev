#include <kernel/interrupt/cpuint.h>

#include <kernel/vga_text.h>

void cpuint_divide_error(void) { kprint("\nerror: #DE fault."); }

void cpuint_debug_exception(void) { kprint("\nerror: #DB trap."); }

void cpuint_nmi(void) { kprint("\nNMI happened."); }

void cpuint_breakpoint(void) { kprint("\n#BP trap."); }

void cpuint_bound_range_exceeded(void) { kprint("\nerror: #BR fault."); }

void cpuint_overflow(void) { kprint("\n#OF trap."); }

void cpuint_undef_opcode(void) { kprint("\nerror: #UD fault."); }

void cpuint_no_math_coproc(void) { kprint("\nerror: #NM fault."); }

void cpuint_double_fault(void) { kprint("\nerror: #DF fault."); }

void cpuint_coproc_seg_overrun(void) {
    kprint("\nCoprocessor Segment Overrun.");
}

void cpuint_invalid_tss(void) { kprint("\nerror: #TS fault."); }

void cpuint_seg_not_present(void) { kprint("\nerror: #NP fault."); }

void cpuint_stack_seg_fault(void) { kprint("\nerror: #SS fault."); }

void cpuint_gen_prot(void) { kprint("\nerror: #GP fault."); }

void cpuint_page_fault(void) { kprint("\nerror: #PF fault."); }

void cpuint_math_fault(void) { kprint("\nerror: #MF fault."); }

void cpuint_align_check(void) { kprint("\nerror: #AC fault."); }

void cpuint_machine_check(void) { kprint("\nerror: #MC abort."); }

void cpuint_simd_fp_exception(void) { kprint("\nerror: #XM fault."); }

void cpuint_virt_exception(void) { kprint("\nerror: #VE fault."); }

void cpuint_control_prot_exception(void) { kprint("\nerror: #CP fault."); }
