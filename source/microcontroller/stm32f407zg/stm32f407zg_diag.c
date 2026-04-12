#include "stm32f407zg_diag.h"

#include "interrupt_types.h"

#define INT_NUM_INFO_DMA

const IntNumInfo_t IntNumInfo[]={
    INT_NUM_INFO_DMA
    { .int_n = USART3_IRQn , .name = "USART3", },
};

uint32_t interrupt_info_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(IntNumInfo);
    return cnt;
}


