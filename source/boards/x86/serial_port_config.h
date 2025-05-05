#ifndef SERIAL_PORT_CONFIG_H
#define SERIAL_PORT_CONFIG_H

#include "std_includes.h"
#include "serial_port_types.h"

#ifndef HAS_SERIAL_PORT
#error " +HAS_SERIAL_PORT"
#endif

extern const SerialPortConfig_t SerialPortConfig[];
extern SerialPortHandle_t SerialPortInstance[];

uint32_t serial_port_get_cnt(void);

#endif /* SERIAL_PORT_CONFIG_H */
