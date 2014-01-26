[global GDTFlush]
GDTFlush:
	mov eax, [esp+4]
	lgdt [eax]
	ret
