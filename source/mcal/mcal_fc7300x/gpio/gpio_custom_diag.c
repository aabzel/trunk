#include "gpio_custom_diag.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bit_utils.h"
#include "gpio_config.h"
#include "gpio_custom_const.h"
#include "gpio_mcal.h"

const char* GpioFc7300xAltFun2Str(uint8_t code) {
    static char name[8];
    snprintf(name, sizeof(name), "AF%u", code);
    return name;
}

#if 0
const char* GpioPortToStr(uint8_t port_num) {
    const char* name = "?";
    return name;
}
#endif

const char* GpioFc7300xOutType2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case OUT_TYPE_PUSH_PULL:
        name = "PushPull";
        break;
    case OUT_TYPE_OPEN_DRAIN:
        name = "OpenDrain";
        break;
    }
    return name;
}

const char* GpioFc7300xSpeed2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case SPEED_LOW_SPEED:
        name = "Low";
        break;
    case SPEED_MEDIUM_SPEED:
        name = "Med";
        break;
    case SPEED_FAST_SPEED:
        name = "Fast";
        break;
    case SPEED_HIGH_SPEED:
        name = "High";
        break;
    }
    return name;
}

const char* GpioFc7300xPull2Str(uint8_t code) {
    char* name = "?";

    return name;
}

GpioPort_t PortLetter2PortNum(char port) {
    GpioPort_t port_num = GPIO_PORT_UNDEF;
    return port_num;
}
