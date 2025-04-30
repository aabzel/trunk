#include "timer_mcal.h"

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_utils.h"
#include "bit_const.h"
#include "hal_nrfx_diag.h"
#include "nrfx_timer.h"
#include "timer_custom_drv.h"
#include "utils_math.h"

#ifdef HAS_LOG
#include "log.h"
#endif /*HAS_LOG*/

#include "timer_types.h"

#ifdef HAS_TIME
#include "time_mcal.h"
#endif


#include "sys_config.h"

static bool ProcNrfxTimerEventHandler(TimerHandle_t* Node, nrf_timer_event_t event) {
    bool res = false;
    if(Node) {
        Node->int_cnt++;
        switch(event) {
        case NRF_TIMER_EVENT_COMPARE0:
            Node->int_com_cnt[0]++;
            nrfx_timer_clear(&Node->timer_h);
            break;
        case NRF_TIMER_EVENT_COMPARE1:
            Node->int_com_cnt[1]++;
            nrfx_timer_clear(&Node->timer_h);
            break;
        case NRF_TIMER_EVENT_COMPARE2:
            Node->int_com_cnt[2]++;
            nrfx_timer_clear(&Node->timer_h);
            break;
        case NRF_TIMER_EVENT_COMPARE3:
            Node->int_com_cnt[3]++;
            nrfx_timer_clear(&Node->timer_h);
            break;
        case NRF_TIMER_EVENT_COMPARE4:
            Node->int_com_cnt[4]++;
            nrfx_timer_clear(&Node->timer_h);
            break;
        case NRF_TIMER_EVENT_COMPARE5:
            Node->int_com_cnt[5]++;
            nrfx_timer_clear(&Node->timer_h);
            break;
#if defined(TIMER_INTENSET_COMPARE6_Msk)
        case NRF_TIMER_EVENT_COMPARE6:
            Node->int_com_cnt[6]++;
            nrfx_timer_clear(&Node->timer_h);
            break;
#endif
#if defined(TIMER_INTENSET_COMPARE7_Msk)
        case NRF_TIMER_EVENT_COMPARE7:
            Node->int_com_cnt[7]++;
            nrfx_timer_clear(&Node->timer_h);
            break;
#endif
        }
    }
    return res;
}

#ifdef NRFX_TIMER0_ENABLED
void nrfx_timer0_event_handler(nrf_timer_event_t event, void* p_context) {
    TimerHandle_t* Node = TimerGetNode(0);
    if(Node) {
        ProcNrfxTimerEventHandler(Node, event);
    }
}
#endif

#ifdef NRFX_TIMER1_ENABLED
void nrfx_timer1_event_handler(nrf_timer_event_t event, void* p_context) {
    TimerHandle_t* Node = TimerGetNode(1);
    if(Node) {
        ProcNrfxTimerEventHandler(Node, event);
    }
}
#endif

#ifdef NRFX_TIMER2_ENABLED
void nrfx_timer2_event_handler(nrf_timer_event_t event, void* p_context) {
    TimerHandle_t* Node = TimerGetNode(2);
    if(Node) {
        ProcNrfxTimerEventHandler(Node, event);
    }
}
#endif

#ifdef NRFX_TIMER3_ENABLED
void nrfx_timer3_event_handler(nrf_timer_event_t event, void* p_context) {
    TimerHandle_t* Node = TimerGetNode(3);
    if(Node) {
        ProcNrfxTimerEventHandler(Node, event);
    }
}
#endif

#ifdef NRFX_TIMER4_ENABLED
void nrfx_timer4_event_handler(nrf_timer_event_t event, void* p_context) {
    TimerHandle_t* Node = TimerGetNode(4);
    if(Node) {
        ProcNrfxTimerEventHandler(Node, event);
    }
}
#endif

