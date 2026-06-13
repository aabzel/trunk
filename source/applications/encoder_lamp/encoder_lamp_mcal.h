#ifndef ENCODER_LAMP_MCAL_H
#define ENCODER_LAMP_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "encoder_lamp_config.h"
#include "encoder_lamp_types.h"

#ifdef HAS_ENCODER_LAMP_DIAG
#include "encoder_lamp_diag.h"
#endif

/* API */
EncoderLampHandle_t* EncoderLampGetNode(uint8_t num);
const EncoderLampConfig_t* EncoderLampGetConfig(uint8_t num);
bool EncoderLampIsValidConfig(const EncoderLampConfig_t* const Config);

#ifdef HAS_ENCODER_LAMP_CUSTOM
const EncoderLampInfo_t* EncoderLampGetInfo(uint8_t num);
#endif

bool encoder_lamp_mcal_init(void);
bool encoder_lamp_init_custom(void);
bool encoder_lamp_init_common(const EncoderLampConfig_t* const Config, EncoderLampHandle_t* const Node);
bool encoder_lamp_init_node(EncoderLampHandle_t* const Node);
bool encoder_lamp_init_one(uint8_t num);

bool encoder_lamp_proc_one(uint8_t num);
bool encoder_lamp_proc(void);

/*setters*/

/*getters*/

#ifdef __cplusplus
}
#endif

#endif /* ENCODER_LAMP_MCAL_H */
