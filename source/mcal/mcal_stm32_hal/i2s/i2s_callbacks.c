#include "i2s_callbacks.h"

#include "i2s_custom_misc.h"
#include "i2s_mcal.h"
#include "gpio_mcal.h"
#include "hal_mcal.h"

bool i2s_isr_custom_echo(I2sHandle_t* Node) {
    bool res = false ;
    if(Node->echo) {
        memcpy((void*) &Node->tx_sample, (void*) &Node->rx_sample, sizeof(Node->tx_sample));
#ifdef SPI_I2S_FULLDUPLEX_SUPPORT
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_I2SEx_TransmitReceive_DMA(Node->pHandle, (uint16_t*) &Node->tx_sample, (uint16_t*) &Node->rx_sample, 2);
        res = HAL_retToRes(ret);
#endif /*SPI_I2S_FULLDUPLEX_SUPPORT*/
    }
    return res;
}

void HAL_I2SEx_TxRxCpltCallback(I2S_HandleTypeDef* hi2s) {
    int8_t num = 0;
    num = get_i2s_index(hi2s->Instance);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->it_cnt++;
        Node->it_done = true;
        //gpio_logic_level_set(Node->PadDmaRx,GPIO_LVL_LOW);
        I2sRxDoneCallback(Node);
        I2sTxDoneCallback(Node);
    }
}

void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef* hi2s) {
    int8_t num = 0;
    num = get_i2s_index(hi2s->Instance);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->it_cnt++;
        Node->it_done = true;
        gpio_logic_level_set(Node->PadDmaRx,GPIO_LVL_HI);
        I2sRxHalfCallback(Node);
    }
}

void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef* hi2s) {
    int8_t num = 0;
    num = get_i2s_index(hi2s->Instance);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->it_cnt++;
        Node->it_done = true;
        gpio_logic_level_set(Node->PadDmaRx,GPIO_LVL_LOW);
        I2sRxDoneCallback(Node);
    }
}

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef* hi2s) {
    int8_t num = 0;
    num = get_i2s_index(hi2s->Instance);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->it_cnt++;
        Node->it_done = true;
        gpio_logic_level_set(Node->PadDmaTx, GPIO_LVL_HI);
        I2sTxHalfCallback(Node);
    }
}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef* hi2s) {
    int8_t num = 0;
    num = get_i2s_index(hi2s->Instance);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->it_cnt++;
        Node->it_done = true;
        gpio_logic_level_set(Node->PadDmaTx, GPIO_LVL_LOW);
        I2sTxDoneCallback(Node);
    }
}

void HAL_I2SEx_TxRxHalfCpltCallback(I2S_HandleTypeDef* hi2s) {
    int8_t num = 0;
    num = get_i2s_index(hi2s->Instance);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->it_cnt++;
        Node->it_done = true;
        I2sRxHalfCallback(Node);
        I2sTxHalfCallback(Node);
    }
}

void HAL_I2S_ErrorCallback(I2S_HandleTypeDef* hi2s) {
    int8_t num = 0;
    num = get_i2s_index(hi2s->Instance);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->it_cnt++;
        Node->it_done = true;
        I2sErrorCallback(Node);
#ifdef SPI_I2S_FULLDUPLEX_SUPPORT
        __HAL_I2SEXT_CLEAR_OVRFLAG(Node->pHandle);
#endif
    }
}
