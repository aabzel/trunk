#include "dma_config.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "data_utils.h"
#include "at32f435_437.h"
#include "hal_diag.h"

#ifndef HAS_DMA
#error "+ HAS_DMA"
#endif /*HAS_DMA*/

const DmaConfig_t DmaConfig[]={
#ifdef HAS_DMA2

#endif /*HAS_DMA2*/

#ifdef HAS_DMA2

#endif /*HAS_DMA2*/
};

DmaHandle_t DmaInstance[]={
#ifdef HAS_DMA2

#endif /*HAS_DMA2*/
};

uint32_t dma_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(DmaInstance); 
    cnt2 = ARRAY_SIZE(DmaConfig); 
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
