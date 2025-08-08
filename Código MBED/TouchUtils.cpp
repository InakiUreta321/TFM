#include "TouchUtils.h"

bool isTouchInside(RectButton btn, uint16_t tx, uint16_t ty) {
    return (tx >= btn.x && tx <= btn.x + btn.w && ty >= btn.y && ty <= btn.y + btn.h);
}
