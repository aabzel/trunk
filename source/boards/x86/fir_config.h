#ifndef FIR_CONFIG_H
#define FIR_CONFIG_H

#include "std_includes.h"
#include "fir_types.h"
#include "fir_dep.h"

typedef enum {
    FIR_MUN_CHIRP_CORRELATION = 7,
	FIR_MUN_SOUND_DIR = 8,
}FirLegalNums_t;

extern const FirConfig_t FirConfig[];
extern FirHandle_t FirInstance[];

uint32_t fir_get_cnt(void);

#endif /* FIR_CONFIG_H */
