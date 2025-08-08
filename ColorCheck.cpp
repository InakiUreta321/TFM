#include "ColorCheck.h"
#include "Botones.h"
#include "stm32746g_discovery_lcd.h"

uint32_t currentRunBtnColor = LCD_COLOR_BLUE;
uint32_t currenthomeBtnColor = LCD_COLOR_BLUE;

struct ButtonFlashState {
    bool active = false;
    uint32_t color;
    uint32_t startTime;
    uint32_t duration;
};

ButtonFlashState runBtnState;
ButtonFlashState homeBtnState;

void drawRunButton() {
    RectButton btn = runBtn;  // runBtn debe estar declarado globalmente en otro archivo
    btn.color = currentRunBtnColor;
    drawRectButton(btn);
}

void drawHomeButton() {
    RectButton btn = homeBtn;  // homeBtn global también
    btn.color = currenthomeBtnColor;
    drawRectButton(btn);
}

void flashRunButtonColor(uint32_t color, uint32_t delay_ms) {
    runBtnState.active = true;
    runBtnState.color = color;
    runBtnState.startTime = HAL_GetTick();
    runBtnState.duration = delay_ms;
    currentRunBtnColor = color;
    drawRunButton();
}

void flashHomeButtonColor(uint32_t color, uint32_t delay_ms) {
    homeBtnState.active = true;
    homeBtnState.color = color;
    homeBtnState.startTime = HAL_GetTick();
    homeBtnState.duration = delay_ms;
    currenthomeBtnColor = color;
    drawHomeButton();
}

void updateButtonFlashes() {
    uint32_t now = HAL_GetTick();

    if (runBtnState.active && (now - runBtnState.startTime >= runBtnState.duration)) {
        runBtnState.active = false;
        currentRunBtnColor = LCD_COLOR_BLUE;
        drawRunButton();
    }

    if (homeBtnState.active && (now - homeBtnState.startTime >= homeBtnState.duration)) {
        homeBtnState.active = false;
        currenthomeBtnColor = LCD_COLOR_BLUE;
        drawHomeButton();
    }

}

