/*
 * VS Code KeyPad for Lilygo H621 - Arduino IDE Version
 * 
 * A touchscreen keypad designed specifically for VS Code with GitHub Copilot support.
 * This is a single-file version compatible with Arduino IDE.
 * 
 * Hardware: Lilygo H621 (ESP32 + 2.4" TFT Touch Display)
 * 
 * Required Libraries (install via Arduino Library Manager):
 * - TFT_eSPI by Bodmer
 * - ESP32-BLE-Keyboard by T-vK
 * 
 * Setup Instructions:
 * 1. Install ESP32 board package in Arduino IDE
 * 2. Install required libraries
 * 3. Copy User_Setup.h to TFT_eSPI library folder (or configure in TFT_eSPI/User_Setup_Select.h)
 * 4. Select "ESP32 Dev Module" as board
 * 5. Upload this sketch
 * 
 * Author: NW-Lab
 * Version: 1.0.0
 */

#include <TFT_eSPI.h>
#include "BleKeyboard.h"

// Display configuration
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

// Keyboard modes
enum KeyboardMode {
    MODE_USB,
    MODE_BLUETOOTH
};

// Virtual key structure
struct VirtualKey {
    int x, y, w, h;
    const char* label;
    uint8_t keycode;
    uint8_t modifier;
    bool isCopilotKey;
    bool isPressed;
};

// Global objects
TFT_eSPI tft = TFT_eSPI();
BleKeyboard bleKeyboard("VS Code KeyPad", "NW-Lab", 100);

// Key definitions
VirtualKey keys[12];
int numKeys = 12;

// Touch variables
int lastTouchedKey = -1;
unsigned long lastTouchTime = 0;
const unsigned long TOUCH_DEBOUNCE = 200;

void setup() {
    Serial.begin(115200);
    Serial.println("VS Code KeyPad Starting...");
    
    // Initialize display
    tft.init();
    tft.setRotation(0); // Portrait mode
    tft.fillScreen(COLOR_BACKGROUND);
    
    // Setup touch calibration
    uint16_t calData[5] = { 275, 3620, 264, 3532, 1 };
    tft.setTouch(calData);
    
    // Initialize Bluetooth keyboard
    bleKeyboard.begin();
    
    // Setup virtual keys
    setupKeys();
    
    // Draw interface
    drawInterface();
    drawHeader("BLE", bleKeyboard.isConnected());
    
    Serial.println("VS Code KeyPad Ready!");
    Serial.println("Waiting for Bluetooth connection...");
}

void loop() {
    static unsigned long lastUpdate = 0;
    unsigned long currentTime = millis();
    
    // Update display header periodically
    if (currentTime - lastUpdate > 1000) {
        drawHeader("BLE", bleKeyboard.isConnected());
        lastUpdate = currentTime;
    }
    
    // Handle touch input
    handleTouch();
    
    delay(10);
}

