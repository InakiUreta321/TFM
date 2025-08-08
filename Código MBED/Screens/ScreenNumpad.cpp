#include "ScreenNumpad.h"
#include "stm32746g_discovery_lcd.h"
#include "TouchUtils.h"
#include "Botones.h"
#include "ScreenState.h"
#include "ScreenMotorControl.h"  // Para dibujar pantalla motor control al volver
#include <cstring>


// Variables externas definidas en main.cpp
extern RectButton numpadButtons[13];
extern RectButton okBtn, backBtn;
extern void drawMotorControlFor(ScreenState screen);


extern char inputBuffer[10];
extern int inputLength;
extern char confirmedValue[16];
extern ScreenState currentScreen;
extern ScreenState previousScreen;
extern int selectedButton;

// Dibuja la pantalla del numpad
void drawNumpadScreen() {
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_DrawRect(30, 20, 200, 30);
    BSP_LCD_DisplayStringAt(35, 25, (uint8_t*)inputBuffer, LEFT_MODE);
    for (int i = 0; i < 13; i++) {
        drawRectButton(numpadButtons[i]);
    }
    drawRectButton(okBtn);
    drawRectButton(backBtn);
}

// Maneja el toque en la pantalla numpad
void handleNumpadTouch(uint16_t x, uint16_t y) {
    for (int i = 0; i < 13; i++) {
        if (isTouchInside(numpadButtons[i], x, y)) {
            const char* label = numpadButtons[i].label;

            if (strcmp(label, "DEL") == 0) {
                inputLength = 0;
                inputBuffer[0] = '\0';
            } else if (inputLength < 9) {
                inputBuffer[inputLength++] = label[0];
                inputBuffer[inputLength] = '\0';
            }
            drawNumpadScreen();
            return;
        }
    }

    if (isTouchInside(okBtn, x, y)) {
        strcpy(confirmedValue, inputBuffer);
        currentScreen = previousScreen;
        drawMotorControlFor(currentScreen);
        return;
    }
    if (isTouchInside(backBtn, x, y)) {
        currentScreen = previousScreen;
        drawMotorControlFor(currentScreen);
        return;
    }
}
