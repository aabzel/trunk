#ifndef GPIO_CUSTOM_DIAG_H
#define GPIO_CUSTOM_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "gpio_custom_const.h"

//const char* GpioEdge2str(PinIntEdge_t code);
const char* GpioStm32AltFun2Str(uint8_t code);
const char* GpioStmPull2Str(uint8_t code);
const char* GpioStmSpeed2Str(uint8_t code);
const char* GpioStmOutType2Str(uint8_t code);
const char* GpioPort2Str(uint8_t port_num);
//const char* GpioMode2Str(uint8_t code);
//const char* GpioType2Str(uint8_t code);
//const char* GpioDir2Str(uint8_t code);
//const char* GpioAlterFun2Str(uint8_t code);
Port_t PortLetter2PortNum(char port);

#endif /* GPIO_CUSTOM_DIAG_H  */
