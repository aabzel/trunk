#ifndef HAL_DIAG_H
#define HAL_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"

#include <stdbool.h>
#include <stdint.h>

const char* HalStatus2Str(HAL_StatusTypeDef code);

#if 0
#define assert_param( expr)                                                    \
                                   do{                                                \
                                      if(0==(expr)){                                    \
	                                      LOG_ERROR(SYS,"Assert! Line:%u", __LINE__); \
	                                      res = true;                                 \
                                      }                                               \
                                   }while(0);
#endif

#ifdef __cplusplus
}
#endif

#endif /* HAL_DIAG_H */
