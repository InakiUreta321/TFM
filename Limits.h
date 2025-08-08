#ifndef LIMITS_H
#define LIMITS_H
#include "stm32746g_discovery_lcd.h"
#include "string.h"

typedef struct {
    double min;
    double max;
} JointLimits;

JointLimits getJointLimits(const char* part, int joint);
float checkAndDisplayLimits(float value, JointLimits limits);
void displaySelectButtonWarning();

#endif
