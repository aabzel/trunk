echo off
cls

::C:\cygwin64\bin\make.exe  clean 2>&1 | tee clean_log.txt
::C:\cygwin64\bin\make.exe  all | tee build_log.txt

::C:\xpack-windows-build-tools-4.4.1-3\bin\make.exe  clean
::C:\xpack-windows-build-tools-4.4.1-3\bin\make.exe -j8 all

make  clean
make -j8 all
