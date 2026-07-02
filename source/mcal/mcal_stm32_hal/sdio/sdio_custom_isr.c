#include "sdio_isr.h"

#include "sdio_mcal.h"
#include "sdio_types.h"
#include "time_mcal.h"

void HAL_SD_ErrorCallback(SD_HandleTypeDef* hsd) {
    uint8_t sdio_num = SdioInstance2num(hsd->Instance);
    SdioHandle_t* Node = SdioGetNode(sdio_num);
    if(Node) {
        Node->err_cnt++;
    }
}

void HAL_SD_AbortCallback(SD_HandleTypeDef* hsd) {
    uint8_t sdio_num = SdioInstance2num(hsd->Instance);
    SdioHandle_t* Node = SdioGetNode(sdio_num);
    if(Node) {
        Node->abort_cnt++;
    }
}

void HAL_SD_TxCpltCallback(SD_HandleTypeDef* hsd) {
    uint8_t sdio_num = SdioInstance2num(hsd->Instance);
    SdioHandle_t* Node = SdioGetNode(sdio_num);
    if(Node) {
        Node->tx_done = true;
        Node->tx_cnt++;
        Node->tx_time_stamp = time_get_ms32();
    }
}

void HAL_SD_RxCpltCallback(SD_HandleTypeDef* hsd) {
    uint8_t sdio_num = SdioInstance2num(hsd->Instance);
    SdioHandle_t* Node = SdioGetNode(sdio_num);
    if(Node) {
        Node->rx_done = true;
        Node->rx_cnt++;
        Node->rx_time_stamp = time_get_ms32();
    }
}
