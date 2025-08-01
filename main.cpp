#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "rtos.h"  
#include "Botones.h"
#include "Screens/ScreenMain.h"
#include "TouchUtils.h"
#include "ScreenState.h"
#include "ScreenComponent.h"
#include "ScreenFan.h"
#include "ScreenDemo.h"
#include "ScreenMotorControl.h"
#include "ScreenNumpad.h"
#include "JointData.h"
#include "SerialCommunication.h"
#include "RobotThreads.h"
#include "TouchHandler.h"
#include "ColorCheck.h"

ScreenState currentScreen = SCREEN_MAIN;
ScreenState previousScreen = SCREEN_MAIN;

char inputBuffer[10] = "";
int inputLength = 0;
char confirmedValue[16] = "0.00";
int selectedButton = -1;

int main() {
    TS_StateTypeDef TS_State;
    uint16_t x, y;
    uint8_t status;

    Thread serialThread;
    serialThread.start(serialReceiverThread);
    Thread displayThread;
    displayThread.start(valueDisplayThread);
 
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

    status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
    if (status != TS_OK) {
        BSP_LCD_Clear(LCD_COLOR_RED);
        BSP_LCD_SetBackColor(LCD_COLOR_RED);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"TOUCHSCREEN INIT FAIL", CENTER_MODE);
        while (1);
    }

    while (1) {
        BSP_TS_GetState(&TS_State);
        if (TS_State.touchDetected) {
            x = TS_State.touchX[0];
            y = TS_State.touchY[0];
        handleTouch(x,y);
        }
        updateButtonFlashes();        
        HAL_Delay(200);
    }
}