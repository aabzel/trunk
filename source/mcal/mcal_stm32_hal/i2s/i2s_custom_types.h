#ifndef I2S_STM32_TYPES_H
#define I2S_STM32_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "microcontroller.h"
#include "std_includes.h"
#include "clock_const.h"
#include "i2s_custom_const.h"
#include "i2s_register_types.h"
#include "dma_channel_types.h"

#define I2S_CONFIG_CUSTOM                 \
        I2S_HandleTypeDef* pHandle;

#define I2S_CUSTOM_VARIABLES              \
        I2S_HandleTypeDef* pHandle;       \
        volatile SPI_TypeDef *I2Sx;

typedef struct {
    uint8_t num;
    volatile SPI_TypeDef *I2Sx;
    DmaIsrHandler_t CallBackTxHalf;
    DmaIsrHandler_t CallBackTxDone;
    DmaIsrHandler_t CallBackRxHalf;
    DmaIsrHandler_t CallBackRxDone;
    IRQn_Type irq_n;
    IRQn_Type dma_tx_irq_n;
    IRQn_Type dma_rx_irq_n;
    ClockBus_t clock_bus;
    DmaInfoChannel_t DmaInfoChannelTx;
    DmaInfoChannel_t DmaInfoChannelRx;
    bool valid;
}I2sInfo_t;

typedef struct {
    I2sReg_SPI_I2SPR_t I2SPR;
    int32_t abs_error;
}I2sPrescalerInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* I2S_STM32_TYPES_H */
