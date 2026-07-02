#ifndef GPIO_GENERAL_DIAG_H
#define GPIO_GENERAL_DIAG_H

#include "std_includes.h"
#include "gpio_types.h"

#ifdef HAS_GPIO_CUSTOM
#include "gpio_custom_diag.h"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

#ifndef HAS_GPIO_DIAG
#error "+HAS_GPIO_DIAG"
#endif

const char* GpioConfigToStr(const GpioConfig_t* const Config);
const char* GpioPortToStr(const GpioPort_t port);
const char* GpioAltFunToStr(  uint8_t alt_foo);
const char* GpioAlterFunToStr(Pad_t Pad);
#ifdef HAS_EXT_INT
const char* GpioEdgeToStr(PinIntEdge_t code);
#endif
const char* GpioDirToStr(GpioDir_t code);
const char* GpioFunToStr(GpioPinFunction_t function);
const char* GpioLevelToStr(GpioLogicLevel_t code);
const char* GpioModeToStr(GpioApiMode_t code);
const char* GpioOutTypeToStr(Pad_t Pad);
const char* GpioPadToStr(Pad_t Pad);
const char* GpioDriveSelectToStr(const GpioDriveSelect_t drive_select);
const char* GpioPad2WireName(const Pad_t Pad);
const char* GpioPullToStr(GpioPullMode_t code);
const char* GpioSpeedToStr(const GpioSpeed_t speed) ;
const char* GpioTypeToStr(Pad_t Pad);
const char* GpioPadsToStr(const Pad_t* const pPad, const uint32_t cnt);

bool diag_gpio(char* key_word1, char* key_word2) ;
bool gpio_diag(char* key_word1, char* key_word2);
bool gpio_raw_reg_diag(const GpioPort_t port);
bool GpioConfigDiag(const GpioConfig_t* Config);

#endif /* GPIO_GENERAL_DIAG_H  */
