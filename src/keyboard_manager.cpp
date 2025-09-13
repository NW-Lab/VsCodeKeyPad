#include "keyboard_manager.h"

KeyboardManager::KeyboardManager() : 
    bleKeyboard("VS Code KeyPad", "NW-Lab", 100),
    currentMode(MODE_BLUETOOTH), // Default to Bluetooth for easier pairing
    bleConnected(false) {
}

void KeyboardManager::init() {
    // Initialize Bluetooth keyboard
    bleKeyboard.begin();
    
    // Set default mode to Bluetooth
    setMode(MODE_BLUETOOTH);
}

void KeyboardManager::setMode(KeyboardMode mode) {
    currentMode = mode;
    
    if (mode == MODE_BLUETOOTH) {
        if (!bleKeyboard.isConnected()) {
            // Start advertising if not connected
            bleKeyboard.begin();
        }
    }
}

KeyboardMode KeyboardManager::getMode() {
    return currentMode;
}

bool KeyboardManager::isBleConnected() {
    bleConnected = bleKeyboard.isConnected();
    return bleConnected;
}

void KeyboardManager::sendKey(uint8_t keycode, uint8_t modifier) {
    if (currentMode == MODE_BLUETOOTH && bleKeyboard.isConnected()) {
        // Bluetooth keyboard
        if (modifier != 0) {
            // Handle modifier keys for BLE
            uint8_t modKeys = 0;
            if (modifier & KEY_CTRL) modKeys |= KEY_LEFT_CTRL;
            if (modifier & KEY_SHIFT) modKeys |= KEY_LEFT_SHIFT;
            if (modifier & KEY_ALT) modKeys |= KEY_LEFT_ALT;
            
            bleKeyboard.press(modKeys);
            bleKeyboard.press(keycode);
            delay(50);
            bleKeyboard.releaseAll();
        } else {
            bleKeyboard.write(keycode);
        }
    }
    // Note: USB mode removed for simplicity - focus on Bluetooth
}

void KeyboardManager::sendCopilotAccept() {
    // Send Tab key to accept GitHub Copilot suggestion
    sendKey(KEY_TAB, 0);
}

void KeyboardManager::sendCopilotAcceptWord() {
    // Send Ctrl + Right Arrow to accept word
    sendKey(KEY_RIGHT_ARROW, KEY_CTRL);
}

void KeyboardManager::sendCopilotReject() {
    // Send Escape to reject GitHub Copilot suggestion
    sendKey(KEY_ESC, 0);
}

void KeyboardManager::sendVSCodeCommand(const char* command) {
    // This could be extended to send specific VS Code commands
    // For now, we'll use the key mappings defined in the keys
}