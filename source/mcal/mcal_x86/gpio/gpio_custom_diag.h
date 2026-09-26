#ifndef GPIO_CUSTOM_DIAG_H
#define GPIO_CUSTOM_DIAG_H

#include "std_includes.h"
#include "gpio_const.h"
#include "gpio_custom_const.h"

//const char* GpioEdge2str(PinIntEdge_t code);
const char* GpioFc7300xAltFun2Str(uint8_t code);
const char* GpioFc7300xPull2Str(uint8_t code);
const char* GpioFc7300xSpeed2Str(uint8_t code);
const char* GpioFc7300xOutType2Str(uint8_t code);
//const char* GpioPortToStr(uint8_t port_num);
//const char* GpioMode2Str(uint8_t code);
//const char* GpioType2Str(uint8_t code);
//const char* GpioDir2Str(uint8_t code);
//const char* GpioAlterFun2Str(uint8_t code);
GpioPort_t PortLetter2PortNum(char port);

#endif /* GPIO_CUSTOM_DIAG_H  */
