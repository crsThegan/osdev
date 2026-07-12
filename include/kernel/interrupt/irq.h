#ifndef INTERRUPT_IRQ_H
#define INTERRUPT_IRQ_H

#include <utils.h>

// ISRs that are defined in kernel/kernel.asm.
// They are uncallable and should only be used for loading their address into an
// IDT entry.
extern void isr_irq0(void);
extern void isr_irq1(void);
extern void isr_irq2(void);
extern void isr_irq3(void);
extern void isr_irq4(void);
extern void isr_irq5(void);
extern void isr_irq6(void);
extern void isr_irq7(void);
extern void isr_irq8(void);
extern void isr_irq9(void);
extern void isr_irq10(void);
extern void isr_irq11(void);
extern void isr_irq12(void);
extern void isr_irq13(void);
extern void isr_irq14(void);
extern void isr_irq15(void);

void irq0_handler(void);
void irq1_handler(void);
void irq2_handler(void);
void irq3_handler(void);
void irq4_handler(void);
void irq5_handler(void);
void irq6_handler(void);
void irq7_handler(void);
void irq8_handler(void);
void irq9_handler(void);
void irq10_handler(void);
void irq11_handler(void);
void irq12_handler(void);
void irq13_handler(void);
void irq14_handler(void);
void irq15_handler(void);

#endif
