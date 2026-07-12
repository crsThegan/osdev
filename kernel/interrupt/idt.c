#include <kernel/interrupt/idt.h>

#include <kernel/interrupt/cpuint.h>
#include <kernel/interrupt/irq.h>
#include <kernel/vga_text.h>
#include <utils.h>

#define IDTENTRY_SET_INT(n, ist)                                               \
    idtentry_set(n, (uintptr_t)isr_cpuint##n, GDT_KERNEL_CODE_ENTRY, ist,      \
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);

#define IDTENTRY_SET_TRAP(n, ist)                                              \
    idtentry_set(n, (uintptr_t)isr_cpuint##n, GDT_KERNEL_CODE_ENTRY, ist,      \
                 IDT_TRAP_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);

#define IDTENTRY_SET_IRQ(n, ist)                                               \
    idtentry_set(n + 0x20, (uintptr_t)isr_irq##n, GDT_KERNEL_CODE_ENTRY, ist,  \
                 IDT_INTERRUPT_GATE, DPL_KERNEL_PRIVILEGE_LEVEL);

struct IDTEntry idt[256] = {0};

struct __attribute__((packed)) {
    uint16_t size;
    uintptr_t base;
} idt_desc;

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
    IDTENTRY_SET_INT(0, 0);
    IDTENTRY_SET_TRAP(1, 0);
    IDTENTRY_SET_INT(2, 0);
    IDTENTRY_SET_TRAP(3, 0);
    IDTENTRY_SET_TRAP(4, 0);
    IDTENTRY_SET_INT(5, 0);
    IDTENTRY_SET_INT(6, 0);
    IDTENTRY_SET_INT(7, 0);
    IDTENTRY_SET_INT(8, 1);
    IDTENTRY_SET_INT(9, 0);
    IDTENTRY_SET_INT(10, 0);
    IDTENTRY_SET_INT(11, 0);
    IDTENTRY_SET_INT(12, 0);
    IDTENTRY_SET_INT(13, 0);
    IDTENTRY_SET_INT(14, 0);
    // int 15 reserved
    IDTENTRY_SET_INT(16, 0);
    IDTENTRY_SET_INT(17, 0);
    IDTENTRY_SET_INT(18, 0);
    IDTENTRY_SET_INT(19, 0);
    IDTENTRY_SET_INT(20, 0);
    IDTENTRY_SET_INT(21, 0);

    // External IRQs
    IDTENTRY_SET_IRQ(0, 0);
    IDTENTRY_SET_IRQ(1, 0);
    IDTENTRY_SET_IRQ(2, 0);
    IDTENTRY_SET_IRQ(3, 0);
    IDTENTRY_SET_IRQ(4, 0);
    IDTENTRY_SET_IRQ(5, 0);
    IDTENTRY_SET_IRQ(6, 0);
    IDTENTRY_SET_IRQ(7, 0);
    IDTENTRY_SET_IRQ(8, 0);
    IDTENTRY_SET_IRQ(9, 0);
    IDTENTRY_SET_IRQ(10, 0);
    IDTENTRY_SET_IRQ(11, 0);
    IDTENTRY_SET_IRQ(12, 0);
    IDTENTRY_SET_IRQ(13, 0);
    IDTENTRY_SET_IRQ(14, 0);
    IDTENTRY_SET_IRQ(15, 0);

    idt_desc_load();
}
