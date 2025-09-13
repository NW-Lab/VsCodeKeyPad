#ifndef KEYPAD_CONFIG_H
#define KEYPAD_CONFIG_H

// Display settings
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
#define KEY_MARGIN 5
#define KEY_HEIGHT 50
#define HEADER_HEIGHT 40

// Colors (RGB565)
#define COLOR_BACKGROUND 0x0000    // Black
#define COLOR_KEY_BG 0x2945        // Dark blue
#define COLOR_KEY_PRESSED 0x07E0   // Green
#define COLOR_TEXT 0xFFFF          // White
#define COLOR_HEADER 0x001F        // Blue
#define COLOR_COPILOT 0xF800       // Red for Copilot keys

// Touch calibration (may need adjustment for your specific display)
#define TOUCH_MIN_X 200
#define TOUCH_MAX_X 3700
#define TOUCH_MIN_Y 300
#define TOUCH_MAX_Y 3800

// Keyboard modes
enum KeyboardMode {
    MODE_USB,
    MODE_BLUETOOTH
};

// Key definitions for GitHub Copilot and VS Code
struct VirtualKey {
    int x, y, w, h;
    const char* label;
    uint8_t keycode;
    uint8_t modifier;
    bool isCopilotKey;
    bool isPressed;
};

// Key codes (ASCII and special keys for ESP32-BLE-Keyboard)
#define KEY_TAB 0x09
#define KEY_ESC 0x1B
#define KEY_RIGHT_ARROW 0xD7    // Right Arrow key code
#define KEY_F1 0xC2
#define KEY_F2 0xC3
#define KEY_F5 0xC6
#define KEY_F12 0xCD

// Modifier keys
#define KEY_LEFT_CTRL 0x80
#define KEY_LEFT_SHIFT 0x81
#define KEY_LEFT_ALT 0x82
#define KEY_CTRL KEY_LEFT_CTRL
#define KEY_SHIFT KEY_LEFT_SHIFT  
#define KEY_ALT KEY_LEFT_ALT

#endif