#include "Limits.h"
#include <string.h>
#include "stm32746g_discovery_lcd.h"
#include <stdio.h>

// Definición de límites para cada parte
static JointLimits leftArmLimits[] = {
    {-96.80, 113.20},
    {-23.90, 76.50},
    {-51.60, 84.10},
    {-101.10, 96.80},
    {-101.30, 76.40},
    {-113.30, 61.30}
};

static JointLimits rightArmLimits[] = {
    {-98.10, 106.00},
    {-75.50, 22.40},
    {-80.10, 57.00},
    {-99.60, 98.40},
    {-80.40, 99.60},
    {-115.10, 44.70}
};

static JointLimits headLimits[] = {
    {-70.00, 70.00},
    {-29.00, 8.40}
};

static JointLimits trunkLimits[] = {
    {-59.30, 46.30},
    {-10.10, 90.40}
};

static JointLimits leftLegLimits[] = {
    {-27.90, 32.80},
    {-12.50, 14.20},
    {-31.60, 42.30},
    {-61.30, 82.40},
    {-23.10, 25.40},
    {-42.50, 19.90}
};

static JointLimits rightLegLimits[] = {
    {-32.80, 27.90},
    {-14.20, 12.50},
    {-31.60, 42.30},
    {-61.30, 82.40},
    {-23.10, 25.40},
    {-19.90, 42.50}
};

// Función para obtener límites según parte y joint
JointLimits getJointLimits(const char* part, int joint) {
    if (strcmp(part, "leftArm") == 0) {
        if (joint >= 0 && joint < 6) return leftArmLimits[joint];
    } else if (strcmp(part, "rightArm") == 0) {
        if (joint >= 0 && joint < 6) return rightArmLimits[joint];
    } else if (strcmp(part, "head") == 0) {
        if (joint >= 0 && joint < 2) return headLimits[joint];
    } else if (strcmp(part, "trunk") == 0) {
        if (joint >= 0 && joint < 2) return trunkLimits[joint];
    } else if (strcmp(part, "leftLeg") == 0) {
        if (joint >= 0 && joint < 6) return leftLegLimits[joint];
    } else if (strcmp(part, "rightLeg") == 0) {
        if (joint >= 0 && joint < 6) return rightLegLimits[joint];
    }

    // Por defecto si no existe
    JointLimits empty = {0.0, 0.0};
    return empty;
}

float checkAndDisplayLimits(float value, JointLimits limits) {
    char buffer1[40];
    char buffer2[40];

    if (value > limits.max) {
        sprintf(buffer1, "Max position is: %.2f", limits.max);
        sprintf(buffer2, "Moving there");

        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_FillRect(0, 130, 480, 80);  // Borra área del mensaje

        BSP_LCD_SetTextColor(LCD_COLOR_RED);
        BSP_LCD_DisplayStringAt(0, 140, (uint8_t *)buffer1, CENTER_MODE);
        BSP_LCD_DisplayStringAt(0, 160, (uint8_t *)buffer2, CENTER_MODE);

        HAL_Delay(1);  // 1segundo

        return limits.max;
    }
    else if (value < limits.min) {
        sprintf(buffer1, "Min position is: %.2f", limits.min);
        sprintf(buffer2, "Moving there");

        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_FillRect(0, 130, 480, 80);  // Borra área del mensaje

        BSP_LCD_SetTextColor(LCD_COLOR_RED);
        BSP_LCD_DisplayStringAt(0, 140, (uint8_t *)buffer1, CENTER_MODE);
        BSP_LCD_DisplayStringAt(0, 160, (uint8_t *)buffer2, CENTER_MODE);

        HAL_Delay(1);  // 1segundo

        return limits.min;
    }
    return value;  // Dentro de los límites
}

//Escribe un aviso si no hay ningún botón seleccionado
void displaySelectButtonWarning() {
    char buffer3[40];
    sprintf(buffer3, "Selecciona una articulacion");
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_FillRect(0, 130, 450, 40);  // Borra zona del mensaje

    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_DisplayStringAt(0, 140, (uint8_t *)buffer3, CENTER_MODE);

    HAL_Delay(1000);  // Esperar 1 segundo (1000 ms)
}
