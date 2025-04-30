#include "cryp_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "cryp_drv.h"
#include "clock.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "sys_config.h"
#include "table_utils.h"
#include "cryp_config.h"
#include "cryp_diag.h"
#include "time_mcal.h"
#include "cryp_api.h"
#include "cryp_diag.h"
#include "writer_config.h"


bool cryp_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = cryp_diag();
    } else {
        LOG_ERROR(LG_CRYP, "Usage: cd");
    }

    return res;
}

static bool fetch_arguments(int32_t argc, char* argv[], uint8_t* cryp_num, uint8_t* data_in, uint32_t* data_len){
    bool res = false;
    *cryp_num=1;
    uint32_t key_len = 0;
    if(1<=argc){
        res = try_str2uint8(argv[0], cryp_num);
        if(false == res) {
            LOG_ERROR(LG_CRYP, "ParseErr CrypNum %s", argv[0]);
        }
    }
    CrypHandle_t* CrypNode=CrypGetNode( *cryp_num);
    if(CrypNode){
        res =  true;
    }else{
        res = false;
    }

    if(2 <= argc) {
         res = try_str2array(argv[1], CrypNode->key32byte, 32,(size_t*) &key_len);
         if(false == res) {
         LOG_WARNING(LG_CRYP, "ExtractHexArrayErr  [%s]", argv[1]);
         snprintf((char *) CrypNode->key32byte, 32, "%s", argv[1]);
         key_len = strlen(argv[1]);
         res = true;
         }
    }

    if(3 <= argc) {
        res = try_str2array(argv[2], data_in, sizeof(data_in),(size_t*) data_len);
        if(false == res) {
        LOG_WARNING(LG_CRYP, "ExtractHexArrayErr  [%s]", argv[2]);
        snprintf((char*)data_in, sizeof(data_in), "%s", argv[2]);
        *data_len = strlen(argv[2]);
        res = true;
        }
    }

    if(4<=argc){
        res = try_str2uint8(argv[3], (uint8_t*) CrypNode->algo_impl);
        if(false == res) {
            LOG_ERROR(LG_CRYP, "ParseErr AlgoImpl %s", argv[3]);
        }else{
            LOG_INFO(LG_CRYP, "AlgoImpl %s", AlgoImpl2Str(CrypNode->algo_impl));
        }
    }
    return res;
}

bool cryp_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = cryp_init();
    } else {
        LOG_ERROR(LG_CRYP, "Usage: ci");
    }

    return res;
}


bool cryp_encrypt_ecb_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t cryp_num=1;
    uint8_t data_in[32];

    uint8_t data_out[32];
    memset(data_in,0,sizeof(data_in));
    memset(data_out,0,sizeof(data_out));
    uint32_t data_len = 0;

    if(4<=argc) {
        res= fetch_arguments(  argc, argv, &cryp_num, data_in, &data_len);
    }

    if (res) {
        CrypHandle_t* CrypNode=CrypGetNode( cryp_num);
        if(CrypNode) {
                res= aes256_ecb_encrypt_api(CrypNode->key32byte, data_in, data_len, data_out,CrypNode->algo_impl);
                if(res) {
                    LOG_INFO(LG_CRYP, "EncryptOk");
                }else{
                    LOG_ERROR(LG_CRYP, "EncryptErr");
                }
        }
    }
    return res;
}

bool cryp_decrypt_ecb_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t data_in[32];
    uint8_t data_out[32];
    memset(data_in,0,sizeof(data_in));
    memset(data_out,0,sizeof(data_out));

    uint32_t data_len = 0;
    uint8_t cryp_num=1;

    if(4<=argc) {
        res= fetch_arguments(  argc, argv, &cryp_num ,data_in, &data_len);
    }

    if(res) {
        CrypHandle_t* CrypNode=CrypGetNode( cryp_num);
        if(CrypNode) {
            res = aes256_ecb_decrypt_api( CrypNode->key32byte, data_in, data_len,
                    data_out,CrypNode->algo_impl);
            if(res) {
                LOG_INFO(LG_CRYP, "DecryptOk");
            }else {
                LOG_ERROR(LG_CRYP, "DecryptErr");
            }
        }
    }else {
        LOG_ERROR(LG_CRYP, "Usage: cd cryp_index key data");
    }
    return res;
}

bool cryp_encrypt_cbc_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t data_in[32];
    uint8_t data_out[32];
    memset(data_in,0,sizeof(data_in));
    memset(data_out,0,sizeof(data_out));

    uint32_t data_len = 0;
    uint8_t cryp_num=1;

    if(4<=argc) {
        res= fetch_arguments(  argc, argv, &cryp_num ,data_in, &data_len);
    }

    if(res) {
        CrypHandle_t* CrypNode=CrypGetNode( cryp_num);
        if(CrypNode) {
            res = aes256_cbc_encrypt_api( CrypNode->key32byte, data_in, data_len, data_out,CrypNode->algo_impl );
            if(res) {
                LOG_INFO(LG_CRYP, "EncryptOk");
            }else {
                LOG_ERROR(LG_CRYP, "EncryptErr");
            }
        }
    }else {
        LOG_ERROR(LG_CRYP, "Usage: cd cryp_index key data");
    }
    return res;
}

bool cryp_decrypt_cbc_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t data_in[32];
    uint8_t data_out[32];
    memset(data_in,0,sizeof(data_in));
    memset(data_out,0,sizeof(data_out));

    uint32_t data_len = 0;
    uint8_t cryp_num=1;

    if(4<=argc) {
        res= fetch_arguments(  argc, argv, &cryp_num ,data_in, &data_len);
    }

    if(res) {
        CrypHandle_t* CrypNode=CrypGetNode( cryp_num);
        if(CrypNode) {
            res = aes256_cbc_decrypt_api( CrypNode->key32byte, data_in, data_len, data_out, CrypNode->algo_impl );
            if(res) {
                LOG_INFO(LG_CRYP, "DecryptOk");
            }else {
                LOG_ERROR(LG_CRYP, "DecryptErr");
            }
        }
    }else {
        LOG_ERROR(LG_CRYP, "Usage: cd cryp_index key data");
    }
    return res;
}
