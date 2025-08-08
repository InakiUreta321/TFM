#ifndef SCREEN_MOTOR_CONTROL_H
#define SCREEN_MOTOR_CONTROL_H
#include "ScreenState.h"
#include <stdint.h>

void drawMotorControlScreen();
void drawMotorControlScreen(int numButtons);
void handleMotorControlTouch(uint16_t x, uint16_t y);
void drawMotorControlFor(ScreenState screen);
void updateConfirmedValue(float delta);

#endif
