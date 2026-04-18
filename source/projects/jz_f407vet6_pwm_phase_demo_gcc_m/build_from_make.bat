echo off
cls

call clean_temp.bat

del /S /Q *.gv
del /S /Q *.svg

make clean 2>&1 | tee clean_log.txt
make all -j8 | tee build_log.txt

