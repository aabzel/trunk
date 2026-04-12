#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H


#ifdef HAS_ADT
#include "adt_init.h"
#else
#define ADT_INIT
#endif

#ifdef HAS_ASICS
#include "asics_init.h"
#else
#define ASICS_INIT
#endif

#ifdef HAS_APPLICATIONS
#include "applications_init.h"
#else
#define APPLICATIONS_INIT
#endif

#ifdef HAS_CONNECTIVITY
#include "connectivity_init.h"
#else
#define CONNECTIVITY_INIT
#define WIN_COLOR_INIT
#define LOG_INIT
#define LOG_ENABLE
#define LOG_DISABLE_INIT
#define WRITER_INIT
#endif

#ifdef HAS_CONTROL
#include "control_init.h"
#else
#define CONTROL_INIT
#endif

#ifdef HAS_MICROCONTROLLER
#include "hw_init.h"
#else
#define HW_INIT
#endif

#ifdef HAS_MCAL
#include "mcal_init.h"
#else
#define MCAL_INIT
#endif


#ifdef HAS_MICROCONTROLLER
#include "board_config.h"

#ifdef HAS_LOG
#define BOARD_INIT_NAME .name = "Board",
#else
#define BOARD_INIT_NAME
#endif

#define BOARD_INIT                                     \
    {                                                  \
        .init_function = board_init,                   \
		BOARD_INIT_NAME                                \
    },

#else
#define BOARD_INIT
#endif

#ifdef HAS_START_PAUSE
#include "clock_mcal.h"
//        .name = "StartPause",
#define START_PAUSE_INIT                                   \
    {                                                      \
        .init_function = clock_start_pause_init,           \
    },
#else
#define START_PAUSE_INIT
#endif

#ifdef HAS_STREAM
#include "debug_info.h"
#define SYSTEM_INFO                                    \
    {                                                   \
        .init_function = print_sys_info,                 \
        .name = "SysInfo",                              \
    },
#else
#define SYSTEM_INFO
#endif

#ifdef HAS_STREAM
#include "debug_info.h"
#define VERSION_INFO                                    \
    {                                                   \
        .init_function = print_version,                 \
        .name = "Version",                              \
    },
#else
#define VERSION_INFO
#endif

#ifdef HAS_INTERFACES
#include "interfaces_init.h"
#else
#define INTERFACES_INIT
#endif

#ifdef HAS_GAMES
#include "games_init.h"
#else
#define GAMES_INIT
#endif


#ifdef HAS_CORE
#include "core_init.h"
#else
#define CORE_INIT
#endif

#ifdef HAS_PROTOCOLS
#include "protocols_init.h"
#else
#define PROTOCOLS_INIT
#endif

#ifdef HAS_SOFTWARE_TIMER
#include "software_timer.h"
#define SOFTWARE_TIMER_INIT                                                                                            \
    {                                                                                                                  \
        .init_function = sw_timer_init,                                                                                \
        .name = "SwTimer",                                                                                             \
    },
#else
#define SOFTWARE_TIMER_INIT
#endif /**/

#ifdef HAS_SW_COMPONENT
#include "sw_component_mcal.h"

#ifdef HAS_LOG
#define SW_COMPONENT_NAME .name = "SwComponent",
#else
#define SW_COMPONENT_NAME
#endif

#define SW_COMPONENT_INIT                                                                                              \
    {                                                                                                                  \
        .init_function = sw_component_mcal_init,                                                                       \
        SW_COMPONENT_NAME                                                                                              \
    },
#else
#define SW_COMPONENT_INIT
#endif /*HAS_SW_COMPONENT*/

#ifdef HAS_STORAGE
#include "storage_init.h"
#else
#define STORAGE_INIT
#define LITTLE_FS_INIT
#define STORAGE_SW_INIT
#define STORE_FS_INIT
#endif

#ifdef HAS_SOCKET
#include "interfaces_init.h"
#else
#define SOCKET_INIT
#endif

#ifdef HAS_TIME
#include "time_mcal.h"

#ifdef HAS_LOG
#define TIME_INIT_NAME .name = "Time",
#else
#define TIME_INIT_NAME
#endif

#define TIME_MCAL_INIT   {.init_function = time_mcal_init, TIME_INIT_NAME},
#else
#define TIME_MCAL_INIT
#endif

#ifdef HAS_FPU
#include "core_driver.h"

#ifdef HAS_LOG
#define FPU_NAME  .name="Fpu",
#else
#define FPU_NAME
#endif

#define FPU_INIT   {.init_function = fpu_init, FPU_NAME},
#else
#define FPU_INIT
#endif

#ifdef HAS_CORTEX_M4
#include "cortex_m4_driver.h"

#ifdef HAS_LOG
#define CORTEX_M4_INIT_NAME .name = "ISRTable",
#else
#define CORTEX_M4_INIT_NAME
#endif

#define ISR_VECTOR_TABLE_INIT {.init_function=cortex_m4_init_isr_vector, CORTEX_M4_INIT_NAME},
#else
#define ISR_VECTOR_TABLE_INIT
#endif

