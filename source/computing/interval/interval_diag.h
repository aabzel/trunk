#ifndef INTERVAL_DIAG_H
#define INTERVAL_DIAG_H


#include "std_includes.h"
#include "interval_types.h"
#include "log.h"

const char* BracketToStr(const IntervalPoint_t type);
const char* DotToStr(const IntervalPoints_t * const dot);
bool IntervalDiagPoints(const IntervalPoints_t *const Point, const  uint32_t cnt);
bool IntervalEDiag(log_level_t level, char* prefix, const IntervalE_t* const interval);
bool IntervalSDiag(log_level_t level, char* prefix, const IntervalS_t* const interval);
#endif
