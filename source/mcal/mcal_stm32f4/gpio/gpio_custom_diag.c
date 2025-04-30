#include "gpio_custom_diag.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bit_utils.h"
#include "gpio_custom_const.h"
#include "gpio_mcal.h"

const char* GpioStm32AltFun2Str(uint8_t code) {
    static char name[8];
    snprintf(name, sizeof(name), "AF%u", code);
    return name;
}

const char* GpioPort2Str(uint8_t port_num) {
    const char* name = "?";
    switch(port_num) {
    case PORT_A:
        name = "A";
        break;
    case PORT_B:
        name = "B";
        break;
    case PORT_C:
        name = "C";
        break;
    case PORT_D:
        name = "D";
        break;
    case PORT_E:
        name = "E";
        break;
    case PORT_F:
        name = "F";
        break;
    case PORT_G:
        name = "G";
        break;
    case PORT_H:
        name = "H";
        break;
    }
    return name;
}

#if 0
static const char* GpioStmMode2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case GP_STM32_MODE_INPUT:
        name = "In";
        break;
    case GP_STM32_MODE_GNRL_PURPOSE_OUT:
        name = "Out";
        break;
    case GP_STM32_MODE_ALT_FUN:
        name = "Alt";
        break;
    case GP_STM32_MODE_ANALOG:
        name = "Ana";
        break;
    }
    return name;
}
#endif

const char* GpioStmOutType2Str(uint8_t code) {
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

const char* GpioStmSpeed2Str(uint8_t code) {
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

const char* GpioStmPull2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case STM32_PULL_AIR:
        name = "Air";
        break;
    case STM32_PULL_UP:
        name = "Up";
        break;
    case STM32_PULL_DOWN:
        name = "Down";
        break;
    }
    return name;
}

Port_t PortLetter2PortNum(char port) {
    Port_t port_num = PORT_UNDEF;
    switch(port) {
    case 'a':
    case 'A':
        port_num = PORT_A;
        break;
    case 'b':
    case 'B':
        port_num = PORT_B;
        break;
    case 'c':
    case 'C':
        port_num = PORT_C;
        break;
    case 'd':
    case 'D':
        port_num = PORT_D;
        break;
    case 'e':
    case 'E':
        port_num = PORT_E;
        break;
    case 'f':
    case 'F':
        port_num = PORT_F;
        break;
    case 'g':
    case 'G':
        port_num = PORT_G;
        break;
    case 'h':
    case 'H':
        port_num = PORT_H;
        break;
    }
    return port_num;
}
