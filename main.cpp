#include <iostream>
#include "driver.cpp"

    int umain() {
        while (true) {
            switchGreen(true, 5000);
            blink(GREEN, 5000, 500);
            switchGreen(false);
            switchRedYellow(YELLOW, 5000);
            switchRedYellow(RED);
            waitForPressBtn(10000);
            switchRedYellow(CLEAN);
        }
    }