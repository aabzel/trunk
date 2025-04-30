#include "aes256_general.h"

#include <stdbool.h>
#include <string.h>

#include "aes256.h"
#include "log.h"

#ifndef HAS_AES256_V1
#include "aes256cbc.h"
#endif


bool aes256_ecb_decrypt(const uint8_t* key,
        uint8_t* data_in, uint32_t datalen,
        uint8_t* data_out, uint32_t* returnlen){
    bool res = false;
#ifndef HAS_AES256_V1
    aes256_context_t ctx;

    uint8_t ret = aes256_init(&ctx, (aes256_key_t *)key);

    uint32_t b = 0;
    uint32_t blk_cnt = datalen/16;
    for(b=0; b<blk_cnt; b++) {
        ret = aes256_decrypt_ecb(&ctx, (aes256_blk_t*) &data_in[b*16]);
        if(AES_SUCCESS==ret) {
            LOG_DEBUG(AES256,"Ok");
            res = true;
        } else {
            LOG_ERROR(AES256,"Err");
            res = false;
        }

    }
    if(res) {
        memcpy(data_out,data_in,datalen);
        *returnlen = datalen;
    }
#endif
    return res;
}

bool aes256_ecb_encrypt(const uint8_t* key,
        uint8_t* data_in, uint32_t datalen,
        uint8_t* data_out,uint32_t* returnlen){
    bool res = false;
#ifndef HAS_AES256_V1
    aes256_context_t ctx;

    uint8_t ret = aes256_init(&ctx, (aes256_key_t *)key);

    uint32_t b = 0;

    uint32_t blk_cnt = datalen/16;
    for(b=0; b<blk_cnt; b++) {
        ret = aes256_encrypt_ecb(&ctx, (aes256_blk_t*) &data_in[b*16]);
        if(AES_SUCCESS==ret){
            LOG_DEBUG(AES256,"Ok");
            res = true;
        }else{
            LOG_ERROR(AES256,"Err");
            res = false;
        }

    }
    if(res){
        memcpy(data_out,data_in,datalen);
        *returnlen = datalen;
    }
#endif
    return res;
}

bool aes256_cbc_encrypt(uint8_t* key, uint8_t* iv,
        uint8_t* in_data, uint32_t datalen,
        uint8_t* out_data, uint32_t* returnlen ){
    bool res = false;
#ifndef HAS_AES256_V1
    AES_ctx ctx;
    AES256CBC_init_ctx_iv( &ctx,  key, iv);
    AES256CBC_encrypt(&ctx, in_data, datalen);
    out_data=in_data;
    *returnlen=datalen;
#endif
    return res;
}

bool aes256_cbc_decrypt(uint8_t* key, uint8_t* iv,
        uint8_t* in_data, uint32_t datalen, uint8_t* out_data,
        uint32_t* returnlen) {
    bool res = false;
#ifndef HAS_AES256_V1
    LOG_DEBUG(AES256, "CBC DeCrypt %u byte",datalen);
    if (datalen && in_data && out_data && key && iv) {
        AES_ctx ctx;
        AES256CBC_init_ctx_iv(&ctx, key, iv);
        memcpy(out_data, in_data, datalen);
        AES256CBC_decrypt(&ctx, out_data, datalen);
        *returnlen = datalen;
    } else {
        LOG_ERROR(AES256, "CbcDecryptErr");
    }
#endif
    return res;
}

bool aes256_cbc_decrypt_stream(AES_ctx* ctx, uint8_t* key,
        uint8_t* in_data, uint32_t datalen, uint8_t* out_data,
        uint32_t* returnlen) {
    bool res = false;
#ifndef HAS_AES256_V1
    LOG_DEBUG(AES256, "CBC DeCrypt %u byte",datalen);
    if(ctx && datalen && in_data && out_data && key) {
    	memcpy(out_data,in_data,datalen);
        AES256CBC_decrypt(ctx, out_data, datalen);
        *returnlen = datalen;
    } else {
        LOG_ERROR(AES256, "CBC DecryptErr Size: %d Byte",datalen);
    }
#endif
    return res;
}

