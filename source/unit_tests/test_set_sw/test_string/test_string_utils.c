#include "test_string_utils.h"

#include <stdio.h>
#include <string.h>

#include "byte_utils.h"
#include "data_utils.h"
#include "log.h"
#include "str_utils.h"
#include "str_utils_ex.h"
#include "unit_test_check.h"

static bool test_delete_char_one(const char* const exp_str, const char* const in_str, char del_char) {
    LOG_INFO(TEST, "%s(): Exp:[%s],In:[%s],Del:[%c]", __FUNCTION__, exp_str, in_str, del_char);
    char temp[20] = {0};
    strcpy(temp, in_str);
    ASSERT_NE(NULL, str_del_char_inplace(temp, del_char));
    ASSERT_STREQ(exp_str, temp);

    return true;
}

static bool test_delete_substr_one(const char* const exp_str, const char* const in_str, char* del_sub_str) {
    LOG_INFO(TEST, "%s(): Exp:[%s],In:[%s],Del:[%s]", __FUNCTION__, exp_str, in_str, del_sub_str);
    char temp[40] = {0};
    char del_temp[40] = {0};
    strcpy(temp, in_str);
    strcpy(del_temp, del_sub_str);
    ASSERT_NE(NULL, str_del_substr_inplace(temp, del_temp));
    ASSERT_STREQ(exp_str, temp);

    return true;
}

bool test_delete_substr(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    log_level_get_set(LINE, LOG_LEVEL_DEBUG);
    log_level_get_set(ARRAY, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(test_delete_substr_one("nucleo_f413zh_uwb_m", ".hexnucleo_f413zh_uwb_m", ".hex"));
    ASSERT_TRUE(test_delete_substr_one("nucleo_f413zh_uwb_m", "nucleo_f413zh_uwb_m.hex", ".hex"));
    ASSERT_TRUE(test_delete_substr_one("nucleo_f413zh_uwb_m", "nucleo_f413.hexzh_uwb_m", ".hex"));
    log_level_get_set(ARRAY, LOG_LEVEL_INFO);
    log_level_get_set(LINE, LOG_LEVEL_INFO);
    return true;
}

bool test_delete_char(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_delete_char_one("", "d", 'd'));
    ASSERT_TRUE(test_delete_char_one("123456", "123ddd456d", 'd'));
    ASSERT_TRUE(test_delete_char_one("", "", 'd'));
    ASSERT_TRUE(test_delete_char_one("", "ddddddd", 'd'));
    ASSERT_TRUE(test_delete_char_one("", "", '3'));
    ASSERT_TRUE(test_delete_char_one("1234567", "12 34 567", ' '));
    ASSERT_TRUE(test_delete_char_one("1234567", "123456~7~", '~'));
    ASSERT_TRUE(test_delete_char_one("1234567", "!1234567", '!'));
    ASSERT_TRUE(test_delete_char_one("123456", "123456e", 'e'));
    ASSERT_TRUE(test_delete_char_one("123456", "ddddd123456", 'd'));
    ASSERT_TRUE(test_delete_char_one("123456", "123ddd456", 'd'));
    ASSERT_TRUE(test_delete_char_one("123456", "123456ddd", 'd'));

    return true;
}

bool test_str_limiter(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_STREQ("1234567", str_limit("1234567", 7));
    ASSERT_STREQ("1..", str_limit("1234567", 1));
    ASSERT_STREQ("1234567", str_limit("1234567", 100));
    ASSERT_STREQ("12345..", str_limit("1234567", 5));
    ASSERT_STREQ("1234..", str_limit("1234567", 4));

    return true;
}

bool test_replace_char(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    char temp[] = "us_1_0x55aa";
    int changes = replace_char(temp, '_', ' ');
    ASSERT_EQ(2, changes);
    ASSERT_STREQ("us 1 0x55aa", temp);
    return true;
}

