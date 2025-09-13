/*
 * VS Code KeyPad for Lilygo H621
 * 
 * A touchscreen keypad designed specifically for VS Code with GitHub Copilot support.
 * Features virtual keys for common VS Code shortcuts and Copilot commands.
 * 
 * Hardware: Lilygo H621 (ESP32 + 2.4" TFT Touch Display)
 * 
 * Author: NW-Lab
 * Version: 1.0.0
 */

#include <Arduino.h>
#include <SPI.h>
#include "display_manager.h"
#include "keyboard_manager.h"
#include "keypad_config.h"

// Global objects
DisplayManager display;
KeyboardManager keyboard;

// Touch variables
int lastTouchedKey = -1;
unsigned long lastTouchTime = 0;
const unsigned long TOUCH_DEBOUNCE = 200; // 200ms debounce

// Mode switching
bool modeSwitchPressed = false;
unsigned long modeSwitchTime = 0;

void setup() {
    Serial.begin(115200);
    Serial.println("VS Code KeyPad Starting...");
    
    // Initialize display
    display.init();
    Serial.println("Display initialized");
    
    // Initialize keyboard
    keyboard.init();
    Serial.println("Keyboard initialized");
    
    // Draw initial interface
    const char* modeStr = (keyboard.getMode() == MODE_USB) ? "USB" : "BLE";
    display.drawHeader(modeStr, keyboard.isBleConnected());
    
    Serial.println("VS Code KeyPad Ready!");
    Serial.println("Waiting for Bluetooth connection...");
}

void loop() {
    static unsigned long lastUpdate = 0;
    unsigned long currentTime = millis();
    
    // Update display header periodically
    if (currentTime - lastUpdate > 1000) {
        const char* modeStr = (keyboard.getMode() == MODE_USB) ? "USB" : "BLE";
        display.drawHeader(modeStr, keyboard.isBleConnected());
        lastUpdate = currentTime;
    }
    
    // Handle touch input
    handleTouch();
    
    // Handle mode switching
    handleModeSwitch();
    
    delay(10); // Small delay to prevent overwhelming the system
}

void handleTouch() {
    // Check if touch is available (this would need to be implemented based on your specific touch controller)
    // For now, we'll use a placeholder implementation
    
    uint16_t touchX, touchY;
    if (getTouchCoordinates(&touchX, &touchY)) {
        unsigned long currentTime = millis();
        
        // Debounce touch input
        if (currentTime - lastTouchTime < TOUCH_DEBOUNCE) {
            return;
        }
        
        // Find which key was touched
        int touchedKey = display.getTouchedKey(touchX, touchY);
        
        if (touchedKey >= 0 && touchedKey != lastTouchedKey) {
            Serial.printf("Key %d touched\n", touchedKey);
            
            // Visual feedback
            display.updateKeyState(touchedKey, true);
            
            // Handle key press
            handleKeyPress(touchedKey);
            
            // Reset visual feedback after delay
            delay(100);
            display.updateKeyState(touchedKey, false);
            
            lastTouchedKey = touchedKey;
            lastTouchTime = currentTime;
        }
    } else {
        lastTouchedKey = -1;
    }
}

void handleKeyPress(int keyIndex) {
    VirtualKey* key = display.getKey(keyIndex);
    if (!key) return;
    
    Serial.printf("Executing key: %s\n", key->label);
    
    // Handle mode switch key specially
    if (strcmp(key->label, "Mode Switch") == 0) {
        KeyboardMode currentMode = keyboard.getMode();
        KeyboardMode newMode = (currentMode == MODE_USB) ? MODE_BLUETOOTH : MODE_USB;
        keyboard.setMode(newMode);
        
        const char* modeStr = (newMode == MODE_USB) ? "USB" : "BLE";
        display.drawHeader(modeStr, keyboard.isBleConnected());
        
        Serial.printf("Switched to %s mode\n", modeStr);
        return;
    }
    
    // Handle GitHub Copilot keys
    if (key->isCopilotKey) {
        if (strcmp(key->label, "Accept") == 0) {
            keyboard.sendCopilotAccept();
        } else if (strcmp(key->label, "Accept Word") == 0) {
            keyboard.sendCopilotAcceptWord();
        } else if (strcmp(key->label, "Reject") == 0) {
            keyboard.sendCopilotReject();
        } else if (strcmp(key->label, "Show Copilot") == 0) {
            keyboard.sendKey(KEY_TAB, KEY_CTRL);
        }
    } else {
        // Handle regular keys
        keyboard.sendKey(key->keycode, key->modifier);
    }
}

void handleModeSwitch() {
    // This could be used for additional mode switching logic if needed
    // For example, holding a key combination to switch modes
}

bool getTouchCoordinates(uint16_t* x, uint16_t* y) {
    // Use TFT_eSPI touch functionality
    // This should work with most TFT_eSPI compatible touch controllers
    
    static TFT_eSPI tft; // Static instance for touch
    static bool touchInitialized = false;
    
    if (!touchInitialized) {
        // Initialize touch if not done already
        uint16_t calData[5] = { 275, 3620, 264, 3532, 1 }; // Default calibration data
        tft.setTouch(calData);
        touchInitialized = true;
    }
    
    // Check for touch
    if (tft.getTouch(x, y)) {
        // Touch detected - coordinates are already calibrated by TFT_eSPI
        Serial.printf("Touch detected at: %d, %d\n", *x, *y);
        return true;
    }
    
    return false; // No touch detected
}