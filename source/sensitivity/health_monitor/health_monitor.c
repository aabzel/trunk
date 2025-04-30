#include "health_monitor.h"

/* RTOS header files */

#include <stdbool.h>
#include <string.h>

#ifdef HAS_ADC
#include "adc_mcal.h"
#endif

#ifdef HAS_BOARD
#include "board_monitor.h"
#endif

#ifdef HAS_CLI
#include "cli_config.h"
#include "cli_drv.h"
#include "cli_general_config.h"
#endif

#ifdef HAS_GNSS
#include "gnss_diag.h"
#include "gnss_utils.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_ANT_MUX
#include "aerial_mux_drv.h"
#endif

#ifdef HAS_RTCM3
#include "rtcm3_protocol.h"
#endif

#ifdef HAS_TBFP
#include "tbfp.h"
#endif

#ifdef HAS_RADIO
#include "radio_drv.h"
#endif

#ifdef HAS_FDA801
#include "fda801_drv.h"
#endif

#ifdef HAS_NMEA
#include "nmea_protocol.h"
#endif

#ifdef HAS_SX1262
#include "sx1262_drv.h"
#endif

#include "sys_config.h"

#ifdef HAS_UBLOX
#include "ublox_driver.h"
#endif

#ifdef HAS_TIMER
#include "timer_mcal.h"
#endif

#ifdef HAS_WM8731
#include "wm8731_drv.h"
#endif /*HAS_WM8731*/

#ifdef HAS_UART
#include "uart_mcal.h"
#endif

#ifdef HAS_PARAM
#include "param_drv.h"
#endif

#if 0
#if(TBFP_MAX_PAYLOAD < RTCM3_RX_MAX_FRAME_SIZE) /*Compile error*/
#error "TBFP frame must be big enough to store RTCM3 frame"
#endif
#endif

HealthMon_t HealthMon = {
    .init_error = false,
    .power = false,
    .error_cnt = 0,
    .crc_error_cnt = 0,
    .error_messege = "",
};

#define MIM_LORA_THROUGHPUT_BYTE_S 1100

bool health_monotor_proc(void) {
    bool res = false;
#warning TODO run check functions in array of function pointers
#ifdef HAS_ADC
#ifdef CC42XX
    if(HealthMon.power) {
        float vKl30 = 0.0;
        vKl30 = adc_get_value_by_dio(DIO_KL30_ADC, true);
        if(vKl30 < KL30_UNDERVOL_ERRPR_THRESHOLD_V) {
#ifdef HAS_LOG
            LOG_ERROR(HMON, "vKl30 %7.3f<%7.3f too low", vKl30, KL30_UNDERVOL_ERRPR_THRESHOLD_V);
#endif
            res = false;
        } else {
            if(vKl30 < KL30_UNDERVOL_WARNING_THRESHOLD_V) {
#ifdef HAS_LOG
                LOG_WARNING(HMON, "vKl30 %7.3f<%7.3f low", vKl30, KL30_UNDERVOL_WARNING_THRESHOLD_V);
#endif
            }
            res = true;
        }
    }
#endif /*CC42XX*/
#endif /*HAS_ADC*/

#ifdef HAS_NMEA
    // res = nmea_check();
#endif

#ifdef HAS_FDA801
    res = fda801_check();
#endif

#ifdef HAS_WM8731_PROC
    res = wm8731_check(1);
#endif /*HAS_WM8731*/

    res = board_check();

#ifdef HAS_ANT_MUX
    res = ant_mux_check();
#endif

#ifdef HAS_TBFP
    res = tbfp_check();
#endif

#ifdef HAS_RTCM3
    res = rtcm3_check();
#endif

#ifdef HAS_SX1262
    res = sx1262_check();
#ifdef HAS_RTCM3
    res = rtcm3_check();
    if((Sx1262Instance.bit_rate / 8) < MIM_LORA_THROUGHPUT_BYTE_S) {
#ifdef HAS_LOG
        LOG_ERROR(HMON, "LoRaByteRate too low %f byte/s Need %u byte/s", Sx1262Instance.bit_rate / 8,
                  MIM_LORA_THROUGHPUT_BYTE_S);
#endif
        res = false;
    }
#endif
#endif

    if(HealthMon.init_error) {
        LOG_ERROR(HMON, "InitErrorIn:[%s]", HealthMon.error_messege);
    }

#ifdef HAS_LORA
    if(LoRaInterface.tx_err_cnt) {
#ifdef HAS_LOG
        LOG_DEBUG(HMON, "LoRaTxError %u", LoRaInterface.tx_err_cnt);
#endif
    }
#endif

#ifdef HAS_STACK_MONITOR
    float stack_precent = stack_used();
    if(60.0 < stack_precent) {
#ifdef HAS_LOG
        LOG_WARNING(HMON, "StackUsed:%f %%", stack_precent);
#endif /*HAS_LOG*/
        if(75.0 < stack_precent) {
#ifdef HAS_LOG
            LOG_ERROR(HMON, "StackUsed:%f %%", stack_precent);
#endif /*HAS_LOG*/
        }
    }
#endif /*HAS_STACK_MONITOR*/

#ifdef HAS_UART
    res = uart_check();
#endif /*HAS_UART*/

#ifdef HAS_RTCM3
    static uint32_t lora_lost_pkt_cnt_prev = 0;
    uint32_t lora_lost_pkt_cnt_diff = 0;
    lora_lost_pkt_cnt_diff = Rtcm3Protocol[IF_UART1].lost_pkt_cnt[IF_LORA] - lora_lost_pkt_cnt_prev;
    if(0 < lora_lost_pkt_cnt_diff) {
#ifdef HAS_LOG
        LOG_WARNING(HMON, "RTCM3 UART1 lost %u", lora_lost_pkt_cnt_diff);
#endif
    }
    lora_lost_pkt_cnt_prev = Rtcm3Protocol[IF_UART1].lost_pkt_cnt[IF_LORA];
#endif

#if defined(HAS_CHECK_TIME) && defined(HAS_NMEA) && defined(HAS_UBLOX)
    bool res_eq = is_time_date_equal(&NavInfo.date_time, &NmeaData.time_date);

    bool res_nm = is_valid_time_date(&NmeaData.time_date);
    bool res_ub = is_valid_time_date(&NavInfo.date_time);
    if((false == res_eq) && res_nm && res_nm) {
#ifdef HAS_LOG
        LOG_ERROR(HMON, "Nmea and UBX Time different");
        LOG_INFO(HMON, "Nmea:");
        print_time_date(&NmeaData.time_date);
        LOG_INFO(HMON, "UBX:");
        print_time_date(&NavInfo.date_time);
#endif
    }
#endif
    return res;
}

