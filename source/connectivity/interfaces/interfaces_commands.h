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

#ifdef HAS_LORA_COMMANDS
#include "sx1262_lora_commands.h"
#else
#define SX1262_LORA_COMMANDS
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

#define INTERFACES_COMMANDS              \
    BLUETOOTH_COMMANDS                   \
    BLE_AUDIO_COMMANDS                   \
    DTMF_COMMANDS                        \
    ONE_WIRE_COMMANDS                    \
    SERIAL_PORT_COMMANDS                 \
    SOCKET_COMMANDS                      \
    RS232_COMMANDS                       \
    RS485_COMMANDS

#endif /* INTERFACES_COMMANDS_H */
