#include "terminal.h"
#include "desctables/gdt.h"
#include "desctables/idt.h"

void KernelMain()
{
        GDTInit();
        IDTInit();
        TerminalInitialize();

        TerminalPutString("Loaded kernel successfully\n\n");        
}

void KernelException(u16 ds, u16 ss, u16 cs, u16 es, u32 edi, u32 esi, u32 ebp, u32 esp, u32 ebx, u32 edx, u32 ecx, u32 eax, u8 type, u8 error)
{
// ================================================================================
// Houston, we have a problem: [0x0D] General protection fault: 0x42
// 
// EAX = 0x12345678    EBX = 0x87654321    ECX = 0xDEADBEEF    EDX = 0xBEEFBABE
// ESP = 0xDEADCAFE    EBP = 0xDEADFEED    ESI = 0xBEEFCAFE    EDI = 0xFEEDCAFE
//  ES = 0x0010         CS = 0x0008         SS = 0x0010         DS = 0x0010
// ================================================================================

        TerminalColour = 0x4F;
        TerminalCursorPos = 9 * 80;
        for (int i = 0; i <  80; i++) TerminalPutChar('=');
        for (int i = 0; i < 400; i++) TerminalPutChar(' ');
        for (int i = 0; i <  80; i++) TerminalPutChar('=');
        TerminalCursorPos = 10 * 80;
        TerminalPutString("Houston, we have a problem: [0x");
        TerminalPutHex8(type);
        TerminalPutString("] ");
        switch (type)
        {
        	case  0: TerminalPutString("Division by 0");                                        break;
        	case  1: TerminalPutString("Debug");                                                break;
        	case  2: TerminalPutString("Non-maskable interrupt");                               break;
        	case  3: TerminalPutString("Breakpoint");                                           break;
        	case  4: TerminalPutString("Overflow");                                             break;
        	case  5: TerminalPutString("Out of bounds");                                        break;
        	case  6: TerminalPutString("Invalid opcode");                                       break;
        	case  7: TerminalPutString("No coprocessor");                                       break;
        	case  8: TerminalPutString("Double fault: 0x");             TerminalPutHex8(error); break;
        	case  9: TerminalPutString("Coprocessor segment overrun");                          break;
        	case 10: TerminalPutString("Bad TSS: 0x");                  TerminalPutHex8(error); break;
        	case 11: TerminalPutString("Segment not present: 0x");      TerminalPutHex8(error); break;
        	case 12: TerminalPutString("Stack fault: 0x");              TerminalPutHex8(error); break;
        	case 13: TerminalPutString("General protection fault: 0x"); TerminalPutHex8(error); break;
        	case 14: TerminalPutString("Page fault: 0x");               TerminalPutHex8(error); break;
        	case 15: TerminalPutString("Unknown interrupt");                                    break;
        	case 16: TerminalPutString("Coprocessor fault");                                    break;
        	case 17: TerminalPutString("Alignment check exception");                            break;
        	case 18: TerminalPutString("Machine check exception");                              break;
        	default: TerminalPutString("Unknown error: 0x");            TerminalPutHex8(error); break;
        }

        TerminalCursorPos = 12 * 80 +  2; TerminalPutString("EAX = 0x"); TerminalPutHex32(eax);
        TerminalCursorPos = 12 * 80 + 22; TerminalPutString("EBX = 0x"); TerminalPutHex32(ebx);
        TerminalCursorPos = 12 * 80 + 42; TerminalPutString("ECX = 0x"); TerminalPutHex32(ecx);
        TerminalCursorPos = 12 * 80 + 62; TerminalPutString("EDX = 0x"); TerminalPutHex32(edx);

        TerminalCursorPos = 13 * 80 +  2; TerminalPutString("ESP = 0x"); TerminalPutHex32(esp);
        TerminalCursorPos = 13 * 80 + 22; TerminalPutString("EBP = 0x"); TerminalPutHex32(ebp);
        TerminalCursorPos = 13 * 80 + 42; TerminalPutString("ESI = 0x"); TerminalPutHex32(esi);
        TerminalCursorPos = 13 * 80 + 62; TerminalPutString("EDI = 0x"); TerminalPutHex32(edi);

        TerminalCursorPos = 14 * 80 +  3; TerminalPutString("ES = 0x"); TerminalPutHex16(es);
        TerminalCursorPos = 14 * 80 + 23; TerminalPutString("CS = 0x"); TerminalPutHex16(cs);
        TerminalCursorPos = 14 * 80 + 43; TerminalPutString("SS = 0x"); TerminalPutHex16(ss);
        TerminalCursorPos = 14 * 80 + 63; TerminalPutString("DS = 0x"); TerminalPutHex16(ds);
        
        while (1) __asm__ volatile("hlt");
}
