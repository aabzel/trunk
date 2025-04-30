#ifndef RS485_CONST_H
#define RS485_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rs485_dep.h"
#include "time_mcal.h"

#define RS485_BUS_MAX 256
#define RS485_PERIOD_US MSEC_2_USEC(5)
#define RS485_RX_TIMEOUT_MS SEC_2_USEC(3)


#ifdef __cplusplus
}
#endif

#endif /* RS485_CONST_H  */
