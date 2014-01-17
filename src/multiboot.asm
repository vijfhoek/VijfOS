format elf

	MEMALIGN = $01
	MEMINFO  = $02
	FLAGS    = MEMALIGN + MEMINFO
	MAGIC    = $1BADB002
	CHECKSUM = -(MAGIC + FLAGS)

section '.multiboot'
	align 4
	dd MAGIC 
	dd FLAGS
	dd CHECKSUM

section ".multibootstack"
MBStackBottom:
	times 16384 db ?
MBStackTop:

section ".text"
	public MBStart
MBStart:
	mov esp, MBStackTop
	extrn KernelMain
	call KernelMain

	; When KernelMain returns, disable interrupts and hang
	cli
@@:	hlt
	jmp @b