#ifdef HAS_HM_RTOS_TASK

/* XDC Module Headers */
static void health_monotor_thread(UArg a0, UArg a1) {
    LOG_NOTICE(HMON, "healthMonitorStart");
    for(;;) {
        health_monotor_proc();
        /*Wait 2000 ms*/
        Task_sleep(200000);
    }
}

#define HEALTH_MONOTOR_TASK_STACK_SIZE 2048
#define HEALTH_MONOTOR_TASK_PRIORITY 1
uint8_t HealthMonotorTaskStack[HEALTH_MONOTOR_TASK_STACK_SIZE];
Task_Struct HealthMonotorTask;

bool health_monotor_create_tirtos_task(void) {
    bool res = true;
    Task_Params taskParams;

    // Configure task
    Task_Params_init(&taskParams);
    taskParams.stack = HealthMonotorTaskStack;
    taskParams.stackSize = HEALTH_MONOTOR_TASK_STACK_SIZE;
    taskParams.priority = HEALTH_MONOTOR_TASK_PRIORITY;

    Task_construct(&HealthMonotorTask, health_monotor_thread, &taskParams, NULL);
    return res;
}
#endif /*HAS_HM_RTOS_TASK*/

bool health_monotor_init(void) {
    bool res = true;
    set_log_level(HMON, LOG_LEVEL_NOTICE);
    LOG_WARNING(HMON, "healthMonitorInit");
    /*DO NOT zero HealthMon structure in here!*/
#if defined(HAS_RTCM3) && defined(HAS_TBFP)
    if(TBFP_MAX_PAYLOAD < RTCM3_RX_MAX_FRAME_SIZE) {
        LOG_ERROR(HMON, "TBFPFrameMustBeBigEnoughToStoreRTCM3Frame TBFP:%u<RTCM3:%u", TBFP_MAX_PAYLOAD,
                  RTCM3_RX_MAX_FRAME_SIZE);
        res = false;
    } else {
        LOG_INFO(HMON, "TbfpRtcmFramesSizesOk RTCM3:%u<TBFP:%u", RTCM3_RX_MAX_FRAME_SIZE, TBFP_MAX_PAYLOAD);
    }
#endif
#ifdef HAS_RELAESE
    HealthMon.power = true;
#endif

#ifdef HAS_DEBUG
    HealthMon.power = false;
#endif
#ifdef HAS_HM_RTOS_TASK
    res = health_monotor_create_tirtos_task();
#endif
    return res;
}

bool health_monitor_reset(void) {
    bool res = true;
    HealthMon.init_error = false;
    return res;
}
