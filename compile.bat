::planned custom locations?
::pff honestly batch files are relics already


set gcc="F:\ProgramData\MinGW\bin\" &::replace with install location of gcc
set in="L:\chess\chess.c"
set out="L:\chess\clickme.exe"
@echo off
set num=1
:start
cls
echo try number %num%
echo.
cd /d %gcc%
call gcc.exe -Wall %in% -o "L:\chess\clickme.exe"
::-o %out%

pause
set /A num=%num%+1
goto start