#if defined(HAS_LOG) && defined(HAS_UART)
#include "uart_mcal.h"
#define PRINT_BANNER_INIT {.init_function=print_hello_banner, .name="Banner",},
#else
#define PRINT_BANNER_INIT
#endif

#ifdef HAS_UART_BANNER
#include "uart_mcal.h"

#ifdef HAS_LOG
#define BANNER_INIT_NAME .name = "Banner",
#else
#define BANNER_INIT_NAME
#endif


#define UART_BANNER_INIT  {.init_function = uart_banner_init, BANNER_INIT_NAME},
#else
#define UART_BANNER_INIT
#endif


#ifdef HAS_BOOTLOADER
#include "bootloader.h"

#ifdef HAS_LOG
#define BOOTLOADER_INIT_NAME .name = "BootLoader",
#else
#define BOOTLOADER_INIT_NAME
#endif

#define BOOTLOADER_INIT  {.init_function = bootloader_init,BOOTLOADER_INIT_NAME},
#else
#define BOOTLOADER_INIT
#endif

#ifdef USE_HAL_DRIVER
#include "hal_mcal.h"

#ifdef HAS_LOG
#define HAL_INIT_NAME .name = "Hal",
#else
#define HAL_INIT_NAME
#endif

#define HAL_INIT {.init_function=hal_init, HAL_INIT_NAME},
#else
#define HAL_INIT
#endif

#ifdef HAL_SYSTICK
#include "systick_custom.h"
#define SYS_TICK_HAL_SUSPEND_INIT   {.init_function=systick_hal_suspend, .name="SysTickStop",},
#else
#define SYS_TICK_HAL_SUSPEND_INIT
#endif

#ifdef HAS_LOG
#define SYSREM_PREINIT_NANE .name = "SysPreInit",
#else
#define SYSREM_PREINIT_NANE
#endif

#if defined(HAS_SYSTEM) && defined(HAS_LOG)
#include "system.h"
#define SYSREM_PREINIT {.init_function=sysrem_pre_init, SYSREM_PREINIT_NANE},
#else
#define SYSREM_PREINIT
#endif

#ifdef HAS_THIRD_PARTY
#include "third_party_init.h"
#else
#define THIRD_PARTY_INIT
#endif

#ifdef HAS_UNIT_TEST
#include "unit_test.h"
#define UNIT_TEST_INIT                                                                                                 \
    {                                                                                                                  \
        .init_function = unit_test_init,                                                                               \
        .name = "UnitTest",                                                                                            \
    },
#else
#define UNIT_TEST_INIT
#endif

#ifdef HAS_SUPER_CYCLE
#include "super_cycle.h"

#ifdef HAS_LOG
#define SUPER_CYCLE_NANE .name = "SuperCycle",
#else
#define SUPER_CYCLE_NANE
#endif

#define SUPER_CYCLE_INIT                                 \
    {                                                    \
        .init_function = super_cycle_mcal_init,          \
        SUPER_CYCLE_NANE                                 \
    },
#else
#define SUPER_CYCLE_INIT
#endif

#include "sw_init.h"

#define PRE_INIT                                                                \
    SOFTWARE_TIMER_INIT                                                         \
    SW_DAC_INIT


/*Order matters!*/
#define INIT_FUNCTIONS                                                         \
    GPIO_INIT                                                                  \
    START_PAUSE_INIT                                                           \
    SYSREM_PREINIT                                                                   \
    FPU_INIT                                                                   \
    CORE_INIT                                                                  \
    SYS_TICK_HAL_SUSPEND_INIT                                                  \
    ISR_VECTOR_TABLE_INIT                                                      \
    UART_BANNER_INIT                                                           \
    HAL_INIT                                                                   \
    ADT_INIT                                                                   \
    LOG_INIT                                                                   \
    LOG_DISABLE_INIT                                                           \
    TIME_MCAL_INIT                                                             \
    WIN_COLOR_INIT                                                             \
    WRITER_INIT                                                                \
    LITTLE_FS_INIT                                                             \
    STORE_FS_INIT                                                              \
    MCAL_INIT                                                                  \
    PRE_INIT                                                                   \
    HW_INIT                                                                    \
    INTERFACES_INIT                                                            \
    PROTOCOLS_INIT                                                             \
    CONTROL_INIT                                                               \
    STORAGE_HW_INIT                                                            \
    STORAGE_SW_INIT                                                            \
    ASICS_INIT                                                                 \
    SW_INIT                                                                    \
    SOCKET_INIT                                                                \
    UNIT_TEST_INIT                                                             \
    ASICS_INIT                                                                 \
    BOARD_INIT                                                                 \
    THIRD_PARTY_INIT                                                           \
    GAMES_INIT                                                                 \
    SW_COMPONENT_INIT                                                          \
    APPLICATIONS_INIT                                                          \
    BOOTLOADER_INIT                                                            \
    SYSTEM_INFO                                                                \
    SUPER_CYCLE_INIT                                                           \
    VERSION_INFO                                                               \
    LOG_ENABLE


#endif /* SYSTEM_INIT_H  */
