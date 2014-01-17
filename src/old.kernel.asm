	format elf
	include 'terminal.inc'

section '.text'
GDT:
;Access Byte[0:7]    Base[16:23]
;   Limit[16:19]|   / 
;    Flags[0:3]||  / Limit[0:15]
; Base[24:31] ||| / /    Base[0:15]
;           | ||| | |   /
	dq $0000000000000000		; Selector 00
	dq $04C09A0004000000		; Selector 08 - Kernel Code (4MB)
	dq $08C0920004000000		; Selector 10 - Kernel Data (4MB)
	dq $

; eax = base
; ebx = limit
; cl  = flags
; ch  = access byte
AddGDTEntry:
	mov [.gdtr+$0], ax ; Base[0:15]
	mov [.gdtr+$2], bx ; Limit[0:15]
	shr eax, 16
	mov [.gdtr+$3], al ; Base[16:23]
	mov [.gdtr+$4], ch ; Access Byte
	shr ebx, 16
	and bl, $0F
	shl cl, 4
	or bl, cl
	mov [.gdtr+$5], bl ; Flags:Limit[16:19]
	mov [.gdtr+$6], ah ; Base[24:31]

	lgdt [.gdtr]

.gdtr:
	dq $0

public KernelMain
KernelMain:
	; Entry 0 - Must be empty
	mov eax, $00000000
	mov ebx, $00000000
	mov cx, $0000
	call AddGDTEntry
	
	; Entry 8 - Kernel code
	mov eax, $04000000
	mov ebx, $00000400	; 0x400 * 4kiB = 4MiB
	mov cx, $9A0C		; Present, kernel priv, executable,
	call AddGDTEntry	; executable by kernel, readable,
				; 4kiB blocks, 32 bit
	; Entry 16 - Kernel data
	mov eax, $08000000
	mov ebx, $00000400
	mov cx, $920C		; Present, kernel priv, data,
	call AddGDTEntry	; grows up, writable, 4kIb blocks,
				; 32 bit
	; Entry 24 - VGA Memory
	mov eax, $000B8000
	mov ebx, $00000040	; 0x40 * 4kiB = 256kiB
	mov cx, $920C
	call AddGDTEntry

	call TerminalInitialize

	mov al, 0
	mov bl, 0
	mov cx, $0700 + 'a'
	call TerminalPutEntryAt
	
	ret
