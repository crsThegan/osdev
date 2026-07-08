#include <kernel/vga_text.h>
#include <utils.h>

#define VGA_START 0xb8000

void idt_init() {}

void kmain() {
    // idt_init();
    //__asm volatile("sti");

    kclrscr();
    kprint("Hello, World!\nAnd something else...\nAnd something different "
           "again...");
}
