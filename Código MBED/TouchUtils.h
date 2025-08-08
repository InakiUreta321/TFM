#ifndef TOUCH_UTILS_H
#define TOUCH_UTILS_H

#include <stdint.h>
#include "Botones.h"

bool isTouchInside(RectButton btn, uint16_t tx, uint16_t ty);

#endif
