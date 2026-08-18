#ifndef LORA_CONFIG_H
#define LORA_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lora_constants.h"

#define DFLT_LORA_BW LORA_BW_125
#define DFLT_SF SF7
#define DFLT_LORA_CR LORA_CR_4_8
#define DFLT_PREAMBLE_LEN 16
#define DFLT_LORA_SYNC_WORD 0x1424

#ifdef __cplusplus
}
#endif

#endif /* LORA_CONFIG_H */
