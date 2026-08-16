#ifndef SERIAL_PORT_DIAG_H
#define SERIAL_PORT_DIAG_H

#include "serial_port_types.h"

bool serial_port_diag(void);
const char* SerialPortNodeToStr(const SerialPortHandle_t* const Node);
const char* SerialPortConfigToStr(const SerialPortConfig_t* const Config);
const char* SerialPortErrorToStr(const uint32_t ret);

#endif /* SERIAL_PORT_DIAG_H  */
