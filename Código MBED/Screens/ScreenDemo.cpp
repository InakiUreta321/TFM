#include "ScreenDemo.h"
#include "Botones.h"
#include "ScreenState.h"
#include "ScreenMain.h"
#include "stm32746g_discovery_lcd.h"
#include "TouchUtils.h"

// Externas necesarias
extern RectButton spanishButton;
extern RectButton englishButton;
extern RectButton backButton;

extern ScreenState currentScreen;

void drawDemoScreen() {
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(0, LINE(3), (uint8_t *)"Selecciona idioma", CENTER_MODE);
    drawRectButton(spanishButton);
    drawRectButton(englishButton);
    drawRectButton(backButton);
}

void handleDemoScreenTouch(uint16_t x, uint16_t y) {
    if (isTouchInside(backButton, x, y)) {
        currentScreen = SCREEN_MAIN;
        drawMainScreen();
    } else if (isTouchInside(englishButton, x, y)) {
        // Aquí va la lógica para inglés
    } else if (isTouchInside(spanishButton, x, y)) {
                // Aquí va la lógica para español
    }
}
