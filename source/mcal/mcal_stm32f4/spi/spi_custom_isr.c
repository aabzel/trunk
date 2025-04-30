#include "spi_isr.h"

#include "spi_drv.h"
#include "spi_custom_drv.h"
#include "stm32f4xx_hal.h"

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi) {
    SpiName_t spi_num = spi_base_2_num(hspi->Instance);
    SpiHandle_t* Node = SpiGetNode(spi_num);
    if(Node) {
        Node->tx_done = true;
        Node->tx_cnt++;
        Node->it_cnt++;
    }
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef* hspi) {
    SpiName_t spi_num = spi_base_2_num(hspi->Instance);
    SpiHandle_t* Node = SpiGetNode(spi_num);
    if(Node) {
        Node->txrx_done = true;
        Node->rx_done = true;
        Node->tx_done = true;
        Node->txrx_cnt++;
        Node->it_cnt++;
    }
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef* hspi) {
    SpiName_t spi_num = spi_base_2_num(hspi->Instance);
    SpiHandle_t* Node = SpiGetNode(spi_num);
    if(Node) {
        Node->rx_done = true;
        Node->rx_cnt++;
        Node->it_cnt++;
    }
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef* hspi) {
    SpiName_t spi_num = spi_base_2_num(hspi->Instance);
    SpiHandle_t* Node = SpiGetNode(spi_num);
    if(Node) {
        Node->err_cnt++;
        hspi->State = HAL_SPI_STATE_READY;
        hspi->ErrorCode = 0;
        hspi->Instance->SR = 0x0002;
    }
}

