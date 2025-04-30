#include "spi_isr.h"

#include "spi_drv.h"
#include "spi_custom_drv.h"
#include "at32f435_437.h"

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi) {
    SpiName_t spi_num = spi_base_2_num(hspi->Instance);
    SpiHandle_t* SpiNode = SpiGetNode(spi_num);
    if(SpiNode) {
        SpiNode->tx_int = true;
        SpiNode->tx_cnt++;
        SpiNode->it_cnt++;
    }
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef* hspi) {
    SpiName_t spi_num = spi_base_2_num(hspi->Instance);
    SpiHandle_t* SpiNode = SpiGetNode(spi_num);
    if(SpiNode) {
        SpiNode->txrx_int = true;
        SpiNode->rx_int = true;
        SpiNode->tx_int = true;
        SpiNode->txrx_cnt++;
        SpiNode->it_cnt++;
    }
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef* hspi) {
    SpiName_t spi_num = spi_base_2_num(hspi->Instance);
    SpiHandle_t* SpiNode = SpiGetNode(spi_num);
    if(SpiNode) {
        SpiNode->rx_int = true;
        SpiNode->rx_cnt++;
        SpiNode->it_cnt++;
    }
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef* hspi) {
    SpiName_t spi_num = spi_base_2_num(hspi->Instance);
    SpiHandle_t* SpiNode = SpiGetNode(spi_num);
    if(SpiNode) {
        SpiNode->err_cnt++;
        hspi->State = HAL_SPI_STATE_READY;
        hspi->ErrorCode = 0;
        hspi->Instance->SR = 0x0002;
    }
}