void setupKeys() {
    // Calculate key dimensions
    int keyWidth = (SCREEN_WIDTH - (KEY_MARGIN * 3)) / 2;
    
    // Row 1: GitHub Copilot keys
    keys[0] = {KEY_MARGIN, HEADER_HEIGHT + KEY_MARGIN, keyWidth, KEY_HEIGHT, 
               "Accept", 0x09, 0, true, false}; // Tab
    keys[1] = {KEY_MARGIN * 2 + keyWidth, HEADER_HEIGHT + KEY_MARGIN, keyWidth, KEY_HEIGHT, 
               "Accept Word", 0xD7, KEY_LEFT_CTRL, true, false}; // Ctrl+Right
    
    // Row 2: More Copilot controls
    keys[2] = {KEY_MARGIN, HEADER_HEIGHT + KEY_MARGIN * 2 + KEY_HEIGHT, keyWidth, KEY_HEIGHT, 
               "Reject", 0x1B, 0, true, false}; // Esc
    keys[3] = {KEY_MARGIN * 2 + keyWidth, HEADER_HEIGHT + KEY_MARGIN * 2 + KEY_HEIGHT, keyWidth, KEY_HEIGHT, 
               "Show Copilot", 0x09, KEY_LEFT_CTRL, true, false}; // Ctrl+Tab
    
    // Row 3: VS Code shortcuts
    keys[4] = {KEY_MARGIN, HEADER_HEIGHT + KEY_MARGIN * 3 + KEY_HEIGHT * 2, keyWidth, KEY_HEIGHT, 
               "Quick Open", 'p', KEY_LEFT_CTRL, false, false};
    keys[5] = {KEY_MARGIN * 2 + keyWidth, HEADER_HEIGHT + KEY_MARGIN * 3 + KEY_HEIGHT * 2, keyWidth, KEY_HEIGHT, 
               "Command", 'p', KEY_LEFT_SHIFT | KEY_LEFT_CTRL, false, false};
    
    // Row 4: More shortcuts
    keys[6] = {KEY_MARGIN, HEADER_HEIGHT + KEY_MARGIN * 4 + KEY_HEIGHT * 3, keyWidth, KEY_HEIGHT, 
               "Save All", 's', KEY_LEFT_CTRL | KEY_LEFT_SHIFT, false, false};
    keys[7] = {KEY_MARGIN * 2 + keyWidth, HEADER_HEIGHT + KEY_MARGIN * 4 + KEY_HEIGHT * 3, keyWidth, KEY_HEIGHT, 
               "Format", 'f', KEY_LEFT_SHIFT | KEY_LEFT_ALT, false, false};
    
    // Row 5: Debug & Terminal
    keys[8] = {KEY_MARGIN, HEADER_HEIGHT + KEY_MARGIN * 5 + KEY_HEIGHT * 4, keyWidth, KEY_HEIGHT, 
               "Debug", 0xC6, 0, false, false}; // F5
    keys[9] = {KEY_MARGIN * 2 + keyWidth, HEADER_HEIGHT + KEY_MARGIN * 5 + KEY_HEIGHT * 4, keyWidth, KEY_HEIGHT, 
               "Terminal", '`', KEY_LEFT_CTRL, false, false};
    
    // Row 6: Settings & Mode switch
    keys[10] = {KEY_MARGIN, HEADER_HEIGHT + KEY_MARGIN * 6 + KEY_HEIGHT * 5, keyWidth, KEY_HEIGHT, 
                "Settings", ',', KEY_LEFT_CTRL, false, false};
    keys[11] = {KEY_MARGIN * 2 + keyWidth, HEADER_HEIGHT + KEY_MARGIN * 6 + KEY_HEIGHT * 5, keyWidth, KEY_HEIGHT, 
                "Mode Switch", 0, 0, false, false};
}

void drawInterface() {
    tft.fillScreen(COLOR_BACKGROUND);
    
    // Draw all keys
    for (int i = 0; i < numKeys; i++) {
        drawKey(i, false);
    }
}

void drawKey(int keyIndex, bool pressed) {
    if (keyIndex < 0 || keyIndex >= numKeys) return;
    
    VirtualKey& key = keys[keyIndex];
    
    // Choose colors based on key type and state
    uint16_t bgColor;
    if (pressed) {
        bgColor = COLOR_KEY_PRESSED;
    } else if (key.isCopilotKey) {
        bgColor = COLOR_COPILOT;
    } else {
        bgColor = COLOR_KEY_BG;
    }
    
    // Draw key background
    tft.fillRoundRect(key.x, key.y, key.w, key.h, 5, bgColor);
    tft.drawRoundRect(key.x, key.y, key.w, key.h, 5, COLOR_TEXT);
    
    // Draw key label
    tft.setTextColor(COLOR_TEXT);
    tft.setTextDatum(MC_DATUM); // Middle center
    
    // Use smaller font for longer labels
    if (strlen(key.label) > 8) {
        tft.setTextSize(1);
    } else {
        tft.setTextSize(2);
    }
    
    tft.drawString(key.label, key.x + key.w / 2, key.y + key.h / 2);
    
    key.isPressed = pressed;
}

