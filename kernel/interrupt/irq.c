#include <kernel/interrupt/irq.h>

#include <kernel/io.h>
#include <kernel/vga_text.h>

#define PIC1_CMD 0x20

uint32_t ticks = 0;

static inline void int_ack() { outb(PIC1_CMD, 0x20); }

void irq0_handler(void) {
    ticks++;
    int_ack();
}
void irq1_handler(void) {
    kprint("\nIRQ1");
    int_ack();
}

void irq2_handler(void) {
    kprint("\nIRQ2");
    int_ack();
}

void irq3_handler(void) {
    kprint("\nIRQ3");
    int_ack();
}

void irq4_handler(void) {
    kprint("\nIRQ4");
    int_ack();
}

void irq5_handler(void) {
    kprint("\nIRQ5");
    int_ack();
}

void irq6_handler(void) {
    kprint("\nIRQ6");
    int_ack();
}

void irq7_handler(void) {
    kprint("\nIRQ7");
    int_ack();
}

void irq8_handler(void) {
    kprint("\nIRQ8");
    int_ack();
}

void irq9_handler(void) {
    kprint("\nIRQ9");
    int_ack();
}

void irq10_handler(void) {
    kprint("\nIRQ10");
    int_ack();
}

void irq11_handler(void) {
    kprint("\nIRQ11");
    int_ack();
}

void irq12_handler(void) {
    kprint("\nIRQ12");
    int_ack();
}

void irq13_handler(void) {
    kprint("\nIRQ13");
    int_ack();
}

void irq14_handler(void) {
    kprint("\nIRQ14");
    int_ack();
}

void irq15_handler(void) {
    kprint("\nIRQ15");
    int_ack();
}
