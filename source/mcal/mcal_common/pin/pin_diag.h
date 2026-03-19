#ifndef PIN_GENERAL_DIAG_H
#define PIN_GENERAL_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "pin_types.h"

#ifdef HAS_PIN_CUSTOM
#include "pin_custom_diag.h"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_PIN
#error "+HAS_PIN"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

#ifndef HAS_PIN_DIAG
#error "+HAS_PIN_DIAG"
#endif

const char* PinConfToStr(const PinConfig_t* Config);

const char* PinAltFunToStr(uint8_t code);
const char* PinAlterFunToStr(uint8_t code);
#ifdef HAS_EXT_INT
const char* PinEdgeToStr(PinIntEdge_t code);
#endif
const char* PinDirToStr(PinDir_t code);
const char* PinFunToStr(PinPinFunction_t function);
const char* PinLevelToStr(PinLogicLevel_t code);
const char* PinModeToStr(PinApiMode_t code);
const char* PinOutTypeToStr(uint8_t code);
const char* PinPadToStr(uint8_t pad);
const char* PinPadToStr(Pad_t pad);
const char* PinPad2WireName(uint8_t pad);
const char* PinPullToStr(PinPullMode_t code);
const char* PinSpeedToStr(uint8_t code);
const char* PinTypeToStr(uint8_t code);

bool pin_diag(char* key_word1, char* key_word2);
bool PinConfigDiag(const PinConfig_t* Config);

#endif /* PIN_GENERAL_DIAG_H  */
