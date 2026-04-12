set SorterTool=C:\cygwin64\bin\sort.exe
set system_dir=%cd%
%SorterTool% "%system_dir%\system_facility_tokens.h" -u -o "%system_dir%\system_facility_tokens.h"
