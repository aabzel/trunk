#ifndef DWT_CONFIG_H
#define DWT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dwt_types.h"

typedef enum{
    DWT_NUM_CORE0,
    DWT_NUM_CNT,
}DwtLegalNums_t;

extern const DwtConfig_t DwtConfig[];
extern DwtHandle_t DwtInstance[];

uint32_t dwt_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* DWT_CONFIG_H */
