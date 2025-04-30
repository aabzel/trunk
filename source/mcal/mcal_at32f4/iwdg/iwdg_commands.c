#include "iwdg_commands.h"

#include "convert.h"
#include "log_utils.h"
#include "log.h"
#include "iwdg_drv.h"

bool wdt_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        double max_period_s=iwdg_calc_period_s(  LSI_FREQ , PRESCALER_VAL_MAX, RELOAD_VAL_MAX-1);
        LOG_INFO(LG_IWDG,"MaxPer: %f s",max_period_s);
        LOG_INFO(LG_IWDG,"BaseAddr: 0x%08x",IWDG_BASE_ADDR);
        cli_printf("state : %u" CRLF, WatchDog.is_on);
        cli_printf("period: %u" CRLF, WatchDog.period_ms);
        uint32_t period_ms = iwdg_get_period_ms();
        LOG_INFO(LG_IWDG,"Real: %u ms",period_ms);
        res = true;
    } else {
        LOG_ERROR(LG_IWDG, "Usage: iwd");
    }
    return res;
}

bool wdt_ctrl_command(int32_t argc, char* argv[]){
    bool res = false;
    if(1 == argc) {
        res = true;
        res = try_str2bool(argv[0], &WatchDog.is_on);
        if(false == res) {
            LOG_ERROR(LG_IWDG, "ParseErr OnOff %s", argv[0]);
        }
    } else {
        LOG_ERROR(LG_IWDG, "Usage: iwc status");
    }
    return res;
}

bool wdt_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 == argc) {
        res = true;
        uint32_t period_ms = 0;

        if(res) {
            res = try_str2uint32(argv[0], &period_ms);
            if(false == res) {
                LOG_ERROR(LG_IWDG, "ParseErr period_ms %s", argv[0]);
            }
        }

        if(res) {
            res = iwdg_set_period_ms(period_ms);
            if(false == res) {
                LOG_ERROR(LG_IWDG, "Unable to set watchdog");
            } else {
                cli_printf(CRLF);
            }
        }

    } else {
        LOG_ERROR(LG_IWDG, "Usage: iws period_ms");
        LOG_INFO(LG_IWDG, "period_ms");
    }
    return res;
}
