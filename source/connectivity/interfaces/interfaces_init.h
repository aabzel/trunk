#ifndef INTERFACES_INIT_H
#define INTERFACES_INIT_H

#include "std_includes.h"

#ifndef HAS_INTERFACES
#error  "+HAS_INTERFACES"
#endif

#ifdef HAS_BLE
#include "ble_drv.h"
#define BLE_INIT   {.init_function=ble_init, .name="BLE",},
#else
#define BLE_INIT
#endif

#ifdef HAS_RF
#define RF_INIT   {.init_function=rf_init, .name="RF",},
#else
#define RF_INIT
#endif

#ifdef HAS_RS232
#include "rs232_mcal.h"
#define RS232_INIT {.init_function=rs232_mcal_init, .name="RS232",},
#else
#define RS232_INIT
#endif

#ifdef HAS_RS485
#include "rs485_mcal.h"
#define RS485_INIT   {.init_function=rs485_mcal_init, .name="RS485",},
#else
#define RS485_INIT
#endif

#ifdef HAS_SEGGER_RTT
#include "segger_rtt_mcal.h"
#define SEGGER_RTT_INIT   {.init_function = segger_rtt_mcal_init, .name = "SEGGER_RTT",},
#else
#define SEGGER_RTT_INIT
#endif

/*Order matters*/
#define HW_WIRE_INTERFACES_INIT \
    SEGGER_RTT_INIT             \
    RS232_INIT                  \
    RS485_INIT

#ifdef HAS_DTMF
#include "dtmf_drv.h"
#define DTMF_INIT   {.init_function=dtmf_init, .name="DTMF",},
#else
#define DTMF_INIT
#endif

#ifdef HAS_SERIAL_PORT
#include "serial_port.h"
#define SERIAL_PORT_INIT {.init_function=serial_port_mcal_init, .name="SerialPort",},
#else
#define SERIAL_PORT_INIT
#endif


#ifdef HAS_SW_UART
#include "sw_uart_mcal.h"
#define SW_UART_INIT {.init_function=sw_uart_mcal_init, .name="SwUart",},
#else
#define SW_UART_INIT
#endif


#ifdef HAS_SOCKET
#include "socket_if.h"
#define SOCKET_INIT {.init_function=socket_init, .name="Socket",},
#else
#define SOCKET_INIT
#endif

/*Order matters*/
#define HW_WIRELESS_INTERFACES_INIT \
    SW_UART_INIT                    \
    DTMF_INIT                       \
    RF_INIT                         \
    LORA_INIT                       \
    WIFI_INIT                       \
    BLE_INIT

/*Order matters*/
#define INTERFACES_INIT             \
    SERIAL_PORT_INIT                \
    HW_WIRE_INTERFACES_INIT         \
    HW_WIRELESS_INTERFACES_INIT     \
    SOCKET_INIT


#ifdef HAS_SUPER_CYCLE
void super_interfaces_loop(uint64_t loop_start_time_us) ;
#endif

#endif /* INTERFACES_INIT_H */
