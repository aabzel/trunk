#include "sdio_isr.h"

#include "sdio_types.h"
#include "sdio_bsp.h"
#include "sdio_drv.h"
#include "time_utils.h"

void HAL_SD_ErrorCallback(SD_HandleTypeDef* hsd) {
    uint8_t sdio_num = SdioInstance2num(hsd->Instance);
    SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
    if(SdioNode) {
        SdioNode->err_cnt++;
    }
}

void HAL_SD_AbortCallback(SD_HandleTypeDef* hsd) {
    uint8_t sdio_num = SdioInstance2num(hsd->Instance);
    SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
    if(SdioNode) {
        SdioNode->abort_cnt++;
    }
}

void HAL_SD_TxCpltCallback(SD_HandleTypeDef* hsd) {
    uint8_t sdio_num = SdioInstance2num(hsd->Instance);
    SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
    if(SdioNode) {
        SdioNode->tx_int = true;
        SdioNode->tx_cnt++;
        SdioNode->tx_time_stamp = time_get_ms32();
    }
}

void HAL_SD_RxCpltCallback(SD_HandleTypeDef* hsd) {
    uint8_t sdio_num = SdioInstance2num(hsd->Instance);
    SdioHandle_t* SdioNode = SdioGetNode(sdio_num);
    if(SdioNode) {
        SdioNode->rx_int = true;
        SdioNode->rx_cnt++;
        SdioNode->rx_time_stamp = time_get_ms32();
    }
}
