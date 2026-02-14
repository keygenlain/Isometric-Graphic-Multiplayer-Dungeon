@echo off
REM Isometric MUD Portable Launcher for Windows
REM This script runs the game from the current directory (DVD/USB)

echo ==========================================
echo Isometric MUD - Portable Edition
echo ==========================================
echo.

REM Get the directory where this script is located
set GAME_DIR=%~dp0

REM Set paths relative to script location
set BIN_DIR=%GAME_DIR%bin
set DATA_DIR=%GAME_DIR%data
set CONFIG_DIR=%GAME_DIR%config
set SAVES_DIR=%GAME_DIR%saves

REM Create user-writable directories if they don't exist
if not exist "%CONFIG_DIR%" mkdir "%CONFIG_DIR%"
if not exist "%SAVES_DIR%" mkdir "%SAVES_DIR%"

REM Set environment variables for portable mode
set ISOMETRIC_MUD_PORTABLE=1
set ISOMETRIC_MUD_ROOT=%GAME_DIR%
set ISOMETRIC_MUD_DATA=%DATA_DIR%
set ISOMETRIC_MUD_CONFIG=%CONFIG_DIR%
set ISOMETRIC_MUD_SAVES=%SAVES_DIR%

REM Add bin directory to PATH for libraries
set PATH=%BIN_DIR%;%PATH%

echo Game directory: %GAME_DIR%
echo.
echo Starting Launcher...
echo.

REM Check if running from read-only media (DVD)
echo. > "%GAME_DIR%test_write.tmp" 2>nul
if errorlevel 1 (
    echo WARNING: Running from read-only media.
    echo Save files will be stored in your user profile.
    echo.
    REM Fallback to user profile for saves
    set CONFIG_DIR=%USERPROFILE%\IsometricMUD\config
    set SAVES_DIR=%USERPROFILE%\IsometricMUD\saves
    if not exist "%CONFIG_DIR%" mkdir "%CONFIG_DIR%"
    if not exist "%SAVES_DIR%" mkdir "%SAVES_DIR%"
) else (
    del "%GAME_DIR%test_write.tmp" 2>nul
)

REM Launch the game launcher
if exist "%BIN_DIR%\Launcher.exe" (
    cd /d "%BIN_DIR%"
    REM Using 'start' without /wait for detached execution - launcher runs independently
    start "" "Launcher.exe"
) else (
    echo ERROR: Launcher.exe not found in %BIN_DIR%
    echo Please ensure the game is properly installed.
    pause
    exit /b 1
)

REM Optional: Wait for launcher to close
REM timeout /t 2 /nobreak >nul

echo Launcher started successfully!
echo.
pause
