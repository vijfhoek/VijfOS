[global GDTFlush]
GDTFlush:
        mov eax, [esp+4]
        lgdt [eax]
        jmp 0x08:.Far 
.Far:   mov ax, 0x10
        mov ds, ax
        mov es, ax
        mov ss, ax
        ret
