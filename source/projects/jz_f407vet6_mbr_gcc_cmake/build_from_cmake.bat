echo off
cls

:: call clean_temp.bat

call generate_gnu_make.bat
cmake --build build/ -- VERBOSE=1

