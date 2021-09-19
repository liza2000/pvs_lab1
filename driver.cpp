#include "hal.h"

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
    delay(time);
}


void switchGreen(bool set, int time = 0){
    HAL_GPIO_WritePin(GPIOD,GREEN, set ? SET : RESET);
    delay(time);
}



void blink(int pin, int time, int period){
    if (pin==0) return;
    for (int i = period; i <= time; i+=period) {
        HAL_GPIO_TogglePin(GPIOD, pin);
        HAL_Delay(period);
    }
}

void waitForPressBtn(int time){
    for (int i = 0;i<=time;i+=50) {
        delay(50);
        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == GPIO_PIN_RESET)
            return;
    }
}
//    int umain() {
//        while (true) {
//            switchGreen(true, 5000);
//            blink(GREEN, 5000, 500);
//            switchGreen(false);
//            switchRedYellow(YELLOW, 5000);
//            switchRedYellow(RED);
//            waitForPressBtn(10000);
//            switchRedYellow(CLEAN);
//        }
//    }