#include "rtc_drv.h"

#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "calendar.h"
#include "clock_utils.h"
#include "common_diag.h"
#include "data_utils.h"
#include "gpio_drv.h"
#include "hal_nrfx_diag.h"
#include "log.h"
#include "nrfx_clock.h"
#include "nrfx_rtc.h"
#include "rtc_custom_drv.h"
#include "rtc_custom_types.h"
#include "rtc_dep.h"
#include "rtc_diag.h"
#include "rtc_isr.h"
#include "rtc_types.h"

const RtcStaticInfo_t RtcStaticInfoLut[] = {
#if NRFX_CHECK(NRFX_RTC0_ENABLED)
    {
        .num = 0,
        .valid = true,
        .event_handler = nrfx_rtc0_event_handler,
        .handle.p_reg = NRF_RTC0_S,
        .handle.instance_id = NRFX_RTC0_INST_IDX,
        .handle.cc_channel_count = 0,
        .handle.irq = RTC0_IRQn,
        .counter_bit = 24,
    },
#endif /*NRFX_RTC0_ENABLED*/

#if NRFX_CHECK(NRFX_RTC1_ENABLED)
    {
        .event_handler = nrfx_rtc1_event_handler,
        .num = 1,
        .handle.p_reg = NRF_RTC1_S,
        .handle.instance_id = NRFX_RTC1_INST_IDX,
        .handle.cc_channel_count = 0,
        .handle.irq = RTC1_IRQn,
        .valid = true,
        .counter_bit = 24,
    },
#endif /*NRFX_RTC1_ENABLED*/

#if NRFX_CHECK(NRFX_RTC2_ENABLED)
    {
        .event_handler = nrfx_rtc2_event_handler,
        .num = 2,
        .valid = true,
        .handle.p_reg = NRF_RTC2_S,
        .handle.instance_id = NRFX_RTC2_INST_IDX,
        .handle.cc_channel_count = 0,
        .handle.irq = RTC2_IRQn,
        .counter_bit = 24,
    },
#endif /*NRFX_RTC2_ENABLED*/
};

RtcStaticInfo_t* RtcGetStaticNode(uint8_t num) {
    RtcStaticInfo_t* InfoNode = NULL;
    uint8_t cnt = ARRAY_SIZE(RtcStaticInfoLut);
    LOG_DEBUG(LG_RTC, "Total: %u Need %u", cnt, num);
    uint8_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(num == RtcStaticInfoLut[i].num) {
            LOG_DEBUG(LG_RTC, "spotNum %u", num);
            if(RtcStaticInfoLut[i].valid) {
                LOG_DEBUG(LG_RTC, "spotValid %u", num);
                InfoNode = (RtcStaticInfo_t*)&RtcStaticInfoLut[i];
                break;
            }
        }
    }
    return InfoNode;
}

bool rtc_set_custom(uint8_t num, const struct tm* const time_date) {
    bool res = false;
    RtcHandle_t* Node = RtcGetNode(num);
    if(Node) {
        Node->raw_sec = calendar_settime(time_date);
        LOG_DEBUG(LG_RTC, "RtcSetOk!");
        res = true;
    } else {
        LOG_ERROR(LG_RTC, "NodeErr");
    }
    return res;
}

bool rtc_get_custom(uint8_t num, struct tm* const time_date) {
    bool res = false;
    RtcHandle_t* Node = RtcGetNode(num);
    if(Node) {
        res = SecondsToTimeDate(Node->raw_sec, time_date);
        if(res) {
            LOG_DEBUG(LG_RTC, "RtcGetOk");
        } else {
            LOG_ERROR(LG_RTC, "Rtc2StructErr");
        }
    } else {
        LOG_ERROR(LG_RTC, "NoNode");
    }
    return res;
}

bool rtc_start(uint8_t num) {
    bool res = false;
    LOG_WARNING(LG_RTC, "RTC%u Start", num);
    RtcHandle_t* Node = RtcGetNode(num);
    if(Node) {
        nrfx_rtc_enable(&Node->handle);
        LOG_INFO(LG_RTC, "RTC%u StartOk", num);
        Node->start_cnt++;
        res = true;
    }
    return res;
}

