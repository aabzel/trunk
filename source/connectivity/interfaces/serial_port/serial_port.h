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


const SerialPortConfig_t* SerialPortGetConfig(uint8_t num) ;
SerialPortHandle_t* SerialPortNumToNode(uint8_t com_num) ;
SerialPortHandle_t* SerialPortGetNode(uint8_t num) ;
uint8_t serial_port_com_to_num(const uint8_t com_port_num);
uint8_t serial_num_to_port_com(const uint8_t num);

bool serial_port_init_custom(void);
bool serial_port_mcal_init(void) ;


bool serial_port_check(uint8_t num);
bool serial_port_scan_ports(void);
bool serial_port_init_one(uint8_t num);
bool serial_port_re_init_one(const uint8_t num,
                             const uint8_t com_port_num,
                             const uint32_t bit_rate,
                             const uint32_t byte_tx_pause_ms) ;

bool serial_port_close(  uint8_t com_port_num);
bool serial_port_proc(void);
bool serial_port_proc_one(uint8_t num);

bool serial_port_send( uint8_t com_num , uint8_t* array, uint32_t array_len) ;

#ifdef __cplusplus
}
#endif

#endif /* SERIAL_PORT_H */
