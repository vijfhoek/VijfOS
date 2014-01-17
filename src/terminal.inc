FG_BLACK         = $00
FG_BLUE          = $01
FG_GREEN         = $02
FG_CYAN          = $03
FG_RED           = $04
FG_MAGENTA       = $05
FG_BROWN         = $06
FG_LIGHT_GREY    = $07
FG_DARK_GREY     = $08
FG_LIGHT_BLUE    = $09
FG_LIGHT_GREEN   = $0A
FG_LIGHT_CYAN    = $0B
FG_LIGHT_RED     = $0C
FG_LIGHT_MAGENTA = $0D
FG_LIGHT_BROWN   = $0E
FG_WHITE         = $0F

BG_BLACK         = $00
BG_BLUE          = $10
BG_GREEN         = $20
BG_CYAN          = $30
BG_RED           = $40
BG_MAGENTA       = $50
BG_BROWN         = $60
BG_LIGHT_GREY    = $70
BG_DARK_GREY     = $80
BG_LIGHT_BLUE    = $90
BG_LIGHT_GREEN   = $A0
BG_LIGHT_CYAN    = $B0
BG_LIGHT_RED     = $C0
BG_LIGHT_MAGENTA = $D0
BG_LIGHT_BROWN   = $E0
BG_WHITE         = $F0

VGA_WIDTH = 80
VGA_HEIGHT = 24

extrn TerminalInitialize
extrn TerminalPutEntryAt
extrn TerminalSetCursorPos
extrn TerminalPutChar
extrn TerminalPutString
