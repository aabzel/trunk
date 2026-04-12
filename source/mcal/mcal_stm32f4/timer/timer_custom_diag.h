#ifndef TIM_CUSTOM_DIAG_H
#define TIM_CUSTOM_DIAG_H

#include "mcal_types.h"
#include "timer_custom_types.h"

extern const Reg32_t TimerRegs[];

bool timer_diag_reg_fields(uint8_t num);
uint32_t time_register_cnt(void);
char *TimDirToStr(uint8_t code);
const char* TimerInfoToStr(const TimerInfo_t* const Info) ;
bool timer_diag_reg_ccmr1(const uint32_t ccmr1) ;
bool timer_diag_reg_ccmr2(const uint32_t ccmr2);

#endif /* TIM_CUSTOM_DIAG_H  */
