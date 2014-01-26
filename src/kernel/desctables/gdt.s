[global GDTFlush]
GDTFlush:
	mov eax, [esp+4]
	lgdt [eax]
	jmp 0x08:.farjmp 
.farjmp:
	ret
