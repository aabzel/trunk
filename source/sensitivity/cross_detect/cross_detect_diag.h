
#ifndef CROSS_DETECT_DIAG_H
#define CROSS_DETECT_DIAG_H

#include <stdbool.h>

#include "cross_detect_types.h"

const char* CrossDetectSolution2Str(CrossDetectSolution_t solution);
const char* CrossDetectState2Str(CrossDetectState_t state);
const char* CrossDetectRead2Str(CrossDetectGpioRead_t read);
const char* CrossDetectFaultToStr(CrossDetectFault_t fault);
bool CrossDetectDiagPair(const CrossDetectPairInfo_t* const pair);
bool cross_detect_diag(void);
bool cross_detect_pin_diag(const char* const key_word1, const char* const key_word2);
bool CrossDetectDiagFault(const CrossDetectHandle_t* const Node);
bool cross_detect_diag_lut(const char* const key_word1, const char* const key_word2);

#endif /* CROSS_DETECT_DIAG_H  */
