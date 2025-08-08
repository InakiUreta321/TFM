#ifndef JOINT_DATA_H
#define JOINT_DATA_H
#include "mbed.h"
#include "ScreenState.h"

// Declaración de variables si son usadas fuera
extern float head[2], trunk[2], leftArm[6], rightArm[6], leftLeg[6], rightLeg[6];
extern int selectedButton;
extern ScreenState currentScreen;
extern Mutex jointMutex;

// Declaración de función
float getCurrentJointValue(ScreenState screen, int selectedButton);

#endif
