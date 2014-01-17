	format elf
	include 'terminal.inc'

section '.text'
public KernelMain
KernelMain:
	call TerminalInitialize

	mov edi, StrSuccessfulLoad
	call TerminalPutString
	
	ret

section '.rodata'
	StrSuccessfulLoad db 'Loaded kernel successfully', $0A, $00

