#include "Botones.h"
#include "stm32746g_discovery_lcd.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
// Definición de funciones

void drawRectButton(const RectButton& btn) {
    BSP_LCD_SetTextColor(btn.color);
    BSP_LCD_FillRect(btn.x, btn.y, btn.w, btn.h);

    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_SetBackColor(btn.color);

    BSP_LCD_DisplayStringAt(btn.x + 5, btn.y + btn.h / 4, (uint8_t*)btn.label, LEFT_MODE);
}



// Definición de variables

RectButton plusBtn = {30, 110, 60, 40, LCD_COLOR_GREEN, "+"};
RectButton minusBtn = {100, 110, 60, 40, LCD_COLOR_RED, "-"};
RectButton hashBtn = {170, 110, 60, 40, LCD_COLOR_ORANGE, "#"};
RectButton runBtn = {30, 160, 100, 40, LCD_COLOR_BLUE, "Run"};
RectButton homeBtn = {140, 160, 100, 40, LCD_COLOR_BLUE, "Home"};
RectButton bigHomeBtn = {300, 20, 150, 50, LCD_COLOR_ORANGE, "AllHome"};
RectButton okBtn = {300, 100, 70, 40, LCD_COLOR_GREEN, "OK"};
RectButton backBtn = {380, 100, 80, 40, LCD_COLOR_BLUE, "Back"};

RectButton buttonsRight[6] = {
    {300, 60, 70, 50, LCD_COLOR_DARKBLUE, "0"},
    {380, 60, 70, 50, LCD_COLOR_DARKBLUE, "1"},
    {300, 120, 70, 50, LCD_COLOR_DARKBLUE, "2"},
    {380, 120, 70, 50, LCD_COLOR_DARKBLUE, "3"},
    {300, 180, 70, 50, LCD_COLOR_DARKBLUE, "4"},
    {380, 180, 70, 50, LCD_COLOR_DARKBLUE, "5"},
};

RectButton numpadButtons[13] = {
    {30, 60, 60, 40, LCD_COLOR_GRAY, "1"},
    {100, 60, 60, 40, LCD_COLOR_GRAY, "2"},
    {170, 60, 60, 40, LCD_COLOR_GRAY, "3"},
    {30, 110, 60, 40, LCD_COLOR_GRAY, "4"},
    {100, 110, 60, 40, LCD_COLOR_GRAY, "5"},
    {170, 110, 60, 40, LCD_COLOR_GRAY, "6"},
    {30, 160, 60, 40, LCD_COLOR_GRAY, "7"},
    {100, 160, 60, 40, LCD_COLOR_GRAY, "8"},
    {170, 160, 60, 40, LCD_COLOR_GRAY, "9"},
    {30, 210, 60, 40, LCD_COLOR_GRAY, "."},
    {100, 210, 60, 40, LCD_COLOR_GRAY, "0"},
    {300, 150, 70, 40, LCD_COLOR_RED, "DEL"},
    {170, 210, 60, 40, LCD_COLOR_GRAY, "-"}
};


RectButton motoresButton = {180, 100, 120, 60, LCD_COLOR_DARKBLUE, "Motors"};
RectButton fanButton = {60, 100, 100, 60, LCD_COLOR_LIGHTBLUE, "Fan"};
RectButton backButton = {10, 10, 80, 40, LCD_COLOR_DARKYELLOW, "Back"};
RectButton demoButton = {320, 100, 100, 60, LCD_COLOR_ORANGE, "Demo"};
RectButton spanishButton = {120, 130, 130, 40, LCD_COLOR_LIGHTBLUE, "Espanol"};
RectButton englishButton = {120, 200, 130, 40, LCD_COLOR_LIGHTBLUE, "Ingles"};

RectButton componentButtons[6] = {
    {175, 40, 90, 40, LCD_COLOR_LIGHTBLUE, "Head"},
    {60, 100, 140, 40, LCD_COLOR_LIGHTBLUE, "LeftArm"},        
    {230, 100, 145, 40, LCD_COLOR_LIGHTBLUE, "RightArm"},
    {60, 220, 140, 40, LCD_COLOR_LIGHTBLUE, "LeftLeg"},
    {230, 220, 145, 40, LCD_COLOR_LIGHTBLUE, "RightLeg"},
    {175, 160, 90, 40, LCD_COLOR_LIGHTBLUE, "Trunk"},  
    };