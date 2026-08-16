#ifndef BACK_COUNT_CONFIG_H
#define BACK_COUNT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "back_count_types.h"
#include "back_count_dep.h"

typedef enum{
    BACK_COUNT_UNDEF = 0,
    BACK_COUNT_WIFI_AP ,
    BACK_COUNT_CNT,
}BackCountLegalNums_t;

extern const BackCountConfig_t BackCountConfig[];
extern BackCountHandle_t BackCountInstance[];

uint32_t back_count_get_cnt(void);


#ifdef __cplusplus
}
#endif

#endif /* BACK_COUNT_CONFIG_H */