const static NrfTimerInfo_t NrfTimerInfoLut[] = {
#ifdef NRFX_TIMER0_ENABLED
    {
        .num = 0,
        .cc_channel_count = TIMER0_CC_NUM,
        .valid = true,
        .instance_id = NRFX_TIMER0_INST_IDX,
        .event_handler = nrfx_timer0_event_handler,
        .p_reg = NRF_TIMER0,
    },
#endif /*NRFX_TIMER0_ENABLED*/

#ifdef NRFX_TIMER1_ENABLED
    {.num = 1,
     .valid = true,
     .cc_channel_count = TIMER1_CC_NUM,
     .instance_id = NRFX_TIMER1_INST_IDX,
     .event_handler = nrfx_timer1_event_handler,
     .p_reg = /*NRF_TIMER1*/ NRF_TIMER1_S},
#endif

#ifdef NRFX_TIMER2_ENABLED
    {.num = 2,
     .valid = true,
     .cc_channel_count = TIMER2_CC_NUM,
     .instance_id = NRFX_TIMER2_INST_IDX,
     .event_handler = nrfx_timer2_event_handler,
     .p_reg = NRF_TIMER2_S /*NRF_TIMER2 NRF_TIMER2_S*/},
#endif

};

static const NrfTimerInfo_t* TimerNum2TimerInfoNode(uint8_t num) {
    const NrfTimerInfo_t* TimerInfoNode = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(NrfTimerInfoLut);
    for(i = 0; i < cnt; i++) {
        if(NrfTimerInfoLut[i].valid) {
            if(NrfTimerInfoLut[i].num == num) {
                TimerInfoNode = &NrfTimerInfoLut[i];
                break;
            }
        }
    }
    return TimerInfoNode;
}

#if 0
static uint8_t TimerNum2TimerIntIdx2(uint8_t num) {
    uint8_t instance_idx = 0xFF;
    const NrfTimerInfo_t* TimerInfoNode = TimerNum2TimerInfoNode(num);
    if(TimerInfoNode) {
        instance_idx = TimerInfoNode->instance_id;
    }
    return instance_idx;
}
static NRF_TIMER_Type* TimerNum2Ptr(uint8_t num) {
    NRF_TIMER_Type* peripheral = NULL;
    const NrfTimerInfo_t* TimerInfoNode = TimerNum2TimerInfoNode(num);
    if(TimerInfoNode) {
        peripheral = TimerInfoNode->p_reg;
    }
    return peripheral;
}
#endif

#ifdef HAS_TIMER_INTERRUPT
static bool timer_interupts_enable(uint8_t num) {
    bool res = false;
    switch(num) {
#ifdef NRFX_TIMER0_ENABLED
    case 0:
        NVIC_SetPriority(TIMER0_IRQn, 7);
        NVIC_EnableIRQ(TIMER0_IRQn);
        break;
#endif
#ifdef NRFX_TIMER1_ENABLED
    case 1:
        NVIC_SetPriority(TIMER1_IRQn, 7);
        NVIC_EnableIRQ(TIMER1_IRQn);
        break;
#endif
#ifdef NRFX_TIMER2_ENABLED
    case 2:
        NVIC_SetPriority(TIMER2_IRQn, 7);
        NVIC_EnableIRQ(TIMER2_IRQn);
        break;
#endif /*NRF_TIMER2_NS_BASE*/
    default:
        res = false;
        break;
    }
    return res;
}
#endif /*HAS_TIMER_INTERRUPT*/

static const TimerEventHandler_t TimerEventHandlerLut[] = {
#ifdef NRFX_TIMER0_ENABLED
    {
        .num = 0,
        .event_handler = nrfx_timer0_event_handler,
        .valid = true,
    },
#endif
#ifdef NRFX_TIMER1_ENABLED
    {
        .num = 1,
        .event_handler = nrfx_timer1_event_handler,
        .valid = true,
    },
#endif
#ifdef NRFX_TIMER2_ENABLED
    {
        .num = 2,
        .event_handler = nrfx_timer2_event_handler,
        .valid = true,
    },
#endif
#ifdef NRFX_TIMER3_ENABLED
    {
        .num = 3,
        .event_handler = nrfx_timer3_event_handler,
        .valid = true,
    },
#endif
};

