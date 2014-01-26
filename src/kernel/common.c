#include "common.h"

void outb(u16 port, u8 value)
{
        __asm__ volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}
