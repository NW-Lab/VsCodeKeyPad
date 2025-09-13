#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include "BleKeyboard.h"
#include "keypad_config.h"

class KeyboardManager {
private:
    BleKeyboard bleKeyboard;
    KeyboardMode currentMode;
    bool bleConnected;
    
public:
    KeyboardManager();
    void init();
    void setMode(KeyboardMode mode);
    KeyboardMode getMode();
    bool isBleConnected();
    void sendKey(uint8_t keycode, uint8_t modifier = 0);
    void sendCopilotAccept();      // Tab
    void sendCopilotAcceptWord();  // Ctrl + Right Arrow
    void sendCopilotReject();      // Esc
    void sendVSCodeCommand(const char* command);
};

#endif