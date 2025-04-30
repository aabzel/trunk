#include "test_base64.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Test based on
 * base64 to hex
 * https://base64.guru/converter/decode/hex
 *
 * hex to base64
 * https://cryptii.com/pipes/hex-to-base64
 */
#include "debug_info.h"
#include "base64.h"
#include "log.h"
#include "unit_test_check.h"

static bool test_base64_encode_one(const uint8_t *const bin, uint32_t size,
		char *exp_res, uint32_t exp_size){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t out[40] = {0};
    uint32_t out_size = 0;
    out_size = base64_encode(bin, size, out) ;
    print_mem(out, out_size, false, true, true, false);
    ASSERT_GR(0, out_size);
    EXPECT_EQ_MEM(out, exp_res, exp_size);
    return true;
}

bool test_base64_code(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    const uint8_t BinIn1[]={0x00,0x00,0x00,0x00,0x00};
    ASSERT_TRUE(test_base64_encode_one(BinIn1, 5, "AAAAAAA=", 8));

    const uint8_t BinIn2[]={0xFF,0xFF,0xFF,0xFF};
    ASSERT_TRUE(test_base64_encode_one(BinIn2, 4, "/////w==", 8));
    return true;
}

bool test_base64_decode(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    const char base64[]="DJ4MdKaHIe4=";
    int32_t len=strlen(base64);
    ASSERT_EQ(12,len);
    const uint8_t exp_bin[]={0x0c,0x9e,0x0c,0x74,0xa6,0x87,0x21,0xee};
    uint8_t out[40] = {0};
    uint32_t out_size = 0;
    ASSERT_TRUE( base64_decode(base64, len, out, &out_size));
    print_mem(  out,   out_size, true, false, true, false);
    ASSERT_GR(0,out_size);
    EXPECT_EQ_MEM(exp_bin, out, 8);
    return true;
}


