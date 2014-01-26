#include "gdt.h"

void GDTInit()
{
        GDTSetEntry(0, 0, 0, 0, 0); // null
        GDTSetEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // 0x08: kernel code
        GDTSetEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // 0x10: kernel data
        GDTSetEntry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // 0x18: usermode code
        GDTSetEntry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // 0x20: usermode data
        
        GDTPointer gdtp = { .Base = (u32)GDTEntries, .Limit = sizeof(GDTEntries) - 1 };
        GDTFlush(&gdtp);
}

void GDTSetEntry(int i, u32 base, u32 limit, u8 access, u8 flags)
{
        GDTEntries[i].BaseLow = base;
        GDTEntries[i].BaseMid = base >> 16;
        GDTEntries[i].BaseHigh = base >> 24;
        GDTEntries[i].LimitLow = limit;
        GDTEntries[i].LimitHigh = (flags & 0xF0) | ((limit >> 16) & 0x0F);
        GDTEntries[i].AccessByte = access;
}
