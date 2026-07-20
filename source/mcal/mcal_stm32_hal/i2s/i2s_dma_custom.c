#include "i2s_dma_custom.h"

#include "i2s_mcal.h"
#include "hal_diag.h"
#include "dma_channel_mcal.h"
#include "i2s_custom_drv.h"

bool i2s_dma_init_tx(const uint8_t num) {
    bool res = false;
    I2sHandle_t *Node = I2sGetNode(num);
    if(Node) {
        res = dma_channel_init_one(Node->dma_channel_tx_num);
        //DMA_HandleTypeDef* pDmaTxHandle = dma_get_handle(Node->DmaChTx.dma_num);
        DmaChannelHandle_t* DmaCh = DmaChannelGetNode(Node->dma_channel_tx_num);
        if(DmaCh) {
            SET_BIT(Node->pHandle->Instance->CR2, SPI_CR2_TXDMAEN );
            __HAL_LINKDMA(Node->pHandle, hdmatx, (DmaCh->dma_h));
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
            SET_BIT(Node->pHandle->Instance->CR2, SPI_CR2_RXDMAEN);
            __HAL_LINKDMA(Node->pHandle, hdmarx, DmaCh->dma_h);
            res = true;
        }
    }
    return res;
}

static bool i2s_dma_full_duplex_init( I2sHandle_t *Node){
    bool res = false;
    res = i2s_dma_init_tx(Node->num) ;
    res = i2s_dma_init_rx(Node->num) && res;


    const I2sInfo_t* Info = I2sGetInfo(4);
    if(Info) {
        I2sReg_SPI_CR2_t SPI_CR2;
        SPI_CR2.dword = Info->I2Sx->CR2;
        SPI_CR2.RXDMAEN=1;
        SPI_CR2.TXDMAEN=1;
        SPI_CR2.ERRIE=1;
        Info->I2Sx->CR2 = SPI_CR2.dword;



        I2sReg_SPI_I2SCFGR_t SPI_I2SCFGR;
        SPI_I2SCFGR.dword = Info->I2Sx->I2SCFGR;

        SPI_I2SCFGR.CHLEN=0;
        SPI_I2SCFGR.DATLEN=0;
        SPI_I2SCFGR.CKPOL=0;
        SPI_I2SCFGR.I2SSTD=0;
        SPI_I2SCFGR.PCMSYNC=0;
        SPI_I2SCFGR.I2SCFG=1;
        SPI_I2SCFGR.I2SE=1;
        SPI_I2SCFGR.I2SMOD=1;
        Info->I2Sx->I2SCFGR=SPI_I2SCFGR.dword;
    }


    return res;
}


static bool i2s_dma_half_duplex_init( I2sHandle_t *Node){
    bool res = false;
        switch(Node->direction) {
            case CONNECT_DIR_TRANSMIT: {
                res = i2s_dma_init_tx(Node->num) ;
            } break;

            case CONNECT_DIR_RECEIVER: {
                res = i2s_dma_init_rx(Node->num) ;
            } break;

            default:{
                res = false;
            } break;
        }
    return res;
}

bool i2s_dma_init(const uint8_t num) {
    bool res = false;
    I2sHandle_t *Node = I2sGetNode(num);
    if(Node){
        switch(Node->full_duplex){
            case FULL_DUPLEX_ON: {
                res = i2s_dma_full_duplex_init( Node);
            }break;
            case FULL_DUPLEX_OFF: {
                res = i2s_dma_half_duplex_init(Node);
            }break;
            default:res = false; break;
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
        HAL_DMA_Abort(Node->pHandle->hdmarx);
        //HAL_I2S_DMAStop(Node->pHandle);
        Node->pHandle->State = HAL_I2S_STATE_READY;
        HAL_StatusTypeDef ret = HAL_I2S_Receive_DMA(Node->pHandle, (uint16_t*) array, words);
        if(HAL_OK == ret) {
            res = true;
        } else {
            LOG_DEBUG(I2S, "ReadErr:%u %s", ret, HalStatusToStr(ret));
        }
    }
    return res;
}

bool i2s_dma_pause(uint8_t num) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret;
        ret = HAL_I2S_DMAPause(Node->pHandle);
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
        HAL_I2S_DMAStop(Node->pHandle);
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