static nrfx_timer_event_handler_t TimerNum2EventHandler(uint8_t num) {
    nrfx_timer_event_handler_t event_handler = NULL;
    uint32_t cnt = ARRAY_SIZE(TimerEventHandlerLut);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(TimerEventHandlerLut[i].valid) {
            if(TimerEventHandlerLut[i].num == num) {
                event_handler = TimerEventHandlerLut[i].event_handler;
                break;
            }
        }
    }

    return event_handler;
}

static bool NrfxTimerInstance(nrfx_timer_t* timer_h, uint8_t num) {
    bool res = false;
    if(timer_h) {
        const NrfTimerInfo_t* NrfTimerInfo = TimerNum2TimerInfoNode(num);
        if(NrfTimerInfo) {
            res = true;
            timer_h->p_reg = NrfTimerInfo->p_reg;
            timer_h->cc_channel_count = NrfTimerInfo->cc_channel_count;
            timer_h->instance_id = NrfTimerInfo->instance_id;
        }
    }
    return res;
}

bool timer_set_status(uint8_t num, bool on_off) {
    bool res = false;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        if(on_off) {
            LOG_DEBUG(TIMER, "%u Start", num);
            nrfx_timer_enable(&Node->timer_h);
            res = true;
        } else {
            LOG_DEBUG(TIMER, "%u Stop", num);
            nrfx_timer_disable(&Node->timer_h);
            res = true;
        }
    }
    return res;
}

static const TimerFreqInfo_t TimerFreqLut[] = {{
                                                   .freq_code = NRF_TIMER_FREQ_16MHz,
                                                   .freq_hz = 16000000,
                                               },
                                               {
                                                   .freq_code = NRF_TIMER_FREQ_8MHz,
                                                   .freq_hz = 8000000,
                                               },
                                               {
                                                   .freq_code = NRF_TIMER_FREQ_4MHz,
                                                   .freq_hz = 4000000,
                                               },
                                               {
                                                   .freq_code = NRF_TIMER_FREQ_2MHz,
                                                   .freq_hz = 2000000,
                                               },
                                               {
                                                   .freq_code = NRF_TIMER_FREQ_1MHz,
                                                   .freq_hz = 1000000,
                                               },
                                               {
                                                   .freq_code = NRF_TIMER_FREQ_500kHz,
                                                   .freq_hz = 500000,
                                               },
                                               {
                                                   .freq_code = NRF_TIMER_FREQ_250kHz,
                                                   .freq_hz = 250000,
                                               },
                                               {
                                                   .freq_code = NRF_TIMER_FREQ_125kHz,
                                                   .freq_hz = 125000,
                                               },
                                               {
                                                   .freq_code = NRF_TIMER_FREQ_62500Hz,
                                                   .freq_hz = 62500,
                                               },
                                               {
                                                   .freq_code = NRF_TIMER_FREQ_31250Hz,
                                                   .freq_hz = 31250,
                                               }};

static uint32_t Code2Freq(nrf_timer_frequency_t code) {
    uint32_t i = 0;
    uint32_t des_freq_hz = 0;
    for(i = 0; i < ARRAY_SIZE(TimerFreqLut); i++) {
        if(code == TimerFreqLut[i].freq_code) {
            des_freq_hz = TimerFreqLut[i].freq_hz;
            break;
        }
    }
    return des_freq_hz;
}

static nrf_timer_bit_width_t TimBit2NrfTimBit(uint8_t bitness) {
    nrf_timer_bit_width_t nrf_timer_bit_width = NRF_TIMER_BIT_WIDTH_32;
    switch(bitness) {
    case 8:
        nrf_timer_bit_width = NRF_TIMER_BIT_WIDTH_8;
        break;
    case 16:
        nrf_timer_bit_width = NRF_TIMER_BIT_WIDTH_16;
        break;
    case 24:
        nrf_timer_bit_width = NRF_TIMER_BIT_WIDTH_24;
        break;
    case 32:
        nrf_timer_bit_width = NRF_TIMER_BIT_WIDTH_32;
        break;
    }
    return nrf_timer_bit_width;
}

