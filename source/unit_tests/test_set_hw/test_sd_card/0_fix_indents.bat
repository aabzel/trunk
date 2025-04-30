@echo off
set style1="{IndentWidth: 4, SortIncludes: true, SortUsingDeclarations: true , SpaceBeforeParens: Always,UseTab: Never,PointerAlignment: Right, BreakBeforeBraces: Attach, TabWidth: 4,ColumnLimit: 120 }"
set format_tool="C:\Program Files\LLVM\bin\clang-format.exe"

find . -iname "*.[ch]" | xargs clang-format -i

%format_tool%  -verbose -i -style=%style1% *.h
%format_tool%  -verbose -i -style=%style1% *.c
%format_tool%  -verbose -i -style=%style1% *.cpp

