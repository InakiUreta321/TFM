#pragma once
#include "mbed.h"
#include "ScreenState.h"

extern BufferedSerial pc;

void send_command(const char* cmd);
void sendRunCommand(ScreenState screen, int selectedButton, const char* confirmedValue);
void sendHomeCommand(ScreenState screen);
void sendAllHomeCommand();
void serialReceiverThread();
