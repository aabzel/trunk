#ifndef GPIO_CUSTOM_DIAG_H
#define GPIO_CUSTOM_DIAG_H

#include "std_includes.h"
#include "gpio_const.h"
#include "gpio_custom_const.h"
#include "mcal_types.h"

extern const Reg32_t GpioReg[];

const char* GpioStm32AltFunToStr(uint8_t code);
const char* GpioStmPullToStr(const uint8_t code);
const char* GpioStmSpeedToStr(uint8_t code);
const char* GpioStmOutTypeToStr(uint8_t code);
const char* GpioPortToStr(uint8_t port_num);
Port_t PortLetter2PortNum(char port);

uint32_t gpio_reg_cnt(void);

#endif /* GPIO_CUSTOM_DIAG_H  */
