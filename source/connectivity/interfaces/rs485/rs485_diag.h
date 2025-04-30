#ifndef RS485_DIAG
#define RS485_DIAG

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "rs485_types.h"

bool rs485_diag(void);
const char* Rs485ToStr(const Rs485Config_t* const Config);

#ifdef __cplusplus
}
#endif

#endif /* RS485_DIAG  */
