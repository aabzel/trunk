#include "system.h"

#include <stdio.h>
#include <string.h>

#include "common_functions.h"
#include "std_includes.h"
#include "system_init.h"

#ifdef HAS_INTERFACES
#include "if_config.h"
#endif

#ifdef HAS_WATCHDOG
#include "watchdog_mcal.h"
#endif

#ifdef HAS_RADIO
#include "radio_mcal.h"
#endif

#ifdef HAS_CAN
#include "can_if_drv.h"
#endif

#ifdef HAS_RS232
#include "rs232_mcal.h"
#endif

#ifdef HAS_SPI
#include "spi_mcal.h"
#endif

#ifdef HAS_RTCM3
#include "rtcm3_protocol.h"
#endif

#ifdef HAS_UWB
#include "uwb_if.h"
#endif /*HAS_UWB*/

#ifdef HAS_ADT
#include "adt_init.h"
#else
#define ADT_INIT
#endif

#ifdef HAS_CONNECTIVITY
#include "connectivity_init.h"
#else
#define CONNECTIVITY_INIT
#endif

#ifdef HAS_STORAGE
#include "storage_init.h"
#else
#define STORAGE_INIT
#endif

#ifdef HAS_CONTROL
#include "control_init.h"
#else
#define CONTROL_INIT
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_MICROCONTROLLER
#include "sys_config.h"
#endif

#ifdef HAS_UART
#include "uart_mcal.h"
#endif

#ifdef HAS_TBFP
#include "tbfp.h"
#endif

#ifdef HAS_SYSTEM_DIAG
#include "system_diag.h"
#endif

#ifdef HAS_BOOTLOADER
//#error "That API only for Generic"
#endif

#ifdef HAS_CORE
#include "core_driver.h"
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
#endif /*HAS_SOFTWARE_TIMER*/

#ifdef HAS_SW_DAC
#include "sw_dac_drv.h"
#define SW_DAC_INIT                                                                                                    \
    {                                                                                                                  \
        .init_function = sw_dac_init,                                                                                  \
        .name = "DACsw",                                                                                               \
    },
#else
#define SW_DAC_INIT
#endif /*HAS_SW_DAC*/

#ifdef HAS_ADC
#include "adc_drv.h"
#define ADC_INIT                                                                                                       \
    {                                                                                                                  \
        .init_function = adc_init,                                                                                     \
        .name = "Adc",                                                                                                 \
    },
#else
#define ADC_INIT
#endif /*HAS_GPIO*/

#if 0
#ifdef HAS_MICROCONTROLLER
#include "board_config.h"
#define BOARD_INIT                                                                                                     \
    {                                                                                                                  \
        .init_function = board_init,                                                                                   \
        .name = "board",                                                                                               \
    },
#else
#define BOARD_INIT
#endif /*HAS_MICROCONTROLLER*/
#endif

#ifdef HAS_MICROCONTROLLER
#include "hw_init.h"
#else
#define HW_INIT
#endif

#ifdef HAS_GAMES
#include "games_init.h"
#else
#define GAMES_INIT
#endif

#ifdef HAS_MCAL
#include "mcal_init.h"
#else
#define MCAL_INIT
#endif

#ifdef HAS_PROTOCOLS
#include "protocols_init.h"
#else
#define PROTOCOLS_INIT
#endif

#ifdef HAS_SOCKET
#include "interfaces_init.h"
#else
#define SOCKET_INIT
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#define SYS_TIME_INIT                                                                                                  \
    {                                                                                                                  \
        .init_function = time_mcal_init,                                                                               \
        .name = "Time",                                                                                                \
    },
#else
#define SYS_TIME_INIT
#endif /**/

#ifdef HAS_INTERFACES
#include "interfaces_init.h"
#else
#define HW_WIRELESS_INTERFACES_INIT
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
#endif /*HAS_UNIT_TEST*/

#include "sw_init.h"

/*Order matter!*/
const SystemInitInstance_t SystemInitInstance[] = {INIT_FUNCTIONS};

System_t System = {
    .init = false,
    .init_finish = false,
};

uint32_t system_init_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(SystemInitInstance);
    return cnt;
}

