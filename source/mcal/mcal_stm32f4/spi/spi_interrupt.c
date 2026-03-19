#include "spi_interrupt.h"

#include "log.h"
#include "spi_mcal.h"

bool spi_read_interrupt(uint8_t num, uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_DEBUG(SPI, "SPI%u,RxInt,Size:%u", num, size);
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        Node->rx_done = false;
        Node->operation = INTERFACE_OPERATION_RECEPTION;
        if(data) {

            HAL_StatusTypeDef ret = HAL_ERROR;
            ret = HAL_SPI_Receive_IT(&Node->handle, data, size);
            if(HAL_OK == ret) {
                LOG_PARN(SPI, "%u RxOk", num);
                res = spi_wait_rx_ll(Node);
                if(res) {
                    Node->rx_byte_cnt += rx_array_len;
                }
            } else {
                LOG_ERROR(SPI, "RxErr %u %s", ret, HalStatusToStr(ret));
            }


        }
        Node->operation = INTERFACE_OPERATION_IDLE;
    }
    return res;
}

bool spi_write_interrupt(uint8_t num, const uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_DEBUG(SPI, "SPI%u,WriteInt,Size:%u", num, size);
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        Node->tx_done = false;
        Node->operation = INTERFACE_OPERATION_SEND;
        if(data) {
            if(size) {
                HAL_StatusTypeDef ret = HAL_ERROR;
                (void)ret;
                ret = HAL_SPI_Transmit_IT(&Node->handle, (uint8_t*)data, size);
                if(HAL_OK == ret) {
                    LOG_PARN(SPI, "TxOk");
                    res = spi_wait_tx_ll(Node);
                    if(res) {
                        Node->tx_byte_cnt += tx_array_len;
                    }
                } else {
                    LOG_ERROR(SPI, "TxErr %u %s", ret, HalStatusToStr(ret));
                }
            }
        }
        Node->operation = INTERFACE_OPERATION_IDLE;
    }
    return res;
}

bool spi_write_read_interrupt(uint8_t num, const uint8_t* const tx_array, uint8_t* const rx_array, uint32_t size) {
    bool res = false;
    LOG_DEBUG(SPI, "SPI%u,TxRxInt,Size:%u", num, size);
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        Node->tx_done = false;
        Node->rx_done = false;
        Node->txrx_done = false;
        Node->operation = INTERFACE_OPERATION_RECEPTION_AND_TRANSMISSION;
        if(tx_array) {
            if(rx_array) {
                if(size) {
                    HAL_StatusTypeDef ret = HAL_ERROR;
                    ret = HAL_SPI_TransmitReceive_IT(&Node->handle, (uint8_t*)tx_array, rx_array, size);
                    if(HAL_OK == ret) {
                        LOG_PARN(SPI, "%u TxRxOk", num);
                        res = spi_wait_txrx_ll(Node);
                        if(res) {
                            Node->rx_byte_cnt += size;
                            Node->tx_byte_cnt += size;
                        }
                    } else {
                        LOG_ERROR(SPI, "TxRxErr %u %s", ret, HalStatusToStr(ret));
                    }
                }
            }
        }
        Node->operation = INTERFACE_OPERATION_IDLE;
    }
    return res;
}
