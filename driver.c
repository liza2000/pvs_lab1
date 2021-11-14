#include "hal.h"
#include <stdio.h>
#include <string.h>

#define CLEAN 0
#define RED GPIO_PIN_15
#define YELLOW  GPIO_PIN_14
#define GREEN GPIO_PIN_13

#define  SET GPIO_PIN_SET
#define  RESET GPIO_PIN_RESET

void delay(int time){
    HAL_Delay(time);
}
void switchRedYellow(int pin, int time = 0) {
    if (pin!= RED && pin!=YELLOW && pin!= CLEAN)
        return;
    HAL_GPIO_WritePin(GPIOD, RED, pin == RED ? SET:RESET);
    HAL_GPIO_WritePin(GPIOD, YELLOW, pin == YELLOW? SET: RESET);
    HAL_Delay(time);
}


void switchGreen(int set, int time = 0){
    HAL_GPIO_WritePin(GPIOD,GREEN, set ? SET : RESET);
    HAL_Delay(time);
}

void help(int timeout, int mode, int inter){
    char* message = "";
    char* buf;
    if(HAL_GPIO_ReadPin(GPIOD,RED) == SET)
       strcat(message,"RED\n");
    else if(HAL_GPIO_ReadPin(GPIOD,YELLOW) == SET)
        strcat(message,"Yellow\n");
    else if(HAL_GPIO_ReadPin(GPIOD,GREEN) == RESET)
        strcat(message,"Green\n");

    strcat(message, "timeout ");
    sprintf(buf,"%d\n", timeout);
    strcat(message, buf);

    strcat(message, "mode ");
    strcat(message,mode?"1\n":"2\n");

    strcat(message, inter?"P\n":"I\n");

    if (inter)
        HAL_UART_Transmit_IT(&huart6, (uint8_t*)message, sizeof message);
    else
        HAL_UART_Transmit(&huart6, (uint8_t*)message, sizeof message, 100)

}



void blink(int pin, int time, int period){
    if (pin!= RED && pin!=YELLOW && pin!= GREEN)
        return;
    for (int i = period; i <= time; i+=period) {
        HAL_GPIO_TogglePin(GPIOD, pin);
        HAL_Delay(period);
    }
}

void waitForPressBtn(int time) {
    for (int i = 0; i <= time; i += 50) {
        HAL_Delay(50);
        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == GPIO_PIN_RESET && i < time * 3 / 4) {
            HAL_Delay(time / 4);
            return;
        }
    }
}
    int umain() {
    int timeout = 10000;
    int mode = 0;
    int interrupt = 0;
        while (1) {

            switchGreen(1, timeout/4);
            blink(GREEN, timeout/4, timeout/40);
            switchGreen(0);
            switchRedYellow(YELLOW, timeout/4);
            switchRedYellow(RED);
            if (!mode)
                waitForPressBtn(timeout);
            else
                HAL_Delay(timeout);
            switchRedYellow(CLEAN);
            return 0;
        }
    }