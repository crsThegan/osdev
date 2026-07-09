#include <kernel/io.h>

#include <utils.h>

void outb(uint16_t port, uint8_t b) {
    __asm volatile("out %0, %1" : : "a"(b), "Nd"(port));
}

uint8_t inb(uint16_t port) {
    uint8_t input;
    __asm volatile("in %1, %0" : "=a"(input) : "Nd"(port));

    return input;
}
