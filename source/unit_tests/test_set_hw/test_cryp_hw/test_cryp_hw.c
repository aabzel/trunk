#include "test_cryp_hw.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "aes_test_case.h"
#include "array.h"
#include "cryp_custom_drv.h"
#include "cryp_drv.h"
#include "debug_info.h"
#include "log.h"
#include "unit_test_check.h"

// https://the-x.cn/en-us/cryptography/Aes.aspx

#define ORIGIN_TEXT "TestMessage"
const uint8_t DecryptedTextExpected[64] = ORIGIN_TEXT;
//static const uint8_t InitVector[16] = {0};

static uint8_t CipherText[64] = "";
static uint8_t DecryptedText[64] = "";
static uint8_t PlainText[64] = ORIGIN_TEXT;

bool test_hw_aes256_ecb_encrypt(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);

    uint8_t plain_data[16];
    memcpy(plain_data, Case1.PlainText, sizeof(Case1.PlainText));

    LOG_INFO(TEST, "PlainText" CRLF);
    print_bin(plain_data, sizeof(plain_data), 0);
    cli_printf(CRLF);

    size_t size = sizeof(plain_data);

    LOG_INFO(TEST, "Key256bit" CRLF);
    print_bin(Case1.Key256bit, sizeof(Case1.Key256bit), 0);
    cli_printf(CRLF);

    ASSERT_TRUE(hw_aes256_ecb_encrypt((uint8_t*)Case1.Key256bit, plain_data, sizeof(plain_data), CipherText));

    LOG_INFO(TEST, "CipherText" CRLF);
    print_bin(CipherText, size, 0);
    cli_printf(CRLF);

    uint32_t match = 0;
    uint32_t diff = 0;
    ASSERT_TRUE(is_array_equal(Case1.CipherText, CipherText, size, &match, &diff));
    return true;
}

bool test_hw_aes256_ecb_encrypt_decrypt(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    memset(PlainText, 0, sizeof(PlainText));
    strcpy(PlainText, ORIGIN_TEXT);

    strcpy(DecryptedText, "");
    strcpy(CipherText, "");

    ASSERT_EQ(32, sizeof(Case1.Key256bit));

    LOG_INFO(TEST, "PlainText");
    print_bin(PlainText, sizeof(PlainText), 0);
    cli_printf(CRLF);

    LOG_INFO(TEST, "Key256bit");
    print_bin(Case1.Key256bit, sizeof(Case1.Key256bit), 0);
    cli_printf(CRLF);

    ASSERT_TRUE(hw_aes256_ecb_encrypt((uint8_t*)Case1.Key256bit, PlainText, sizeof(PlainText), CipherText));

    LOG_INFO(TEST, "CipherText");
    print_bin(CipherText, sizeof(CipherText), 0);
    cli_printf(CRLF);

    ASSERT_TRUE(hw_aes256_ecb_decrypt((uint8_t*)Case1.Key256bit, CipherText, sizeof(CipherText), DecryptedText));
    uint32_t match = 0;
    uint32_t diff = 0;
    ASSERT_TRUE(is_array_equal(DecryptedTextExpected, DecryptedText, sizeof(PlainText), &match, &diff));
    LOG_INFO(TEST, "%s() Ok", __FUNCTION__);
    return true;
}

bool test_hw_aes256_cbc_encrypt(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    memset(CipherText, 0, sizeof(CipherText));

    memcpy(PlainText, Case3.PlainText, sizeof(PlainText));

    LOG_INFO(TEST, "PlainText");
    print_bin(Case3.PlainText, sizeof(Case3.PlainText), 0);
    cli_printf(CRLF);

    LOG_INFO(TEST, "Key256bit");
    print_bin(Case3.Key256bit, sizeof(Case3.Key256bit), 0);
    cli_printf(CRLF);

    LOG_INFO(TEST, "InitVector");
    print_bin(Case3.InitVector, sizeof(Case3.InitVector), 0);
    cli_printf(CRLF);

    ASSERT_EQ(32, sizeof(Case3.Key256bit));

    ASSERT_TRUE(hw_aes256_cbc_init(Case3.Key256bit, Case3.InitVector, IV_SKIP_CFG_ALWAYS));
    cli_printf(CRLF);

    ASSERT_TRUE(hw_aes256_cbc_encrypt((uint8_t*)Case3.Key256bit, PlainText, sizeof(PlainText), CipherText));

    LOG_INFO(TEST, "CipherText");
    print_bin(CipherText, sizeof(CipherText), 0);
    cli_printf(CRLF);

    uint32_t match = 0;
    uint32_t diff = 0;

    ASSERT_TRUE(is_array_equal(Case3.CipherText, CipherText, sizeof(Case3.CipherText), &match, &diff));

    LOG_INFO(TEST, "%s() Ok", __FUNCTION__);
    return true;
}

bool test_hw_aes256_cbc_encrypt_decrypt(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    strcpy(PlainText, ORIGIN_TEXT);
    strcpy(DecryptedText, "");
    strcpy(CipherText, "");

    LOG_INFO(TEST, "PlainText");
    print_bin(PlainText, sizeof(PlainText), 0);

    LOG_INFO(TEST, "Key256bit");
    print_bin(Case1.Key256bit, sizeof(Case1.Key256bit), 0);

    ASSERT_EQ(32, sizeof(Case1.Key256bit));
    ASSERT_TRUE(hw_aes256_cbc_encrypt((uint8_t*)Case1.Key256bit, PlainText, sizeof(PlainText), CipherText));

    LOG_INFO(TEST, "CipherText");
    print_bin(CipherText, sizeof(CipherText), 0);

    ASSERT_TRUE(hw_aes256_cbc_decrypt((uint8_t*)Case1.Key256bit, CipherText, sizeof(CipherText), DecryptedText));
    uint32_t match = 0;
    uint32_t diff = 0;

    ASSERT_TRUE(is_array_equal(DecryptedText, DecryptedTextExpected, sizeof(PlainText), &match, &diff));
    LOG_INFO(TEST, "%s() Ok", __FUNCTION__);
    return true;
}
