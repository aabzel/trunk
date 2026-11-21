echo off
cls

call clean_temp.bat

make clean 2>&1 | tee clean_log.txt
make -j8 all 2>&1 | tee build_log.txt

