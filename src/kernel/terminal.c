#include "terminal.h"
#include <string.h>
u16 *Terminal = (u16 *)0xB8000;

void TerminalInitialize()
{
	TerminalCursorPos = 0;
	TerminalColour = 0x07;
	TerminalUpdateCursor();
	
	for (int i = 0; i < 80*25; i++)
		Terminal[i] = 0x0720;
}

void TerminalUpdateCursor()
{
	outb(0x03D4, 14); outb(0x03D5, TerminalCursorPos >> 8);
	outb(0x03D4, 15); outb(0x03D5, TerminalCursorPos & 0xFF);
}

void TerminalPutChar(u8 c)
{
	switch (c)
	{
	case '\b': // Backspace
		TerminalCursorPos--;
		Terminal[TerminalCursorPos] &= 0xFF00;
		Terminal[TerminalCursorPos] |= 0x0020;
		break;

	case '\n':
		TerminalCursorPos = (TerminalCursorPos / 80 + 1) * 80;
		break;

	case '\r':
		TerminalCursorPos = TerminalCursorPos / 80 * 80;
		break;

	case '\t':
		TerminalCursorPos = (TerminalCursorPos / 8 + 1) * 8;
		break;

	default:
		Terminal[TerminalCursorPos++] = (u16)c | (TerminalColour << 8);
	}

	if (TerminalCursorPos > (80*24))
	{
		TerminalCursorPos -= 80;
		for (int i = 0; i < (80 * 24); i++)
			Terminal[i] = Terminal[i + 80];
	}

	TerminalUpdateCursor();
}

void TerminalPutString(u8 *str)
{
	while (*str) TerminalPutChar(*str++);
}

void TerminalPutDecimal(s32 in)
{
	u32 i = in & 0x7FFFFFFF; u8 b = 0;
	if (in < 0) { TerminalPutChar('-'); i++; }
	if (i / 1000000000)     { b = 1; TerminalPutChar(i / 1000000000 + '0'); i -= i / 1000000000 * 1000000000; }
	if (i / 100000000 || b) { b = 1; TerminalPutChar(i / 100000000  + '0'); i -= i / 100000000  * 100000000;  }
	if (i / 10000000  || b) { b = 1; TerminalPutChar(i / 10000000   + '0'); i -= i / 10000000   * 10000000;   }
	if (i / 1000000   || b) { b = 1; TerminalPutChar(i / 1000000    + '0'); i -= i / 1000000    * 1000000;    }
	if (i / 100000    || b) { b = 1; TerminalPutChar(i / 100000     + '0'); i -= i / 100000     * 100000;     }
	if (i / 10000     || b) { b = 1; TerminalPutChar(i / 10000      + '0'); i -= i / 10000      * 10000;      }
	if (i / 1000      || b) { b = 1; TerminalPutChar(i / 1000       + '0'); i -= i / 1000       * 1000;       }
	if (i / 100       || b) { b = 1; TerminalPutChar(i / 100        + '0'); i -= i / 100        * 100;        }
	if (i / 10        || b) { b = 1; TerminalPutChar(i / 10         + '0'); i -= i / 10         * 10;         }
	if (i             || b) {        TerminalPutChar(i              + '0');                                   }
}

const u8 *lut = "0123456789ABCDEF";

void TerminalPutHex32(u32 in)
{
	for (int i = 28; i >= 0; i -= 4)
		TerminalPutChar(lut[(in >> i) & 0x0F]);
}

void TerminalPutHex8(u8 in)
{
	for (int i = 4; i >= 0; i -= 4)
		TerminalPutChar(lut[(in >> i) & 0x0F]);
}
