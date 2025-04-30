cls
@echo on
set PROJECT_DIR=%~dp0
echo PROJECT_DIR=%PROJECT_DIR%
cd %PROJECT_DIR%

rm main_generated.tex
:: clean.bat
echo makefile_path=%makefile_path%

make -i all
cd %PROJECT_DIR%


