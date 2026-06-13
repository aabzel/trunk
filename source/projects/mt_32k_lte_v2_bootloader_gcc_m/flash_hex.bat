echo off
cls

set project_name=mt_32k_lte_v2_bootloader_gcc_m
set project_dir=%cd%
echo project_dir=%project_dir%
set artefact_hex=%project_dir%\build\%project_name%.hex
echo artefact_hex=%artefact_hex%

set FlashTool="C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe"
rem set Device= ID=0x463 SN=066CFF323535474B43013113 
set Device= 
set options= -c %Device% JTAG freq=4000 HOTPLUG  LPM 
set options=%options% -P %artefact_hex% 
set options=%options% -V "after_programming" 
set options=%options% -Log
set options=%options% -TVolt

call %FlashTool% %options%
rem Reset System
call %FlashTool% -Rst
