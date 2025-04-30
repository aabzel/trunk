#include "cryp_cbc_drv.h"

#include <string.h>

#include "byte_utils.h"
#include "cryp_api.h"
#include "cryp_config.h"
#include "cryp_custom_drv.h"
#include "hal_diag.h"
#include "log.h"
#include "artery_at32f4xx.h"


static uint32_t IvSkipCfg2StmSkipConfig(IvSkipCfg_t iv_skip_cfg){
    uint32_t KeyIVConfigSkip =CRYP_KEYIVCONFIG_ALWAYS ;
    switch( (uint8_t) iv_skip_cfg){
    case IV_SKIP_CFG_ALWAYS: KeyIVConfigSkip =CRYP_KEYIVCONFIG_ALWAYS ;break;
    case IV_SKIP_CFG_ONCE: KeyIVConfigSkip = CRYP_KEYIVCONFIG_ONCE;break;
    }
    return KeyIVConfigSkip;
}


bool hw_aes256_cbc_init(const uint8_t* key32byte, const uint8_t* init_vector, IvSkipCfg_t iv_skip_cfg) {
    bool res = false;
    LOG_INFO(LG_CRYP, "HwAes256CbcInit");
    CrypHandle_t* CrypNode = CrypGetNode(CRYP_HW_NUM);
    if(CrypNode) {
        LOG_INFO(LG_CRYP, "SpotNode");
        memcpy(CrypNode->Key256BitQwords, key32byte, 32);
        uint32_t i = 0;
        for(i = 0; i < 8; i++) {
            CrypNode->Key256BitQwords[i] = reverse_byte_order_uint32(CrypNode->Key256BitQwords[i]);
        }

        memcpy(CrypNode->init_vector, init_vector, 16);
        memcpy(CrypNode->InitVectorQwords, init_vector, 16);
        for(i = 0; i < 4; i++) {
            CrypNode->InitVectorQwords[i] = reverse_byte_order_uint32(CrypNode->InitVectorQwords[i]);
        }

        CrypNode->int_flag = false;

        CrypNode->cryp_h.Instance = CRYP;
        CrypNode->cryp_h.Init.Algorithm = CRYP_AES_CBC;
        CrypNode->cryp_h.Init.DataType = CRYP_DATATYPE_8B;
        CrypNode->cryp_h.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_BYTE;
        //CrypNode->cryp_h.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_WORD;
        CrypNode->cryp_h.Init.KeySize = CRYP_KEYSIZE_256B; /*32 byte*/
        CrypNode->cryp_h.Init.pKey = (uint32_t*)CrypNode->Key256BitQwords;
        CrypNode->cryp_h.Init.pInitVect = (uint32_t*)CrypNode->InitVectorQwords;
        //CrypNode->cryp_h.Init.KeyIVConfigSkip = CRYP_KEYIVCONFIG_ONCE; /*err*/
        CrypNode->cryp_h.Init.KeyIVConfigSkip = IvSkipCfg2StmSkipConfig(iv_skip_cfg);

        HAL_StatusTypeDef ret;
#if 1
        ret= HAL_CRYP_DeInit(&CrypNode->cryp_h);
        if(HAL_OK ==ret){
            LOG_INFO(LG_CRYP, "DeInitOk");
            CrypNode->init_done = false;
        }
#endif

        if(false==CrypNode->init_done){
             ret = HAL_CRYP_Init((CRYP_HandleTypeDef*)&CrypNode->cryp_h);
            if(HAL_OK == ret) {
                res = true;
                CrypNode->init_done= true;
                LOG_INFO(LG_CRYP, "AesCbcInitOk");
            } else {
                res = false;
                LOG_ERROR(LG_CRYP, "InitCbcErr %d=%s", ret, HalStatus2Str(ret));
            }
        } else {
            LOG_INFO(LG_CRYP, "Aes256CbcReInit");
            CrypNode->Conf.DataType = CRYP_DATATYPE_8B;
            CrypNode->Conf.KeySize = CRYP_KEYSIZE_256B;
            CrypNode->Conf.pKey = (uint32_t*)CrypNode->Key256BitQwords;;
            CrypNode->Conf.pInitVect = (uint32_t*)CrypNode->InitVectorQwords;
            CrypNode->Conf.Algorithm = CRYP_AES_CBC;
            CrypNode->Conf.DataWidthUnit = CRYP_DATAWIDTHUNIT_BYTE;
            CrypNode->Conf.KeyIVConfigSkip =  IvSkipCfg2StmSkipConfig(iv_skip_cfg);
            //CrypNode->Conf.KeyIVConfigSkip = CRYP_KEYIVCONFIG_ONCE; /*err*/

            ret = HAL_CRYP_SetConfig(&CrypNode->cryp_h, &CrypNode->Conf);
            if(HAL_OK == ret) {
                res = true;
                CrypNode->init_done= true;
                LOG_INFO(LG_CRYP, "AesCbcConfigOk");
            } else {
                res = false;
                LOG_ERROR(LG_CRYP, "ConfigCbcErr %d=%s", ret, HalStatus2Str(ret));
            }
        }
    } else {
        LOG_ERROR(LG_CRYP, "NodeErr");
    }
    return res;
}

