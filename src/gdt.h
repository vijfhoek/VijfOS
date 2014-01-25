#pragma once
#include "common.h"

struct GDTEntry
{
	u32 Limit;
	u32 Base;
	u8  Access;
	u8  Flags;
};

void GDTInit();
void GDTSetEntry(int i, u32 base, u32 limit, u8 flags, u8 access);

u64 GDTTable[5];
