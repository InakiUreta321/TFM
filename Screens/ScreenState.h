#ifndef SCREEN_STATE_H
#define SCREEN_STATE_H

// Enumeración de las pantallas disponibles
enum ScreenState {  
    SCREEN_MAIN,
    SCREEN_COMPONENT,
    SCREEN_FAN,
    SCREEN_DEMO,
    SCREEN_BRAZO_IZQ,
    SCREEN_BRAZO_DCHO,
    SCREEN_PIERNA_IZQ,
    SCREEN_PIERNA_DCHA,
    SCREEN_TORSO,
    SCREEN_CABEZA,
    SCREEN_NUMPAD
};

// Variables globales para controlar la pantalla actual y anterior
extern ScreenState currentScreen;
extern ScreenState previousScreen;

#endif // SCREEN_STATE_H
