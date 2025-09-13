#!/bin/bash
# Build test script for VS Code KeyPad

echo "=== VS Code KeyPad Build Test ==="

# Check if PlatformIO is available
if command -v pio &> /dev/null; then
    echo "✓ PlatformIO found"
    
    # Try to build the project
    echo "Building project..."
    if pio run; then
        echo "✓ Build successful!"
        echo "Ready to upload to Lilygo H621"
    else
        echo "✗ Build failed"
        echo "Check library dependencies and configuration"
        exit 1
    fi
else
    echo "✗ PlatformIO not found"
    echo "Please install PlatformIO:"
    echo "  pip install platformio"
    echo ""
    echo "Or use Arduino IDE with the files in src/ directory"
fi

echo ""
echo "=== Hardware Setup ==="
echo "1. Connect Lilygo H621 via USB"
echo "2. Select correct COM port"
echo "3. Upload with: pio run --target upload"
echo "4. Monitor serial: pio device monitor"
echo ""
echo "=== Pairing Instructions ==="
echo "1. Power on the device"
echo "2. Open Bluetooth settings on your computer"
echo "3. Look for 'VS Code KeyPad'"
echo "4. Pair the device"
echo "5. Open VS Code and start coding with Copilot!"