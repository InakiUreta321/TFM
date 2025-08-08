// ScreenFan.cpp
#include "ScreenFan.h"
#include "ScreenMain.h"
#include "stm32746g_discovery_lcd.h"
#include "Botones.h"
#include "ScreenState.h"
#include "TouchUtils.h"


// Variables externas necesarias
extern RectButton backButton;
extern ScreenState currentScreen;

void drawFanScreen() {
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(0, LINE(3), (uint8_t *)"Ventilador Encendido", CENTER_MODE);
    drawRectButton(backButton);
}

void handleFanScreenTouch(uint16_t x, uint16_t y) {
    if (isTouchInside(backButton, x, y)) {
        currentScreen = SCREEN_MAIN;
        drawMainScreen();
    }
}
