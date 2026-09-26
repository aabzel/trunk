#include "stm32fx_hal_msp.h"

#include "compiler_const.h"
#include "stm32fx_hal.h"

#ifdef HAS_DWT
#include "dwt_mcal.h"
#endif

#ifdef HAS_SYSTICK
#include "systick_mcal.h"
#endif

uint32_t HAL_GetTick(void) {
    static uint32_t local_cnt = 0;
    local_cnt++;
    uint32_t up_time_ms = 0;
#ifdef HAS_DWT
    up_time_ms = dwt_get_time_ms32(1);
#endif

#ifdef HAS_SYSTICK
    bool res = systick_is_run();
    if(res) {
        up_time_ms = uwTick;
    } else {
        up_time_ms = local_cnt;
    }
#endif

    return up_time_ms;
}

void HAL_Delay(uint32_t Delay) {
    uint32_t tickstart = HAL_GetTick();
    uint32_t wait = Delay;

    /* Add a freq to guarantee minimum wait */
    if(wait < HAL_MAX_DELAY) {
        wait += (uint32_t)(uwTickFreq);
    }

    while(1) {
        uint32_t cur = HAL_GetTick();
        uint32_t diff = cur - tickstart;
        if(wait < diff) {
            break;
        }
    }
}

_WEAK_FUN_
void HAL_MspInit(void) {
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);
#ifdef HAS_RTOS
    /* PendSV_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
#endif
}
