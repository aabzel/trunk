#ifndef RUNNING_LINE_DIAG_H
#define RUNNING_LINE_DIAG_H

#include "std_includes.h"
#include "running_line_types.h"

const char* RunningLineConfigToStr(const RunningLineConfig_t* const Config);
const char* RunningLineNodeToStr(const RunningLineHandle_t* const Node);

bool running_line_diag(void);

#endif /* RUNNING_LINE_DIAG_H  */
