#include "i2s_dma_custom.h"

#include "i2s_mcal.h"
#include "hal_diag.h"
#include "dma_channel_mcal.h"


bool i2s_dma_init_tx(const uint8_t num) {
    bool res = false;
    I2sHandle_t *Node = I2sGetNode(num);
    if(Node) {
        res = dma_channel_init_one(Node->dma_channel_tx_num);
        //DMA_HandleTypeDef* pDmaTxHandle = dma_get_handle(Node->DmaChTx.dma_num);
        DmaChannelHandle_t* DmaCh = DmaChannelGetNode(Node->dma_channel_tx_num);
        if(DmaCh) {
            SET_BIT(Node->handle.Instance->CR2, SPI_CR2_TXDMAEN );
            __HAL_LINKDMA(&Node->handle, hdmatx, (DmaCh->dma_h));
            res = true;
        }
    }
    return res;
}

bool i2s_dma_init_rx(const uint8_t num) {
    bool res = false;
    I2sHandle_t *Node = I2sGetNode(num);
    if(Node) {
        res = dma_channel_init_one(Node->dma_channel_rx_num);
        DmaChannelHandle_t* DmaCh = DmaChannelGetNode(Node->dma_channel_rx_num);
        if(DmaCh) {
            SET_BIT(Node->handle.Instance->CR2, SPI_CR2_RXDMAEN);
            __HAL_LINKDMA(&Node->handle, hdmarx, DmaCh->dma_h);
            res = true;
        }
    }
    return res;
}

bool i2s_dma_init(const uint8_t num) {
    bool res = false;
    I2sHandle_t *Node = I2sGetNode(num);
    if(Node){
        switch(Node->direction) {

            case CONNECT_DIR_TRANSMIT: {
                res = i2s_dma_init_tx(num) ;
            } break;

            case CONNECT_DIR_RECEIVER: {
                res = i2s_dma_init_rx(num) ;
            } break;

            default:{
                res = false;
            } break;
        }
    }
    return res;
}

bool i2s_dma_read(const uint8_t num, uint16_t* const array, const uint32_t words) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->rx_done = false;
        Node->rx_half = false;
        //HAL_DMA_Abort(Node->handle.hdmarx);
        //HAL_I2S_DMAStop(&Node->handle);
        HAL_StatusTypeDef ret = HAL_I2S_Receive_DMA(&Node->handle, (uint16_t*) array, words);
        if(HAL_OK == ret) {
            res = true;
        } else {
            LOG_ERROR(I2S, "ReadErr:%u %s", ret, HalStatusToStr(ret));
        }
    }
    return res;
}

bool i2s_dma_pause(uint8_t num) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret;
        ret = HAL_I2S_DMAPause(&Node->handle);
        if(HAL_OK == ret) {
            res = true;
            LOG_INFO(I2S, "DmaPause" LOG_OK);
        } else {
            LOG_ERROR(I2S, "DmaPause %s", HalStatusToStr(ret));
        }
    } else {
        LOG_ERROR(I2S, "NodeGetErr");
    }
    return res;
}

bool i2s_dma_stop(uint8_t num) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret = HAL_OK;
        HAL_I2S_DMAStop(&Node->handle);
        if(HAL_OK == ret) {
            res = true;
            LOG_INFO(I2S, "DmaStop" LOG_OK);
        } else {
            LOG_ERROR(I2S, "I2S_%u,DmaStop:%u=%s",num,ret, HalStatusToStr(ret));
        }
    } else {
        LOG_ERROR(I2S, "NodeGetErr");
    }
    return res;
}
