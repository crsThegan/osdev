#ifndef VGA_TEXT_H
#define VGA_TEXT_H

#include <utils.h>

#define VGA_TEXT_START 0xb8000

void kprint(const char *s);
void kclrscr();
void kputch(uint8_t c);

#endif