bool hw_aes256_cbc_encrypt(const uint8_t* key32byte, uint8_t* data_in, uint32_t datalen, uint8_t* data_out) {
    bool res = false;
    LOG_INFO(LG_CRYP, "Aes256CbcEncrypt Len:%u", datalen);
    CrypHandle_t* CrypNode = CrypGetNode(CRYP_HW_NUM);
    if(CrypNode) {
        memcpy(CrypNode->Key256BitQwords, key32byte, 32);
        uint32_t i = 0;
        for(i = 0; i < 8; i++) {
            CrypNode->Key256BitQwords[i] = reverse_byte_order_uint32(CrypNode->Key256BitQwords[i]);
        }

        CrypNode->cryp_h.Instance = CRYP;
        CrypNode->cryp_h.Init.Algorithm = CRYP_AES_CBC;
        CrypNode->cryp_h.Init.DataType = CRYP_DATATYPE_8B;
        CrypNode->cryp_h.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_WORD;
        CrypNode->cryp_h.Init.pKey = (uint32_t*)CrypNode->Key256BitQwords;
        CrypNode->cryp_h.Init.KeyIVConfigSkip = CRYP_KEYIVCONFIG_ALWAYS;
        CrypNode->cryp_h.Init.KeySize = CRYP_KEYSIZE_256B;

        HAL_StatusTypeDef ret = HAL_CRYP_Init((CRYP_HandleTypeDef*)&CrypNode->cryp_h);
        if(HAL_OK == ret) {
            res = true;
            CrypNode->int_flag = true;
            ret =
                HAL_CRYP_Encrypt(&CrypNode->cryp_h, (uint32_t*)data_in, (uint16_t)datalen, (uint32_t*)data_out, 100000);
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
    LOG_INFO(LG_CRYP, "Aes256CbcDecrypt Len:%u", datalen);
    CrypHandle_t* CrypNode = CrypGetNode(CRYP_HW_NUM);
    if(CrypNode) {
        memcpy(CrypNode->Key256BitQwords, key32byte, 32);
        uint32_t i = 0;
        for(i = 0; i < 8; i++) {
            CrypNode->Key256BitQwords[i] = reverse_byte_order_uint32(CrypNode->Key256BitQwords[i]);
        }
        CrypNode->cryp_h.Instance = CRYP;
        CrypNode->cryp_h.Init.Algorithm = CRYP_AES_CBC;
        CrypNode->cryp_h.Init.DataType = CRYP_DATATYPE_8B;
        CrypNode->cryp_h.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_WORD;
        CrypNode->cryp_h.Init.KeySize = CRYP_KEYSIZE_256B;
        CrypNode->cryp_h.Init.KeyIVConfigSkip = CRYP_KEYIVCONFIG_ALWAYS;
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
                LOG_ERROR(LG_CRYP, "EncryptCbcErr %d=%s", ret, HalStatus2Str(ret));
            }
        } else {
            res = false;
            LOG_ERROR(LG_CRYP, "InitCbcErr %d=%s", ret, HalStatus2Str(ret));
        }
    }
    return res;
}

uint32_t hw_aes256_cbc_decrypt_stream(const uint8_t* key32byte, uint8_t* data_in, uint32_t datalen, uint8_t* data_out) {
    bool res = false;
    (void) res;
    uint32_t return_len = 0;
    LOG_DEBUG(LG_CRYP,"HwCbcDecrypt Len:%u", datalen);
    CrypHandle_t* CrypNode = CrypGetNode(CRYP_HW_NUM);
    if(CrypNode) {
        memcpy(CrypNode->Key256BitQwords, key32byte, 32);
        uint32_t i = 0;
        for(i = 0; i < 8; i++) {
            CrypNode->Key256BitQwords[i] = reverse_byte_order_uint32(CrypNode->Key256BitQwords[i]);
        }
#if 0
        CrypNode->cryp_h.Instance = CRYP;
        CrypNode->cryp_h.Init.pKey = (uint32_t*)CrypNode->Key256BitQwords;
        CrypNode->cryp_h.Init.KeySize = CRYP_KEYSIZE_256B;
        CrypNode->cryp_h.Init.Algorithm = CRYP_AES_CBC;
        CrypNode->cryp_h.Init.DataType = CRYP_DATATYPE_8B;
        CrypNode->cryp_h.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_WORD;
#endif

        HAL_StatusTypeDef ret;
#if 0
        CrypNode->int_flag = true;
        ret = HAL_CRYP_Decrypt(&CrypNode->cryp_h, (uint32_t*)data_in, (uint16_t)datalen, (uint32_t*)data_out, 100000);
#endif
#if 1
        CrypNode->int_flag = false;
        ret = HAL_CRYP_Decrypt_IT(&CrypNode->cryp_h, (uint32_t*)data_in, (uint16_t)datalen, (uint32_t*)data_out);
#endif
        if(HAL_OK == ret) {
            while(false == CrypNode->int_flag) {
            }
            res = true;
            return_len = datalen;
        } else {
            res = false;
            LOG_ERROR(LG_CRYP, "EncryptCbcStreamErr %d=%s", ret, HalStatus2Str(ret));
        }
    }
    LOG_DEBUG(LG_CRYP,"HwCbcDecryptOk Len:%u", datalen);
    return return_len;
}