#ifdef HAS_PC
bool test_replace_substr(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    char lText[100];
    strncpy(lText, "ksz8081_reg_parser.c", sizeof(lText));
    ASSERT_TRUE(replace_substring(lText, ".c", ".h"));
    ASSERT_STREQ(lText, "ksz8081_reg_parser.h");

    strncpy(lText, "aabzelaabzelaabzelaabzel", sizeof(lText));
    ASSERT_TRUE(replace_substring(lText, "bz", "MOS"));
    ASSERT_STREQ(lText, "aaMOSelaaMOSelaaMOSelaaMOSel");

    strncpy(lText, "aabzelaabzel", sizeof(lText));
    ASSERT_TRUE(replace_substring(lText, "bz", "MOS"));
    ASSERT_STREQ(lText, "aaMOSelaaMOSel");

    strncpy(lText, "aabzel", sizeof(lText));
    ASSERT_FALSE(replace_substring(lText, "spb", "mos"));
    ASSERT_STREQ(lText, "aabzel");

    strncpy(lText, "qwertyuioo", sizeof(lText));
    ASSERT_TRUE(replace_substring(lText, "rty", "ZXC"));
    ASSERT_STREQ(lText, "qweZXCuioo");

    strncpy(lText, "qwertyuiop", sizeof(lText));
    ASSERT_TRUE(replace_substring(lText, "qwe", "ASD"));
    ASSERT_STREQ(lText, "ASDrtyuiop");

    strncpy(lText, "asdfghjkl", sizeof(lText));
    ASSERT_TRUE(replace_substring(lText, "jkl", "BNM"));
    ASSERT_STREQ(lText, "asdfghBNM");

    return true;
}
#endif

// tsr replace_substr_first
bool test_replace_substr_first(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    log_level_get_set(LINE, LOG_LEVEL_DEBUG);
    char lText[1000];
    char exp_text[1000];
    strncpy(lText,
            "I2S,I2C,Relay,GPIO,Swd,GPIO,StartPause,,Writer,Log,Time,UART,Int,,SysTick,Clk,Flash,Timer,Clk,GPIO,UART,"
            "GPIO,ADC,GPIO,AdcChannels,board,I2C,GPIO,SPI,GPIO,CAN,GPIO,I2S,GPIO,WatchDog,Clk,DID,DID,Relay,GPIO,"
            "LedMonoInit,NVS,Flash,FlashFs,NVS,Flash,Param,Flash,FlashFs,ADT,Heap,Time,Timer,SysTick,SuperCycle,Time,"
            "Task,Time,Flash,Limiter,Button,GPIO,Time,HwInit,UnitTest,Cli",
            sizeof(lText));
    strncpy(exp_text,
            "I2S,I2C,Relay,Swd,GPIO,StartPause,,Writer,Log,Time,UART,Int,,SysTick,Clk,Flash,Timer,Clk,GPIO,UART,GPIO,"
            "ADC,GPIO,AdcChannels,board,I2C,GPIO,SPI,GPIO,CAN,GPIO,I2S,GPIO,WatchDog,Clk,DID,DID,Relay,GPIO,"
            "LedMonoInit,NVS,Flash,FlashFs,NVS,Flash,Param,Flash,FlashFs,ADT,Heap,Time,Timer,SysTick,SuperCycle,Time,"
            "Task,Time,Flash,Limiter,Button,GPIO,Time,HwInit,UnitTest,Cli",
            sizeof(exp_text));
    ASSERT_TRUE(replace_substring_first(lText, ",GPIO,", ","));
    LOG_INFO(TEST, "[%s]", lText);
    ASSERT_STREQ(exp_text, lText);
    log_level_get_set(LINE, LOG_LEVEL_INFO);
    return true;
}

#ifdef HAS_PC
static const char out_array2_exp[2] = {0xb1, 0xe4};
static const char out_array1_exp[16] = {0x94, 0x09, 0x94, 0x20, 0x1d, 0x1e, 0x00, 0x12,
                                        0x13, 0x17, 0x00, 0x5f, 0x0d, 0x9f, 0xf2, 0x04};

static const char testStrArray[] = " 0x940994201d1e00121317005f0d9ff204 0xb1e4";
bool test_count_substring(void) {
    ASSERT_EQ(2, count_substring((char*)testStrArray, "0x"));
    return true;
}

