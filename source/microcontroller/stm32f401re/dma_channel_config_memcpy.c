#include "dma_channel_config_memcpy.h"

#include "data_utils.h"
#include "microcontroller_const.h"

uint8_t toArray[DMA_MEMCPY_SIZE]={0};
uint8_t fromArray[DMA_MEMCPY_SIZE]={0};

bool CallBackHalfMemCpy(void){return true;}
bool CallBackDoneMemCpy(void){return true;}






