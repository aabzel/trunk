#include "cryp_api.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "data_utils.h"
#ifdef HAS_LOG
#include "log.h"
#endif

#include "aes256_general.h"
#include "aes256cbc.h"
#include "cryp_config.h"
#include "cryp_diag.h"
#include "cryp_drv.h"

CrypHandle_t* CrypGetNode(uint8_t cryp_num) {
    CrypHandle_t* node = NULL;
    uint32_t i = 0;
    uint32_t cnt = cryp_get_cnt();
    for(i = 0; i <= cnt; i++) {
        if(CrypItem[i].valid) {
            if(cryp_num == CrypItem[i].num) {
                node = &CrypItem[i];
                break;
            }
        }
    }
    return node;
}

const CrypConfig_t* CrypGetConfigNode(uint8_t cryp_num) {
    const CrypConfig_t* CongNode = 0;
    uint32_t i = 0;
    for(i = 0; i < cryp_get_cnt(); i++) {
        if(CrypConfigLut[i].valid) {
            if(cryp_num == CrypConfigLut[i].num) {
                CongNode = &CrypConfigLut[i];
                break;
            }
        }
    }
    return CongNode;
}

bool cryp_is_valid(uint8_t cryp_num) {
    bool res = false;
    CrypHandle_t* Node = CrypGetNode(cryp_num);
    if(Node) {
        const CrypConfig_t* CrypConfigNode = CrypGetConfigNode(cryp_num);
        if(CrypConfigNode) {
            res = true;
        }
    }
    return res;
}

bool aes256_ecb_encrypt_api(const uint8_t* key32byte, uint8_t* data_in, uint32_t data_len, uint8_t* data_out,
                            AlgImpl_t alg_impl) {
    bool res = false;
    switch(alg_impl) {
    case ALG_IMPL_SW: {
        uint32_t returnlen = 0;
        res = aes256_ecb_encrypt(key32byte, data_in, data_len, data_out, &returnlen);
    } break;
    case ALG_IMPL_HW: {
#ifdef HAS_CRYP_HW
        res = hw_aes256_ecb_encrypt(key32byte, data_in, data_len, data_out);
#endif
    } break;
    default: {
    } break;
    } // switch
    return res;
}

bool aes256_ecb_decrypt_api(const uint8_t* key32byte, uint8_t* data_in, uint32_t data_len, uint8_t* data_out,
                            AlgImpl_t alg_impl) {
    bool res = false;
    switch(alg_impl) {
    case ALG_IMPL_SW: {
        uint32_t returnlen = 0;
        res = aes256_ecb_decrypt(key32byte, data_in, data_len, data_out, &returnlen);
    } break;
    case ALG_IMPL_HW: {
#ifdef HAS_CRYP_HW
        res = hw_aes256_ecb_decrypt(key32byte, data_in, data_len, data_out);
#endif
    } break;
    default: {
    } break;
    } // switch
    return res;
}

bool aes256_cbc_encrypt_api(const uint8_t* key32byte, uint8_t* data_in, uint32_t data_len, uint8_t* data_out,
                            AlgImpl_t alg_impl) {
    bool res = false;
    switch(alg_impl) {
    case ALG_IMPL_SW: {
        uint32_t returnlen = 0;
        CrypHandle_t* Node = CrypGetNode(CRYP_SW_NUM);
        if(Node) {
            res = aes256_cbc_encrypt(key32byte, Node->ctx.Iv, data_in, data_len, data_out, &returnlen);
        }
    } break;
    case ALG_IMPL_HW: {
#ifdef HAS_CRYP_HW
        res = hw_aes256_cbc_encrypt(key32byte, data_in, data_len, data_out);
#endif
    } break;
    default: {
    } break;
    } // switch
    return res;
}

uint32_t aes256_cbc_decrypt_api(const uint8_t* key32byte, uint8_t* data_in, uint32_t data_len, uint8_t* data_out,
                                AlgImpl_t alg_impl) {
    uint32_t returnlen = 0;
    bool res = false;
    switch(alg_impl) {
    case ALG_IMPL_SW: {
        CrypHandle_t* Node = CrypGetNode(CRYP_SW_NUM);
        if(Node) {
            res = aes256_cbc_decrypt(key32byte, Node->ctx.Iv, data_in, data_len, data_out, &returnlen);
        }
    } break;
    case ALG_IMPL_HW: {
#ifdef HAS_CRYP_HW
        res = hw_aes256_cbc_decrypt(key32byte, data_in, data_len, data_out);
        if(res) {
            returnlen = data_len;
        }
#endif
    } break;
    default: {
        returnlen = 0;
    } break;
    } // switch
    if(!res) {
        LOG_ERROR(AES256, "CbcDecrErr");
    }
    return returnlen;
}

bool aes256_cbc_init_api(const uint8_t* key, const uint8_t* init_vector, AlgImpl_t alg_impl, IvSkipCfg_t iv_skip_cfg) {
    bool res = false;
    LOG_INFO(LG_CRYP, "Init Impl:%s", AlgoImpl2Str(alg_impl));
    if(key && init_vector) {
        switch(alg_impl) {
        case ALG_IMPL_SW: {
            CrypHandle_t* Node = CrypGetNode(CRYP_SW_NUM);
            if(Node) {
                AES256CBC_init_ctx_iv(&(Node->ctx), key, init_vector);
                res = true;
            }
        } break;
        case ALG_IMPL_HW: {
#ifdef HAS_CRYP_HW
            res = hw_aes256_cbc_init(key, init_vector, iv_skip_cfg);
#endif
        } break;
        default: {

        } break;
        } // switch
    } else {
        LOG_ERROR(LG_CRYP, "ArgErr");
    }
    LOG_INFO(LG_CRYP, "Init Impl:%s Ok", AlgoImpl2Str(alg_impl));
    return res;
}

uint32_t aes256_cbc_decrypt_stream_api(const uint8_t* key32byte, uint8_t* data_in, uint32_t data_len, uint8_t* data_out,
                                       AlgImpl_t alg_impl) {
    uint32_t return_len = 0;
    LOG_DEBUG(LG_CRYP, "CbcDecrypt Impl:%s", AlgoImpl2Str(alg_impl));
    switch(alg_impl) {
    case ALG_IMPL_SW: {
        CrypHandle_t* Node = CrypGetNode(CRYP_SW_NUM);
        if(Node) {
            bool res = false;
            res = aes256_cbc_decrypt_stream(&(Node->ctx), key32byte, data_in, data_len, data_out, &return_len);
            if(!res) {
                LOG_ERROR(AES256, "SwCbcDecrStreamErr");
            }
        }
    } break;
    case ALG_IMPL_HW: {
#ifdef HAS_CRYP_HW
        return_len = hw_aes256_cbc_decrypt_stream(key32byte, data_in, data_len, data_out);
#endif
    } break;
    default: {

    } break;
    } // switch
    return return_len;
}

bool cryp_init(void) {
    bool res = false;
#ifdef HAS_CRYP_HW
    res = cryp_hw_init();
#endif
    return res;
}
