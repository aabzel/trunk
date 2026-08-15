#ifndef SONAR_DIAG_H
#define SONAR_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sonar_types.h"

bool sonar_diag(void);
bool sonar_diag_one(uint8_t num);
bool SonarDiag(const SonarHandle_t* const Node);
const char* SonarNodeToStr(const SonarHandle_t* const Node);
const char* SonarBestCorrelationToStr(const SonarCorrelationInfo_t * const Info) ;
const char* SonarConfigToStr(const SonarConfig_t* const Config);
const char* SonarChirpParamToStr(const SonarChirpParam_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* SONAR_DIAG_H */
