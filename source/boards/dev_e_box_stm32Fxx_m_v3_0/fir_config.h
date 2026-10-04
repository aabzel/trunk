#ifndef FIR_CONFIG_H
#define FIR_CONFIG_H

#include "std_includes.h"
#include "fir_types.h"
#include "fir_dep.h"

typedef enum {
#ifdef HAS_SONAR
    FIR_MUN_CHIRP_CORRELATION ,
#endif
    FIR_MUN_TEST1 ,
    FIR_MUN_TEST2 ,

    FIR_MUN_CNT,
}FirLegalNums_t;

extern const FirConfig_t FirConfig[];
extern FirHandle_t FirInstance[];

uint32_t fir_get_cnt(void);

#endif /* FIR_CONFIG_H */
