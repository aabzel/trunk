::cls 

echo off
set arg1=%1
set arg1=%arg1% -time-statistics   
set arg1=%arg1% -aux-directory=build    
::set arg1=%arg1% -quiet
pdflatex  %arg1%  


:: https://waterprogramming.wordpress.com/2018/08/26/converting-latex-to-ms-word-docx-almost-perfectly/