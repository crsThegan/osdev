#include <kernel/interrupt/idt.h>
#include <kernel/vga_text.h>
#include <utils.h>

void kmain(void) {
    kclrscr();
    idt_init();
    __asm volatile("sti");

    kprint("Hello, World!\nAnd something else...\nAnd something different "
           "again...");
}
