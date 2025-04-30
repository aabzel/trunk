#include "cryp_isr.h"

#include "cryp_drv.h"

#include "stm32f4xx_hal.h"
#include "cryp_custom_drv.h"

void HAL_CRYP_InCpltCallback(CRYP_HandleTypeDef* hcryp) {
    if(CRYP == hcryp->Instance) {
        int8_t cryp_num = CrypInstance2Num(hcryp->Instance);
        CrypHandle_t* CrypNode = CrypGetNode(cryp_num);
        if(CrypNode) {
            CrypNode->int_flag = true;
            CrypNode->int_cnt++;
            CrypNode->in_cnt++;
        }
    }
}

void HAL_CRYP_OutCpltCallback(CRYP_HandleTypeDef* hcryp) {
    if(CRYP == hcryp->Instance) {
        int8_t cryp_num = CrypInstance2Num(hcryp->Instance);
        CrypHandle_t* CrypNode = CrypGetNode(cryp_num);
        if(CrypNode) {
            CrypNode->int_flag = true;
            CrypNode->int_cnt++;
            CrypNode->out_cnt++;
        }
    }
}

void HAL_CRYP_ErrorCallback(CRYP_HandleTypeDef* hcryp) {
    if(CRYP == hcryp->Instance) {
        int8_t cryp_num = CrypInstance2Num(hcryp->Instance);
        CrypHandle_t* CrypNode = CrypGetNode(cryp_num);
        if(CrypNode) {
            CrypNode->int_flag = true;
            CrypNode->int_cnt++;
            CrypNode->error_cnt++;
        }
    }
}