static bool test_parse_hex_array_after_prefix(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    char out_array[16] = {0};
    ASSERT_EQ(2, count_substring((char*)testStrArray, "0x"));
    ASSERT_TRUE(parse_lhex_array_after_prefix("0x", 0, (char*)testStrArray, out_array, 16));
    EXPECT_EQ_MEM(out_array, out_array1_exp, 16);

    Type16Union_t un16 = {0};
    ASSERT_TRUE(parse_lhex_array_after_prefix("0x", 1, (char*)testStrArray, &un16.u8[0], 2));
    EXPECT_EQ_MEM(&un16.u8[0], out_array2_exp, 2);
    ASSERT_EQ(0xb1e4, reverse_byte_order_uint16(un16.u16))
    return true;
}
#endif

bool test_string_extract(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    log_level_get_set(LINE, LOG_LEVEL_DEBUG);

    char in_text[80] = {0};
    char out_text[80] = {0};
    uint16_t ret_len = 0;

    ret_len = 0;
    memset(out_text, 0, sizeof(out_text));
    strncpy(in_text, "prefix:some_text", sizeof(in_text));
    ASSERT_TRUE(parse_text_after_prefix(in_text, strlen(in_text), out_text, &ret_len, "prefix:", ' '));
    ASSERT_STREQ("some_text", out_text);
    ASSERT_EQ(9, ret_len)

    ret_len = 0;
    memset(out_text, 0, sizeof(out_text));
    strncpy(in_text, "prefix:some_text\r\n", sizeof(in_text));
    ASSERT_TRUE(parse_text_after_prefix(in_text, strlen(in_text), out_text, &ret_len, "prefix:", '\n'));
    ASSERT_STREQ("some_text", out_text);
    ASSERT_EQ(9, ret_len)

    log_level_get_set(LINE, LOG_LEVEL_INFO);
    return true;
}

#ifdef HAS_PC
bool test_string_utils_ext(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_parse_hex_array_after_prefix());

    return true;
}
#endif

bool test_str_delete_con_duplicat(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    char lText[100] = {0};
    strcpy(lText, "h    vi ");
    ASSERT_TRUE(string_delete_continuous_duplicat(lText, ' '));
    LOG_INFO(LINE, "text [%s]", lText);
    ASSERT_STREQ("h vi ", lText);

    strcpy(lText, "        ");
    ASSERT_TRUE(string_delete_continuous_duplicat(lText, ' '));
    LOG_INFO(LINE, "text [%s]", lText);
    ASSERT_STREQ(" ", lText);

    return true;
}

bool test_string_delete_end(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    log_level_get_set(LINE, LOG_LEVEL_DEBUG);
    char lText[100] = {0};
    uint32_t del = 0;
    size_t size = 0;

    strcpy(lText, "h vi  ");
    size = strlen(lText);
    del = string_delete_end(lText, size, ' ');
    ASSERT_EQ(1, del);
    LOG_INFO(LINE, "lText [%s]", lText);
    ASSERT_STREQ("h vi", lText);

    strcpy(lText, "h    vi ");
    size = strlen(lText);
    del = string_delete_end(lText, size, ' ');
    ASSERT_EQ(1, del);
    LOG_INFO(LINE, "lText [%s]", lText);
    ASSERT_STREQ("h    vi", lText);

    strcpy(lText, "        ");
    size = strlen(lText);
    del = string_delete_end(lText, size, ' ');
    ASSERT_EQ(8, del);
    LOG_INFO(LINE, "lText [%s]", lText);
    ASSERT_STREQ("", lText);

    log_level_get_set(LINE, LOG_LEVEL_INFO);
    return true;
}
// tsr str_del_substr_inplace_firts
const char ExpText[] = "I2C,Flash,DID,DID,Relay,GPIO,NVS,Flash,NVS,Flash,Flash,FlashFs,UnitTest";
bool test_str_del_substr_inplace_firts(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    log_level_get_set(LINE, LOG_LEVEL_DEBUG);

    char lText[] = "I2C,Flash,DID,DID,Relay,GPIO,NVS,Flash,FlashFs,NVS,Flash,Flash,FlashFs,UnitTest";
    LOG_INFO(LINE, "Prev  [%s]", lText);
    str_del_substr_inplace_firts(lText, "FlashFs,");
    LOG_INFO(LINE, "Afrer [%s]", lText);

    ASSERT_STREQ(ExpText, lText);

    log_level_get_set(LINE, LOG_LEVEL_INFO);
    return true;
}
