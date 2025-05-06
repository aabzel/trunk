#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "serial_port_types.h"
#include "serial_port_config.h"
#ifdef HAS_SERIAL_PORT_DIAG
#include "serial_port_diag.h"
#endif

SerialPortHandle_t* SerialPortGetNode(uint8_t num) ;
const SerialPortConfig_t* SerialPortGetConfig(uint8_t num) ;

bool serial_port_init_custom(void);

bool serial_port_mcal_init(void) ;
bool serial_port_init_one(uint8_t num);

bool serial_port_proc(void);
bool serial_port_proc_one(uint8_t num);

bool serial_port_send( uint8_t num , uint8_t* array, uint32_t array_len) ;

#ifdef __cplusplus
}
#endif

#endif /* SERIAL_PORT_H */
