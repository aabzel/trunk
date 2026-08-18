#ifndef BC127_DIAG_H
#define BC127_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "bc127_types.h"

const char* ErrorCodeToStr(uint16_t err_code);
char* DigitalFormatToStr(uint8_t code);
char* Bc127I2sBusRoleToStr(uint8_t code);
char* JustifyFormatToStr(uint8_t code);
char* JustifyResolutionToStr(uint8_t code);
char* StartSamplingToStr(uint8_t code);
char* CropToStr(uint8_t code);
char* AudioAttenuationToStr(uint8_t code);
char* ChannelPolarityToStr(uint8_t code);
char* LeftJustifyDelayToStr(uint8_t code);
bool parse_i2s_param2(uint32_t reg_val);

#endif /* BC127_DIAG_H  */
