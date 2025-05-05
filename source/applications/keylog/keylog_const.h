#ifndef KEYLOG_CONST_H
#define KEYLOG_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "time_mcal.h"

#define KEYLOG_HEAP_SIZE 200
#define KEYLOG_PERIOD_US MSEC_2_USEC(100)
#define KEYLOG_FILE "keLg.txt"

#ifdef __cplusplus
}
#endif

#endif /* KEYLOG_CONST_H */
