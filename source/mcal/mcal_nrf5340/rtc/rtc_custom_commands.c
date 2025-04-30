#include "rtc_custom_commands.h"

#include "convert.h"
#include "hal_nrfx_diag.h"
#include "log.h"
#include "nrfx_rtc.h"
#include "rtc_custom_diag.h"
#include "rtc_custom_drv.h"
#include "rtc_custom_types.h"
#include "rtc_drv.h"

bool rtc_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = rtc_diag_low_level();
    return res;
}

bool rtc_cc_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    bool enable_irq = 0;
    uint32_t channel = 0;
    uint32_t value = 0;
    if(4 == argc) {
        res = try_str2uint8(argv[0], &num);
        res = try_str2uint32(argv[1], &channel);
        res = try_str2uint32(argv[2], &value);
        res = try_str2bool(argv[3], &enable_irq);
    }

    if(res) {
        RtcStaticInfo_t* InfoNode = RtcGetStaticNode(num);
        if(InfoNode) {
            LOG_INFO(LG_RTC, "RTC%u Chan %x, Val: %u, ISR %u", num, channel, value, enable_irq);
            nrfx_err_t ret = nrfx_rtc_cc_set(&InfoNode->handle, channel, value, enable_irq);
            if(NRFX_SUCCESS == ret) {
                LOG_INFO(LG_RTC, "RTC%u CcSetOk", num);
            } else {
                LOG_ERROR(LG_RTC, "RTC%u CcSetErr %u=%s", num, ret, HalStatus2Str(ret));
            }
        } else {
        }
    }
    return res;
}

bool rtc_tick_ctrl_command(int32_t argc, char* argv[]) {
    uint8_t num = 0;
    bool on_off = 0;
    bool res = false;
    if(2 == argc) {
        res = try_str2uint8(argv[0], &num);
        res = try_str2bool(argv[1], &on_off);
    }

    if(res) {
        res = rtc_tick_ctrl(num, on_off);
    }
    return res;
}

bool rtc_int_ctrl_command(int32_t argc, char* argv[]) {
    uint8_t num = 0;
    uint32_t mask = 0;
    bool on_off = 0;
    bool res = false;
    if(2 == argc) {
        res = try_str2uint8(argv[0], &num);
        res = try_str2bool(argv[1], &on_off);
        res = try_str2uint32(argv[2], &mask);
    }

    if(res) {
        res = rtc_int_ctrl(num, on_off, mask);
    }
    return res;
}
