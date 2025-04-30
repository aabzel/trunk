#ifndef INTERFACES_TASKS_H
#define INTERFACES_TASKS_H

#ifdef HAS_BLUETOOTH_PROC
#define BLUETOOTH_TASK {.name="BlueTooth", .period_us=BLUETOOTH_PERIOD_US, .limiter.function=bluetooth_process,},
#else
#define BLUETOOTH_TASK
#endif

#ifdef HAS_CAN_HEARTBEAT_PROC
#include "can_mcal.h"
#define CAN_HEARTBEAT_TASK  \
   {.name="CAN_HB", .period_us=CAN_HEARTBEAT_PERIOD_US, .limiter.function=can_heartbeat_proc,},
#else
#define CAN_HEARTBEAT_TASK
#endif

#ifdef HAS_CAN_PROC
#include "can_mcal.h"
#define CAN_TASK  \
    CAN_HEARTBEAT_TASK \
    {.name="CAN", .period_us=CAN_PERIOD_US, .limiter.function=can_proc,},
#else
#define CAN_TASK
#endif

#ifdef HAS_RF_PROC
#define RF_TASK {.name="RF", .period_us=RF_PERIOD_US, .limiter.function=rf_process,},
#else
#define RF_TASK
#endif

#ifdef HAS_LORA_PROC
#include "lora_drv.h"
#define LORA_TASK {.name="LORA", .period_us=LORA_PERIOD_US, .limiter.function=lora_process,},
#else
#define LORA_TASK
#endif

#ifdef HAS_QSPI_PROC
#define QSPI_TASK {.name="QSPI", .period_us=QSPI_PERIOD_US, .limiter.function=qspi_process,},
#else
#define QSPI_TASK
#endif

#ifdef HAS_I2S_PROC
#include "i2s_mcal.h"
#define I2S_TASK {.name="I2S", .period_us=I2S_PERIOD_US, .limiter.function=i2s_proc,},
#else
#define I2S_TASK
#endif

#ifdef HAS_ONE_WIRE_PROC
#define ONE_WIRE_TASK {.name="ONE_WIRE", .period_us=ONE_WIRE_PERIOD_US, .limiter.function=one_wire_proc,},
#else
#define ONE_WIRE_TASK
#endif

#ifdef HAS_RF_PROC
#define RF_TASKS  {.name="RF", .period_us=RF_PERIOD_US, .limiter.function=rf_process,},
#else
#define RF_TASKS
#endif

#ifdef HAS_SPI_PROC
#include "spi_mcal.h"
#define SPI_TASKS {.name="SPI", .period_us=SPI_PERIOD_US, .limiter.function=spi_process,},
#else
#define SPI_TASKS
#endif

#ifdef HAS_RS485_PROC
#include "rs485_mcal.h"
#define RS485_TASKS {.name="RS485", .period_us=RS485_PERIOD_US, .limiter.function=rs485_proc,},
#else
#define RS485_TASKS
#endif

#ifdef HAS_RS232_PROC
#include "rs232_mcal.h"
#define RS232_TASK  {.name="RS232", .period_us=RS232_PERIOD_US, .limiter.function=rs232_proc,},
#else
#define RS232_TASK
#endif

#ifdef HAS_SDIO_PROC
#include "sdio_mcal.h"
#define SDIO_TASKS  {.name="SDIO", .period_us=SDIO_PERIOD_US, .limiter.function=sdio_proc,},
#else
#define SDIO_TASKS
#endif

#ifdef HAS_SWD_PROC
#include "swd_mcal.h"
#define SWD_TASKS {.name="SWD", .period_us=SWD_PERIOD_US, .limiter.function=swd_process,},
#else
#define SWD_TASKS
#endif

#ifdef HAS_USB_HOST_PROC
#include "usb_host.h"
#define USB_HOST_TASK {.name="USB_HOST", .period_us=USB_HOST_PERIOD_US, .limiter.function=usb_host_process,},
#else
#define USB_HOST_TASK
#endif

#ifdef HAS_UWB_PROC
#include "uwb_if.h"
#define UWB_TASK {.name="UWB", .period_us=UWB_PERIOD_US, .limiter.function=uwb_process,},
#else
#define UWB_TASK
#endif

#ifdef HAS_SOCKET_PROC
#include "socket_if.h"
#define SOCKET_TASK {.name="Socket", .period_us=SOCKET_PERIOD_US, .limiter.function=socket_proc,},
#else
#define SOCKET_TASK
#endif


#define USB_TASKS USB_HOST_TASK

#define CONNECTIVITY_WIRELESS_TASKS    \
    BLUETOOTH_TASK                     \
    LORA_TASK                          \
    RF_TASKS                           \
    UWB_TASK

#define CONNECTIVITY_WIRE_TASKS  \
    CAN_TASK                     \
    RF_TASK                      \
    ONE_WIRE_TASK                \
    QSPI_TASK                    \
    RS232_TASK                   \
    RS485_TASKS                  \
    SDIO_TASKS                   \
    SWD_TASKS                    \
    USB_TASKS

#define INTERFACES_TASKS         \
    CONNECTIVITY_WIRE_TASKS      \
    CONNECTIVITY_WIRELESS_TASKS  \
    SOCKET_TASK

#endif /* INTERFACES_TASKS_H */
