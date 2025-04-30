#include "test_base16.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "base16.h"
#include "log.h"
#include "unit_test_check.h"
#include "debug_info.h"

bool test_is_base16_str(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_FALSE( is_base16("r234ab5c6d7e8f", strlen("r234ab5c6d7e8f")));
    ASSERT_TRUE( is_base16("1234ab5c6d7e8f", strlen("1234ab5c6d7e8f")));
    return true;
}

static bool test_base16_encode_one(const uint8_t *const bin, uint32_t size,
		char *exp_res, uint32_t exp_size){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t out[40] = {0};

    ASSERT_TRUE( base16_encode(bin, size, out) );
    print_mem(out, size*2, false, true, true, false);

    EXPECT_EQ_MEM(out, exp_res, exp_size);
    return true;
}

bool test_base16_code(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    const uint8_t BinIn1[]={0x00,0x00,0x00,0x00,0x00};
    ASSERT_TRUE(test_base16_encode_one(BinIn1, 5, "0000000000", 10));

    const uint8_t BinIn2[]={0xFF,0xFF,0xFF,0xFF};
    ASSERT_TRUE(test_base16_encode_one(BinIn2, 4, "FFFFFFFF", 8));
    return true;
}

bool test_base16_decode(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    const char base16[]="0c9e0c74a68721ee";
    int32_t len = strlen(base16);
    ASSERT_EQ(16, len);
    const uint8_t exp_bin[]={0x0c,0x9e,0x0c,0x74,0xa6,0x87,0x21,0xee};
    uint8_t out[40] = {0};
    uint32_t out_size = 0;
    ASSERT_TRUE( base16_decode(base16, len, out, &out_size));
    print_mem(  out,   out_size, true, false, true, false);
    ASSERT_EQ(8,out_size);
    EXPECT_EQ_MEM(exp_bin, out, 8);
    return true;
}


