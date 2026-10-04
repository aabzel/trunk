#include "systick_mcal.h"

#include <stdlib.h>

#include "bit_const.h"
#include "clock_mcal.h"
#include "clock_utils.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "core_driver.h"
#include "std_includes.h"
#include "time_mcal.h"

#ifdef HAS_DIAG
#include "common_diag.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

// COMPONENT_GET_INFO(SysTick)
COMPONENT_GET_NODE(SysTick, systick)
COMPONENT_GET_CONFIG(SysTick, systick)

_WEAK_FUN_ bool systick_custom_init(void) {
    bool res = false;
    return res;
}

_WEAK_FUN_
uint32_t systick_get_base_freq(void) {
    bool res = false;
    return res;
}

_WEAK_FUN_ uint64_t systick_cnt_get(uint8_t num) {
    uint64_t counter = 0;
    SysTickHandle_t* Node = SysTickGetNode(num);
    if(Node) {
        enter_critical();
        uint64_t rest = Node->SYSTICKx->Load.reload - Node->SYSTICKx->Val.current;
        counter = Node->counter_wrap + rest;
        exit_critical();
    }
    return counter;
}

_WEAK_FUN_ bool systick_stop(void) {
    bool res = false;
    return res;
}

static bool systick_init_custom(void) {
    bool res = true;
    res = systick_custom_init();
    return res;
}

#ifdef HAS_SYSTIC_INT
/*if call every 1ms 32bit overflows after 49 days*/
#endif /*HAS_SYSTICK_INT*/

static bool SysTickIsValidConfig(const SysTickConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;

        if(res) {
            if(Config->period_ms) {
                res = true;
            } else {
                res = false;
            }
        }

        if(res) {
            if(Config->SYSTICKx) {
                res = true;
            } else {
                res = false;
            }
        }
    }
    return res;
}

bool systick_is_run(void) {
    bool res = false;
    SysTickHandle_t* Node = SysTickGetNode(1);
    if(Node) {
        if(Node->SYSTICKx) {
            if(Node->SYSTICKx->Cntl.enable) {
                res = true;
            }
        }
    }
    return res;
}

bool systick_mcal_stop(void) {

    SysTickHandle_t* Node = SysTickGetNode(1);
    if(Node) {

        SysTickCntl_t SysTickCntl;
        SysTickCntl.reg_val = Node->SYSTICKx->Cntl.reg_val;
        SysTickCntl.enable = 0;
        SysTickCntl.tickint = 0;

        Node->SYSTICKx->Cntl.reg_val = SysTickCntl.reg_val;
    }

    return true;
}

bool systick_start(void) {
    bool res = false;
    SysTickHandle_t* Node = SysTickGetNode(1);
    if(Node) {
        if(Node->SYSTICKx) {
            SysTickCntl_t SysTickCntl;
            SysTickCntl.reg_val = Node->SYSTICKx->Cntl.reg_val;
            SysTickCntl.enable = 1;
            SysTickCntl.tickint = 1;
            Node->SYSTICKx->Cntl.reg_val = SysTickCntl.reg_val;
            res = true;
        }
    }
    return res;
}

bool systick_set_load(uint32_t new_load) {
    bool res = false;
    SysTickHandle_t* Node = SysTickGetNode(1);
    if(Node) {
        SysTickReload_t SysTickReload;
        SysTickReload.reg_val = 0;
        SysTickReload.reload = MASK_24BIT & new_load;
        if(Node->SYSTICKx) {
            Node->SYSTICKx->Load.reg_val = SysTickReload.reg_val;
            res = true;
        }
    }
    return res;
}

bool systick_clksrc_set(const SysTickClkSrc_t clksrc) {
    bool res = false;
    SysTickHandle_t* Node = SysTickGetNode(1);
    if(Node) {
        if(Node->SYSTICKx) {
            Node->SYSTICKx->Cntl.clksource = clksrc;
            res = true;
        }
    }
    return res;
}

SysTickClkSrc_t systick_source_get(void) {
    SysTickClkSrc_t clk_src = SYSTICK_CLK_SRC_UNDEF;
    SysTickHandle_t* Node = SysTickGetNode(1);
    if(Node) {
        if(Node->SYSTICKx) {
            clk_src = Node->SYSTICKx->Cntl.clksource;
        }
    }
    return clk_src;
}

