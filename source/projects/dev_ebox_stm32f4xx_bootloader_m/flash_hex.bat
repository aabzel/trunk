echo off
cls

set project_name=dev_ebox_stm32f4xx_bootloader_m
set project_dir=%cd%
echo project_dir=%project_dir%
set artefact_hex=%project_dir%\build\%project_name%.hex
echo artefact_hex=%artefact_hex%

set FlashTool=ST-LINK_CLI.exe
rem set Device= ID=0x463 SN=066CFF323535474B43013113 
set Device= 
set options= -c %Device% SWD freq=4000 HOTPLUG  LPM -P %artefact_hex% -V "after_programming" -Log -TVolt
call %FlashTool% %options%
rem Reset System
call %FlashTool% -Rst
