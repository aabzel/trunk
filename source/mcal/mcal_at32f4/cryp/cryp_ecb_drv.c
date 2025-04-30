#include "cryp_ecb_drv.h"

#include <string.h>

#include "byte_utils.h"
#include "cryp_api.h"
#include "cryp_config.h"
#include "cryp_custom_drv.h"
#include "hal_diag.h"
#include "log.h"
#include "artery_at32f4xx.h"

bool hw_aes256_ecb_init(const uint8_t* const key32byte) {
    bool res = false;
    LOG_INFO(LG_CRYP, "Aes256EcbInit");
    CrypHandle_t* CrypNode = CrypGetNode(CRYP_HW_NUM);
    if(CrypNode) {
        memcpy(CrypNode->Key256BitQwords, key32byte, 32);
        uint32_t i = 0;
        for(i = 0; i < 8; i++) {
            CrypNode->Key256BitQwords[i] = reverse_byte_order_uint32(CrypNode->Key256BitQwords[i]);
        }

        CrypNode->int_flag = false;

        CrypNode->cryp_h.Instance = CRYP;
        CrypNode->cryp_h.Init.Algorithm = CRYP_AES_ECB;
        CrypNode->cryp_h.Init.DataType = CRYP_DATATYPE_8B;
        CrypNode->cryp_h.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_WORD;
        CrypNode->cryp_h.Init.KeySize = CRYP_KEYSIZE_256B;
        CrypNode->cryp_h.Init.pInitVect = (uint32_t*)NULL;
        CrypNode->cryp_h.Init.pKey = (uint32_t*)CrypNode->Key256BitQwords;
        CrypNode->cryp_h.Init.KeyIVConfigSkip = CRYP_KEYIVCONFIG_ALWAYS;

        HAL_StatusTypeDef ret = HAL_CRYP_Init((CRYP_HandleTypeDef*)&CrypNode->cryp_h);
        if(HAL_OK == ret) {
            res = true;
            LOG_INFO(LG_CRYP, "InitOk");
        } else {
            res = false;
            LOG_ERROR(LG_CRYP, "InitEcbErr %d=%s", ret, HalStatus2Str(ret));
        }
    }
    return res;
}

bool hw_aes256_ecb_encrypt(const uint8_t* key32byte, uint8_t* data_in, uint32_t datalen, uint8_t* data_out) {
    bool res = false;
    LOG_DEBUG(LG_CRYP, "EncryptEcb Len:%u", datalen);
    CrypHandle_t* CrypNode = CrypGetNode(CRYP_HW_NUM);
    if(CrypNode) {
        memcpy(CrypNode->Key256BitQwords, key32byte, 32);
        uint32_t i = 0;
        for(i = 0; i < 8; i++) {
            CrypNode->Key256BitQwords[i] = reverse_byte_order_uint32(CrypNode->Key256BitQwords[i]);
        }

        CrypNode->cryp_h.Instance = CRYP;
        CrypNode->cryp_h.Init.Algorithm = CRYP_AES_ECB;
        CrypNode->cryp_h.Init.DataType = CRYP_DATATYPE_8B;
        CrypNode->cryp_h.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_BYTE;
        CrypNode->cryp_h.Init.KeySize = CRYP_KEYSIZE_256B;
        CrypNode->cryp_h.Init.pInitVect = (uint32_t*)NULL;
        CrypNode->cryp_h.Init.pKey = (uint32_t*)CrypNode->Key256BitQwords;


        HAL_StatusTypeDef ret = HAL_OK;
        if(false==CrypNode->init_done){
            ret = HAL_CRYP_Init((CRYP_HandleTypeDef*)&CrypNode->cryp_h);
            if(HAL_OK == ret) {
                CrypNode->init_done= true;
                res = true;
            }else{
                res = false;
            }

        }else{
            CrypNode->Conf.Algorithm = CRYP_AES_ECB;
            CrypNode->Conf.DataType = CRYP_DATATYPE_8B;
            CrypNode->Conf.DataWidthUnit = CRYP_DATAWIDTHUNIT_BYTE;
            CrypNode->Conf.KeySize = CRYP_KEYSIZE_256B;
            CrypNode->Conf.pKey = (uint32_t*)CrypNode->Key256BitQwords;
            CrypNode->Conf.pInitVect = NULL;
            ret = HAL_CRYP_SetConfig(&CrypNode->cryp_h, &CrypNode->Conf);
            if(HAL_OK == ret) {
                res = true;
            }else{
                res = false;
            }
        }

        if(res) {
            res = true;

#if 0
                CrypNode->int_flag = true;
                ret = HAL_CRYP_Encrypt(&CrypNode->cryp_h, (uint32_t*)data_in, (uint16_t)datalen, (uint32_t*)data_out,
                                       100000);
#endif
#if 1
                CrypNode->int_flag = false;
                ret = HAL_CRYP_Encrypt_IT(&CrypNode->cryp_h, (uint32_t*)data_in, (uint16_t)datalen, (uint32_t*)data_out);
#endif
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
    LOG_INFO(LG_CRYP, "Aes256EcbDecrypt Len:%u", datalen);
    CrypHandle_t* CrypNode = CrypGetNode(CRYP_HW_NUM);
    if(CrypNode) {
        memcpy(CrypNode->Key256BitQwords, key32byte, 32);
        uint32_t i = 0;
        for(i = 0; i < 8; i++) {
            CrypNode->Key256BitQwords[i] = reverse_byte_order_uint32(CrypNode->Key256BitQwords[i]);
        }
        CrypNode->cryp_h.Instance = CRYP;
        CrypNode->cryp_h.Init.Algorithm = CRYP_AES_ECB;
        CrypNode->cryp_h.Init.DataType = CRYP_DATATYPE_8B;
        CrypNode->cryp_h.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_WORD;
        CrypNode->cryp_h.Init.KeySize = CRYP_KEYSIZE_256B;
        CrypNode->cryp_h.Init.pInitVect = (uint32_t*)NULL;
        CrypNode->cryp_h.Init.pKey = (uint32_t*)CrypNode->Key256BitQwords;

        HAL_StatusTypeDef ret = HAL_CRYP_Init((CRYP_HandleTypeDef*)&CrypNode->cryp_h);
        if(HAL_OK == ret) {
            res = true;
            CrypNode->int_flag = true;
            ret =
                HAL_CRYP_Decrypt(&CrypNode->cryp_h, (uint32_t*)data_in, (uint16_t)datalen, (uint32_t*)data_out, 100000);
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
