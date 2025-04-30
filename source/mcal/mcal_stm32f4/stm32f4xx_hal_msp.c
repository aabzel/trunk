#include "stm32f4xx_hal_msp.h"

#include "stm32f4xx_hal.h"
#include "systick_mcal.h"

uint32_t HAL_GetTick(void) {
    static uint32_t local_cnt = 0;
    local_cnt++;
    uint32_t ret_val = 0;
    bool res = systick_general_is_run();
    if(res) {
        ret_val = uwTick;
    } else {
        ret_val = local_cnt;
    }

    return ret_val;
}

void HAL_IncTick(void) { uwTick += uwTickFreq; }

#if 0
void HAL_MspInit(void) {
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();

    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);
}
#endif
