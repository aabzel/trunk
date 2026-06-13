#ifndef RUNNING_LINE_CONFIG_H
#define RUNNING_LINE_CONFIG_H

#include "std_includes.h"
#include "running_line_types.h"

extern const RunningLineConfig_t RunningLineConfig[];
extern RunningLineHandle_t RunningLineInstance[];

uint32_t running_line_get_cnt(void);

#endif /* RUNNING_LINE_CONFIG_H */
