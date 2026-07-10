#ifndef I2S_STM32_TYPES_H
#define I2S_STM32_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "microcontroller.h"
#include "std_includes.h"
#include "i2s_custom_const.h"
#include "i2s_register_types.h"
#include "dma_channel_types.h"

#define I2S_CUSTOM_VARIABLES \
      I2S_HandleTypeDef handle;

typedef struct {
    uint8_t num;
    SPI_TypeDef *I2Sx;
    DmaIsrHandler_t CallBackTxHalf;
    DmaIsrHandler_t CallBackTxDone;
    DmaIsrHandler_t CallBackRxHalf;
    DmaIsrHandler_t CallBackRxDone;
    IRQn_Type irq_n;
    IRQn_Type dma_tx_irq_n;
    IRQn_Type dma_rx_irq_n;
    DmaInfoChannel_t DmaInfoChannelTx;
    DmaInfoChannel_t DmaInfoChannelRx;
    bool valid;
}I2sInfo_t;



#ifdef __cplusplus
}
#endif

#endif /* I2S_STM32_TYPES_H */
