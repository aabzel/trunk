#ifndef INTERFACE_DRV_H
#define INTERFACE_DRV_H

#include "interfaces_init.h"
#include "interfaces_const.h"
#include "interfaces_diag.h"
#include "if_config.h"

bool sys_send_if(const  uint8_t* const array, const uint32_t len, const Interfaces_t interface_if, const IfRetx_t retx) ;

bool sys_available_interfaces(void) ;
bool interface_valid(Interfaces_t interface_if);
bool system_calc_byte_rate(void) ;

Interfaces_t InterfaceComPortToInterface(uint8_t com_port_num);

#ifdef HAS_HARVESTER_V1
bool sys_bypass_nmea_rs232(void);
#endif

#endif /* INTERFACE_DRV_H */