static nrf_timer_frequency_t freqHz2NfrFreq(uint32_t des_freq_hz) {
    nrf_timer_frequency_t code = NRF_TIMER_FREQ_31250Hz;
    uint32_t i = 0;
    double freq_error_hz = 0.0;
    double min_freq_error_hz = 64000000.0;
    for(i = 0; i < ARRAY_SIZE(TimerFreqLut); i++) {
        freq_error_hz = fabs(((double)des_freq_hz) - ((double)TimerFreqLut[i].freq_hz));
        if(freq_error_hz < min_freq_error_hz) {
            LOG_DEBUG(TIMER, "New Err %f Hz", min_freq_error_hz);
            min_freq_error_hz = freq_error_hz;
            code = TimerFreqLut[i].freq_code;
        }
    }
    LOG_INFO(TIMER, "DesFreq %u Hz SetFreq %u Hz Err %f Hz", des_freq_hz, Code2Freq(code), min_freq_error_hz);
    return code;
}

static nrf_timer_short_mask_t TimerChannel2ShortMask(CapComChannel_t channel) {
    nrf_timer_short_mask_t timer_short_mask = NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK;
    switch((uint32_t)channel) {
    case TIMER_CC_CHAN0:
        timer_short_mask = NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK;
        break;
    case TIMER_CC_CHAN1:
        timer_short_mask = NRF_TIMER_SHORT_COMPARE1_CLEAR_MASK;
        break;
    case TIMER_CC_CHAN2:
        timer_short_mask = NRF_TIMER_SHORT_COMPARE2_CLEAR_MASK;
        break;
    case TIMER_CC_CHAN3:
        timer_short_mask = NRF_TIMER_SHORT_COMPARE3_CLEAR_MASK;
        break;
    }
    return timer_short_mask;
}

bool timer_set_cc_val(uint8_t num, CapComChannel_t channel, uint32_t cc_value, bool int_on) {
    bool res = false;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        res = timer_set_status(num, false);
        // nrfx_timer_clear(&Node->timer_h);
#if 1
        nrf_timer_short_mask_t timer_short_mask = TimerChannel2ShortMask(channel);
        nrfx_timer_extended_compare(&Node->timer_h, (nrf_timer_cc_channel_t)channel, cc_value, timer_short_mask,
                                    int_on);
#else
        nrfx_timer_compare(&Node->timer_h, (nrf_timer_cc_channel_t)channel, cc_value, int_on);
#endif
        // nrfx_timer_resume(&Node->timer_h);
        res = timer_set_status(num, true);
    }
    return res;
}

bool timer_init_one(uint8_t num) {
    bool res = false;
    LOG_INFO(TIMER, "%u Init", num);
    const TimerConfig_t* Config = TimerGetConfig(num);
    if(Config) {
        TimerHandle_t* Node = TimerGetNode(num);
        if(Node) {
            nrfx_timer_event_handler_t event_handler;
            event_handler = TimerNum2EventHandler(num);
            res = NrfxTimerInstance(&Node->timer_h, num);
            if(res) {
                uint32_t freq_hz = TimerGetCntFreq(Config->cnt_period_us);

                Node->config.frequency = freqHz2NfrFreq(freq_hz);
                Node->config.bit_width = TimBit2NrfTimBit(Config->bitness);
                // Node->config.interrupt_priority=NRFX_TIMER_DEFAULT_CONFIG_IRQ_PRIORITY;
                Node->config.mode = NRF_TIMER_MODE_TIMER;
                Node->config.p_context = NULL;
                nrfx_err_t ret = nrfx_timer_init(&Node->timer_h, &Node->config, event_handler);
                if(NRFX_SUCCESS == ret) {
                    Node->init_done = true;
                    LOG_INFO(TIMER, "%u InitOk", num);
                    res = timer_set_cc_val(num, TIMER_CC_CHAN0, Config->period_us, true);
                    // res=timer_set_cc_val(  num, TIMER_CC_CHAN2, Config->compare[0], true);
                    // res=timer_set_cc_val(  num, TIMER_CC_CHAN1, Config->compare[1], true);
                    // res=timer_set_cc_val(  num, TIMER_CC_CHAN3, Config->compare[3], true);
                    res = timer_set_status(num, Config->on_off);
                } else {
                    LOG_ERROR(TIMER, "%u InitErr", num);
                }
            } else {
                LOG_ERROR(TIMER, "%u InstErr", num);
            }
        }
    }

    return res;
}

