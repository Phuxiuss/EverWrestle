@echo off
setlocal EnableDelayedExpansion

:: ==========================================================
reg add "HKCU\Console" /v QuickEdit /t REG_DWORD /d 0 /f >nul 2>&1
for /F "tokens=1,2 delims=#" %%a in ('"prompt #$H#$E# & echo on & for %%b in (1) do rem"') do (set "ESC=%%b")

set "ColGreen=%ESC%[92m"
set "ColRed=%ESC%[91m"
set "ColYellow=%ESC%[93m"
set "ColCyan=%ESC%[96m"
set "ColWhite=%ESC%[97m"
set "ColGrey=%ESC%[90m"
set "ColReset=%ESC%[0m"

:: ==========================================================
:: ENGINE PATH CONFIGURATION
set "CONFIG_FILE=%~dp0EnginePath.txt"
set "PROJECT_NAME=EverWrestle"

if exist "%CONFIG_FILE%" (
    set /p UE_ROOT=<"%CONFIG_FILE%"
) else (
    echo %ColCyan%==========================================================
    echo   FIRST TIME SETUP: ENGINE PATH REQUIRED
    echo ==========================================================%ColReset%
    echo %ColWhite% Please enter your Unreal Engine Root Folder.
    echo  Example: D:\Epic Games\UE_5.6
    echo.
    set /p "UE_ROOT=%ColYellow% Path: %ColReset%"
    set "UE_ROOT=!UE_ROOT:"=!"
    echo !UE_ROOT!>"%CONFIG_FILE%"
)

set "MANUAL_ENGINE_BUILD_BAT_FULLPATH=!UE_ROOT!\Engine\Build\BatchFiles\Build.bat"
set "ENGINE_EDITOR_EXE=!UE_ROOT!\Engine\Binaries\Win64\UnrealEditor.exe"

set "PLATFORM=Win64"
set "CONFIGURATION=Development"
set "TARGET_NAME=%PROJECT_NAME%Editor"
set "MAX_PARALLEL_ACTIONS=8"

set "LOG_GEN=project_gen_log.txt"
set "LOG_BUILD=build_log.txt"

echo.
echo %ColYellow%[SAFETY] Checking for running Unreal Editors...%ColReset%
tasklist /FI "IMAGENAME eq UnrealEditor.exe" 2>NUL | find /I /N "UnrealEditor.exe">NUL
if "%ERRORLEVEL%"=="0" (
    echo %ColRed%    Found running Editor. Killing process to prevent file locks...%ColReset%
    taskkill /F /IM "UnrealEditor.exe" >nul 2>&1
    timeout /t 2 >nul
    echo %ColGreen%    [OK] Editor closed.%ColReset%
) else (
    echo %ColGrey%    No running Editor found. Safe to proceed.%ColReset%
)

cls

:: ==========================================================
:: SMART CLEAN
echo %ColYellow%[?] Perform PROJECT CLEAN? (Binaries, Intermediate, .sln) %ColReset%
echo %ColGrey%    Note: This will not delete your compiled Plugins.%ColReset%
set /p "CHOICE=%ColWhite%    (y/n): %ColReset%"

if /i "%CHOICE%"=="y" (
    echo.
    echo %ColCyan%[PHASE 1] WIPING PROJECT DATA%ColReset%
    
    if exist "%~dp0Binaries" rd /s /q "%~dp0Binaries"
    if exist "%~dp0Intermediate" rd /s /q "%~dp0Intermediate"
    if exist "%~dp0DerivedDataCache" rd /s /q "%~dp0DerivedDataCache"

    for %%F in ("%~dp0*.sln" "%~dp0*.vcxproj" "%~dp0*.vcxproj.filters" "%~dp0*.vcxproj.user") do (
        if exist "%%F" del "%%F" 2>nul
    )
    echo %ColGreen% [OK] Project Clean finished.%ColReset%
    echo.
)

:: ==========================================================
:: EXECUTION

echo %ColCyan%[PHASE 2] GENERATING PROJECT FILES%ColReset%
set "t_start=%time%"
call "%MANUAL_ENGINE_BUILD_BAT_FULLPATH%" -projectfiles -project="%~dp0%PROJECT_NAME%.uproject" -game -rocket -log="%~dp0%LOG_GEN%"
if %errorlevel% neq 0 goto :FAIL
set "t_end=%time%" & call :CalcDuration
echo %ColGreen% [OK] (Took !DURATION!)%ColReset%
echo.

echo %ColCyan%[PHASE 3] COMPILING SOURCE CODE%ColReset%
set "t_start=%time%"

echo %ColGrey%    Starting Live Log Monitor...%ColReset%
echo [BUILD START] %DATE% %TIME% > "%~dp0%LOG_BUILD%"
start "UE Build Log - %PROJECT_NAME%" PowerShell -NoProfile -Command "Get-Content -Path '%~dp0%LOG_BUILD%' -Wait"

call "%MANUAL_ENGINE_BUILD_BAT_FULLPATH%" %TARGET_NAME% %PLATFORM% %CONFIGURATION% -Project="%~dp0%PROJECT_NAME%.uproject" -waitmutex -MaxParallelActions=%MAX_PARALLEL_ACTIONS% >> "%~dp0%LOG_BUILD%" 2>&1

if %errorlevel% gtr 1 (
    echo [BUILD FAILED] Code: %errorlevel% >> "%~dp0%LOG_BUILD%"
    goto :FAIL
) else (
    echo [BUILD SUCCESS] >> "%~dp0%LOG_BUILD%"
)

set "t_end=%time%" & call :CalcDuration
echo %ColGreen% [OK] (Took !DURATION!)%ColReset%

echo.
echo %ColGreen%==========================================================
echo BUILD SUCCESSFUL - RELAUNCHING PROJECT
echo ==========================================================%ColReset%

if exist "%ENGINE_EDITOR_EXE%" (
    echo %ColGrey% Launching Editor...%ColReset%
    start "" "%ENGINE_EDITOR_EXE%" "%~dp0%PROJECT_NAME%.uproject"
    timeout /t 3 >nul
) else (
    echo %ColYellow% [WARN] Editor EXE not found at:
    echo %ENGINE_EDITOR_EXE%
    echo %ColReset%
    pause
)
exit /b

:FAIL
echo.
echo %ColRed%==========================================================
echo   BUILD FAILED (Error Code: %errorlevel%)
echo   Check the external Log Window for details!
echo ==========================================================%ColReset%
pause
exit /b

:CalcDuration
set /a "h_s=1%t_start:~0,2%-100, m_s=1%t_start:~3,2%-100, s_s=1%t_start:~6,2%-100, cs_s=1%t_start:~9,2%-100"
set /a "h_e=1%t_end:~0,2%-100, m_e=1%t_end:~3,2%-100, s_e=1%t_end:~6,2%-100, cs_e=1%t_end:~9,2%-100"
set /a "start_cs=%h_s%*360000 + %m_s%*6000 + %s_s%*100 + %cs_s%"
set /a "end_cs=%h_e%*360000 + %m_e%*6000 + %s_e%*100 + %cs_e%"
if %end_cs% LSS %start_cs% set /a "end_cs+=24*360000"
set /a "dur_cs=%end_cs%-%start_cs%, dur_s=%dur_cs%/100, dur_m=%dur_s%/60, dur_s=%dur_s%%%60"
set "DURATION=!dur_m!m !dur_s!s"
exit /b