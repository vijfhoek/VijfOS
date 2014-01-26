#pragma once
#include "common.h"

u16 TerminalCursorPos;
u8 TerminalColour;

extern u16 *Terminal;
void TerminalInitialize();
void TerminalUpdateCursor();
void TerminalPutChar(u8 c);
void TerminalPutString(u8 *str);
void TerminalPutDecimal(s32 in);
void TerminalPutHex32(u32 in);
void TerminalPutHex16(u16 in);
void TerminalPutHex8(u8 in);
