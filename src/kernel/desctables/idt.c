#include "idt.h"
#include <string.h>

void IDTInit()
{
        IDTSetEntry(0,  (u32)ISR00, 0x08, 0x8E);
        IDTSetEntry(1,  (u32)ISR01, 0x08, 0x8E);
        IDTSetEntry(2,  (u32)ISR02, 0x08, 0x8E);
        IDTSetEntry(3,  (u32)ISR03, 0x08, 0x8E);
        IDTSetEntry(4,  (u32)ISR04, 0x08, 0x8E);
        IDTSetEntry(5,  (u32)ISR05, 0x08, 0x8E);
        IDTSetEntry(6,  (u32)ISR06, 0x08, 0x8E);
        IDTSetEntry(7,  (u32)ISR07, 0x08, 0x8E);
        IDTSetEntry(8,  (u32)ISR08, 0x08, 0x8E);
        IDTSetEntry(9,  (u32)ISR09, 0x08, 0x8E);
        IDTSetEntry(10, (u32)ISR10, 0x08, 0x8E);
        IDTSetEntry(11, (u32)ISR11, 0x08, 0x8E);
        IDTSetEntry(12, (u32)ISR12, 0x08, 0x8E);
        IDTSetEntry(13, (u32)ISR13, 0x08, 0x8E);
        IDTSetEntry(14, (u32)ISR14, 0x08, 0x8E);
        IDTSetEntry(15, (u32)ISR15, 0x08, 0x8E);
        IDTSetEntry(16, (u32)ISR16, 0x08, 0x8E);
        IDTSetEntry(17, (u32)ISR17, 0x08, 0x8E);
        IDTSetEntry(18, (u32)ISR18, 0x08, 0x8E);
        IDTSetEntry(19, (u32)ISR19, 0x08, 0x8E);
        IDTSetEntry(20, (u32)ISR20, 0x08, 0x8E);
        IDTSetEntry(21, (u32)ISR21, 0x08, 0x8E);
        IDTSetEntry(22, (u32)ISR22, 0x08, 0x8E);
        IDTSetEntry(23, (u32)ISR23, 0x08, 0x8E);
        IDTSetEntry(24, (u32)ISR24, 0x08, 0x8E);
        IDTSetEntry(25, (u32)ISR25, 0x08, 0x8E);
        IDTSetEntry(26, (u32)ISR26, 0x08, 0x8E);
        IDTSetEntry(27, (u32)ISR27, 0x08, 0x8E);
        IDTSetEntry(28, (u32)ISR28, 0x08, 0x8E);
        IDTSetEntry(29, (u32)ISR29, 0x08, 0x8E);
        IDTSetEntry(30, (u32)ISR30, 0x08, 0x8E);
        IDTSetEntry(31, (u32)ISR31, 0x08, 0x8E);

        IDTPointer idtp = { .Base = (u32)IDTEntries, .Limit = sizeof(IDTEntries) - 1 };
        IDTFlush(&idtp);
}

void IDTSetEntry(u8 i, u32 base, u16 selector, u8 flags)
{
        IDTEntries[i].BaseLow = (u16)base;
        IDTEntries[i].BaseHigh = (u16)(base >> 16);
        IDTEntries[i].Selector = selector;
        IDTEntries[i].Flags = flags;
}

