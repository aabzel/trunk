#ifndef HAL_DIAG_H
#define HAL_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

//#include "mik32_hal.h"

#include <stdbool.h>
#include <stdint.h>


#if 0
#define ASSERT_PARAM( expr)   \
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
