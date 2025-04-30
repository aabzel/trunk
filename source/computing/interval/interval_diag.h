#ifndef INTERVAL_DIAG_H
#define INTERVAL_DIAG_H

#include <stdbool.h>

#include "interval_types.h"
#include "log.h"

bool IntervalEDiag(log_level_t level, char* prefix, const IntervalE_t* const interval);
bool IntervalSDiag(log_level_t level, char* prefix, const IntervalS_t* const interval);

#endif
