#pragma once
#include "../common.h"

typedef struct __attribute__((packed))
{
	u16 BaseLow;			// Lower 16 bits of address to jump to
	u16 Selector;			// Kernel segment selector
	u8  Reserved;			// Should always be 0
	u8  Flags;
	u16 BaseHigh;			// Higher 16 bits of the address to jump to
} IDTEntry;

typedef struct __attribute__((packed))
{
	u16 Limit;
	u32 Base;
} IDTPointer;

IDTEntry IDTEntries[256];

void IDTInit();
void IDTSetEntry(u8 i, u32 base, u16 selector, u8 flags);
extern void IDTFlush();

// Extern because these have to be handled in assembly
extern void ISR00();
extern void ISR01();
extern void ISR02();
extern void ISR03();
extern void ISR04();
extern void ISR05();
extern void ISR06();
extern void ISR07();
extern void ISR08();
extern void ISR09();
extern void ISR10();
extern void ISR11();
extern void ISR12();
extern void ISR13();
extern void ISR14();
extern void ISR15();
extern void ISR16();
extern void ISR17();
extern void ISR18();
extern void ISR19();
extern void ISR20();
extern void ISR21();
extern void ISR22();
extern void ISR23();
extern void ISR24();
extern void ISR25();
extern void ISR26();
extern void ISR27();
extern void ISR28();
extern void ISR29();
extern void ISR30();
extern void ISR31();
