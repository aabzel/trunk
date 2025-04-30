#ifndef AT32F435ZM_H
#define AT32F435ZM_H

#include "at32f435zm_const.h"

#ifdef HAS_AT32F43X_FIRMWARE_LIB
#include "at32f435x.h"
#include "at32f435_437_misc.h"
#endif

#ifdef HAS_DIAG
#include "at32f435zm_diag.h"
#endif

#ifdef HAS_EHAL
void SystemInit(void);
#endif


#endif /* AT32F435ZM_H */
