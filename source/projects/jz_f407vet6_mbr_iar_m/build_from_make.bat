echo off
cls

call clean_temp.bat

del /S /Q *.gv
del /S /Q *.svg

make -i clean 2>&1 | tee clean_log.txt
make -i all  | tee build_log.txt

