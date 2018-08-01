; This file contains errors in jmp instructions using addressing mode 2.

; Each line (except a few) contains an error in the assembly language code.
; A comment preceding each line explains the error.

; All errors should be detectable in the first pass of the assembler.

; Run the assembler on this file, and verify that it catches all the errors.
; Your assembler messages need not be identical to the comments in this file.

; Disclaimer: this list of errors is not exhaustive; 
;             you are encouraged to identify additional errors.

; 1. this line is ok 
JMP1:   jmp sof

; 2. this line is ok 
JMP2:   bne sof(r1,r2)

; 3. this line is ok 
        beq JMP2(#100,sof)

; 4. this line is ok 
        beq sof(sof,sof)

; 5. missing argument
        jmp sof(r1,)

; 6. missing argument
        jmp sof()

; 7. invalid argument (cannot be instruction)
        jmp sof(r1,mov)

; 8. invalid characters ( r1))
        jmp JMP1(#100, r1)

; 9. invalid characters (, r3))
        jmp JMP1(#200, r3)

; 10. invalid argument (immediate too large)
        jmp JMP1(r2,#10000)		
		
; 11. invalid characters ((#100,r1))
        jmp JMP1 (#100,r1)
		
; 12. invalid characters (,r1))
        beq sof(,r1)
		
; 13. invalid characters (,#100))
        jmp sof(r1,,#100)
				
; 14. invalid characters (,blabla))
        bne sof(#100,#200,blabla)
	
; 15. invalid characters ([r1,r2])
        beq sof[r1,r2]

; 16. invalid characters (,#100,#200)		
        jmp JMP1,#100,#200
		
; 17. invalid characters (1000))
        bne JMP1(r2,1000)

; 18. this line is ok
sof:    stop 