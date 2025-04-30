#ifndef RS485_CONFIG_H
#define RS485_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rs485_types.h"

extern Rs485Bus_t Rs485Bus;
extern ProtocolNode_t BusNet[];
extern const uint32_t BusNetConfig[];

uint32_t bus_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* RS485_CONFIG_H  */
