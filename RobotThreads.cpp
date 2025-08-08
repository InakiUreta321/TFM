#include "RobotThreads.h"
#include "mbed.h"
#include <cstring>
#include <cstdio>
#include "ScreenState.h"
#include "stm32746g_discovery_lcd.h"
#include "JointData.h"

// Externos necesarios
extern BufferedSerial pc;
extern Mutex jointMutex;
extern ScreenState currentScreen;
extern float head[2], trunk[2], leftArm[6], rightArm[6], leftLeg[6], rightLeg[6];


void valueDisplayThread() {
    char lastDisplay[20] = "";

    while (true) {
        if (currentScreen == SCREEN_CABEZA || currentScreen == SCREEN_TORSO ||
            currentScreen == SCREEN_BRAZO_IZQ || currentScreen == SCREEN_BRAZO_DCHO ||
            currentScreen == SCREEN_PIERNA_IZQ || currentScreen == SCREEN_PIERNA_DCHA) {
       
            float currentValue = getCurrentJointValue(currentScreen, selectedButton);
            char displayValue[20];
            snprintf(displayValue, sizeof(displayValue), "Now: %.2f", currentValue);

            if (strcmp(displayValue, lastDisplay) != 0) {
                BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
                BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
                BSP_LCD_DisplayStringAt(35, 215, (uint8_t*)lastDisplay, LEFT_MODE);

                BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
                BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
                BSP_LCD_DisplayStringAt(35, 215, (uint8_t*)displayValue, LEFT_MODE);

                strcpy(lastDisplay, displayValue);
            }
        }

        ThisThread::sleep_for(300ms);
    }
}
