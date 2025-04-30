echo off
cls

set GDBServerPath=openocd.exe
set options=-s mik32-uploader/penocd-scripts
set options=%options% -f start-link.cfg
set options=%options% -f mik32.cfg
set options=%options% -c "init;halt"
call %GDBServerPath% %options%
