@echo off
setlocal enabledelayedexpansion

set OUT=main.exe

g++ -Wall -Wextra -std=c++17 ./src/*.cpp -o %OUT%
if ERRORLEVEL 1 (
    pause
    exit /b 1
)

%OUT%
pause
