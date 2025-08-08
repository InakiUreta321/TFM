#include "TouchHandler.h"
#include "Screens/ScreenMain.h"
#include "ScreenComponent.h"
#include "ScreenFan.h"
#include "ScreenDemo.h"
#include "ScreenMotorControl.h"
#include "ScreenNumpad.h"
#include "ScreenState.h"

// Variables globales necesarias (si las usas externamente)
extern ScreenState currentScreen;
extern int selectedButton;  // Si es necesario para MotorControl

// Implementación de la función handleTouch
void handleTouch(uint16_t x, uint16_t y) {
    switch (currentScreen) {
        case SCREEN_MAIN:
            drawMainScreen();
            handleMainScreenTouch(x, y);
            break;
        case SCREEN_COMPONENT:
            drawComponentScreen();
            handleComponentScreenTouch(x, y);
            break;
        case SCREEN_FAN:
            drawFanScreen();
            handleFanScreenTouch(x, y);
            break;
        case SCREEN_DEMO:
            drawDemoScreen();
            handleDemoScreenTouch(x, y);
            break;
        case SCREEN_NUMPAD:
            drawNumpadScreen();
            handleNumpadTouch(x, y);
            break;
        case SCREEN_CABEZA:
        case SCREEN_BRAZO_IZQ:
        case SCREEN_BRAZO_DCHO:
        case SCREEN_PIERNA_IZQ:
        case SCREEN_PIERNA_DCHA:
        case SCREEN_TORSO:
            drawMotorControlScreen();
            handleMotorControlTouch(x, y);
            break;
        default:
            // Opcional: manejar caso desconocido
            break;
    }
}
