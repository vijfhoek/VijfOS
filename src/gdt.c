#include "gdt.h"

void GDTInit()
{
	int i = (u32)GDTTable << 16 | (u16)sizeof(GDTTable) - 1;

	GDTSetEntry(0, 0, 0, 0, 0); // null
	GDTSetEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // kernel code
	GDTSetEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // kernel data
	GDTSetEntry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // usermode code
	GDTSetEntry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // usermode data

	// TODO Load the GDT table
}

void GDTSetEntry(int i, u32 base, u32 limit, u8 flags, u8 access)
{
	GDTTable[i] =
		(u64)(base   & 0xFF000000) << (56 - 24) |
		(u64)(flags  & 0x000000F0) <<  48       | 
		(u64)(limit  & 0x000F0000) << (48 - 16) |
		(u64)(access             ) <<  40       | 
		(u64)(base   & 0x00FF0000) << (32 - 16) |
		(u64)(base   & 0x0000FFFF) <<  16       |
		(u64)(limit  & 0x0000FFFF);
}
