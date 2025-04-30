#include "cryp_drv.h"

#include "cryp_api.h"
#include "cryp_config.h"
#include "cryp_custom_drv.h"
#include "hal_diag.h"
#include "log.h"
#include "at32f435_437.h"

// CRYP_HandleTypeDef hcryp;
__ALIGN_BEGIN static const uint8_t KeyCRYP[32] __ALIGN_END = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

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
        LOG_ERROR(LG_CRYP, "UndefAlgo %u", algo);
        break;
    }
    return algo_code;
}

bool cryp_init_one(uint8_t cryp_num) {
    bool res = false;
    LOG_INFO(LG_CRYP, "%u Init", cryp_num);
    CrypHandle_t* CrypNode = CrypGetNode(cryp_num);
    if(CrypNode) {
        const CrypConfig_t* CrypConfigNode = CrypGetConfigNode(cryp_num);
        if(CrypConfigNode) {
            CrypNode->int_flag = false;
            CrypNode->cryp_h.Instance = CRYP;
            CrypNode->cryp_h.Init.DataType = CRYP_DATATYPE_8B;
            CrypNode->cryp_h.Init.KeySize = CRYP_KEYSIZE_256B;
            CrypNode->cryp_h.Init.pKey = (uint32_t*)KeyCRYP;
            CrypNode->cryp_h.Init.pInitVect = (uint32_t*)CrypConfigNode->init_vector;
            CrypNode->cryp_h.Init.Algorithm = CrypAlgo2StmAlgo(CrypConfigNode->algo);
            CrypNode->cryp_h.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_WORD;
            HAL_StatusTypeDef ret = HAL_CRYP_Init((CRYP_HandleTypeDef*)&CrypNode->cryp_h);
            if(HAL_OK == ret) {
                LOG_INFO(LG_CRYP, "InitOk");
                res = true;
            } else {
                res = false;
                LOG_ERROR(LG_CRYP, "InitErr %d=%s", ret, HalStatus2Str(ret));
            }
        } else {
            LOG_ERROR(LG_CRYP, "ConfErr %d", cryp_num);
        }
    }
    return res;
}

bool hw_aes256_cbc_init(const uint8_t* key, const uint8_t* init_vector) {
    bool res = false;
    CrypHandle_t* CrypNode = CrypGetNode(CRYP_HW_NUM);
    if(CrypNode) {
        const CrypConfig_t* CrypConfigNode = CrypGetConfigNode(CRYP_HW_NUM);
        if(CrypConfigNode) {
            CrypNode->int_flag = false;
            CrypNode->cryp_h.Instance = CRYP;
            CrypNode->cryp_h.Init.DataType = CRYP_DATATYPE_8B;
            CrypNode->cryp_h.Init.KeySize = CRYP_KEYSIZE_256B;
            CrypNode->cryp_h.Init.pKey = (uint32_t*)key;
            CrypNode->cryp_h.Init.pInitVect = (uint32_t*)init_vector;
            CrypNode->cryp_h.Init.Algorithm = CRYP_AES_CBC;
            CrypNode->cryp_h.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_WORD;
            HAL_StatusTypeDef ret = HAL_CRYP_Init((CRYP_HandleTypeDef*)&CrypNode->cryp_h);
            if(HAL_OK == ret) {
                res = true;
                LOG_ERROR(LG_CRYP, "InitOk");
            } else {
                res = false;
                LOG_ERROR(LG_CRYP, "InitCbcErr %d=%s", ret, HalStatus2Str(ret));
            }
        } else {
            LOG_ERROR(LG_CRYP, "ConfErr 1");
        }
    }
    return res;
}

bool cryp_hw_init(void) {
    bool res = false;
    res = cryp_init_one(CRYP_HW_NUM);
    return res;
}

