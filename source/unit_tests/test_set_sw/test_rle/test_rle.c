#include "test_rle.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
/*
 */

#include "debug_info.h"
#include "log.h"
#include "rle.h"
#include "unit_test_check.h"

static bool test_rle_encode_one(char* bin, uint32_t size, char* exp_res, uint32_t exp_size) {
    bool res = true;
    set_log_level(RLE, LOG_LEVEL_DEBUG);
    LOG_INFO(RLE, "%s(): In[%s] Exp[%s]", __FUNCTION__, bin, exp_res);
    uint8_t out[80] = {0};
    uint32_t out_size = 0;
    EXPECT_TRUE(rle_encode(bin, size, out, &out_size));
    LOG_INFO(RLE, "Out [%s]", out);
    print_mem(out, out_size, false, true, true, false);
    EXPECT_GR(0, out_size);
    EXPECT_STREQ(out, exp_res);
    return res;
}

bool test_rle_encode(void) {
    LOG_INFO(RLE, "%s():", __FUNCTION__);
    set_log_level(RLE, LOG_LEVEL_DEBUG);
    char in_str[100];
    bool res = true;
    EXPECT_TRUE(test_rle_encode_one("CAAAABBBBB", 10, "CA4B5", 5));
    EXPECT_TRUE(test_rle_encode_one("ABC", 3, "ABC", 3));

    strcpy(in_str, "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW");
    EXPECT_TRUE(test_rle_encode_one(in_str, strlen(in_str), "W12BW12B3W24BW14", 16));
    set_log_level(RLE, LOG_LEVEL_INFO);
    return res;
}

static bool test_rle_decode_one(char* in_text, uint32_t size, char* exp_res, uint32_t exp_size) {
    LOG_INFO(RLE, "%s(): In[%s] Exp[%s]", __FUNCTION__, in_text, exp_res);
    bool res = true;
    uint8_t out[40] = {0};
    uint32_t out_size = 0;
    EXPECT_TRUE(rle_decode(in_text, size, out, &out_size));
    LOG_INFO(RLE, "Out [%s]", out);
    print_mem(out, out_size, false, true, true, false);
    EXPECT_GR(0, out_size);
    EXPECT_STREQ(out, exp_res);
    return res;
}

bool test_rle_decode(void) {
    LOG_INFO(RLE, "%s():", __FUNCTION__);
    set_log_level(RLE, LOG_LEVEL_DEBUG);
    bool res = true;
    EXPECT_TRUE(test_rle_decode_one("CA4B5", 5, "CAAAABBBBB", 10));
    EXPECT_TRUE(test_rle_decode_one("AB2CD", 5, "ABBCD", 5));
    EXPECT_TRUE(test_rle_decode_one("ABCD", 4, "ABCD", 4));
    set_log_level(RLE, LOG_LEVEL_INFO);
    return res;
}

static bool test_rle_encode_decode_one(char* text) {
    LOG_INFO(RLE, "%s(): [%s] Size:%u", __FUNCTION__, text, strlen(text));
    bool res = true;
    uint8_t out[100] = {0};
    uint32_t out_size = 0;

    uint8_t raw_text[100] = {0};
    uint32_t raw_size = 0;

    EXPECT_TRUE(rle_encode(text, strlen(text), out, &out_size));
    EXPECT_TRUE(rle_decode(out, strlen(out), raw_text, &raw_size));

    EXPECT_EQ(strlen(text), strlen(raw_text));
    EXPECT_STREQ(text, raw_text);

    return res;
}

bool test_rle_encode_decode(void) {
    bool res = true;
    LOG_INFO(RLE, "%s():", __FUNCTION__);
    set_log_level(RLE, LOG_LEVEL_DEBUG);

    EXPECT_TRUE(test_rle_encode_decode_one("WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW"));
    EXPECT_TRUE(test_rle_encode_decode_one("CAAAABBBBB"));
    EXPECT_TRUE(test_rle_encode_decode_one("ABC"));

    set_log_level(RLE, LOG_LEVEL_INFO);
    return res;
}

bool test_rle_encode_v2(void) {
    bool res = true;
    LOG_INFO(RLE, "%s():", __FUNCTION__);
    set_log_level(RLE, LOG_LEVEL_DEBUG);
    char in_str[100];
    strcpy(in_str, "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW");
    rle_encode_v2(in_str, strlen(in_str));

    EXPECT_STREQ("W12BW12B3W24BW14", in_str);
    set_log_level(RLE, LOG_LEVEL_INFO);
    return res;
}

bool test_rle_encode_in_place(void) {
    bool res = true;
    LOG_INFO(RLE, "%s():", __FUNCTION__);
    set_log_level(RLE, LOG_LEVEL_DEBUG);
    char in_str[100];
    strcpy(in_str, "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW");
    rle_encode_in_place(in_str, strlen(in_str));

    EXPECT_STREQ("W12BW12B3W24BW14", in_str);
    set_log_level(RLE, LOG_LEVEL_INFO);
    return res;
}