void drawHeader(const char* mode, bool bleConnected) {
    // Clear header area
    tft.fillRect(0, 0, SCREEN_WIDTH, HEADER_HEIGHT, COLOR_HEADER);
    
    // Draw title and status
    tft.setTextColor(COLOR_TEXT);
    tft.setTextSize(2);
    tft.setTextDatum(TL_DATUM);
    tft.drawString("VS Code Pad", 5, 5);
    
    // Draw mode and connection status
    tft.setTextSize(1);
    tft.setTextDatum(TR_DATUM);
    String status = String(mode);
    if (strcmp(mode, "BLE") == 0) {
        status += bleConnected ? " Connected" : " Pairing...";
    }
    tft.drawString(status, SCREEN_WIDTH - 5, 5);
}

void handleTouch() {
    uint16_t touchX, touchY;
    
    if (tft.getTouch(&touchX, &touchY)) {
        unsigned long currentTime = millis();
        
        // Debounce touch input
        if (currentTime - lastTouchTime < TOUCH_DEBOUNCE) {
            return;
        }
        
        // Find which key was touched
        int touchedKey = getTouchedKey(touchX, touchY);
        
        if (touchedKey >= 0 && touchedKey != lastTouchedKey) {
            Serial.printf("Key %d touched: %s\n", touchedKey, keys[touchedKey].label);
            
            // Visual feedback
            drawKey(touchedKey, true);
            
            // Handle key press
            handleKeyPress(touchedKey);
            
            // Reset visual feedback after delay
            delay(100);
            drawKey(touchedKey, false);
            
            lastTouchedKey = touchedKey;
            lastTouchTime = currentTime;
        }
    } else {
        lastTouchedKey = -1;
    }
}

int getTouchedKey(int touchX, int touchY) {
    for (int i = 0; i < numKeys; i++) {
        VirtualKey& key = keys[i];
        if (touchX >= key.x && touchX <= key.x + key.w &&
            touchY >= key.y && touchY <= key.y + key.h) {
            return i;
        }
    }
    return -1; // No key touched
}

void handleKeyPress(int keyIndex) {
    if (keyIndex < 0 || keyIndex >= numKeys) return;
    
    VirtualKey& key = keys[keyIndex];
    
    // Handle mode switch key specially
    if (strcmp(key.label, "Mode Switch") == 0) {
        // For now, just show a message
        Serial.println("Mode switch pressed (feature coming soon)");
        return;
    }
    
    // Send key only if Bluetooth is connected
    if (!bleKeyboard.isConnected()) {
        Serial.println("Bluetooth not connected!");
        return;
    }
    
    Serial.printf("Sending key: %s\n", key.label);
    
    // Handle GitHub Copilot keys
    if (key.isCopilotKey) {
        if (strcmp(key.label, "Accept") == 0) {
            bleKeyboard.write(0x09); // Tab
        } else if (strcmp(key.label, "Accept Word") == 0) {
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.press(KEY_RIGHT_ARROW);
            delay(50);
            bleKeyboard.releaseAll();
        } else if (strcmp(key.label, "Reject") == 0) {
            bleKeyboard.write(0x1B); // Esc
        } else if (strcmp(key.label, "Show Copilot") == 0) {
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.write(0x09); // Ctrl+Tab
            bleKeyboard.releaseAll();
        }
    } else {
        // Handle regular keys
        if (key.modifier != 0) {
            bleKeyboard.press(key.modifier);
            bleKeyboard.press(key.keycode);
            delay(50);
            bleKeyboard.releaseAll();
        } else {
            bleKeyboard.write(key.keycode);
        }
    }
}