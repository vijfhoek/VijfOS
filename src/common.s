[global memmove]
memmove:
	xchg edi, [esp+4]
	xchg esi, [esp+8]
	xchg ecx, [esp+12]
	rep movsb
	xchg edi, [esp+4]
	xchg esi, [esp+8]
	xchg ecx, [esp+12]
	ret
