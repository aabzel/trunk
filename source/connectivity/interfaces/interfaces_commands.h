#ifndef INTERFACES_COMMANDS_H
#define INTERFACES_COMMANDS_H

#ifdef HAS_LOG
#include "log.h"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_INTERFACES
#error "+HAS_INTERFACES"
#endif

#ifndef HAS_INTERFACES_COMMANDS
#error "+HAS_INTERFACES_COMMANDS"
#endif

#ifdef HAS_BLUETOOTH_COMMANDS
#include "bluetooth_commands.h"
#else
#define BLUETOOTH_COMMANDS
#endif

#ifdef HAS_BLE_AUDIO_COMMANDS
#include "ble_audio_commands.h"
#else
#define BLE_AUDIO_COMMANDS
#endif

#ifdef HAS_DTMF_COMMANDS
#include "dtmf_commands.h"
#else
#define DTMF_COMMANDS
#endif

#ifdef HAS_SEGGER_RTT_COMMANDS
#include "segger_rtt_commands.h"
#else
#define SEGGER_RTT_COMMANDS
#endif

#ifdef HAS_LORA_COMMANDS
#include "lora_commands.h"
#else
#define LORA_COMMANDS
#endif

#ifdef HAS_SW_UART_COMMANDS
#include "sw_uart_commands.h"
#else
#define SW_UART_COMMANDS
#endif

#ifdef HAS_RS232_COMMANDS
#include "rs232_commands.h"
#else
#define RS232_COMMANDS
#endif

#ifdef HAS_RS485_COMMANDS
#include "rs485_commands.h"
#else
#define RS485_COMMANDS
#endif

#ifdef HAS_ONE_WIRE_COMMANDS
#include "1wire_commands.h"
#else
#define ONE_WIRE_COMMANDS
#endif

#ifdef HAS_SOCKET_COMMANDS
#include "socket_commands.h"
#else
#define SOCKET_COMMANDS
#endif

#ifdef HAS_SERIAL_PORT_COMMANDS
#include "serial_port_commands.h"
#else
#define SERIAL_PORT_COMMANDS
#endif

#ifdef HAS_WIFI_COMMANDS
#include "wifi_commands.h"
#else
#define WIFI_COMMANDS
#endif

#define INTERFACE_WIRELESS_COMMANDS      \
    BLUETOOTH_COMMANDS                   \
    LORA_COMMANDS                        \
    WIFI_COMMANDS                        \
    BLE_AUDIO_COMMANDS

#define INTERFACE_WIRED_COMMANDS      \
    SW_UART_COMMANDS                  \
    SEGGER_RTT_COMMANDS               \
    ONE_WIRE_COMMANDS                 \
    RS232_COMMANDS                    \
    RS485_COMMANDS                    \
    SERIAL_PORT_COMMANDS               
    
#define INTERFACES_COMMANDS              \
    INTERFACE_WIRELESS_COMMANDS          \
    INTERFACE_WIRED_COMMANDS             \
    DTMF_COMMANDS                        \
    SOCKET_COMMANDS                      

#endif /* INTERFACES_COMMANDS_H */
