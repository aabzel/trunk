#ifndef AT32F413RC_H
#define AT32F413RC_H


//#include "at32f413rc_const.h"



#ifdef HAS_AT32F413_FIRMWARE_LIB
//#include <stdint.h>
#include "at32f413.h"
#else
void SystemInit (void);
#endif

#ifdef HAS_CMSIS
#include "core_cm4.h"
#endif

#ifdef HAS_DIAG
#include "at32f413rc_diag.h"
#endif

#ifdef HAS_MCAL_AT32
#include "at32f413_misc.h"
#endif


#ifdef HAS_GPIO
#include "gpio_types.h"
#endif



/*MBR does not need GPIO*/
#if defined(HAS_GPIO) && defined(HAS_PINS)
//extern const PinData_t PinConfig[];
//uint16_t pin_get_cnt(void);
#endif



#endif /* AT32F413RC_H */
