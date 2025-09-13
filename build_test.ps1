# Build test script for VS Code KeyPad (PowerShell)

Write-Host "=== VS Code KeyPad Build Test ===" -ForegroundColor Cyan
Write-Host ""

# Check if PlatformIO is available
if (Get-Command pio -ErrorAction SilentlyContinue) {
    Write-Host "✓ PlatformIO found" -ForegroundColor Green
    
    # Try to build the project
    Write-Host "Building project..." -ForegroundColor Yellow
    $result = & pio run
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "✓ Build successful!" -ForegroundColor Green
        Write-Host "Ready to upload to Lilygo H621" -ForegroundColor Green
    } else {
        Write-Host "✗ Build failed" -ForegroundColor Red
        Write-Host "Check library dependencies and configuration" -ForegroundColor Red
        exit 1
    }
} else {
    Write-Host "✗ PlatformIO not found" -ForegroundColor Red
    Write-Host "Please install PlatformIO:" -ForegroundColor Yellow
    Write-Host "  pip install platformio" -ForegroundColor White
    Write-Host ""
    Write-Host "Or use Arduino IDE with the files in src/ directory" -ForegroundColor Yellow
}

Write-Host ""
Write-Host "=== Hardware Setup ===" -ForegroundColor Cyan
Write-Host "1. Connect Lilygo H621 via USB"
Write-Host "2. Select correct COM port"
Write-Host "3. Upload with: pio run --target upload"
Write-Host "4. Monitor serial: pio device monitor"
Write-Host ""
Write-Host "=== Pairing Instructions ===" -ForegroundColor Cyan
Write-Host "1. Power on the device"
Write-Host "2. Open Bluetooth settings on your computer"
Write-Host "3. Look for 'VS Code KeyPad'"
Write-Host "4. Pair the device"
Write-Host "5. Open VS Code and start coding with Copilot!"