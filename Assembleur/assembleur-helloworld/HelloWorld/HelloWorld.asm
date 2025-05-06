.386
.model flat,stdcall
option casemap:none

include c:\masm32\include\windows.inc
include c:\masm32\include\gdi32.inc
include c:\masm32\include\gdiplus.inc
include c:\masm32\include\user32.inc
include c:\masm32\include\kernel32.inc
include c:\masm32\include\msvcrt.inc

includelib c:\masm32\lib\gdi32.lib
includelib c:\masm32\lib\kernel32.lib
includelib c:\masm32\lib\user32.lib
includelib c:\masm32\lib\msvcrt.lib

.DATA
; variables initialisees
Phrase     db    "Hello World : %d",10,0
strCommand db "Pause",13,10,0

.DATA?
; variables non-initialisees (bss)

.CODE
start:
		; on place le premier argument de la fonction appelée sur la pile
		push 42
		; On place le second argument de la fonction appelée sur la pile
        push offset Phrase
        ; call printf
        call crt_printf
		
		
		invoke crt_system, offset strCommand
		mov eax, 0
	    invoke	ExitProcess,eax

end start

