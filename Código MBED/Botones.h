#ifndef BOTONES_H
#define BOTONES_H

#include <stdint.h>

// Estructura para botones
typedef struct {
    uint16_t x, y, w, h;
    uint32_t color;
    const char* label;
} RectButton;


// Declaracion de funcion
void drawRectButton(const RectButton& btn);

// Declaración de variables externas
extern RectButton plusBtn;
extern RectButton minusBtn;
extern RectButton hashBtn;
extern RectButton runBtn;
extern RectButton homeBtn;
extern RectButton bigHomeBtn;
extern RectButton okBtn;
extern RectButton backBtn;
extern RectButton numpadButtons[13];
extern RectButton buttonsRight[6];

extern RectButton backButton;
extern RectButton motoresButton;
extern RectButton fanButton;
extern RectButton demoButton;
extern RectButton spanishButton;
extern RectButton englishButton;
extern RectButton componentButtons[6];

#endif // BOTONES_H
