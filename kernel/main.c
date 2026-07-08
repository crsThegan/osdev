#include <kernel/vga_text.h>
#include <utils.h>

void idt_init() {}

void kmain() {
    // idt_init();
    //__asm volatile("sti");

    kclrscr();
    kprint("Hello, World!\nAnd something else...\nAnd something different "
           "again...");
}
