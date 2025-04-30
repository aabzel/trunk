#include "scr1_timer.h"
/*
 https://mik32-amur.ru/Appendix/systim64.html
 */
#include <stddef.h>

#include "bit_const.h"
#include "csr.h"
#include "data_types.h"
#include "interrupt_mcal.h"
#include "log.h"
#include "scr1_csr_encoding.h"
#include "scr1_timer_config.h"
#include "std_includes.h"

#ifdef HAS_SCR1_TIMER_DIAG
#include "scr1_timer_diag.h"
#endif

#include "time_mcal.h"
#ifdef HAS_CLOCK
#include "clock.h"
#endif

static uint32_t ScrTimerClkSrcToFreqHz(const SCR1_TIMER_CLKSRC_t clk_src) {
    uint32_t base_clock_hz = 0;
    switch(clk_src) {
    case CLK_SRC_AHB_CLK:
        base_clock_hz = 32000000;
        break;
    case CLK_SRC_RTC_CLK:
        base_clock_hz = 32768;
        break;
    default:
        base_clock_hz = CLK_SRC_AHB_CLK;
        break;
    }
    return base_clock_hz;
}

static SCR1_TIMER_CLKSRC_t ClockSourceToScr1TimerClkSrc(ClockSource_t clock_source) {
    SCR1_TIMER_CLKSRC_t clk_src = CLK_SRC_AHB_CLK;
    switch(clock_source) {
    case CLOCK_SRC_INTERNAL:
        clk_src = CLK_SRC_AHB_CLK;
        break;
    case CLOCK_SRC_EXTERNAL:
        clk_src = CLK_SRC_AHB_CLK;
        break;
    case CLOCK_SRC_RTC:
        clk_src = CLK_SRC_RTC_CLK;
        break;
    case CLOCK_SRC_EXTERNAL_32MHZ:
        clk_src = CLK_SRC_AHB_CLK;
        break;
    default:
        clk_src = CLK_SRC_AHB_CLK;
        break;
    }
    return clk_src;
}

uint64_t scr1_timer_counter_get(const Scr1Timer_t* const Node) {
    uint64_t counter = 0;
    if(Node) {
        if(SCR1_TIMER_BASE == Node->Scr1TimerRegMapPtr) {
            Type64Union_t ComposedVar;
            ComposedVar.u64 = 0;
            ComposedVar.u32[0] = Node->Scr1TimerRegMapPtr->MTIME.MTIME;
            ComposedVar.u32[1] = Node->Scr1TimerRegMapPtr->MTIMEH.MTIMEH;
            counter = ComposedVar.u64;
        }
    }
    return counter;
}

bool scr1_timer_counter_set(Scr1Timer_t* const Node, const uint64_t value) {
    bool res = false;
    if(SCR1_TIMER_BASE == Node->Scr1TimerRegMapPtr) {
        LOG_WARNING(SCR_TIMER, "LoadVal");
        Type64Union_t ComposedVar = {0};
        ComposedVar.u64 = value;
        Node->Scr1TimerRegMapPtr->MTIME.MTIME = ComposedVar.u32[0];
        Node->Scr1TimerRegMapPtr->MTIMEH.MTIMEH = ComposedVar.u32[1];
    }
    return res;
}

bool scr1_timer_divider_set(Scr1Timer_t* const Node, uint32_t divider) {
    bool res = false;
    if(divider < SCR1_TIMER_MAX_DIV) {
        Node->Scr1TimerRegMapPtr->DIV.DIV = divider;
        res = true;
    } else {
        Node->Scr1TimerRegMapPtr->DIV.DIV = SCR1_TIMER_MAX_DIV;
    }
    return res;
}

void Scr1TimerIntHandler(void) { Scr1TimerInstance.int_cnt++; }

bool scr1_timer_is_run(void) {
    bool res = false;
    if(Scr1TimerInstance.Scr1TimerRegMapPtr) {
        if(SCR1_TIMER_CTRL_ENABLE == Scr1TimerInstance.Scr1TimerRegMapPtr->CTRL.ENABLE) {
            res = true;
        }
    }
    return res;
}

bool scr1_timer_stop(void) {
    bool res = false;
    if(Scr1TimerInstance.Scr1TimerRegMapPtr) {
        Scr1TimerInstance.Scr1TimerRegMapPtr->CTRL.ENABLE = SCR1_TIMER_CTRL_DISABLE;
        LOG_WARNING(SCR_TIMER, "Stop");
        res = true;
    }

    return res;
}

bool scr1_timer_disable(void) {
    bool res = false;
    res = scr1_timer_stop();
    return res;
}

bool scr1_timer_reset(void) {
    bool res = false;
    LOG_WARNING(SCR_TIMER, "ReStart");
    res = scr1_timer_stop();
    res = scr1_timer_counter_set(&Scr1TimerInstance, 0);
    res = scr1_timer_start();
    return res;
}

