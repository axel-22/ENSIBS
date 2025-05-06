@echo off
c:\masm32\bin\ml /c /Zd /coff HelloWorld.asm
c:\\masm32\bin\Link /SUBSYSTEM:CONSOLE HelloWorld.obj
pause