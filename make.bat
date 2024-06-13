@echo off

@REM :: Check if a build directory already exists
@REM if exist "build" (
@REM   echo Build directory "build" already exists.
@REM ) else (
@REM   echo Creating build directory...
@REM   mkdir build
@REM )

@REM cmake -G "Ninja" -S . -B build

cmake --build build

echo Build complete

echo Attempting to override High DPI Settings...

set APP_NAME=main.exe

set DPI_SCALING_MODE=2

:: Specify the Registry key path for the application
set REG_PATH=HKCU\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers

:: Create a Registry entry to override High DPI scaling
reg add "%REG_PATH%" /v "C:\Users\Joel\Desktop\Programming\SnLTool\main.exe" /t REG_SZ /d "~ HIGHDPIAWARE %DPI_SCALING_MODE%" /f

:: Notify the user that the operation is complete
echo DPI scaling settings for %APP_NAME% have been updated.

pause