bool hw_aes256_ecb_init(const uint8_t* const key32byte) {
    bool res = false;
    CrypHandle_t* CrypNode = CrypGetNode(CRYP_HW_NUM);
    if(CrypNode) {
        CrypNode->int_flag = false;
        CrypNode->cryp_h.Instance = CRYP;
        CrypNode->cryp_h.Init.pKey = (uint32_t*)key32byte;
        CrypNode->cryp_h.Init.KeySize = CRYP_KEYSIZE_256B;
        CrypNode->cryp_h.Init.Algorithm = CRYP_AES_ECB;
        HAL_StatusTypeDef ret = HAL_CRYP_Init((CRYP_HandleTypeDef*)&CrypNode->cryp_h);
        if(HAL_OK == ret) {
            res = true;
        } else {
            res = false;
            LOG_ERROR(LG_CRYP, "InitEcbErr %d=%s", ret, HalStatus2Str(ret));
        }
    }
    return res;
}

bool hw_aes256_ecb_encrypt(const uint8_t* key32byte, uint8_t* data_in, uint32_t datalen, uint8_t* data_out) {
    bool res = false;
    CrypHandle_t* CrypNode = CrypGetNode(CRYP_HW_NUM);
    if(CrypNode) {
        CrypNode->cryp_h.Instance = CRYP;
        CrypNode->cryp_h.Init.pKey = (uint32_t*)key32byte;
        CrypNode->cryp_h.Init.KeySize = CRYP_KEYSIZE_256B;
        CrypNode->cryp_h.Init.Algorithm = CRYP_AES_ECB;
        HAL_StatusTypeDef ret = HAL_CRYP_Init((CRYP_HandleTypeDef*)&CrypNode->cryp_h);
        if(HAL_OK == ret) {
            res = true;
            CrypNode->int_flag = false;
            ret = HAL_CRYP_Encrypt_IT(&CrypNode->cryp_h, (uint32_t*)data_in, (uint16_t)datalen, (uint32_t*)data_out);
            if(HAL_OK == ret) {
                while(false == CrypNode->int_flag) {
                }
                res = true;
            } else {
                res = false;
                LOG_ERROR(LG_CRYP, "EncryptEcbErr %d=%s", ret, HalStatus2Str(ret));
            }
        } else {
            res = false;
            LOG_ERROR(LG_CRYP, "InitEcbErr %d=%s", ret, HalStatus2Str(ret));
        }
    }
    return res;
}

bool hw_aes256_ecb_decrypt(const uint8_t* key32byte, uint8_t* data_in, uint32_t datalen, uint8_t* data_out) {
    bool res = false;
    CrypHandle_t* CrypNode = CrypGetNode(CRYP_HW_NUM);
    if(CrypNode) {
        CrypNode->cryp_h.Instance = CRYP;
        CrypNode->cryp_h.Init.pKey = (uint32_t*)key32byte;
        CrypNode->cryp_h.Init.KeySize = CRYP_KEYSIZE_256B;
        CrypNode->cryp_h.Init.Algorithm = CRYP_AES_ECB;
        HAL_StatusTypeDef ret = HAL_CRYP_Init((CRYP_HandleTypeDef*)&CrypNode->cryp_h);
        if(HAL_OK == ret) {
            res = true;
            CrypNode->int_flag = false;
            ret = HAL_CRYP_Decrypt_IT(&CrypNode->cryp_h, (uint32_t*)data_in, (uint16_t)datalen, (uint32_t*)data_out);
            if(HAL_OK == ret) {
                while(false == CrypNode->int_flag) {
                }
                res = true;
            } else {
                res = false;
                LOG_ERROR(LG_CRYP, "EncryptEcbErr %d=%s", ret, HalStatus2Str(ret));
            }
        } else {
            res = false;
            LOG_ERROR(LG_CRYP, "InitEcbErr %d=%s", ret, HalStatus2Str(ret));
        }
    }
    return res;
}

