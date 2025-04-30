echo off
echo %0
set project_dir=%1
set workspace_dir=%project_dir%\..\..\..\
echo sing_firmware
echo ....

echo workspace_dir=%workspace_dir%
echo project_dir=%project_dir%


COPY /Y  %workspace_dir%auto_version_pattern.h %project_dir%\auto_version.h
set tool_path=%workspace_dir%tool\
echo tool_path=%tool_path% 
FOR /F "tokens=* delims=" %%a IN ('git branch') DO (
 set branch_var=%%a
)

FOR /F "tokens=*delims=" %%a IN ('git rev-parse --short HEAD') DO (
 set last_hash_var=%%a
)
rem echo branch_var=%branch_var% 
set branch_var=%branch_var:~2%
echo branch_var=%branch_var%
echo last_hash_var=%last_hash_var%

python %tool_path%replace_word_in_file.py %project_dir%\auto_version.h GIT_BRANCH_AUTO_REPLACE %branch_var%
python %tool_path%replace_word_in_file.py %project_dir%\auto_version.h GIT_LAST_COMMIT_HASH_AUTO_REPLACE %last_hash_var%
