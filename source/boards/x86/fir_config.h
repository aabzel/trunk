#ifndef FIR_CONFIG_H
#define FIR_CONFIG_H

#include "std_includes.h"
#include "fir_types.h"
#include "fir_dep.h"

typedef enum {
#ifdef HAS_PHASE_DETECTOR
    FIR_MUN_LO_PHASE ,
#endif

#ifdef HAS_SONAR
    FIR_MUN_CHIRP_CORRELATION ,
#endif

#ifdef HAS_SDR
    FIR_MUN_I,
    FIR_MUN_Q,
#endif

#ifdef HAS_SOUND_LOCALIZATION
    FIR_MUN_SOUND_DIR ,
#endif

    FIR_MUN_CNT,
}FirLegalNums_t;

extern const FirConfig_t FirConfig[];
extern FirHandle_t FirInstance[];

uint32_t fir_get_cnt(void);

#endif /* FIR_CONFIG_H */
