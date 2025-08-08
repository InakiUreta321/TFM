#include "ScreenComponent.h"
#include "Botones.h"
#include "ScreenMain.h"
#include "stm32746g_discovery_lcd.h"
#include "TouchUtils.h"
#include "ScreenState.h"
#include "ScreenNumpad.h"
#include "SerialCommunication.h"


// Variables externas que necesitas (definidas en main o donde estén)
extern ScreenState currentScreen;

extern RectButton componentButtons[6];
extern RectButton backButton;

// Aquí debes definir drawMotorControlFor si no está en otro módulo
extern void drawMotorControlFor(ScreenState screen);

void drawComponentScreen() {
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

    for (int i = 0; i < 6; i++) {
        drawRectButton(componentButtons[i]);
    }
    drawRectButton(backButton);
    drawRectButton(bigHomeBtn);
}

void handleComponentScreenTouch(uint16_t x, uint16_t y) {

   if (isTouchInside(backButton, x, y)) {
        currentScreen = SCREEN_MAIN;
        drawMainScreen();
        return;
    }

    if (isTouchInside(bigHomeBtn, x, y)) {
    sendAllHomeCommand();
    }



    // Primero checamos si tocó algún componente
    for (int i = 0; i < 6; i++) {
        if (isTouchInside(componentButtons[i], x, y)) {
            switch(i) {
                case 0: currentScreen = SCREEN_CABEZA; break;
                case 1: currentScreen = SCREEN_BRAZO_IZQ; break;
                case 2: currentScreen = SCREEN_BRAZO_DCHO; break;
                case 3: currentScreen = SCREEN_PIERNA_IZQ; break;
                case 4: currentScreen = SCREEN_PIERNA_DCHA; break;
                case 5: currentScreen = SCREEN_TORSO; break;
            }
            drawMotorControlFor(currentScreen);
            return;
        }
    }
 
    if (currentScreen == SCREEN_BRAZO_IZQ || currentScreen == SCREEN_BRAZO_DCHO ||
                    currentScreen == SCREEN_PIERNA_IZQ || currentScreen == SCREEN_PIERNA_DCHA ||
                    currentScreen == SCREEN_TORSO) {
                    BSP_LCD_Clear(LCD_COLOR_WHITE);
                    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
                    drawRectButton(backButton);
                }

}
