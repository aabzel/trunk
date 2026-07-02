#include "spi_dma.h"

#include "log.h"
#include "spi_mcal.h"
#include "stm32fx_hal.h"
#include "hal_mcal.h"
#include "dma_custom.h"
#include "spi_dma_custom.h"

bool spi_dma_init_tx(const uint8_t num) {
    bool res = false;
    SpiHandle_t *Node = SpiGetNode(num);
    if(Node) {
        res = dma_channel_init_one(Node->dma_channel_tx_num);
        //DMA_HandleTypeDef* pDmaTxHandle = dma_get_handle(Node->DmaChTx.dma_num);
        DmaChannelHandle_t* DmaCh = DmaPadGetNodeItem(Node->DmaChTx);
        if(DmaCh){
            SET_BIT(Node->handle.Instance->CR2, SPI_CR2_TXDMAEN );
            __HAL_LINKDMA(&Node->handle,hdmatx,(DmaCh->dma_h));
            res = true;
        }
    }
    return res;
}

bool spi_dma_init_rx(const uint8_t num) {
    bool res = false;
    SpiHandle_t *Node = SpiGetNode(num);
    if(Node) {
        res = dma_channel_init_one(Node->dma_channel_rx_num);
        //DMA_HandleTypeDef* pDmaRxHandle = dma_get_handle(Node->DmaChRx.dma_num);
        DmaChannelHandle_t* DmaCh = DmaPadGetNodeItem(Node->DmaChRx);
        if(DmaCh) {
            SET_BIT(Node->handle.Instance->CR2, SPI_CR2_RXDMAEN);
            __HAL_LINKDMA(&Node->handle,hdmarx,DmaCh->dma_h);
            res = true;
        }
    }
    return res;
}

bool spi_dma_init(const uint8_t num) {
    bool res = true;
    res = spi_dma_init_rx(num)&&res;
    res = spi_dma_init_tx(num)&&res;
    return res;
}

bool spi_dma_write(const uint8_t num, const uint8_t* const data, const uint32_t size) {
    bool res = false;
    SpiHandle_t *Node = SpiGetNode(num);
    if(Node) {
        Node->tx_done = false;
        HAL_StatusTypeDef ret;
        //res = spi_dma_init_tx(num);
        Node->handle.hdmatx->State = HAL_DMA_STATE_READY;
        ret = HAL_SPI_DMAStop(&Node->handle);
        ret = HAL_SPI_Transmit_DMA(&Node->handle, data, (uint16_t) size);
        res = HAL_retToRes(ret);
        if(res) {
            LOG_PARN(SPI_DMA, "TxOk");
            res = spi_wait_tx_ll(Node);
            if(res) {
                Node->tx_cnt += size;
            }
        } else {
            LOG_ERROR(SPI_DMA, "SPI%u,TxErr:%u=%s", num, ret, HalStatusToStr(ret));
        }
    }
    return res;
}


bool spi_dma_read(const uint8_t num, uint8_t* const data, const uint32_t size) {
    bool res = false;
    SpiHandle_t *Node = SpiGetNode(num);
    if(Node) {
        Node->rx_done = false;
        //res = spi_dma_init_rx(num);
        HAL_StatusTypeDef ret = HAL_ERROR;
        Node->handle.hdmarx->State = HAL_DMA_STATE_READY;
        ret = HAL_SPI_DMAStop(&Node->handle);
        ret = HAL_SPI_Receive_DMA(&Node->handle, data, (uint16_t) size);
        if(HAL_OK == ret) {
            LOG_PARN(SPI_DMA, "SPI%u RxOk", num);
            res = spi_wait_rx_ll(Node);
            if(res) {
                Node->rx_cnt += size;
            }
        } else {
            LOG_ERROR(SPI_DMA, "SPI%u,RxErr:%u=%s",num, ret, HalStatusToStr(ret));
        }
    }
    return res;
}


bool spi_dma_write_read(const uint8_t num, const uint8_t* const tx_array, uint8_t* const rx_array, const uint32_t size) {
    bool res = false;
    SpiHandle_t *Node = SpiGetNode(num);
    if(Node) {
        Node->rx_done = false;
        Node->tx_done = false;
        Node->txrx_done = false;
        Node->handle.hdmatx->State = HAL_DMA_STATE_READY;
        Node->handle.hdmarx->State = HAL_DMA_STATE_READY;
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_SPI_DMAStop(&Node->handle);
        ret = HAL_SPI_TransmitReceive_DMA(&Node->handle, tx_array, rx_array, size);
        if(HAL_OK == ret) {
            LOG_PARN(SPI_DMA, "SPI%u,RxTxOk", Node->num);
            res = spi_wait_txrx_ll(Node);
            if(res) {
                Node->rx_cnt += size;
                Node->tx_cnt += size;
                Node->txrx_cnt += size;
            }
        } else {
            LOG_ERROR(SPI_DMA, "SPI%u,RxTxErr:%u=%s",num, ret, HalStatusToStr(ret));
        }
    }
    return res;
}

