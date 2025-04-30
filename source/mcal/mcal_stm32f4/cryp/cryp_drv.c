#include "cryp_drv.h"

#include "byte_utils.h"
#include "cryp_api.h"
#include "cryp_config.h"
#include "cryp_custom_drv.h"
#include "hal_diag.h"
#include "log.h"
#include "stm32f4xx_hal.h"

static uint32_t CrypAlgo2StmAlgo(CrypAlgorithm_t algo) {
    uint32_t algo_code = 0;
    switch(algo) {
    case CRYP_ALGO_AES_CTR:
        algo_code = CRYP_AES_CTR;
        break;
    case CRYP_ALGO_AES_CBC:
        algo_code = CRYP_AES_CBC;
        break;
    case CRYP_ALGO_AES_ECB:
        algo_code = CRYP_AES_ECB;
        break;
    // case CRYP_ALGO_AES_GCM: algo_code = CRYP_AES_GCM; break; //Galois/Counter Mode
    // case CRYP_ALGO_AES_GCM_GMAC: algo_code = CRYP_AES_GCM_GMAC; break;
    case CRYP_ALGO_DES_ECB:
        algo_code = CRYP_DES_ECB;
        break;
    case CRYP_ALGO_DES_CBC:
        algo_code = CRYP_DES_CBC;
        break;
    case CRYP_ALGO_TDES_ECB:
        algo_code = CRYP_TDES_ECB;
        break;
    default:
        LOG_ERROR(HW_CRYP, "UndefAlgo %u", algo);
        break;
    }
    return algo_code;
}

bool cryp_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(HW_CRYP, "%u Init", num);
    CrypHandle_t* CrypNode = CrypGetNode(num);
    if(CrypNode) {
        const CrypConfig_t* CrypConfigNode = CrypGetConfigNode(num);
        if(CrypConfigNode) {
            CrypNode->int_flag = false;
            CrypNode->cryp_h.Instance = CRYP;
            CrypNode->cryp_h.Init.Algorithm = CrypAlgo2StmAlgo(CrypConfigNode->algo);
            CrypNode->cryp_h.Init.DataType = CRYP_DATATYPE_8B;
            CrypNode->cryp_h.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_BYTE;
            CrypNode->cryp_h.Init.KeySize = CRYP_KEYSIZE_256B;
            CrypNode->cryp_h.Init.KeyIVConfigSkip = CRYP_KEYIVCONFIG_ALWAYS;
            CrypNode->cryp_h.Init.pKey = (uint32_t*)CrypNode->Key256BitQwords;
            CrypNode->cryp_h.Init.pInitVect = (uint32_t*)CrypNode->InitVectorQwords;

            HAL_StatusTypeDef ret = HAL_CRYP_Init((CRYP_HandleTypeDef*)&CrypNode->cryp_h);
            if(HAL_OK == ret) {
                LOG_INFO(HW_CRYP, "InitOk");
                CrypNode->init_done = true;
                res = true;
            } else {
                res = false;
                LOG_ERROR(HW_CRYP, "InitErr %d=%s", ret, HalStatus2Str(ret));
            }
        } else {
            LOG_ERROR(HW_CRYP, "ConfErr %d", num);
        }
    }
    return res;
}

bool cryp_hw_init(void) {
    bool res = true;
    LOG_WARNING(HW_CRYP, "Init..");
    res = cryp_init_one(CRYP_HW_NUM);
    return res;
}

void HAL_CRYP_MspInit(CRYP_HandleTypeDef* crypHandle) {
    if(CRYP == crypHandle->Instance) {
        __HAL_RCC_CRYP_CLK_ENABLE();
        HAL_NVIC_SetPriority(CRYP_IRQn, 7, 7);
        HAL_NVIC_EnableIRQ(CRYP_IRQn);
    }
}

void HAL_CRYP_MspDeInit(CRYP_HandleTypeDef* crypHandle) {
    if(CRYP == crypHandle->Instance) {
        __HAL_RCC_CRYP_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(CRYP_IRQn);
    }
}

int8_t CrypInstance2Num(CRYP_TypeDef* Instance) {
    int8_t num = 0;
    if(CRYP == Instance) {
        num = 1;
    }
    return num;
}
