#ifndef CONNECTIVITY_INIT_H
#define CONNECTIVITY_INIT_H

#include "std_includes.h"

#ifdef HAS_LOG
#include "log.h"
#define LOG_INIT  { .init_function = log_mcal_init, .name="Log",},
#else
#define LOG_INIT
#endif


#ifdef HAS_UART
#define TASK_UART TASK(UART)
#else
#define TASK_UART
#endif

#ifndef HAS_CONNECTIVITY
#error  "+HAS_CONNECTIVITY"
#endif

#ifdef HAS_LOG_UTILS
#include "writer_generic.h"
#define WRITER_INIT {.init_function=writer_init, .name="Writer",},
#else
#define WRITER_INIT
#endif

#ifdef HAS_PROTOCOLS
#include "protocols_init.h"
#else
#define PROTOCOLS_INIT
#endif

#ifdef HAS_SX1262
#define SX1262_INIT {.init_function=sx1262_init, .name="sx1262",},
#else
#define SX1262_INIT
#endif /*HAS_SX1262*/

#ifdef HAS_DW1000
#define DW1000_INIT {.init_function=dw1000_init, .name="dw1000",},
#else
#define DW1000_INIT
#endif /*HAS_DW1000*/

#ifdef HAS_DWM3000
#define DWM3000_INIT {.init_function=dwm3000_init, .name="dwm3000",},
#else
#define DWM3000_INIT
#endif /*HAS_DWM3000*/

#ifdef HAS_CAN
#include "can_mcal.h"
#define CAN_INIT {.init_function=can_init, .name="CAN",},
#else
#define CAN_INIT
#endif /*HAS_CAN*/

#ifdef HAS_LORA
#include "radio_drv.h"
#define LORA_INIT {.init_function=lora_init, .name="LoRa",},
#else
#define LORA_INIT
#endif /*HAS_LORA*/

#ifdef HAS_SERIAL
#include "scan_serial_port.h"
#define SERIAL_INIT {.init_function= serial_init, .name="Serial",},
#else
#define SERIAL_INIT
#endif /*HAS_SERIAL*/

#ifdef HAS_WIN
#include "win_utils.h"
#define WIN_COLOR_INIT {.init_function=win_color_init, .name="WinColor",},
#else
#define WIN_COLOR_INIT
#endif

#define CONNECTIVITY_INIT            \
    INTERFACES_INIT                  \
    SERIAL_INIT                      \
    PROTOCOLS_INIT

#ifdef HAS_SUPER_CYCLE
void super_connectivity_loop(uint64_t loop_start_time_us) ;
#endif /*SUPER_LOOP*/

#endif /* CONNECTIVITY_INIT_H */
