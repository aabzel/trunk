#include "interrupt_mcal.h"

#ifdef HAS_BIT_UTILS
#include "bit_utils.h"
#endif
#include "csr.h"
#include "interrupt_custom_drv.h"
#ifdef HAS_LOG
#include "log.h"
#endif
#include "mik32_hal_irq.h"
#include "scr1_csr_encoding.h"
#include "std_includes.h"
#include "sys_config.h"

extern uint8_t __TRAP_TEXT_START__;

bool interrupt_enable(void) {
    bool res = true;
    // write_csr
    // write_csr(mtvec, &__TRAP_TEXT_START__); //
    __HAL_PCC_EPIC_CLK_ENABLE();
    HAL_IRQ_EnableInterrupts();
    return res;
}

bool interrupt_disable(void) {
    bool res = true;
    HAL_IRQ_DisableInterrupts();
    // clear_csr(mie, MIE_MEIE);
    return res;
}

bool interrupt_is_valid_num(int16_t irq_n) {
    bool res = false;
    if(irq_n <= INT_NUM_DAC1) {
        res = true;
    }
    return res;
}

bool interrupt_level_control(int16_t irq_n, bool on_off) {
    bool res = false;
    res = interrupt_is_valid_num(irq_n);
    if(res) {
        uint32_t interrupt_mask = 1U << irq_n;
        switch((uint32_t)on_off) {
        case true:
            HAL_EPIC_MaskLevelSet(interrupt_mask);
            break;
        case false:
            HAL_EPIC_MaskLevelClear(interrupt_mask);
            break;
        default:
            break;
        }
    }
    return res;
}

bool interrupt_edge_ctrl(int16_t irq_n, bool on_off) {
    bool res = false;
    res = interrupt_is_valid_num(irq_n);
    if(res) {
        uint32_t interrupt_mask = 1U << irq_n;
        switch((uint32_t)on_off) {
        case true:
            HAL_EPIC_MaskEdgeSet(interrupt_mask);
            break;
        case false:
            HAL_EPIC_MaskEdgeClear(interrupt_mask);
            break;
        default:
            break;
        }
    }
    return res;
}

bool interrupt_control(int16_t irq_n, bool on_off) {
    bool res = false;
    res = interrupt_edge_ctrl(irq_n, on_off);
    res = interrupt_level_control(irq_n, on_off) && res;
    return res;
}

bool interrupt_init_custom(void) {
    bool res = true;
    // write_csr(mtvec, &__TEXT_START__);
    return res;
}

bool interrupt_is_active(int16_t irq_n) {
    bool res = false;
    res = interrupt_is_valid_num(irq_n);
    if(res) {
        uint32_t status = HAL_EPIC_GetRawStatus();
        res = false;
        if(CHECK_BIT_NUM(status, irq_n)) {
            res = true;
        }
    }
    return res;
}

bool interrupt_get_priority(int16_t irq_n, uint8_t* const preempt_priority, uint8_t* const sub_priority) {
    bool res = false;
    res = interrupt_is_active(irq_n);
    if(res) {
        *preempt_priority = 0;
        *sub_priority = 0;
    } else {
        *preempt_priority = 0xFE;
        *sub_priority = 0xFE;
    }

    return res;
}
