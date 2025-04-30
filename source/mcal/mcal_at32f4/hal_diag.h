#ifndef HAL_DIAG_H
#define HAL_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>
#include <stdint.h>

#include "artery_at32f4xx.h"
#include "at32_const.h"

#if 0
#define assert_param( expr)                                                             \
                                   do{                                                  \
                                      if(0==(expr)){                                    \
	                                      LOG_ERROR(SYS,"Assert!,Line:%u", __LINE__);   \
	                                      res = true;                                   \
                                      }                                                 \
                                   }while(0);
#endif



#ifdef __cplusplus
}
#endif

#endif /* HAL_DIAG_H */