bool rtc_stop(uint8_t num) {
    bool res = false;
    LOG_WARNING(LG_RTC, "RTC%u Stop", num);
    RtcHandle_t* Node = RtcGetNode(num);
    if(Node) {
        nrfx_rtc_disable(&Node->handle);
        Node->stop_cnt++;
        LOG_INFO(LG_RTC, "RTC%u StopOk", num);
        res = true;
    }
    return res;
}

bool rtc_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(LG_RTC, "RTC%u Init", num);

    set_log_level(LG_CAL, LOG_LEVEL_DEBUG);

    const RtcConfig_t* Config = RtcGetConfig(num);
    if(Config) {
#ifdef HAS_RTC_DIAG
        RtcDiagConfig(Config);
#endif
        LOG_INFO(LG_RTC, "RTC%u SpotConfig ", num);
        RtcHandle_t* Node = RtcGetNode(num);
        if(Node) {
            LOG_DEBUG(LG_RTC, "RTC%u SpotNode", num);
            if(Node->init_done) {
                LOG_WARNING(LG_RTC, "RTC%u UnInit", num);
                nrfx_rtc_uninit(&Node->handle);
            }

            res = rtc_init_common(Node);

            const RtcStaticInfo_t* StaticNode = RtcGetStaticNode(num);
            if(StaticNode) {
                LOG_DEBUG(LG_RTC, "RTC%u SpotStaticConfigFor", num);
#ifdef HAS_RTC_DIAG
                RtcDiagConfig(Config);
#endif
                nrfx_rtc_config_t config = {0};
                config.prescaler = Config->prescaler;
                config.interrupt_priority = Config->irq_priority;
                config.tick_latency = 0; // NRFX_RTC_US_TO_TICKS(2000, 32768);
                config.reliable = false;

                Node->handle = StaticNode->handle;

                // Node->handle.p_reg = StaticNode->handle.p_reg;
                // Node->handle.irq = StaticNode->handle.irq;
                // Node->handle.instance_id = StaticNode->handle.instance_id;
                // Node->handle.cc_channel_count = StaticNode->handle.cc_channel_count;
                nrfx_err_t ret = NRFX_ERROR_NULL;
#ifdef HAS_RTC_ISR
                Node->isr_handler = StaticNode->event_handler;
                nrfx_rtc_tick_enable(&Node->handle, true);
#endif /*HAS_RTC_ISR*/
                ret = nrfx_rtc_init(&Node->handle, &config, Node->isr_handler);
                if(NRFX_SUCCESS == ret) {
                    Node->init_done = true;
                    LOG_INFO(LG_RTC, "RTC%u InitOk", num);
                    res = rtc_ctrl(num, true);
                } else {
                    LOG_ERROR(LG_RTC, "RTC%u InitErr %u=%s", num, ret, HalStatus2Str(ret));
                }
            } else {
                LOG_ERROR(LG_RTC, "RTC%u NoStaticNode", num);
            }
        } else {
            LOG_ERROR(LG_RTC, "RTC%u NoNode", num);
        }
    } else {
        LOG_DEBUG(LG_RTC, "RTC%u NoConfig", num);
    }
    return res;
}

bool rtc_set_date_custom(uint8_t num, const struct tm* const time_date) {
    bool res = false;
    return res;
}
bool rtc_set_time_custom(uint8_t num, const struct tm* const time_date) {
    bool res = false;

    return res;
}

bool rtc_tick_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    const RtcStaticInfo_t* StaticNode = RtcGetStaticNode(num);
    if(StaticNode) {
        switch(on_off) {
        case true: {
            nrfx_rtc_tick_enable(&StaticNode->handle, true);
            res = true;
        } break;
        case false: {
            nrfx_rtc_tick_disable(&StaticNode->handle);
            res = true;
        } break;
        }
    }
    return res;
}

bool rtc_int_ctrl(uint8_t num, bool on_off, uint32_t mask) {
    bool res = false;
    const RtcStaticInfo_t* StaticNode = RtcGetStaticNode(num);
    if(StaticNode) {
        switch(on_off) {
        case true: {
            nrfx_rtc_int_enable(&StaticNode->handle, mask);
            res = true;
        } break;
        case false: {
            nrfx_rtc_int_disable(&StaticNode->handle, &mask);
            res = true;
        } break;
        }
    }
    return res;
}