#ifdef HAS_SYSTEM_EXT
static bool sys_init_is_uniq_node(const SystemInitInstance_t* const Node) {
    bool res = false;
    uint32_t init_cnt = system_init_get_cnt();
    uint32_t spot_cnt = 0;
    uint32_t i = 0;

    for(i = 0; i < init_cnt; i++) {
        if(SystemInitInstance[i].init_function == Node->init_function) {
            spot_cnt++;
        }
    }

    if(1 == spot_cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
#endif

#ifdef HAS_SYSTEM_EXT
bool system_init_array_uniq(void) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok = 0;
    uint32_t init_cnt = system_init_get_cnt();
    for(i = 0; i < init_cnt; i++) {
        res = sys_init_is_uniq_node(&SystemInitInstance[i]);
        if(res) {
            ok++;
        } else {
#ifdef HAS_LOG
            LOG_ERROR(SYS, "DoubleInit %u=[%s]", i, SystemInitInstance[i].name);
#endif
        }
    }

    if(init_cnt == ok) {
        res = true;
    } else {
        res = false;
    }

    return res;
}
#endif

uint32_t send_err_cnt = 0;

bool system_init(void) {
    bool res = true;
    // super_loop_run = false;
    System.init = false;
    System.init_finish = false;
#ifdef HAS_CORTEX_M4
    low_stack = (uint8_t*)RAM_END;
#endif /*HAS_CORTEX_M4*/
    uint32_t init_cnt = system_init_get_cnt();

    if(init_cnt) {
        /*init from array */
#ifdef HAS_LOG
        char InitOrder[200] = {0};
        strcpy(InitOrder, "");
#endif

        uint32_t i = 0;
        uint32_t ok = 0;
        for(i = 0; i < init_cnt; i++) {
#ifdef HAS_WATCHDOG
            res = watchdog_proc();
#endif
            res = SystemInitInstance[i].init_function();
            if(res) {
                ok++;
            }
#ifdef HAS_LOG
            res = try_init(res, SystemInitInstance[i].name);
#endif

#ifdef HAS_LOG
            cli_printf("%u:----^" CRLF, i + 1);
#endif

#ifdef HAS_LOG
            snprintf(InitOrder, sizeof(InitOrder), "%s%s,", InitOrder, SystemInitInstance[i].name);
#endif
        } // for(i = 0; i < init_cnt; i++)
#ifdef HAS_LOG
        LOG_INFO(SYS, "InitOrder:[%s]", InitOrder);
#endif
        // led_mono_ctrl(2, true);
        if(ok == init_cnt) {
            res = true;
#ifdef HAS_LOG
            LOG_INFO(SYS, "InitComplete %u", init_cnt);
#endif
            System.init = true;
        } else {
            System.init = false;
            uint32_t error_cnt = init_cnt - ok;
            (void)error_cnt;
            res = false;
            double init_compleetness = 100.0 * ((double)ok) / ((double)init_cnt);
            (void)init_compleetness;
#ifdef HAS_LOG
            LOG_ERROR(SYS, "InitInComplete:%u/%u,Only:%5.2f %%,Err:%u", ok, init_cnt, init_compleetness, error_cnt);
#endif
        }

#ifdef HAS_SYSTEM_EXT
        bool all_uniq = system_init_array_uniq();
#ifdef HAS_LOG
        log_info_res(SYS, all_uniq, "CheckUniqInit");
#endif
        res = res && all_uniq;
#endif /*HAS_SYSTEM_EXT*/
    }

    System.init_finish = true;
#ifdef HAS_TI
    Board_init();
    /* Start NoRTOS */
    NoRTOS_start();
#endif /*HAS_TI*/

#ifdef HAS_LOG
    LOG_INFO(SYS, "InitCnt:%u", init_cnt);
#endif
    return res;
}

BuildType_t system_get_prog_type(void) {
    BuildType_t FwType = BUILD_TYPE_UNDEF;
#ifdef HAS_MBR
    FwType = BUILD_TYPE_MBR;
#endif /*HAS_MBR*/

#ifdef HAS_BOOTLOADER
    FwType = BUILD_TYPE_BOOTLOADER;
#endif /*HAS_BOOTLOADER*/

#ifdef HAS_GENERIC
    FwType = BUILD_TYPE_GENERIC;
#endif /*HAS_GENERIC*/
    return FwType;
}
