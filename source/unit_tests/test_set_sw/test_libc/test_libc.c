#include "test_libc.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*
 */

#include "log.h"
#include "unit_test_check.h"

static char test_text[250] = "";
bool test_libc_stdio(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    double val = 123.45;
    strcpy(test_text, "");
    sprintf(test_text, "val=%6.2f", val);
    // snprintf(test_text, sizeof(test_text), "val=%6.2f", val);
    LOG_INFO(TEST, "test_text [%s]", test_text);
    ASSERT_STREQ("val=123.45", test_text);

    val = 543.21;
    strcpy(test_text, "");
    snprintf(test_text, sizeof(test_text), "val=%6.2f", val);
    LOG_INFO(TEST, "test_text [%s]", test_text);
    ASSERT_STREQ("val=543.21", test_text);

    return res;
}

//| 100 |     accenture |  aabzele@gmail.. | sTNEQ#ImB@KVnnO7Sgv4.. | nFEoWE5rYKxFU9y1WeXS.. | 32 | 22 | 68.
static char const test_text_exp[250] =
    "  0.00  1.00  2.00  3.00  4.00  5.00  6.00  7.00  8.00  9.00 10.00 11.00 12.00 13.00 14.00 15.00 16.00 17.00 "
    "18.00 19.00 20.00 21.00 22.00 23.00 24.00 25.00 26.00 27.00 28.00 29.00 30.00 31.00 32.00 33.00 34.00";
bool test_libc_sprintf_long(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    strcpy(test_text, "");
    uint16_t i = 0;
    for(i = 0; i <= 34; i++) {
        sprintf(test_text, "%s %5.2f", test_text, (double)i);
    }

    ASSERT_STREQ(test_text_exp, test_text);
    cli_printf("%s" CRLF, test_text);

    strcpy(test_text, "");
    i = 0;
    for(i = 0; i <= 34; i++) {
        snprintf(test_text, sizeof(test_text), "%s %5.2f", test_text, (double)i);
    }
    ASSERT_STREQ(test_text_exp, test_text);
    cli_printf("%s" CRLF, test_text);

    return res;
}

bool test_libc_stdio_uint64(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint64_t val64 = 0x1012345678ABCDEF;
    strcpy(test_text, "");
    sprintf(test_text, "val=0x%08llX", val64);

    LOG_WARNING(TEST, "test_text [%s]", test_text);
    LOG_WARNING(TEST, "val=0x%08llX", val64);
    ASSERT_STREQ("val=0x1012345678ABCDEF", test_text); //=0x78abcdef

    sprintf(test_text, "val=%llu", val64);
    LOG_WARNING(TEST, "test_text [%s]", test_text);
    LOG_WARNING(TEST, "val=%llu", val64);
    ASSERT_STREQ("val=1158045600183995887", test_text); //=1158045600183995887

    return res;
}

bool test_libc_stdio_small_double(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    double val = 0.000000003125;
    strcpy(test_text, "");
    sprintf(test_text, "val=%14.12f", val);
    LOG_INFO(TEST, "test_text [%s]", test_text);
    LOG_INFO(TEST, "val=%f", val);
    LOG_INFO(TEST, "val=%lf", val);
    ASSERT_STREQ("val=0.000000003125", test_text);
    return res;
}

bool test_libc_sprintf_minus(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    int16_t sample = -1;

    strcpy(test_text, "");
    cli_printf("cli test_text 0x%04x", (uint16_t)sample);
    sprintf(test_text, "0x%04X", (uint16_t)sample);
    LOG_INFO(TEST, "sprintf test_text [%s]", test_text);
    cli_printf("cli test_text 0x%04X" CRLF, (uint16_t)sample);
    ASSERT_STREQ("0xFFFF", test_text);

    strcpy(test_text, "");
    sprintf(test_text, "0x%04x", (uint16_t)sample);
    LOG_INFO(TEST, "sprintf test_text [%s]" CRLF, test_text);
    ASSERT_STREQ("0xffff", test_text);
    return res;
}
