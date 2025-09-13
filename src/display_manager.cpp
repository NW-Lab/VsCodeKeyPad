#include "display_manager.h"

DisplayManager::DisplayManager() : tft(), numKeys(0) {
}

void DisplayManager::init() {
    tft.init();
    tft.setRotation(0); // Portrait mode
    tft.fillScreen(COLOR_BACKGROUND);
    setupKeys();
    drawInterface();
}

void DisplayManager::setupKeys() {
    numKeys = 12;
    
    // Calculate key dimensions
    int keyWidth = (SCREEN_WIDTH - (KEY_MARGIN * 3)) / 2;
    
    // Row 1: GitHub Copilot keys
    keys[0] = {KEY_MARGIN, HEADER_HEIGHT + KEY_MARGIN, keyWidth, KEY_HEIGHT, 
               "Accept", KEY_TAB, 0, true, false};
    keys[1] = {KEY_MARGIN * 2 + keyWidth, HEADER_HEIGHT + KEY_MARGIN, keyWidth, KEY_HEIGHT, 
               "Accept Word", KEY_RIGHT_ARROW, KEY_CTRL, true, false};
    
    // Row 2: More Copilot controls
    keys[2] = {KEY_MARGIN, HEADER_HEIGHT + KEY_MARGIN * 2 + KEY_HEIGHT, keyWidth, KEY_HEIGHT, 
               "Reject", KEY_ESC, 0, true, false};
    keys[3] = {KEY_MARGIN * 2 + keyWidth, HEADER_HEIGHT + KEY_MARGIN * 2 + KEY_HEIGHT, keyWidth, KEY_HEIGHT, 
               "Show Copilot", KEY_TAB, KEY_CTRL, true, false};
    
    // Row 3: VS Code shortcuts  
    keys[4] = {KEY_MARGIN, HEADER_HEIGHT + KEY_MARGIN * 3 + KEY_HEIGHT * 2, keyWidth, KEY_HEIGHT, 
               "Quick Open", 'p', KEY_CTRL, false, false};
    keys[5] = {KEY_MARGIN * 2 + keyWidth, HEADER_HEIGHT + KEY_MARGIN * 3 + KEY_HEIGHT * 2, keyWidth, KEY_HEIGHT, 
               "Command", 'p', KEY_SHIFT | KEY_CTRL, false, false}; // Ctrl+Shift+P
    
    // Row 4: More shortcuts
    keys[6] = {KEY_MARGIN, HEADER_HEIGHT + KEY_MARGIN * 4 + KEY_HEIGHT * 3, keyWidth, KEY_HEIGHT, 
               "Save All", 's', KEY_CTRL | KEY_SHIFT, false, false};
    keys[7] = {KEY_MARGIN * 2 + keyWidth, HEADER_HEIGHT + KEY_MARGIN * 4 + KEY_HEIGHT * 3, keyWidth, KEY_HEIGHT, 
               "Format", 'f', KEY_SHIFT | KEY_ALT, false, false}; // Shift+Alt+F
    
    // Row 5: Debug & Terminal
    keys[8] = {KEY_MARGIN, HEADER_HEIGHT + KEY_MARGIN * 5 + KEY_HEIGHT * 4, keyWidth, KEY_HEIGHT, 
               "Debug", KEY_F5, 0, false, false};
    keys[9] = {KEY_MARGIN * 2 + keyWidth, HEADER_HEIGHT + KEY_MARGIN * 5 + KEY_HEIGHT * 4, keyWidth, KEY_HEIGHT, 
               "Terminal", '`', KEY_CTRL, false, false};
    
    // Row 6: Settings & Mode switch
    keys[10] = {KEY_MARGIN, HEADER_HEIGHT + KEY_MARGIN * 6 + KEY_HEIGHT * 5, keyWidth, KEY_HEIGHT, 
                "Settings", ',', KEY_CTRL, false, false};
    keys[11] = {KEY_MARGIN * 2 + keyWidth, HEADER_HEIGHT + KEY_MARGIN * 6 + KEY_HEIGHT * 5, keyWidth, KEY_HEIGHT, 
                "Mode Switch", 0, 0, false, false};
}

void DisplayManager::drawInterface() {
    tft.fillScreen(COLOR_BACKGROUND);
    
    // Draw all keys
    for (int i = 0; i < numKeys; i++) {
        drawKey(i, false);
    }
}

void DisplayManager::drawKey(int keyIndex, bool pressed) {
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

void DisplayManager::drawHeader(const char* mode, bool bleConnected) {
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

int DisplayManager::getTouchedKey(int touchX, int touchY) {
    for (int i = 0; i < numKeys; i++) {
        VirtualKey& key = keys[i];
        if (touchX >= key.x && touchX <= key.x + key.w &&
            touchY >= key.y && touchY <= key.y + key.h) {
            return i;
        }
    }
    return -1; // No key touched
}

void DisplayManager::updateKeyState(int keyIndex, bool pressed) {
    if (keyIndex >= 0 && keyIndex < numKeys) {
        drawKey(keyIndex, pressed);
    }
}

VirtualKey* DisplayManager::getKey(int index) {
    if (index >= 0 && index < numKeys) {
        return &keys[index];
    }
    return nullptr;
}

int DisplayManager::getNumKeys() {
    return numKeys;
}