bool hw_aes256_cbc_encrypt(const uint8_t* key32byte, uint8_t* data_in, uint32_t datalen, uint8_t* data_out) {
    bool res = false;
    CrypHandle_t* CrypNode = CrypGetNode(CRYP_HW_NUM);
    if(CrypNode) {
        CrypNode->cryp_h.Instance = CRYP;
        CrypNode->cryp_h.Init.pKey = (uint32_t*)key32byte;
        CrypNode->cryp_h.Init.KeySize = CRYP_KEYSIZE_256B;
        CrypNode->cryp_h.Init.Algorithm = CRYP_AES_CBC;
        HAL_StatusTypeDef ret = HAL_CRYP_Init((CRYP_HandleTypeDef*)&CrypNode->cryp_h);
        if(HAL_OK == ret) {
            res = true;
            CrypNode->int_flag = false;
            ret = HAL_CRYP_Encrypt_IT(&CrypNode->cryp_h, (uint32_t*)data_in, (uint16_t)datalen, (uint32_t*)data_out);
            if(HAL_OK == ret) {
                while(false == CrypNode->int_flag) {
                }
                res = true;
            } else {
                res = false;
                LOG_ERROR(LG_CRYP, "EncryptCbcErr %d=%s", ret, HalStatus2Str(ret));
            }
        } else {
            res = false;
            LOG_ERROR(LG_CRYP, "InitCbcErr %d=%s", ret, HalStatus2Str(ret));
        }
    }
    return res;
}

bool hw_aes256_cbc_decrypt(const uint8_t* key32byte, uint8_t* data_in, uint32_t datalen, uint8_t* data_out) {
    bool res = false;
    CrypHandle_t* CrypNode = CrypGetNode(CRYP_HW_NUM);
    if(CrypNode) {
        CrypNode->cryp_h.Instance = CRYP;
        CrypNode->cryp_h.Init.pKey = (uint32_t*)key32byte;
        CrypNode->cryp_h.Init.KeySize = CRYP_KEYSIZE_256B;
        CrypNode->cryp_h.Init.Algorithm = CRYP_AES_CBC;
        HAL_StatusTypeDef ret = HAL_CRYP_Init((CRYP_HandleTypeDef*)&CrypNode->cryp_h);
        if(HAL_OK == ret) {
            res = true;
            CrypNode->int_flag = false;
            ret = HAL_CRYP_Decrypt_IT(&CrypNode->cryp_h, (uint32_t*)data_in, (uint16_t)datalen, (uint32_t*)data_out);
            if(HAL_OK == ret) {
                while(false == CrypNode->int_flag) {
                }
                res = true;
            } else {
                res = false;
                LOG_ERROR(LG_CRYP, "EncryptCbcErr %d=%s", ret, HalStatus2Str(ret));
            }
        } else {
            res = false;
            LOG_ERROR(LG_CRYP, "InitCbcErr %d=%s", ret, HalStatus2Str(ret));
        }
    }
    return res;
}

bool hw_aes256_cbc_decrypt_stream(const uint8_t* key32byte, uint8_t* data_in, uint32_t datalen, uint8_t* data_out) {
    bool res = false;
    CrypHandle_t* CrypNode = CrypGetNode(CRYP_HW_NUM);
    if(CrypNode) {
        CrypNode->cryp_h.Instance = CRYP;
        CrypNode->cryp_h.Init.pKey = (uint32_t*)key32byte;
        CrypNode->cryp_h.Init.KeySize = CRYP_KEYSIZE_256B;
        CrypNode->cryp_h.Init.Algorithm = CRYP_AES_CBC;
        HAL_StatusTypeDef ret;
        CrypNode->int_flag = false;
        ret = HAL_CRYP_Decrypt_IT(&CrypNode->cryp_h, (uint32_t*)data_in, (uint16_t)datalen, (uint32_t*)data_out);
        if(HAL_OK == ret) {
            while(false == CrypNode->int_flag) {
            }
            res = true;
        } else {
            res = false;
            LOG_ERROR(LG_CRYP, "EncryptCbcStreamErr %d=%s", ret, HalStatus2Str(ret));
        }
    }
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

static int8_t CrypInstance2Num(CRYP_TypeDef* Instance) {
    int8_t cryp_num = 0;
    if(CRYP == Instance) {
        cryp_num = 1;
    }
    return cryp_num;
}

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
