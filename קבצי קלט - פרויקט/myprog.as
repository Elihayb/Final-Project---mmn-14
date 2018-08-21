; Write your own assembly language source program.
; The program should contain at least 10 insructions, 5 labels, 5 directives
; No errors: the assembler should generate successfully all output files:
;     myprog.ob, myprog.ext, myprog.ent

XYZ: .data 7,-57,-9,33

MOV: mov XYZ,r2

lea MOV,r7

STR: .string "C language"

.entry HELLO

HELLO: cmp #-5,MOV

VeryLongLabelString: .data 5,2,5,4,8,7,6,9,5,4,1,8,5,-5,-1000

.extern EXT

not r5

TNX: .string "thank you for the great lessons"

STOP: stop