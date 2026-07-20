echo off
cls

call clean_temp.bat

make clean 2>&1 | tee clean_log.txt
make all -j8 2>&1 | tee build_log.txt

