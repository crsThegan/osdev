#include <kernel/vga_text.h>

#include <utils.h>

struct {
    uint8_t *data;
    size_t offset;
} vga = {(uint8_t *)VGA_TEXT_START, 0};

static uint8_t *vga_ptr() {
    if (vga.offset >= 4000)
        vga.offset = 0;
    return &vga.data[vga.offset];
}

static void newline() {
    size_t hskip = 80 * 2 - (vga.offset % 160);
    vga.offset += hskip;
}

void kclrscr() {
    vga.offset = 0;
    for (size_t i = 0; i < 4000; i += 2) {
        vga.data[i] = 0;
        vga.data[i + 1] = 0;
    }
}

void kputch(uint8_t c) {
    if (c == '\n') {
        newline();
        return;
    }

    uint8_t *ptr = vga_ptr();
    *ptr = c;
    *(ptr + 1) = 0x07;
    vga.offset += 2;
}

void kprint(const char *s) {
    for (uint32_t i = 0; s[i] != '\0'; i++) {
        kputch(s[i]);
    }
}
