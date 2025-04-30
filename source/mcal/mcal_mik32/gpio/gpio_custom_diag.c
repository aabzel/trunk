#include "gpio_custom_diag.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bit_utils.h"
#include "gpio_custom_const.h"
#include "gpio_mcal.h"

#include "shared_array.h"

const char* GpioMik32AltFun2Str(uint8_t code) {

    snprintf(text, sizeof(text), "AF%u", code);
    return text;
}

const char* GpioPort2Str(uint8_t port_num) {
    const char* name = "?";
    switch(port_num) {
    case PORT_0:
        name = "0";
        break;
    case PORT_1:
        name = "1";
        break;
    case PORT_2:
        name = "2";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

#if 0
static const char* GpioMik32Mode2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case GP_MIK32_MODE_INPUT:
        name = "In";
        break;
    case GP_MIK32_MODE_GNRL_PURPOSE_OUT:
        name = "Out";
        break;
    case GP_MIK32_MODE_ALT_FUN:
        name = "Alt";
        break;
    case GP_MIK32_MODE_ANALOG:
        name = "Ana";
        break;
    }
    return name;
}
#endif

const char* GpioMik32OutType2Str(uint8_t code) {
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

const char* GpioMik32Speed2Str(uint8_t code) {
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

const char* GpioMik32Pull2Str(HAL_GPIO_PullTypeDef code) {
    char* name = "?";
    switch(code) {
    case HAL_GPIO_PULL_NONE:
        name = "Air";
        break;
    case HAL_GPIO_PULL_UP:
        name = "Up";
        break;
    case HAL_GPIO_PULL_DOWN:
        name = "Down";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

Port_t PortLetter2PortNum(char port) {
    Port_t port_num = PORT_UNDEF;
    switch(port) {
      case '0':  port_num = PORT_0; break;
      case '1':  port_num = PORT_1; break;
      case '2':  port_num = PORT_2; break;
      default:   port_num = PORT_UNDEF;  break;
    }
    return port_num;
}

bool gpio_diag_ll(void) {
    bool res = false;
#if 0
    char debug_text[200] = {0};
    snprintf(debug_text,sizeof(debug_text),"%s,P0_PAD_CFG:0x%x",debug_text, PAD_CONFIG->PORT_0_CFG);
    snprintf(debug_text,sizeof(debug_text),"%s,P0_PAD_PUL:0x%x",debug_text, PAD_CONFIG->PORT_0_PUPD);
    snprintf(debug_text,sizeof(debug_text),"%s,P0_DIR_OUT:0x%x",debug_text, GPIO_0->DIRECTION_OUT);
    snprintf(debug_text,sizeof(debug_text),"%s,P0_DIR_IN:0x%x",debug_text, GPIO_0->DIRECTION_IN);
    snprintf(debug_text,sizeof(debug_text),"%s%s",debug_text, CRLF);
    UartHandle_t* Node = UartGetNode(0);
    res = uart_send_wait_ll(Node, (uint8_t*) debug_text, strlen(debug_text));
#endif
    return res;
}
