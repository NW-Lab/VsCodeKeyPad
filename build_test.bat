@echo off
REM Build test script for VS Code KeyPad (Windows)

echo === VS Code KeyPad Build Test ===
echo.

REM Check if PlatformIO is available
where pio >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo ✓ PlatformIO found
    
    REM Try to build the project
    echo Building project...
    pio run
    if %ERRORLEVEL% EQU 0 (
        echo ✓ Build successful!
        echo Ready to upload to Lilygo H621
    ) else (
        echo ✗ Build failed
        echo Check library dependencies and configuration
        exit /b 1
    )
) else (
    echo ✗ PlatformIO not found
    echo Please install PlatformIO:
    echo   pip install platformio
    echo.
    echo Or use Arduino IDE with the files in src/ directory
)

echo.
echo === Hardware Setup ===
echo 1. Connect Lilygo H621 via USB
echo 2. Select correct COM port
echo 3. Upload with: pio run --target upload
echo 4. Monitor serial: pio device monitor
echo.
echo === Pairing Instructions ===
echo 1. Power on the device
echo 2. Open Bluetooth settings on your computer
echo 3. Look for 'VS Code KeyPad'
echo 4. Pair the device
echo 5. Open VS Code and start coding with Copilot!