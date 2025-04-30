#ifndef GPIO_GENERAL_DIAG_H
#define GPIO_GENERAL_DIAG_H

#include <stdbool.h>
#include <stdint.h>

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

const char* GpioConfToStr(const GpioConfig_t* Config);

const char* GpioAltFun2Str(uint8_t code);
const char* GpioAlterFun2Str(uint8_t code);
#ifdef HAS_EXT_INT
const char* GpioEdgeToStr(PinIntEdge_t code);
#endif
const char* GpioDir2Str(GpioDir_t code);
const char* GpioFunToStr(GpioPinFunction_t function);
const char* GpioLevel2Str(GpioLogicLevel_t code);
const char* GpioMode2Str(GpioApiMode_t code);
const char* GpioOutType2Str(uint8_t code);
const char* GpioPad2Str(uint8_t pad);
const char* GpioPadToStr(Pad_t pad);
const char* GpioPad2WireName(uint8_t pad);
const char* GpioPull2Str(GpioPullMode_t code);
const char* GpioSpeed2Str(uint8_t code);
const char* GpioType2Str(uint8_t code);

bool gpio_diag(char* key_word1, char* key_word2);
bool GpioConfigDiag(const GpioConfig_t* Config);

#endif /* GPIO_GENERAL_DIAG_H  */
