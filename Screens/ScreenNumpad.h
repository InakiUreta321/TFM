#ifndef SCREEN_NUMPAD_H
#define SCREEN_NUMPAD_H

#include <cstdint>
#include "ScreenState.h"

void drawNumpadScreen();
void handleNumpadTouch(uint16_t x, uint16_t y);

extern char inputBuffer[10];
extern int inputLength;
extern char confirmedValue[16];
extern int selectedButton;
extern ScreenState currentScreen;
extern ScreenState previousScreen;

#endif // SCREEN_NUMPAD_H
