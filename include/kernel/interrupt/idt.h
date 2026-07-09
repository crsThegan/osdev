#ifndef INTERRUPT_IDT_H
#define INTERRUPT_IDT_H

#include <utils.h>

#define GDT_KERNEL_CODE_ENTRY 0x18
#define GDT_KERNEL_DATA_ENTRY 0x20
#define GDT_USER_CODE_ENTRY 0x28
#define GDT_USER_DATA_ENTRY 0x30

#define IDT_INTERRUPT_GATE 0xe
#define IDT_TRAP_GATE 0xf

#define DPL_KERNEL_PRIVILEGE_LEVEL 0
#define DPL_USER_PRIVILEGE_LEVEL 3

struct IDTEntry {
    uint16_t offset1;
    uint16_t selector;
    uint8_t ist;
    uint8_t type_attr;
    uint16_t offset2;
    uint32_t offset3;
    uint32_t zero;
};

void idtentry_set_offset(struct IDTEntry *self, uintptr_t offset);
void idtentry_set_type_attr(struct IDTEntry *self, uint8_t gate_type,
                            uint8_t dpl);
void idtentry_set(size_t entry_id, uintptr_t offset, uint16_t selector,
                  uint8_t ist, uint8_t gate_type, uint8_t dpl);
void idt_init(void);

extern struct IDTEntry idt[256];

#endif
