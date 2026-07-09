#include <kernel/interrupt/idt.h>

#include <kernel/interrupt/irq.h>
#include <kernel/vga_text.h>
#include <utils.h>

struct IDTEntry idt[256] = {0};

struct __attribute__((packed)) {
    uint16_t size;
    uintptr_t base;
} idt_desc;

static void divide_error(void) {
    kprint("\nerror: #DE fault.");
    __asm volatile("hlt");
}

static void debug_exception(void) {
    kprint("\nerror: #DB trap.");
    __asm volatile("hlt");
}

static void nmi_int(void) {
    kprint("\nNMI happened.");
    __asm volatile("hlt");
}

static void breakpoint(void) {
    kprint("\n#BP trap.");
    __asm volatile("hlt");
}

static void bound_range_exceeded(void) {
    kprint("\nerror: #BR fault.");
    __asm volatile("hlt");
}

static void overflow(void) {
    kprint("\n#OF trap.");
    __asm volatile("hlt");
}

static void undef_opcode(void) {
    kprint("\nerror: #UD fault.");
    __asm volatile("hlt");
}

static void no_math_coproc(void) {
    kprint("\nerror: #NM fault.");
    __asm volatile("hlt");
}

static void double_fault(void) {
    kprint("\nerror: #DF fault.");
    __asm volatile("hlt");
}

static void coproc_seg_overrun(void) {
    kprint("\nCoprocessor Segment Overrun.");
    __asm volatile("hlt");
}

static void invalid_tss(void) {
    kprint("\nerror: #TS fault.");
    __asm volatile("hlt");
}

static void seg_not_present(void) {
    kprint("\nerror: #NP fault.");
    __asm volatile("hlt");
}

static void stack_seg_fault(void) {
    kprint("\nerror: #SS fault.");
    __asm volatile("hlt");
}

static void gen_prot(void) {
    kprint("\nerror: #GP fault.");
    __asm volatile("hlt");
}

static void page_fault(void) {
    kprint("\nerror: #PF fault.");
    __asm volatile("hlt");
}

static void math_fault(void) {
    kprint("\nerror: #MF fault.");
    __asm volatile("hlt");
}

static void align_check(void) {
    kprint("\nerror: #AC fault.");
    __asm volatile("hlt");
}

static void machine_check(void) {
    kprint("\nerror: #MC abort.");
    __asm volatile("hlt");
}

static void simd_fp_exception(void) {
    kprint("\nerror: #XM fault.");
    __asm volatile("hlt");
}

static void virt_exception(void) {
    kprint("\nerror: #VE fault.");
    __asm volatile("hlt");
}

static void control_prot_exception(void) {
    kprint("\nerror: #CP fault.");
    __asm volatile("hlt");
}

void idtentry_set_offset(struct IDTEntry *self, uintptr_t offset) {
    self->offset1 = offset & 0xffff;
    self->offset2 = (offset >> 16) & 0xffff;
    self->offset3 = (offset >> 32) & 0xffffffff;
}

void idtentry_set_type_attr(struct IDTEntry *self, uint8_t gate_type,
                            uint8_t dpl) {
    uint8_t type_attr = 0;
    type_attr |= gate_type & 0xf;
    type_attr |= dpl << 5;
    type_attr |= 0b10000000; // set present bit

    self->type_attr = type_attr;
}

void idtentry_set(size_t entry_id, uintptr_t offset, uint16_t selector,
                  uint8_t ist, uint8_t gate_type, uint8_t dpl) {
    if (entry_id >= sizeof(idt) / sizeof(struct IDTEntry)) {
        kprint("\nerror: tried setting an IDT entry that isn't mapped.");
        return;
    }

    idtentry_set_offset(idt + entry_id, offset);
    idt[entry_id].selector = selector;
    idt[entry_id].ist = ist;
    idtentry_set_type_attr(idt + entry_id, gate_type, dpl);
}

static void idt_desc_load() {
    idt_desc.size = sizeof(idt) - 1;
    idt_desc.base = (uintptr_t)idt;

    __asm volatile("lidt %0" : : "m"(idt_desc));
}

void idt_init(void) {
    // Internal CPU interrupts
    idtentry_set(0, (uintptr_t)divide_error, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(1, (uintptr_t)debug_exception, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_TRAP_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(2, (uintptr_t)nmi_int, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(3, (uintptr_t)breakpoint, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_TRAP_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(4, (uintptr_t)overflow, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_TRAP_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(5, (uintptr_t)bound_range_exceeded, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(6, (uintptr_t)undef_opcode, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(7, (uintptr_t)no_math_coproc, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(8, (uintptr_t)double_fault, GDT_KERNEL_CODE_ENTRY, 1,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(9, (uintptr_t)coproc_seg_overrun, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(10, (uintptr_t)invalid_tss, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(11, (uintptr_t)seg_not_present, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(12, (uintptr_t)stack_seg_fault, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(13, (uintptr_t)gen_prot, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(14, (uintptr_t)page_fault, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(16, (uintptr_t)math_fault, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(17, (uintptr_t)align_check, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(18, (uintptr_t)machine_check, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(19, (uintptr_t)simd_fp_exception, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(20, (uintptr_t)virt_exception, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(21, (uintptr_t)control_prot_exception, GDT_KERNEL_CODE_ENTRY,
                 0, IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);

    // External IRQs
    idtentry_set(32, (uintptr_t)isr0, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(33, (uintptr_t)isr1, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(34, (uintptr_t)isr2, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(35, (uintptr_t)isr3, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(36, (uintptr_t)isr4, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(37, (uintptr_t)isr5, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(38, (uintptr_t)isr6, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(39, (uintptr_t)isr7, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(40, (uintptr_t)isr8, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(41, (uintptr_t)isr9, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(42, (uintptr_t)isr10, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(43, (uintptr_t)isr11, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(44, (uintptr_t)isr12, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(45, (uintptr_t)isr13, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(46, (uintptr_t)isr14, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);
    idtentry_set(47, (uintptr_t)isr15, GDT_KERNEL_CODE_ENTRY, 0,
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);

    idt_desc_load();
}
