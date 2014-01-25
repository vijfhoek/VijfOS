[global IDTFlush]
IDTFlush:
	mov eax, [esp]
	lidt [eax]
	ret

%macro _ISR 1
[global ISR%1]
ISR%1:
	push byte 0
	push byte %1
	pushad
	extern KernelException
	call KernelException
	popad
	pop ax
	iret
%endmacro

%macro _ISR_ERR 1
[global ISR%1]
ISR%1:
	push byte %1
	pushad
	extern KernelException
	call KernelException
	popad
	pop ax
	iret
%endmacro

_ISR 00		; Division by zero
_ISR 01		; Debug
_ISR 02		; Non-maskable interrupt
_ISR 03		; Breakpoint
_ISR 04		; Overflow
_ISR 05		; Out of bounds
_ISR 06		; Invalid opcode
_ISR 07		; No coprocessor
_ISR_ERR 08	; Double fault
_ISR 09		; Coprocessor segment overrun
_ISR_ERR 10	; Bad TSS
_ISR_ERR 11	; Segment not present
_ISR_ERR 12	; Stack fault
_ISR_ERR 13	; General protection fault
_ISR_ERR 14	; Page fault
_ISR 15		; Unknown interrupt
_ISR 16		; Coprocessor fault
_ISR 17		; Alignment check exception
_ISR 18		; Machine check exception
_ISR 19		; Reserved
_ISR 20
_ISR 21
_ISR 22
_ISR 23
_ISR 24
_ISR 25
_ISR 26
_ISR 27
_ISR 28
_ISR 29
_ISR 30
_ISR 31

