#include "i2s_full_duplex.h"

#include "dma_channel_mcal.h"
#include "i2s_mcal.h"
#include "stm32fx_hal.h"
#include "i2s_custom_drv.h"

/**
  * @brief  DMA I2S communication error callback
  * @param  hdma pointer to a DMA_HandleTypeDef structure that contains
  *                the configuration information for the specified DMA module.
  * @retval None
  */
static void I2S_DMAError(DMA_HandleTypeDef *hdma) {
  I2S_HandleTypeDef *hi2s = (I2S_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent; /* Derogation MISRAC2012-Rule-11.5 */

  /* Disable Rx and Tx DMA Request */
  CLEAR_BIT(hi2s->Instance->CR2, (SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN));
  hi2s->TxXferCount = 0U;
  hi2s->RxXferCount = 0U;

  hi2s->State = HAL_I2S_STATE_READY;

  /* Set the error code and execute error callback*/
  SET_BIT(hi2s->ErrorCode, HAL_I2S_ERROR_DMA);
  /* Call user error callback */
  HAL_I2S_ErrorCallback(hi2s);
}

/**
  * @brief  DMA I2S transmit process half complete callback
  * @param  hdma pointer to a DMA_HandleTypeDef structure that contains
  *                the configuration information for the specified DMA module.
  * @retval None
  */
static void I2S_DMATxHalfCplt(DMA_HandleTypeDef *hdma)
{
  I2S_HandleTypeDef *hi2s = (I2S_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent; /* Derogation MISRAC2012-Rule-11.5 */

  /* Call user Tx half complete callback */
#if (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
  hi2s->TxHalfCpltCallback(hi2s);
#else
  HAL_I2S_TxHalfCpltCallback(hi2s);
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
}

static void I2S_DMARxHalfCplt(DMA_HandleTypeDef *hdma){
  /* Derogation MISRAC2012-Rule-11.5 */
  I2S_HandleTypeDef *hi2s = (I2S_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;
  HAL_I2S_RxHalfCpltCallback(hi2s);
}


/**
  * @brief  DMA I2S receive process complete callback
  * @param  hdma pointer to a DMA_HandleTypeDef structure that contains
  *                the configuration information for the specified DMA module.
  * @retval None
  */
static void I2S_DMARxCplt(DMA_HandleTypeDef *hdma){
  I2S_HandleTypeDef *hi2s = (I2S_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent; /* Derogation MISRAC2012-Rule-11.5 */
  /* if DMA is configured in DMA_NORMAL Mode */
  if (hdma->Init.Mode == DMA_NORMAL)
  {
    /* Disable Rx DMA Request */
    CLEAR_BIT(hi2s->Instance->CR2, SPI_CR2_RXDMAEN);
    hi2s->RxXferCount = 0U;
    hi2s->State = HAL_I2S_STATE_READY;
  }
  HAL_I2S_RxCpltCallback(hi2s);
}


/**
  * @brief  DMA I2S transmit process complete callback
  * @param  hdma pointer to a DMA_HandleTypeDef structure that contains
  *                the configuration information for the specified DMA module.
  * @retval None
  */
static void I2S_DMATxCplt(DMA_HandleTypeDef *hdma)
{
  I2S_HandleTypeDef *hi2s = (I2S_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent; /* Derogation MISRAC2012-Rule-11.5 */

  /* if DMA is configured in DMA_NORMAL Mode */
  if (hdma->Init.Mode == DMA_NORMAL)
  {
    /* Disable Tx DMA Request */
    CLEAR_BIT(hi2s->Instance->CR2, SPI_CR2_TXDMAEN);

    hi2s->TxXferCount = 0U;
    hi2s->State = HAL_I2S_STATE_READY;
  }
  /* Call user Tx complete callback */
#if (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
  hi2s->TxCpltCallback(hi2s);
#else
  HAL_I2S_TxCpltCallback(hi2s);
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
}

bool i2s_tx_dma_restart(uint8_t dma_node_num,
                               uint8_t i2s_num,
                               uint32_t SrcAddress,
                               uint32_t DataLength
                               ) {
    bool res = false;
    DmaChannelConfig_t *DmaChannel = DmaChannelGetConfig(dma_node_num);
    if(DmaChannel) {
        I2S_HandleTypeDef *pI2sHandle = i2s_num_to_handle(i2s_num);
        if(pI2sHandle) {
            HAL_StatusTypeDef ret;
            (void) ret;
            if(pI2sHandle->hdmatx) {
                pI2sHandle->hdmatx->State = HAL_DMA_STATE_BUSY;
                ret = HAL_DMA_Abort_IT(pI2sHandle->hdmatx);
                __HAL_UNLOCK(pI2sHandle->hdmatx);
                pI2sHandle->hdmatx->State = HAL_DMA_STATE_READY;
                pI2sHandle->hdmatx->Init.Direction = DMA_MEMORY_TO_PERIPH;

                /* Set the I2S Tx DMA Half transfer complete callback */
                pI2sHandle->hdmatx->XferHalfCpltCallback = I2S_DMATxHalfCplt;

                /* Set the I2S Tx DMA transfer complete callback */
                pI2sHandle->hdmatx->XferCpltCallback = I2S_DMATxCplt;

                /* Set the DMA error callback */
                pI2sHandle->hdmatx->XferErrorCallback = I2S_DMAError;

                ret = HAL_DMA_Start_IT(pI2sHandle->hdmatx,
                                       SrcAddress,
                                       (uint32_t) DmaChannel->base_addr_destination,
                                       DataLength);
                res = dma_channel_half_move_it_ctrl(DmaChannel->DmaChPad, true);
            }
        }
        res = true;
    }
    return res;
}


bool i2s_rx_dma_restart(uint8_t dma_node_num,
                        uint8_t i2s_num,
                        uint32_t DstAddress,
                        uint32_t DataLength ) {
    bool res = false;
    DmaChannelConfig_t *DmaChannel = DmaChannelGetConfig(dma_node_num);
    if(DmaChannel) {
        I2S_HandleTypeDef *pI2sHandle = i2s_num_to_handle(i2s_num);
        if(pI2sHandle) {
            HAL_StatusTypeDef ret;
            (void) ret;
            if(pI2sHandle->hdmarx) {
                pI2sHandle->hdmarx->State = HAL_DMA_STATE_BUSY;
                ret = HAL_DMA_Abort_IT(pI2sHandle->hdmarx);
                __HAL_UNLOCK(pI2sHandle->hdmarx);
                pI2sHandle->hdmarx->State = HAL_DMA_STATE_READY;
                pI2sHandle->hdmarx->Init.Direction = DMA_PERIPH_TO_MEMORY;

                /* Set the I2S Rx DMA Half transfer complete callback */
                pI2sHandle->hdmarx->XferHalfCpltCallback = I2S_DMARxHalfCplt;

                /* Set the I2S Rx DMA transfer complete callback */
                pI2sHandle->hdmarx->XferCpltCallback = I2S_DMARxCplt;

                /* Set the DMA error callback */
                pI2sHandle->hdmarx->XferErrorCallback = I2S_DMAError;

                ret = HAL_DMA_Start_IT(pI2sHandle->hdmarx,
                                       (uint32_t) DmaChannel->base_addr_source,
                                       DstAddress, DataLength);
                res = dma_channel_half_move_it_ctrl(DmaChannel->DmaChPad, true);
            }
        }
        res = true;
    }
    return res;
}
