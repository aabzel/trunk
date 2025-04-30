echo off
cls

set project_name=start_mik32_v1_heartbeat_eeprom_m
set project_dir=%cd%
set workspace_dir=%project_dir%\..\..\..\
echo workspace_dir=%workspace_dir%

echo project_dir=%project_dir%
set artefact_hex=build\%project_name%.hex

