echo off
cls

call clean_temp.bat

make clean | tee clean_log.txt

make all -j8 | tee build_log.txt
