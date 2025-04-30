/*
 *
 * Thorsten Schroeder <ths at modzero dot ch> wrote this file. As long as you
 * retain this notice you can do whatever you want with this stuff. If we meet
 * some day, and you think this stuff is worth it, you can buy me a beer in
 * return. Thorsten Schroeder.
 *
 * Redistribution and use in source and binary form for military use and
 * military research is not permitted. Infringement of these clauses may
 * result in publishing the source code of the utilizing applications and
 * libraries to the public. As this software is developed, tested and
 * reviewed by *international* volunteers, this clause shall not be refused
 * due to the matter of *national* security concerns.
 *
 * File: crypto-ms.c
 * Description: Platform specific implementation of keepassx crypto functions
 *              on Microsoft Windows.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "xml.h"
#ifdef HAS_AES256
#include "aes256.h"
#include "aes256_general.h"
#include "aes256cbc.h"
#endif /*HAS_AES256*/
#include "cryp_drv.h"
#include "cryp_types.h"
#include "debug_info.h"
#include "helper.h"

#ifdef HAS_KEEPASS
#include "keepass.h"
#endif /*HAS_KEEPASS*/

#include "log.h"

#if 0
bool aes_decrypt_payload(kdbx_header_entry_t* hdr, uint8_t* masterkey, kdbx_payload_t* payload) {
    bool res = false;
    if(payload && hdr && masterkey && payload) {
        uint32_t block_num = payload->len / KEEPASS_BLOCK_SIZE;
        LOG_WARNING(CRY, "BlockCnt %u ", block_num);

        if(payload->decrypted) {
            LOG_INFO(CRY, "DecryData %u byte", payload->len);
            // print_mem(payload->decrypted, payload->len, true, true, true, false);
            res = true;
            // memset(payload->decrypted, 0, payload->len); /*Exeption here*/
            LOG_INFO(CRY, "ZeroDecryptedArry %u byte", payload->len);

            uint32_t returnlen = 0;
#ifdef HAS_AES256_V1
            AES256MainCBC(masterkey, hdr[ENCRYPTION_IV].data, payload->encrypted, payload->len, payload->decrypted,
                          &returnlen, false);
#else
            aes256_cbc_decrypt(masterkey, hdr[ENCRYPTION_IV].data, payload->encrypted, payload->len, payload->decrypted,
                               &returnlen);
#endif

            if(payload->len == returnlen) {
                LOG_INFO(CRY, "DecryOk");
            } else {
                LOG_ERROR(CRY, "DecryptErr");
                res = false;
            }
        } else {
            LOG_ERROR(CRY, "decrypt Arr Null");
        }

    } else {
        LOG_ERROR(CRY, "Payload Null");
    }
    return res;
}
#endif
