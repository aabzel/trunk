#ifndef HAL_STM_DIAG_H
#define HAL_STM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32fx_hal.h"
//#include "stm32fx_hal_def.h"
#include "std_includes.h"

const char* HalStatusToStr(const HAL_StatusTypeDef ret);

#if 0
#define assert_param( expr)                                                             \
                                   do{                                                  \
                                      if(0==(expr)){                                    \
                                        LOG_ERROR(SYS,"Assert! Line:%u", __LINE__);     \
                                        res = true;                                     \
                                      }                                                 \
                                   }while(0);
#endif

#ifdef __cplusplus
}
#endif

#endif /* HAL_STM_DIAG_H */
