#ifndef YTM32B1ME05G0MLQ_H
#define YTM32B1ME05G0MLQ_H

#include "ytm32b1me05g0mlq_const.h"
#ifdef HAS_YTM32B1ME0_1_3_1
#include "YTM32B1ME0.h"
#endif

#ifdef HAS_CMSIS
//#include "core_cm33.h"
#endif

#ifdef HAS_DIAG
#include "ytm32b1me05g0mlq_diag.h"
#endif

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

/*MBR does not need GPIO*/
#if defined(HAS_GPIO) && defined(HAS_PINS)
//extern const PinData_t PinConfig[];
//uint16_t pin_get_cnt(void);
#endif



#endif /* YTM32B1ME05G0MLQ_H */
