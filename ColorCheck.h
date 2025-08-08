#ifndef COLORCHECK_H
#define COLORCHECK_H

#include "stdint.h"

// Funciones públicas
void drawRunButton();
void drawHomeButton();

void flashRunButtonColor(uint32_t color, uint32_t delay_ms);
void flashHomeButtonColor(uint32_t color, uint32_t delay_ms);

void updateButtonFlashes();  // ✅ Esta es la nueva que necesitas exportar

#endif // COLORCHECK_H
