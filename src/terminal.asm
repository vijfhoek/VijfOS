format elf

VGA_WIDTH = 80
VGA_HEIGHT = 24

	public TerminalCursorPos
	TerminalCursorPos dw 0
	public TerminalColour
	TerminalColour db 0

public TerminalInitialize
TerminalInitialize:
	mov [TerminalCursorPos], 0
	mov [TerminalColour], $07

	xor bx, bx
	call TerminalSetCursorI

	mov esi, $B8000
	mov edi, $B8004
	mov dword [$B8000], $0720
	mov cx, (VGA_WIDTH * VGA_HEIGHT / 2) - 1
	rep movsd
	ret

; al = y position
; bl = x position
; ch = colour/attributes
; cl = ascii character
public TerminalPutEntryAt
TerminalPutEntryAt:
	mov ah, VGA_WIDTH
	mul ah
	xor bh, bh
	add ax, bx
	movzx edi, ax
	mov [$B8000 + edi], cx
	ret

; bx = cursor index
; ch = colour/attributes
; cl = ascii character
public TerminalPutEntryAtI
TerminalPutEntryAtI:
	movzx edi, bx
	mov [$B8000 + edi], cx
	ret

; al = y position
; bl = x position
public TerminalSetCursorPos
TerminalSetCursorPos:
	mov ah, VGA_WIDTH
	mul ah
	xor bh, bh
	add bx, ax
	call TerminalSetCursorI
	ret

; bx = cursor index
public TerminalSetCursorI
TerminalSetCursorI:
	mov [TerminalCursorPos], bx
	; Low byte
	mov al, $0F
	mov dx, $03D4
	out dx, al
	mov al, bl
	inc dl
	out dx, al
	; High byte
	mov al, $0E
	mov dx, $03D4
	out dx, al
	mov al, bh
	inc dl
	out dx, al
	ret

public TerminalPutChar
TerminalPutChar:
	xor ebx, ebx
	mov bx, [TerminalCursorPos]

	cmp al, $0A		; newline
	jne @f
	mov ax, bx
	mov bx, 80
	xor dx, dx
	div bx
	sub ax, 80
	sub [TerminalCursorPos], ax
	call TerminalSetCursorI
	ret

@@:	xor ebx, ebx
	mov bx, [TerminalCursorPos]
	mov ah, [TerminalColour]
	shl bx, 1
	mov [$B8000 + ebx], ax
	shr bx, 1
	inc bx
	call TerminalSetCursorI
	ret

public TerminalPutString
TerminalPutString:
	mov al, [edi]
	or al, al
	jz .end
	inc edi
	call TerminalPutChar
	jmp TerminalPutString
.end:	ret
