#include "dwt_mcal.h"

#include "clock_mcal.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "hal_mcal.h"
#ifdef HAS_LOG
#include "log.h"
#endif

COMPONENT_GET_NODE(Dwt, dwt)
COMPONENT_GET_CONFIG(Dwt, dwt)


/*   ISO-26262 require verify configuration   */
bool DwtIsValidConfig(const DwtConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
#ifdef HAS_LOG
            LOG_ERROR(LG_DWT, "DWT%u,Name,Err", Config->num);
#endif
            //res = false;
        }
        ifn(Config->DWTx) {
#ifdef HAS_LOG
            LOG_ERROR(LG_DWT, "DWT%u,DWTx,Err", Config->num);
#endif
            res = false;
        }
        ifn(Config->counter_freq) {
#ifdef HAS_LOG
            LOG_ERROR(LG_DWT, "DWT%u,CoreFreq,Err", Config->num);
#endif
            //res = false;
        }
    }
    return res;
}

bool dwt_init_custom(void) {
    bool res = false;
#ifdef HAS_LOG
    LOG_INFO(LG_DWT, "Version:%s", DWT_VERSION);
#endif
    return res;
}

bool dwt_init_common(const DwtConfig_t* const Config, DwtHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->DWTx = Config->DWTx;
            Node->num = Config->num;
            Node->counter_freq = Config->counter_freq;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

uint32_t dwt_timer_get(uint8_t num) {
    uint32_t cyc_cnt = 0;
    DwtHandle_t* Node = DwtGetNode(num);
    if(Node) {
        /*32-bit, incrementing (up) cycle counter. When enabled, this
          counter counts the number of core cycles.
          Counting is suspended when the core is halted in Debug state.
          The counter is UNKNOWN on reset.*/
        cyc_cnt = Node->DWTx->CYCCNT;
    }
    return cyc_cnt;
}

#if 0
void configureTimerForRunTimeStats(void) {
    static bool already_init = false;
    if (already_init) {
        return;
    }
    CoreDebug->DEMCR |= 0x01000000;
    DWT->CYCCNT = 0;
    DWT->CTRL |= 1; /* enable the counter */
    already_init = true;
}

#endif

uint64_t dwt_get_run_time_counter_u64(uint8_t num) {
    uint64_t up_time_u64 = 0;
    DwtHandle_t* Node = DwtGetNode(num);
    if(Node) {
        enter_critical();
        Node->up_time_u32 = Node->DWTx->CYCCNT;
        if(Node->up_time_u32 < Node->up_time_u32_prev) {
            Node->wrap_counter += DWT_U32_OVERFLOW_VALUE;
        }
        Node->up_time_u32_prev = Node->up_time_u32;
        exit_critical();
        Node->up_time_u64 = Node->wrap_counter | Node->up_time_u32;
        up_time_u64 = Node->up_time_u64;
    }
    return up_time_u64;
}

uint64_t dwt_get_time_ms64(uint8_t num) {
    uint64_t time_ms64 = 0;
    DwtHandle_t* Node = DwtGetNode(num);
    if(Node) {
        uint64_t counter_u64 = dwt_get_run_time_counter_u64(num);
        uint64_t divider = Node->counter_freq * 1000UL;
        time_ms64 = counter_u64 / divider;
    }
    return time_ms64;
}

uint64_t dwt_get_time_us64(uint8_t num) {
    uint64_t time_us64 = 0;
    DwtHandle_t* Node = DwtGetNode(num);
    if(Node) {
        uint64_t counter_u64 = dwt_get_run_time_counter_u64(num);
        // Node->divider_1us = Node->counter_freq/1000000UL;
        time_us64 = (counter_u64 / Node->divider_1us);
    }
    return time_us64;
}

uint32_t dwt_get_time_ms32(uint8_t num) {
    uint32_t time_ms32 = 0;
    DwtHandle_t* Node = DwtGetNode(num);
    if(Node) {
        uint64_t counter_u64 = dwt_get_run_time_counter_u64(num);
        // Node->divider_1ms = Node->counter_freq/1000UL;
        time_ms32 = (uint32_t)(counter_u64 / Node->divider_1ms);
    }
    return time_ms32;
}

void dwt_delay_ms(uint8_t num, uint32_t delay_in_ms) {
    uint64_t stop = dwt_get_time_ms64(num) + delay_in_ms;
    while(dwt_get_time_ms64(num) < stop) {
    }
}

bool dwt_proc_one(uint8_t num) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(LG_DWT, "DWT_%u,Proc", num);
#endif
    DwtHandle_t* Node = DwtGetNode(num);
    if(Node) {
        Node->spin++;
        dwt_get_run_time_counter_u64(num);
    }
    return res;
}

bool dwt_init_one(uint8_t num) {
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(LG_DWT, "DWT_%u", num);
#endif
    const DwtConfig_t* Config = DwtGetConfig(num);
    if(Config) {
        res = DwtIsValidConfig(Config);
        if(res) {
#ifdef HAS_DWT_DIAG
            LOG_WARNING(LG_DWT, "%s", DwtConfigToStr(Config));
#endif
            DwtHandle_t* Node = DwtGetNode(num);
            if(Node) {
                res = dwt_init_common(Config, Node);

                // Enable trace block (Core Debug Interface)
                CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // set bit 24
                // CoreDebug->DEMCR |= 0x01000000;  // ????
                Node->DWTx->CYCCNT = 0;
                Node->counter_freq = clock_core_freq_get();
                Node->divider_1us = Node->counter_freq / 1000000UL;
                Node->divider_1ms = Node->counter_freq / 1000UL;
                ARM_DWT_CTRL_t DWT_CTRL;
                DWT_CTRL.dword = Node->DWTx->CTRL;
                DWT_CTRL.CYCCNTENA = 1;            /* enable the counter */
                Node->DWTx->CTRL = DWT_CTRL.dword; /* enable the counter */
                Node->valid = true;
                Node->init = true;
            } else {
#ifdef HAS_LOG
                LOG_ERROR(LG_DWT, "NodeErr %u", num);
#endif
            }
        } else {
#ifdef HAS_LOG
            LOG_ERROR(LG_DWT, "ConfigErr %u", num);
#endif
        }
    } else {
#ifdef HAS_LOG
        LOG_PARN(LG_DWT, "ConfigErr %u", num);
#endif
    }
    return res;
}

COMPONENT_INIT_PATTERT(LG_DWT, DWT, dwt)
COMPONENT_PROC_PATTERT(LG_DWT, DWT, dwt)
