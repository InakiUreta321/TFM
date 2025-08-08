#include "ScreenMotorControl.h"
#include "Limits.h"
#include "ScreenComponent.h"
#include "ScreenState.h"
#include "Botones.h"
#include "TouchUtils.h"
#include "stm32746g_discovery_lcd.h"
#include <string.h>
#include "ScreenNumpad.h"
#include "SerialCommunication.h"
#include "JointData.h"
#include "ColorCheck.h"

// Externs necesarios
extern RectButton plusBtn, minusBtn, hashBtn, runBtn;
extern RectButton backButton;
extern RectButton buttonsRight[6];
extern RectButton componentButtons[6];
extern RectButton bigHomeBtn;

extern ScreenState currentScreen;
extern ScreenState previousScreen;

extern int inputLength;
extern char inputBuffer[10];

extern int selectedButton;
extern char confirmedValue[16];

extern void drawMotorControlFor(ScreenState screen);
extern void updateConfirmedValue(float delta);

void drawMotorControlScreen() {

    drawMotorControlFor(currentScreen);
}

void handleMotorControlTouch(uint16_t x, uint16_t y) {
    if (isTouchInside(hashBtn, x, y)) {
        previousScreen = currentScreen;
        currentScreen = SCREEN_NUMPAD;
        inputLength = 0;
        inputBuffer[0] = '\0';
        drawNumpadScreen();
    }

    if (isTouchInside(plusBtn, x, y)) {
        updateConfirmedValue(1.0f);
    }

    if (isTouchInside(minusBtn, x, y)) {
        updateConfirmedValue(-1.0f);
    }

    for (int i = 0; i < 6; i++) {
        if (isTouchInside(buttonsRight[i], x, y)) {
            selectedButton = i;
            drawMotorControlScreen();
            break;
        }
    }

    if (isTouchInside(runBtn, x, y)) {
        if (selectedButton != -1) {
            sendRunCommand(currentScreen, selectedButton, confirmedValue);
        }
        else{
            displaySelectButtonWarning();
        }
    }

    if (isTouchInside(homeBtn, x, y)) {
            sendHomeCommand(currentScreen);
    }

    if (isTouchInside(backButton, x, y)) {
        currentScreen = SCREEN_COMPONENT;
        drawComponentScreen();
    }
}


void drawMotorControlScreen(int numButtons) {
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);

    // Mostrar valor confirmado
    BSP_LCD_DrawRect(30, 55, 200, 30);
    BSP_LCD_DisplayStringAt(35, 60, (uint8_t*)confirmedValue, LEFT_MODE);

    // Botones principales
    drawRectButton(plusBtn);
    drawRectButton(minusBtn);
    drawRectButton(hashBtn);
    drawRectButton(runBtn);
    drawRectButton(homeBtn);
    drawRectButton(backButton);

    // === TÍTULO ===
    const char* screenLabel = "";
    switch (currentScreen) {
        case SCREEN_CABEZA:      screenLabel = "Head"; break;
        case SCREEN_TORSO:       screenLabel = "Trunk"; break;
        case SCREEN_BRAZO_IZQ:   screenLabel = "Left arm"; break;
        case SCREEN_BRAZO_DCHO:  screenLabel = "Right arm"; break;
        case SCREEN_PIERNA_IZQ:  screenLabel = "Left leg"; break;
        case SCREEN_PIERNA_DCHA: screenLabel = "Right leg"; break;
    }
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);   // Color del texto
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);   // Fondo del texto
    BSP_LCD_DisplayStringAt(0, 12, (uint8_t*)screenLabel, CENTER_MODE);


    // Botones laterales
    for (int i = 0; i < numButtons; i++) {
        buttonsRight[i].color = (selectedButton == i) ? LCD_COLOR_GREEN : LCD_COLOR_DARKBLUE;
        drawRectButton(buttonsRight[i]);
    }

    // Mostrar valor actual recibido
    float currentValue = getCurrentJointValue(currentScreen, selectedButton);
    char displayValue[20];
    snprintf(displayValue, sizeof(displayValue), "Now: %.2f", currentValue);

    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DrawRect(30, 210, 210, 30);  // Recuadro
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(35, 215, (uint8_t*)displayValue, LEFT_MODE);
}



void drawMotorControlFor(ScreenState screen) {
    int numButtons = 0;

    switch (screen) {
        case SCREEN_CABEZA:
        case SCREEN_TORSO:
            numButtons = 2;
            break;
        case SCREEN_BRAZO_IZQ:
        case SCREEN_BRAZO_DCHO:
            numButtons = 6;
            break;
        case SCREEN_PIERNA_IZQ:
        case SCREEN_PIERNA_DCHA:
            numButtons = 6;
            break;
        default:
            numButtons = 0;
            break;
    }

    drawMotorControlScreen(numButtons); 
}


void updateConfirmedValue(float delta) {
    float value = atof(confirmedValue);
    value += delta;
    snprintf(confirmedValue, sizeof(confirmedValue), "%.2f", value);
    drawMotorControlFor(currentScreen);
}