bool scr1_timer_start(void) {
    Scr1TimerInstance.Scr1TimerRegMapPtr->CTRL.ENABLE = SCR1_TIMER_CTRL_ENABLE;
    LOG_WARNING(SCR_TIMER, "Start");
    return false;
}

bool scr1_timer_tick_time_set(uint32_t scr1_timer_clock_hz, float period_s) {
    bool res = false;
    uint32_t divider = 0;
#ifdef HAS_LOG
    LOG_INFO(SCR_TIMER, "Clock: %u Hz", scr1_timer_clock_hz);
#endif
    float tick_s = 1.0 / ((float)scr1_timer_clock_hz);
#ifdef HAS_LOG
    LOG_INFO(SCR_TIMER, "Tick:%f", tick_s);
#endif
    divider = (uint32_t)(period_s / tick_s);
#ifdef HAS_LOG
    LOG_INFO(SCR_TIMER, "divider:%u", divider);
#endif
    res = scr1_timer_divider_set(&Scr1TimerInstance, divider);
    return res;
}

float scr1_timer_tick_time_get(Scr1Timer_t* const Node) {
    float tick_time_s = 0.0;
    if(Node) {
        if(SCR1_TIMER_BASE == Node->Scr1TimerRegMapPtr) {
            uint32_t base_clock_hz = ScrTimerClkSrcToFreqHz(Node->Scr1TimerRegMapPtr->CTRL.CLKSRC);
            float clock_time_s = 1.0 / ((float)base_clock_hz);
            uint32_t divider = Node->Scr1TimerRegMapPtr->DIV.DIV;
            tick_time_s = clock_time_s * ((float)divider);
        }
    }
    return tick_time_s;
}

float scr1_timer_get_s(void) {
    uint64_t counter = scr1_timer_counter_get(&Scr1TimerInstance);
    float tick_time_s = scr1_timer_tick_time_get(&Scr1TimerInstance);
    float up_time_s = ((float)counter) * tick_time_s;
    return up_time_s;
}

uint64_t scr1_timer_get_us(void) {
    float up_time_s = 0.0;
    up_time_s = scr1_timer_get_s();
    float up_time_us_f = up_time_s * 1000000.0;
    uint64_t up_time_us = (uint64_t)up_time_us_f;
    return up_time_us;
}

uint32_t scr1_timer_get_ms(void) {
    float up_time_s = 0.0;
    up_time_s = scr1_timer_get_s();
    float up_time_ms_f = up_time_s * 1000.0;
    uint32_t up_time_ms = (uint64_t)up_time_ms_f;
    return (uint32_t)up_time_ms;
}

bool scr1_timer_clock_source_set(Scr1Timer_t* const Node, ClockSource_t clock_source) {
    bool res = false;
    if(SCR1_TIMER_BASE == Node->Scr1TimerRegMapPtr) {
        Node->Scr1TimerRegMapPtr->CTRL.ENABLE = SCR1_TIMER_CTRL_DISABLE;
        Node->Scr1TimerRegMapPtr->CTRL.CLKSRC = ClockSourceToScr1TimerClkSrc(clock_source);
        res = true;
    }
    return res;
}

static bool Scr1IsValidConfig(const Scr1TimerConfig_t* const Config) {
    bool res = true;
    if(Config) {
        res = true;
    } else {
        res = false;
    }

    if(res) {
        if(0.0 < Config->tick_s) {
            res = true;
        } else {
            res = false;
        }
    }
    if(res) {
        if(Config->base_addr) {
            res = true;
        } else {
            res = false;
        }
    }

    if(res) {
        if(Config->clock_source) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

static bool scr1_timer_init_one(const Scr1TimerConfig_t* const Config, Scr1Timer_t* const Node) {
    bool res = true;
    if(Config) {
        res = Scr1IsValidConfig(Config);
        if(res) {
            if(Node) {
                Node->Scr1TimerRegMapPtr = (Scr1TimerRegs_t*)Config->base_addr;
                res = scr1_timer_stop();
                res = scr1_timer_clock_source_set(Node, Config->clock_source);
                uint32_t scr1_timer_clock_hz = ClockSourcToHz(Config->clock_source);
                res = scr1_timer_tick_time_set(scr1_timer_clock_hz, Config->tick_s) && res;
                Node->scr1_timer_up_time_us = 0;
                Node->int_cnt = 0;
                res = scr1_timer_start();
            }
        }
    }
    return res;
}

bool scr1_timer_init(void) {
    bool res = true;
    res = interrupt_disable();
    clear_csr(mie, MIE_MTIE); // Machine Timer Interrupt  Disable.
    res = scr1_timer_init_one(&Scr1TimerConfig, &Scr1TimerInstance);
    res = scr1_timer_reset() && res;
    res = interrupt_enable();
    return res;
}
