#include "interval_diag.h"

#include "interval_types.h"
#include "log.h"

bool IntervalEDiag(log_level_t level, char* prefix, const IntervalE_t* const interval) {
    bool res = false;
    if(interval) {
        log_write(level, INTERVAL, "%s [%u...%u]", prefix, interval->start, interval->end);
        res = false;
    }
    return res;
}

bool IntervalSDiag(log_level_t level, char* prefix, const IntervalS_t* const interval) {
    bool res = false;
    if(interval) {
        log_write(level, INTERVAL, "%s [%u:+%u", prefix, interval->start, interval->size);
        res = false;
    }
    return res;
}
