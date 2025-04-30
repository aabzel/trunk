#include "test_salsa20.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "base64.h"
#include "salsa20.h"
#include "log.h"
#include "debug_info.h"
#include "unit_test_check.h"
#include "sha256.h"

static const uint8_t ProtectedStreamKey[32] ={
0x8C, 0xE6, 0xD6, 0x92, 0x36, 0xB3, 0x4C, 0x60,
0x15, 0x19, 0x74, 0xD3, 0x5F, 0x54, 0x32, 0x7F,
0xBD, 0x81, 0x1F, 0xEF, 0xDE, 0xF5, 0x68, 0xDF,
0xEE, 0x36, 0x8A, 0xBD, 0x4D, 0x98, 0xCC, 0xC7
};

static const  uint8_t nonce[8] = {
		0xE8, 0x30, 0x09, 0x4B, 0x97, 0x20, 0x5D, 0x2A };


bool test_salsa20(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t KeyStream[64]={0};
    uint8_t HashedKey[32]={0};
    LOG_INFO(SALSA20, "ProtectedStreamKey");
    print_mem(ProtectedStreamKey,sizeof(ProtectedStreamKey), true, true, true, true);
    sha256_hash(HashedKey, ProtectedStreamKey, 32);
    ASSERT_EQ(S20_SUCCESS, s20_crypt(HashedKey, S20_KEYLEN_256, nonce, 0, KeyStream, 64));
    LOG_INFO(SALSA20, "StramKey");
    print_mem(KeyStream,sizeof(KeyStream), true, true, true, true);
    char decoded_pass[20]="DJ4MdKaHIe4=";
    int len=strlen(decoded_pass);
    ASSERT_EQ(12,len);
    uint8_t out[64]={0};
    uint32_t out_size=0;
    ASSERT_TRUE(base64_decode(decoded_pass, len, out, &out_size));
    ASSERT_EQ(8,out_size);
    print_mem(out,out_size, true, true, true, false);
    //char decoded_pass[64]={0x0c,0x9e,0x0c,0x74,0xa6,0x87,0x21,0xee};
    print_mem(decoded_pass,len, true, true, true, false);

    uint32_t i=0;
    for(i=0; i<len; i++) {
    	out[i] ^= KeyStream[i];
    }

    LOG_INFO(TEST, "After Decrypt");
    print_mem(out,len, true, true, true, false);
    char exp_message[20]="4eoDjwgg";
    EXPECT_EQ_MEM(exp_message, out, 8);
    //6b9a7dbc7c6e73e32ee11cbf8aeb807a    |k□}□|ns□.□∟□□□□z|

    return true;
}
