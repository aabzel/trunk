#ifndef TIM_CUSTOM_DIAG_H
#define TIM_CUSTOM_DIAG_H

#include "mcal_types.h"

extern const Reg32_t TimerRegs[];

uint32_t time_register_cnt(void);
char *TimDirToStr(uint8_t code);
const char* TimerInfoToStr(const TimerInfo_t* const Info) ;

#endif /* TIM_CUSTOM_DIAG_H  */
