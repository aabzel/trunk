echo off
cls

make clean 2>&1 | tee clean_log.txt
make  -j8 | tee build_log.txt

