#include "mbed.h"  // Esta incluye Mutex, Thread, etc.
#include "JointData.h"
#include "string.h"

Mutex jointMutex;

float head[2] = {0};
float trunk[2] = {0};
float leftArm[6] = {0};
float rightArm[6] = {0};
float leftLeg[6] = {0};
float rightLeg[6] = {0};

float getCurrentJointValue(ScreenState screen, int selectedButton) {
    float value = 0.0f;
    jointMutex.lock();
    switch (screen) {
        case SCREEN_CABEZA:
            if (selectedButton >= 0 && selectedButton < 2) value = head[selectedButton];
            break;
        case SCREEN_TORSO:
            if (selectedButton >= 0 && selectedButton < 2) value = trunk[selectedButton];
            break;
        case SCREEN_BRAZO_IZQ:
            if (selectedButton >= 0 && selectedButton < 6) value = leftArm[selectedButton];
            break;
        case SCREEN_BRAZO_DCHO:
            if (selectedButton >= 0 && selectedButton < 6) value = rightArm[selectedButton];
            break;
        case SCREEN_PIERNA_IZQ:
            if (selectedButton >= 0 && selectedButton < 6) value = leftLeg[selectedButton];
            break;
        case SCREEN_PIERNA_DCHA:
            if (selectedButton >= 0 && selectedButton < 6) value = rightLeg[selectedButton];
            break;
        default:
            value = 0.0f;
    }
    jointMutex.unlock();
    return value;
}

