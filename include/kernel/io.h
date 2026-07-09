#ifndef IO_H
#define IO_H

#include <utils.h>

void outb(uint16_t port, uint8_t b);
uint8_t inb(uint16_t port);

#endif
