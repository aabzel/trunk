echo off
cls

set project_name=dev_ebox_stm32f4x_sonar_rec_gcc_m
set project_dir=%cd%
echo project_dir=%project_dir%

set ide_tool=C:\eclipse\eclipsec.exe
set workspace_dir=%project_dir%\..\..\
echo workspace_dir=%workspace_dir%

call %ide_tool% -nosplash -application org.eclipse.cdt.managedbuilder.core.headlessbuild -data %workspace_dir% -import %project_dir% -name UtestGcc -build %project_name% 2>&1 | tee build_log.txt

cd %project_dir%
echo project_dir=%project_dir%
dir %project_dir%\Release | grep -ri %project_name%
cat.exe %project_dir%\build_log.txt