uint32_t systick_get_load(void) {
    SysTickReload_t SysTickReload = {0};
    SysTickHandle_t* Node = SysTickGetNode(1);
    if(Node) {
        if(Node->SYSTICKx) {
            SysTickReload.reg_val = Node->SYSTICKx->Load.reg_val;
        }
    }
    return SysTickReload.reload;
}

uint64_t systick_get_us(uint8_t num) {
    uint64_t cur_time_us = 0;
    SysTickHandle_t* Node = SysTickGetNode(num);
    if(Node) {
        uint64_t counter = systick_cnt_get(num);
        cur_time_us = counter / Node->divider_1us;
    }

    return cur_time_us;
}

uint32_t systick_get_ms(void) {
    uint32_t up_time_ms = 0;
    SysTickHandle_t* Node = SysTickGetNode(1);
    if(Node) {
        bool res = systick_is_run();
        if(res) {
        } else {
            Node->err_cnt++;
        }
        up_time_ms = Node->up_time_ms32;
    }
    return up_time_ms;
}

bool systick_ctrl(bool on_off) {
    bool res = false;
#ifdef HAS_DIAG
    LOG_INFO(LG_SYSTICK, "Ctrl:%s", OnOffToStr(on_off));
#endif
    switch(on_off) {
    case true:
        res = systick_start();
        break;
    case false:
        res = systick_stop();
        break;
    default:
        res = false;
        break;
    }
    return res;
}

static bool systick_init_one_ll(const SysTickConfig_t* const Config, SysTickHandle_t* const Node) {
    bool res = false;
    if(Config) {
#ifdef HAS_SYSTICK_DIAG
        LOG_WARNING(LG_SYSTICK, "%s", SysTickConfigToStr(Config));
#endif
        res = SysTickIsValidConfig(Config);
        if(res) {
            if(Node) {
#ifdef HAS_LOG
                LOG_INFO(LG_SYSTICK, "Period:%u ms", Config->period_ms);
#endif

                Node->SYSTICKx = Config->SYSTICKx;
                Node->num = Config->num;
                Node->interrupt_on = Config->interrupt_on;
                Node->period_ms = Config->period_ms;

                Node->up_time_ms32 = 0;
                Node->counter_wrap = 0;
                Node->up_time_ms64 = 0;
                if(Config->SYSTICKx) {
                    Node->counter_freq = systick_get_base_freq();
#ifdef HAS_LOG
                    LOG_INFO(LG_SYSTICK, "CoreFrequency:%u Hz", Node->counter_freq);
#endif

                    Node->divider_1us = Node->counter_freq / 1000000UL;

                    if(0 < Node->counter_freq) {
                        Node->SYSTICKx = (SysTickMap_t*)Config->SYSTICKx;
                        float period_s = MSEC_2_SEC(Config->period_ms);
                        float reload = SEC_TO_TIMER_PERIOD(period_s, Node->counter_freq);
                        Node->SYSTICKx->Load.reload = (uint32_t)reload;
#ifdef HAS_LOG
                        LOG_INFO(LG_SYSTICK, "Reload:%u", Node->SYSTICKx->Load.reload);
#endif

                        Node->SYSTICKx->Val.current = 0;

                        SysTickCntl_t SysTickCntlNew;
                        SysTickCntlNew.reg_val = 0;
                        SysTickCntlNew.enable = 1;
                        SysTickCntlNew.tickint = 1;
                        SysTickCntlNew.clksource = Config->clk_source;

                        if(Config->interrupt_on) {
                            SysTickCntlNew.tickint = 1;
                        }

                        Node->SYSTICKx->Cntl.reg_val = SysTickCntlNew.reg_val;
                        res = true;
                        Node->init_done = true;
                    }
                }
            }
        }
    }
    return res;
}

static bool systick_init_one(uint8_t num) {
    bool res = false;
    const SysTickConfig_t* Config = SysTickGetConfig(num);
    if(Config) {
        SysTickHandle_t* Node = SysTickGetNode(num);
        if(Node) {
            res = systick_init_one_ll(Config, Node);
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(LG_SYSTICK, LG_SYSTICK, systick)
// COMPONENT_PROC_PATTERT(LG_SYSTICK, LG_SYSTICK, systick)
