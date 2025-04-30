#ifndef GPIO_MIK32_DIAG_H
#define GPIO_MIK32_DIAG_H

#include "std_includes.h"
#include "gpio_custom_const.h"
#include "mik32_hal_gpio.h"

//const char* GpioEdge2str(PinIntEdge_t code);
const char* GpioMik32AltFun2Str(uint8_t code);
const char* GpioMik32Pull2Str(HAL_GPIO_PullTypeDef code);
const char* GpioMik32Speed2Str(uint8_t code);
const char* GpioMik32OutType2Str(uint8_t code);
const char* GpioPort2Str(uint8_t port_num);
//const char* GpioMode2Str(uint8_t code);
//const char* GpioType2Str(uint8_t code);
//const char* GpioDir2Str(uint8_t code);
//const char* GpioAlterFun2Str(uint8_t code);
Port_t PortLetter2PortNum(char port);
bool gpio_diag_ll(void);

#endif /* GPIO_MIK32_DIAG_H  */
