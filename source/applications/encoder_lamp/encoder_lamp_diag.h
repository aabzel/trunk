#ifndef ENCODER_LAMP_DIAG_H
#define ENCODER_LAMP_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "encoder_lamp_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_ENCODER_LAMP
#error "+HAS_ENCODER_LAMP"
#endif

#ifndef HAS_ENCODER_LAMP_DIAG
#error "+HAS_ENCODER_LAMP_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool encoder_lamp_diag(void);
bool encoder_lamp_diag_one(uint8_t num);
bool encoder_lamp_raw_reg_diag(uint8_t num);
const char* EncoderLampConfigToStr(const EncoderLampConfig_t* const Config);
const char* EncoderLampNodeToStr(const EncoderLampHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* ENCODER_LAMP_DIAG_H  */
