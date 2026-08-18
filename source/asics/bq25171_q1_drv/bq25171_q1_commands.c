#include "bq25171_q1_commands.h"

#include <gpio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAS_ADC
#include "adc_drv.h"
#endif /*HAS_ADC*/
#include "bq25171_q1_drv.h"
#include "convert.h"
#include "io_utils.h"
#include "log.h"
#include "sys_config.h"

static const char* bq25171_q1_stat2str(ChargingStatus_t mode) {
    const char* name = "undef";
    switch(mode) {
    case CHRG_STAT_NON_RECOV_FAULT:
        name = "NonRecovFault";
        break;
    case CHRG_STAT_INPROC:
        name = "IiProc";
        break;
    case CHRG_STAT_COMPLETED:
        name = "Completed";
        break;
    case CHRG_STAT_RECOV_FAULT:
        name = "RecovFault";
        break;
    default:
        break;
    }
    return name;
}

bool bq25171_q1_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
        uint32_t cen = 0;
#ifdef HAS_ADC
        float batt_vltage;
        batt_vltage = adc_get_value_by_dio(DIO_BATT_ADC, true);
        io_printf("Vbat: %f V" CRLF, batt_vltage);
#endif /*HAS_ADC*/
        cen = GPIO_readDio((uint32_t)DIO_GNSS_INT);
        io_printf("Charge %s" CRLF, (0 == cen) ? "Enable" : "Shutdown");
        ChargingStatus_t stat = bq25171_q1_get_status();
        io_printf("stat: 0x%u %s" CRLF, stat, bq25171_q1_stat2str(stat));
    } else {
        LOG_ERROR(BATT, "Usage: bcd");
    }
    return res;
}

bool bq25171_q1_ctrl_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 == argc) {
        bool state = false;
        res = try_str2bool(argv[0], &state);
        if(false == res) {
            LOG_ERROR(BATT, "Unable to extract state %s", argv[0]);
        }
        if(res) {
            res = bq25171_q1_charge_enable(state);
        }
    } else {
        LOG_ERROR(BATT, "Usage: bcc state");
    }
    return res;
}
