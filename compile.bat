set gcc="F:\ProgramData\MinGW\bin\" &::replace with install location of gcc
set in="F:\CodeStuff\chess\chess.c"
set out="F:\CodeStuff\chess\clickme.exe"
@echo off
set num=1
:start
cls
echo try number %num%
echo.
cd /d %gcc%
call gcc.exe -Wall %in% -o %out%

pause
set /A num=%num%+1
goto start
