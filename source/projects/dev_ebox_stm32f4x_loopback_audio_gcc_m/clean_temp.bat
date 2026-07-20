@echo off
echo %0

del /S *.o
del /S *.obj
del /S *.d
del /S *.map
del /S *.hex
del /S *.elf
del /S *.pdf
del /S *.gv
rmdir /s /q build
rm build
del /S *.tar
del clean_log.txt
del build_log.txt
del c_defines_generated.h
del /S *.svg
del /S *.lst
del /S *.bin
del /S *.su
del /S *.pp
del /S *.bak


