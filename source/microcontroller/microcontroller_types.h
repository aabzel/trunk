#ifndef MICROCONTROLLER_TYPES_H
#define MICROCONTROLLER_TYPES_H

#include "std_includes.h"
#include "microcontroller_const.h"

#ifdef HAS_AT32F413RC
#include "at32f413rc.h"
#endif

#ifdef HAS_AT32F413X
#ifdef HAS_EHAL
#include "at32f413_sfr.h"
#endif
#endif

#ifdef HAS_AT32F435ZM
#include "at32f435zm.h"
#endif

#ifdef HAS_AT32F437ZM
#include "at32f437zm.h"
#endif

#ifdef HAS_AT32F43X
#ifdef HAS_EHAL
#include "at32f43x_sfr.h"
#endif
#endif

#ifdef HAS_STM32F407ZG
#include "stm32f407zg.h"
#endif

#ifdef HAS_STM32F407VG
#include "stm32f407vg.h"
#endif

#ifdef HAS_YTM32B1ME05G0MLQ
#include "ytm32b1me05g0mlq.h"
#endif



typedef struct {
    bool valid ;
    uint32_t offset;
    char* name ;
}McuReg_t;


#endif /* MICROCONTROLLER_TYPES_H */
