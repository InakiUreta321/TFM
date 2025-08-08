#include "ScreenMain.h"
#include "Botones.h"  
#include "stm32746g_discovery_lcd.h"       
#include "string.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "TouchUtils.h"
#include "ScreenState.h"
#include "ScreenComponent.h"

// Necesitarás estas variables extern si están en main.cpp:
extern char confirmedValue[32];
extern int selectedButton;

void drawMainScreen() {
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);

    // Dibuja los tres botones circulares principales
    drawRectButton(motoresButton);
    drawRectButton(fanButton);
    drawRectButton(demoButton);
}

void handleMainScreenTouch(uint16_t x, uint16_t y) {
    if (isTouchInside(motoresButton, x, y)) {
        currentScreen = SCREEN_COMPONENT;
        drawComponentScreen();
    }
    else if (isTouchInside(fanButton, x, y)) {
        currentScreen = SCREEN_FAN;
        BSP_LCD_Clear(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(0, LINE(3), (uint8_t *)"Ventilador Encendido", CENTER_MODE);
        drawRectButton(backButton);
    }
    else if (isTouchInside(demoButton, x, y)) {
        currentScreen = SCREEN_DEMO;
        BSP_LCD_Clear(LCD_COLOR_WHITE);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(0, LINE(3), (uint8_t *)"Selecciona idioma", CENTER_MODE);
        drawRectButton(spanishButton);
        drawRectButton(englishButton);
        drawRectButton(backButton);
    }
}