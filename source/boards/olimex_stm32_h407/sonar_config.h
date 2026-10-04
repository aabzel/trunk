#ifndef SONAR_CONFIG_H
#define SONAR_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sonar_types.h"

typedef enum{
    SONAR_NUM_CHIRP,
    SONAR_NUM_CNT
}SonarLegalNums_t;

extern const SonarConfig_t SonarConfig[];
extern SonarHandle_t SonarInstance[];

uint32_t sonar_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /*SONAR_CONFIG_H*/
