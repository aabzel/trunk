#ifndef MANCHESTER_DECODE_CONFIG_H
#define MANCHESTER_DECODE_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "manchester_decode_types.h"
#include "manchester_decode_dep.h"

extern const ManchesterDecodeConfig_t ManchesterDecodeConfig[];
extern ManchesterDecodeHandle_t ManchesterDecodeInstance[];

uint32_t manchester_decode_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* MANCHESTER_DECODE_CONFIG_H */
