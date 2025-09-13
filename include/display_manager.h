#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <TFT_eSPI.h>
#include "keypad_config.h"

class DisplayManager {
private:
    TFT_eSPI tft;
    VirtualKey keys[12];
    int numKeys;
    
public:
    DisplayManager();
    void init();
    void setupKeys();
    void drawInterface();
    void drawKey(int keyIndex, bool pressed = false);
    void drawHeader(const char* mode, bool bleConnected = false);
    int getTouchedKey(int touchX, int touchY);
    void updateKeyState(int keyIndex, bool pressed);
    VirtualKey* getKey(int index);
    int getNumKeys();
};

#endif