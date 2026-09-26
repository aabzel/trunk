#ifndef TIMER_CUSTOM_DIAG_H
#define TIMER_CUSTOM_DIAG_H

#include <stdint.h>
#include <stdbool.h>

#include "timer_custom_types.h"

bool timer_reg_parse(uint8_t num);
bool timer_raw_reg_diag(uint8_t num) ;
const char* TimerInfoToStr(const TimerInfo_t * const Info);;

#endif /* TIMER_CUSTOM_DIAG_H  */
