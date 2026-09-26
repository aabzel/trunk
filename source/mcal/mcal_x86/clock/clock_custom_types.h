#ifndef CLOCK_CUSTOM_TYPES_H
#define CLOCK_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"
#include "clock_custom_const.h"
#include "microcontroller_types.h"

typedef struct {
    uint32_t* CLOCKx;
    bool valid;
}ClockInfo_t;






#define CLOCK_CUSTOM_TYPES     uint32_t* CLOCKx;



#ifdef __cplusplus
}
#endif

#endif // CLOCK_CUSTOM_TYPES_H
