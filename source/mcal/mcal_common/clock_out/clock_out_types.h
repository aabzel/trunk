#ifndef CLOCK_OUT_TYPES_H
#define CLOCK_OUT_TYPES_H

#include "clock_out_const.h"
#include "std_includes.h"

typedef struct{
	uint8_t num;
	uint8_t channel;
	ClockOutBus_t clock_bus;
    uint32_t divider;
    bool valid;
    char *name;
}ClockOutConfig_t;

typedef struct{
	uint8_t num;
	uint8_t channel;
    uint32_t clock_bus;
    uint32_t divider;
    bool valid;
    char *name;
}ClockOutHandle_t;


#endif /* CLOCK_OUT_TYPES_H  */
