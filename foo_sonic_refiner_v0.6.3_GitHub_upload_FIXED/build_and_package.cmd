@echo off
setlocal
cd /d "%~dp0"

powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0scripts\build-package.ps1" -Configuration Release

if errorlevel 1 (
    echo.
    echo Build or packaging failed.
    pause
    exit /b 1
)

echo.
echo Build and packaging completed.
pause
