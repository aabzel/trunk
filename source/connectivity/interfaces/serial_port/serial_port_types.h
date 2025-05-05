#ifndef SERIAL_PORT_IF_TYPES_H
#define SERIAL_PORT_IF_TYPES_H

#include <windows.h>

#include "std_includes.h"
#include "serial_port_const.h"
#include "data_types.h"



#define SERIAL_PORT_COMMON_VARIABLES                 \
    uint8_t num;                                     \
    uint16_t com_port_num;                           \
    uint16_t bit_rate;                               \
    bool valid;

typedef struct {
    SERIAL_PORT_COMMON_VARIABLES
}SerialPortConfig_t;

typedef struct {
    SERIAL_PORT_COMMON_VARIABLES
    uint32_t rx_err_cnt;
    uint32_t rx_cnt;
    uint32_t tx_cnt;
    HANDLE hComm;
}SerialPortHandle_t;

#endif /* SERIAL_PORT_IF_TYPES_H  */
