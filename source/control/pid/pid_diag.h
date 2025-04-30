#ifndef PID_DIAG_H
#define PID_DIAG_H

#include "pid_types.h"

bool pid_diag(char* key_word1, char* key_word2);
const char* PidConfigToStr(const PidConfig_t* const Config);
const char* PidNodeToStr(const PidHandle_t* const Node);

#endif /* PID_DIAG_H  */
