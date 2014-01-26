#pragma once
#include "../common.h"

typedef struct __attribute__((packed))
{
        u16 LimitLow;
        u16 BaseLow;
        u8  BaseMid;
        u8  AccessByte;
        u8  LimitHigh;
        u8  BaseHigh;
} GDTEntry;

typedef struct __attribute__((packed))
{
        u16 Limit;
        u32 Base;
} GDTPointer;

void GDTInit();
void GDTSetEntry(int i, u32 base, u32 limit, u8 access, u8 flags);
extern void GDTFlush();

GDTEntry GDTEntries[5];