uint32_t timer_get_ms(void) { return 0; }

uint64_t timer_get_us(void) { return 0; }

static uint8_t BitCode2Bitness(uint8_t code) {
    uint8_t bitness = 0;
    switch(code) {
    case TIMER_8BIT:
        bitness = 8;
        break;
    case TIMER_16BIT:
        bitness = 16;
        break;
    case TIMER_24BIT:
        bitness = 24;
        break;
    case TIMER_32BIT:
        bitness = 32;
        break;
    }
    return bitness;
}

uint8_t timer_get_bitness(uint8_t num) {
    uint32_t bitness = 0;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        bitness = BitCode2Bitness(MASK_2BIT & Node->timer_h.p_reg->BITMODE);
    }
    return bitness;
}

uint32_t timer_get_period(uint8_t num) {
    uint32_t period = 0;
    uint64_t period64 = 0;
    uint8_t bitness = timer_get_bitness(num);
    period64 = int_pow(2, bitness);
    if(0xFFFFFFFF < period64) {
        period = 0xFFFFFFFF;
    }
    return period;
}

uint32_t timer_get_prescaler(uint8_t num) {
    uint32_t prescaler = 0;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        uint32_t prescaler_degree = MASK_4BIT & (Node->timer_h.p_reg->PRESCALER);
        prescaler = int_pow(2, prescaler_degree);
    }
    return prescaler;
}

double timer_get_freq(uint8_t num) {
    double freq = 0.0;
    uint32_t prescaler = timer_get_prescaler(num);
    freq = ((double)TIMER_CLOCK_HZ) / ((double)prescaler);
    return freq;
}

bool timer_get_auto_reload(uint8_t num) { return false; }

bool timer_get_status(uint8_t num) {
    bool res = false;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        res = nrfx_timer_is_enabled(&Node->timer_h);
    }
    return res;
}

uint32_t timer_nrf_get_counter(uint8_t num, CapComChannel_t channel) {
    uint32_t counter = 0;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        // counter=Node->timer_h.p_reg->TASKS_COUNT;
        counter = nrfx_timer_capture(&Node->timer_h, (nrf_timer_cc_channel_t)channel);
    }
    return counter;
}

uint32_t timer_get_cc_val(uint8_t num, CapComChannel_t channel) {
    uint32_t capture_compare = 0;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        capture_compare = nrfx_timer_capture_get(&Node->timer_h, (nrf_timer_cc_channel_t)channel);
    }
    return capture_compare;
}

TimDir_t timer_get_dir(uint8_t num) { return CNT_DIR_UNDEF; }

uint32_t timer_get_bus_clock(uint8_t num) { return TIMER_CLOCK_HZ; }

double timer_get_tick_s(uint8_t num) {
    double tick_s = 0.0;
    uint32_t prescaler = timer_get_prescaler(num);
    tick_s = ((double)prescaler) / ((double)TIMER_CLOCK_HZ);
    return tick_s;
}

double timer_get_period_s(uint8_t num) {
    double period_s = 0.0;
    uint32_t period = timer_get_period(num);
    double tick_s = timer_get_tick_s(num);
    period_s = ((double)period) * tick_s;
    return period_s;
}

uint32_t timer_get_uptime_ms(uint8_t num) {
    /*TODO Implement leter*/
    return 0;
}

uint32_t timer_get_uptime_us(uint8_t num) {
    /*TODO Implement leter*/
    return 0;
}


uint32_t timer_get_counter(uint8_t num) {
    uint32_t counter = 0;
    return counter;
}


bool timer_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    return res;
}
