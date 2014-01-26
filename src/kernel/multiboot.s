        %define MAGIC 0x1BADB002

section ".multibootstack"
MBStackBottom:
        times 16384 db 0
MBStackTop:

section ".text"
[global MBStart]
MBStart:
        mov esp, MBStackTop

        [extern KernelMain]
        call KernelMain

        ; When KernelMain returns, disable interrupts and hang
        cli
.Crash: hlt
        jmp .Crash
