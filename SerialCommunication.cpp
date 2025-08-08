#include "SerialCommunication.h"
#include "JointData.h"
#include "string.h"
#include "mbed.h"
#include "JointData.h"
#include "Limits.h"
#include "stm32746g_discovery_lcd.h"
#include "ColorCheck.h"


BufferedSerial pc(USBTX, USBRX, 115200);
char outBuf[128];  // Para mensajes formateados
enum CommandType {
    CMD_NONE,
    CMD_RUN,
    CMD_HOME,
    CMD_AllHOME,

};

volatile CommandType lastCommandType = CMD_NONE;
volatile uint32_t lastCommandSentTime = 0;
volatile bool waitingResponse = false;
constexpr uint32_t RESPONSE_TIMEOUT_MS = 1000;  // 3 segundos de espera, ajusta a lo que necesites
uint32_t lastResponseTime = 0;




void send_command(const char* cmd) {
    pc.write(cmd, strlen(cmd));
}

void sendRunCommand(ScreenState screen, int selectedButton, const char* confirmedValue) {
    char message[50];
    const char* screenName;
    
    switch (screen) {
        case SCREEN_CABEZA: screenName = "head"; break;
        case SCREEN_TORSO: screenName = "trunk"; break;
        case SCREEN_BRAZO_IZQ: screenName = "leftArm"; break;
        case SCREEN_BRAZO_DCHO: screenName = "rightArm"; break;
        case SCREEN_PIERNA_IZQ: screenName = "leftLeg"; break;
        case SCREEN_PIERNA_DCHA: screenName = "rightLeg"; break;
        default: screenName = "Desconocido"; break;
    }

    float value = atof(confirmedValue);  // Convierte string a floa
    JointLimits limits = getJointLimits(screenName, selectedButton);
    value = checkAndDisplayLimits(value, limits);
    
    char formattedValue[10];
    snprintf(formattedValue, sizeof(formattedValue), "%.2f", value);

    snprintf(message, sizeof(message), "<%s:%d:%s>\n", screenName, selectedButton, formattedValue);
    pc.write(message, strlen(message));
    lastCommandSentTime = get_ms_count();  // Marca el momento actual
    waitingResponse = true;
    lastCommandType = CMD_RUN;

}

void sendHomeCommand(ScreenState screen) {
    const char* screenName;
    int numSubIndices = 0;

    switch (screen) {
        case SCREEN_CABEZA:
            screenName = "head";
            numSubIndices = 2;  // 0, 1
            break;
        case SCREEN_TORSO:
            screenName = "trunk";
            numSubIndices = 2;  // 0, 1
            break;
        case SCREEN_BRAZO_IZQ:
            screenName = "leftArm";
            numSubIndices = 6;  // 0–5
            break;
        case SCREEN_BRAZO_DCHO:
            screenName = "rightArm";
            numSubIndices = 6;
            break;
        case SCREEN_PIERNA_IZQ:
            screenName = "leftLeg";
            numSubIndices = 6;
            break;
        case SCREEN_PIERNA_DCHA:
            screenName = "rightLeg";
            numSubIndices = 6;
            break;
        default:
            return;  // No hace nada si no estás en una pantalla válida
    }

    lastCommandSentTime = get_ms_count();  // Marca el momento actual
    waitingResponse = true;
    lastCommandType = CMD_HOME;
    for (int subIndex = 0; subIndex < numSubIndices; subIndex++) {
        char message[50];
        snprintf(message, sizeof(message), "<%s:%d:0.00>\n", screenName, subIndex);
        pc.write(message, strlen(message));        
        ThisThread::sleep_for(50ms);  // Pequeño retardo para asegurar envío correcto
    }
}

void sendAllHomeCommand() {
    const char* allScreens[] = {"head", "trunk", "leftArm", "rightArm", "leftLeg", "rightLeg"};
    const int subcounts[] = {2, 2, 6, 6, 6, 6}; // Subarticulaciones por articulación

    char message[50];

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < subcounts[i]; j++) {
            snprintf(message, sizeof(message), "<%s:%d:0.00>\n", allScreens[i], j);
            pc.write(message, strlen(message));
            ThisThread::sleep_for(30ms);  // Pequeño retardo para evitar saturar el canal
        }
    }
    lastCommandSentTime = get_ms_count();  // Marca el momento actual
    waitingResponse = true;
    lastCommandType = CMD_AllHOME;
}


void serialReceiverThread() {
    static const int BUFFER_SIZE = 128;
    char inputBuffer[BUFFER_SIZE];
    size_t bufferIndex = 0;

    char joint[20];
    int subIndex;
    float value;
    char outBuf[128];

    while (true) {
        while (pc.readable()) {
            char c;
            if (pc.read(&c, 1)) {
                if (c == '\n') {
                    inputBuffer[bufferIndex] = '\0';  // Terminar cadena

                    // Revisar si es "True" o "False" antes de intentar parsear como comando
                    if (strcmp(inputBuffer, "True") == 0) {
                        if (lastCommandType == CMD_RUN) {
                            flashRunButtonColor(LCD_COLOR_GREEN, 2000);
                        } else if (lastCommandType == CMD_HOME) {
                            flashHomeButtonColor(LCD_COLOR_GREEN, 2000);
                        }
                    waitingResponse = false; 
                    lastCommandType = CMD_NONE; 
                    }
                    else if (waitingResponse){
                        uint32_t now = get_ms_count();
                        if (now - lastCommandSentTime > RESPONSE_TIMEOUT_MS) {
                        // No llegó respuesta dentro del tiempo límite
                            if (lastCommandType == CMD_RUN) {
                                flashRunButtonColor(LCD_COLOR_RED, 2000);
                            } else if (lastCommandType == CMD_HOME) {
                                flashHomeButtonColor(LCD_COLOR_RED, 2000);
                         // Para no repetir la alerta
                            }
                            waitingResponse = false; 
                            lastCommandType = CMD_NONE;
                        }
                    }
                    // ⛓ Si no es una respuesta lógica, intentamos parsear como movimiento
                    else if (sscanf(inputBuffer, "<%[^:]:%d:%f>", joint, &subIndex, &value) == 3) {
                        jointMutex.lock();
                        if (strcmp(joint, "head") == 0 && subIndex < 2) head[subIndex] = value;
                        else if (strcmp(joint, "trunk") == 0 && subIndex < 2) trunk[subIndex] = value;
                        else if (strcmp(joint, "leftArm") == 0 && subIndex < 6) leftArm[subIndex] = value;
                        else if (strcmp(joint, "rightArm") == 0 && subIndex < 6) rightArm[subIndex] = value;
                        else if (strcmp(joint, "leftLeg") == 0 && subIndex < 6) leftLeg[subIndex] = value;
                        else if (strcmp(joint, "rightLeg") == 0 && subIndex < 6) rightLeg[subIndex] = value;
                        jointMutex.unlock();

                        int outLen = sprintf(outBuf, "[✔️] OK: <%s:%d:%.2f>\n", joint, subIndex, value);
                        pc.write(outBuf, outLen);
                        
                    } 
                    else{
                        int outLen = sprintf(outBuf, "[❌] Formato inválido: %s\n", inputBuffer);
                        pc.write(outBuf, outLen);
                    }                   

                    bufferIndex = 0;  // Reiniciar para siguiente mensaje
                } else if (bufferIndex < BUFFER_SIZE - 1) {
                    inputBuffer[bufferIndex++] = c;
                } else {
                    // Buffer overflow, reiniciar
                    bufferIndex = 0;
                }
            }
        }

        ThisThread::sleep_for(5ms);
    }
}





