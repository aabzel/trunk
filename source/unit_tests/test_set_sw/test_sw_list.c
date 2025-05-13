#include "test_sw_list.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "array.h"
#include "data_utils.h"
#ifdef HAS_STRING
#include "convert.h"
#endif

#ifdef HAS_AUDIO
#include "audio_types.h"
#endif

#include "unit_test_check.h"

#ifdef HAS_CLOCK
#include "clock.h"
#endif

#ifdef HAS_LOG
#include "debug_info.h"
#include "log.h"
#include "writer_generic.h"
#endif /*HAS_LOG*/

#ifdef HAS_SYSTEM
#include "system.h"
#endif

static uint64_t mul64(uint64_t val_a, uint64_t val_b) {
    uint64_t out = val_a * val_b;
    return out;
}
#ifdef HAS_MCU
bool test_float_to_uint16(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_EQ(1, float_to_uint16(1.0f));     /*Fails on desktop*/
    ASSERT_EQ(50, float_to_uint16(50.0f));   /*Fails on desktop*/
    ASSERT_EQ(100, float_to_uint16(100.5f)); /*Fails on desktop*/
    uint16_t val = 0;
    for(val = 0; val < 0xFFFA; val++) {
        ASSERT_EQ(val, float_to_uint16(0.13f + ((float)val)));
    }
    return true;
}
#endif

bool test_double_to_uint16(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_EQ(100, double_to_uint16(100.5));
    uint16_t val = 0;
    for(val = 0; val < 0xFFFA; val++) {
        ASSERT_EQ(val, double_to_uint16(0.13 + ((double)val)));
    }
    return true;
}

bool test_array(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t a = 3;
    uint8_t b[4] = {1, 2, 3, 4};
#ifdef HAS_CLI
    cli_printf("a[b]: %u " CRLF, a[b]);
    cli_printf("b[a]: %u " CRLF, b[a]);
#endif /*HAS_CLI*/
    ASSERT_EQ(a[b], b[a]);

    a = 0xff;
    a++;
    ASSERT_EQ(0x00, a);
    return true;
}

bool test_uspec_behavior(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_EQ(11, sizeof("plane_text"));
    return true;
}

bool test_utoa_bin8(void) {
    /*Clang fail here in Run time*/
#if 0
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    char *name = utoa_bin8(0xaa);
    char temp[100]="";
    strcpy(temp,"1010_1010");
    EXPECT_STREQ(temp, name);

    LOG_INFO(TEST, "%s(): middle", __FUNCTION__);
    strcpy(temp,"0101_0101");
    name = utoa_bin8(0x55);
    EXPECT_STREQ(temp, (char*)utoa_bin8(0x55));

    LOG_INFO(TEST, "%s() done", __FUNCTION__);
#endif
    return true;
}

// tsr array_init
bool test_array_init(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t arr[4] = {42, 2};
    ASSERT_EQ(42, arr[0]);
    ASSERT_EQ(2, arr[1]);
    ASSERT_EQ(0, arr[2]);
    ASSERT_EQ(0, arr[3]);
    // ++i=i++; build error
    // i++=++i; build error
    return true;
}

bool test_64bit_mult(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    ASSERT_EQ(8, sizeof(uint64_t));
    uint64_t temp10x3 = mul64((uint64_t)1000, (uint64_t)12000000);
#ifdef HAS_ARRAY_DIAG
    print_mem((uint8_t*)&temp10x3, sizeof(temp10x3), false, false, false, false);
#endif /*HAS_CLI*/
    // in memory          0x007841cb00000000
    // value              0x00000000cb417800
    EXPECT_EQ_U64((uint64_t)12000000000, temp10x3);
    // exp        3410065408 cb417800 2 3410065408 14646119404580896770
    //  temp10x3: 48         cb417800 2 3410065408 14646119404580896770!
#ifdef HAS_CLI
#ifdef HAS_ARRAY_DIAG
    uint64_t exp = 0x00000002CB417800;
    cli_printf("\n exp: %llu" "" CRLF, 0x00000002CB417800);
    print_mem((uint8_t*)&exp, 8U, false, false, false, false);
    print_mem((uint8_t*)&temp10x3, 8U, false, false, false, false);
#endif
    cli_printf("\n temp10x3: %llu" "" CRLF, temp10x3);
#endif /*HAS_CLI*/
    return res;
}

#ifdef HAS_MCU
static bool test_type_transformation_arg(uint16_t expected, float input) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_EQ(expected, (uint16_t)(((float)10U) * (input)));
    ASSERT_EQ(expected, (uint16_t)(((float)10.0f) * (input)));
    return true;
}
#endif

bool test_type_transformation(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
#ifdef HAS_MCU
    ASSERT_TRUE(test_type_transformation_arg(125, 12.5f));
    ASSERT_TRUE(test_type_transformation_arg(1256, 125.6f));
#endif
    return true;
}

typedef struct {
    uint8_t a;
    uint8_t b;
    uint8_t c;
} SomeType_t;

bool test_c_types(void) {
    LOG_INFO(TEST, "%s()..", __FUNCTION__);
    bool res = true;
    LOG_INFO(TEST, "(uint32_t)-1 %u", (uint32_t)-1);
#ifdef HAS_SYSTEM
#ifdef HAS_GCC
    // ASSERT_EQ(1, sizeof(Interfaces_t));
#endif /*HAS_GCC*/
#ifdef HAS_CLANG
    EXPECT_EQ(4, sizeof(Interfaces_t));
#endif /*HAS_CLANG*/
#endif /*HAS_SYSTEM*/

#if defined(HAS_CLANG)
    EXPECT_EQ(8, sizeof(long));   /*clang 8*/
    EXPECT_EQ(8, sizeof(1UL));    /*clang 8*/
    EXPECT_EQ(8, sizeof(1L));     /*clang 8*/
    EXPECT_EQ(8, sizeof(size_t)); /*clang 8*/
    EXPECT_EQ(8, sizeof(1l));     /*clang 8*/
#else
    EXPECT_EQ(4, sizeof(long));
    EXPECT_EQ(4, sizeof(1UL));
    EXPECT_EQ(4, sizeof(1L));
    EXPECT_EQ(4, sizeof(size_t));
    EXPECT_EQ(4, sizeof(1l));
#endif

    EXPECT_EQ(4, sizeof(1));
    EXPECT_EQ(4, sizeof(-1));
    EXPECT_EQ(4, sizeof(0b1));
    EXPECT_EQ(4, sizeof(1U));
    EXPECT_EQ(4, sizeof(1u));
    EXPECT_EQ(10, sizeof("0000_0000"));
    EXPECT_EQ(4, sizeof(1.f));
#ifdef HAS_CORE_NET
    EXPECT_EQ(4, sizeof(1.0));
#else
    EXPECT_EQ(8, sizeof(1.0));
#endif
    EXPECT_EQ(8, sizeof(1LL));
    EXPECT_EQ(1, sizeof(char));
    EXPECT_EQ(4, sizeof(float));
    // EXPECT_EQ(4, sizeof(ssize_t));
    EXPECT_EQ(4, sizeof(unsigned));
    EXPECT_EQ(1, sizeof(uint8_t));
    EXPECT_EQ(8, sizeof(uint64_t));
    EXPECT_EQ(4, sizeof(int));
    EXPECT_EQ(2, sizeof(short int));
#ifdef HAS_AUDIO
    EXPECT_EQ(3, sizeof(Sample24bit_t));
#endif
    EXPECT_EQ(3, sizeof(SomeType_t));
    ASSERT_TRUE(is_little_endian());

    uint8_t uval = 0;
    uval--;
    ASSERT_EQ_CONST(0xFF, uval);

    uval = 0;
    uval = uval >> 1;
    ASSERT_EQ_CONST((int8_t)0, uval);

    int8_t sval = -2; // 0b11111110    0xFE
    ASSERT_EQ_CONST((int8_t)0xFE, sval);
    sval = sval >> 1;
    // 0b11111110 0xFE
    ASSERT_EQ_CONST((int8_t)-1, sval);
    ASSERT_EQ_CONST((int8_t)0xFF, sval);

    sval = sval >> 1;
    // 0b11111111 0xFF
    ASSERT_EQ_CONST((int8_t)0xFF, (int8_t)sval);
    ASSERT_EQ_CONST((int8_t)-1, sval);

    sval = (int8_t)0xFE;
    LOG_INFO(TEST, "%u %d", sval, sval);

    LOG_INFO(TEST, "%s() Ok", __FUNCTION__);
    return res;
}

bool test_swap_xor(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint32_t a = 3;
    uint32_t b = 32;
    ASSERT_TRUE(swap_u32_xor(&a, &b));
    ASSERT_EQ(3, b);
    ASSERT_EQ(32, a);
    return true;
}

bool test_endian(void) {
    LOG_INFO(TEST, "%s() Ok", __FUNCTION__);
    uint8_t data8[4] = {0x87, 0x65, 0x43, 0x21};
    uint32_t data32 = 0x87654321;
    ASSERT_FALSE(array_is_equal((uint8_t*)data8, (uint8_t*)&data32, 4));
    return true;
}

bool test_general(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    int i = 10;
    while(i-- > 0) {
        LOG_INFO(TEST, "IterationDown %u", i);
    }

    i = 0;
    while(i++ < 10) {
        LOG_INFO(TEST, "IterationUp %u", i);
    }
    return true;
}

bool test_struct_copy(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);

    SomeType_t a;
    SomeType_t b;
    a.a = 1;
    a.b = 2;
    a.c = 3;
    ASSERT_EQ(1, a.a);
    ASSERT_EQ(2, a.b);
    ASSERT_EQ(3, a.c);

    b.a = 11;
    b.b = 22;
    b.c = 33;

    ASSERT_EQ(11, b.a);
    ASSERT_EQ(22, b.b);
    ASSERT_EQ(33, b.c);

    b = a;

    ASSERT_EQ(1, b.a);
    ASSERT_EQ(2, b.b);
    ASSERT_EQ(3, b.c);

    return true;
}

typedef struct {
    uint32_t x;
    uint32_t y;
} SmType_t;

SomeType_t xyz;

bool test_visibility(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    char xYz[4] = "xyz";
    bool res = true;
    ASSERT_EQ(4, sizeof(xYz));

    return res;
}

static char test_text[250] = "";
bool test_snprintf_d(void) {
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

bool test_snprintf_f(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    float val = 123.45;
    strcpy(test_text, "");
    sprintf(test_text, "val=%6.2f", val);
    LOG_INFO(TEST, "test_text[%s]", test_text);
    ASSERT_STREQ("val=123.45", test_text);

    val = 543.21;
    strcpy(test_text, "");
    snprintf(test_text, sizeof(test_text), "val=%6.2f", val);
    LOG_INFO(TEST, "test_text[%s]", test_text);
    ASSERT_STREQ("val=543.21", test_text);

    return res;
}

bool test_sprintf_minus(void) {
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

bool test_snprintf_small_double(void) {
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

bool test_sprintf_u64(void) {
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

//| 100 |     accenture |  aabzele@gmail.. | sTNEQ#ImB@KVnnO7Sgv4.. | nFEoWE5rYKxFU9y1WeXS.. | 32 | 22 | 68.
static char const test_text_exp[250] =
    "  0.00  1.00  2.00  3.00  4.00  5.00  6.00  7.00  8.00  9.00 10.00 11.00 12.00 13.00 14.00 15.00 16.00 17.00 "
    "18.00 19.00 20.00 21.00 22.00 23.00 24.00 25.00 26.00 27.00 28.00 29.00 30.00 31.00 32.00 33.00 34.00";
bool test_sprintf_long(void) {
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

bool test_bit_shift(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint32_t val = 0xFFFFFFFF;

    val = 0xFFFFFFFF;
    val = val >> 4;
    ASSERT_EQ(0x0FFFFFFF, val);
#if 0
    val = 0xFFFFFFFF;
    val = val>>32;
    ASSERT_EQ(0xFFFFFFFF, val);

    val = 0xFFFFFFFF;
    val = val<<32;
    ASSERT_EQ(0xFFFFFFFF, val); /**/

    val = 0;
    val = val>>32;
    ASSERT_EQ(0, val);

    val = 0;
    val=val<<32;
    ASSERT_EQ(0, val); /**/
#endif

    return res;
}

bool test_int_overflow(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    int8_t int8 = INT8_MAX;
    int8++;
    ASSERT_EQ(INT8_MIN, int8);

    uint8_t uint8 = UINT8_MAX;
    uint8++;
    ASSERT_EQ(0, uint8);

    return res;
}

char* c[] = {"abcdef", "123", "qwert", "asdf"};
char** cp[] = {c + 3, c + 2, c + 1, c};
char*** cpp = cp;

bool test_pointers(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    // printf("*cpp[-1] [%s]", *cpp[-1]); run time error
    cpp = cp;
    printf("*--*++cpp+2 [%s]", *--*++cpp + 2);

    cpp = cp;
    // ASSERT_STREQ("3", *--*++cpp + 2);

    cpp = cp;
    // ASSERT_STREQ("3", *(--*++cpp + 2));

    printf("*cpp[0] [%s]", *cpp[0]);
    // ASSERT_STREQ("asdf", *cpp[0]);

    printf("**cpp [%s]", **cpp);
    // ASSERT_STREQ("asdf", **cpp);

    cpp = cp;
    printf("**cpp++ [%s] ", **cpp++);

    cpp = cp;
    // ASSERT_STREQ("asdf", **cpp++);

    printf("**++cpp [%s]", **++cpp);
    //  printf("%s ", *--*++cpp+2);
    //  printf("%s ", *cpp[-2]);
    //  printf("%s ", *cpp[-2]+3);
    //  printf("%s ", cpp[-1][-1]+1);
    return true;
}

#ifdef HAS_EXTRA_TEST
static const char name[5] = "1234567";
bool test_print_name(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_EQ(5, sizeof(name));
    cli_printf("[%s]" CRLF, name);
    return res;
}
#endif

typedef struct {
    int a : 1;
    int b;
} ab_t;

bool test_bit_fields(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ab_t ab;
    ab.a = 1;
    cli_printf("%u" CRLF, ab.a);
    ASSERT_EQ(-1, ab.a);
    return res;
}

bool test_snprintf(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    char lText[40] = {0};
    uint32_t value = 0x55555555;
    snprintf(lText, sizeof(lText), "0x%08x", value);
    ASSERT_STREQ("0x55555555", lText)

    value = 0xaaaaaaaa;
    snprintf(lText, sizeof(lText), "0x%08x", value);
    ASSERT_STREQ("0xaaaaaaaa", lText)

    return res;
}

bool test_memset(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint8_t array[10] = {0};
    memset(array, 0x55, 6);
    ASSERT_EQ(0x55, array[0]);
    ASSERT_EQ(0x55, array[1]);
    ASSERT_EQ(0x55, array[2]);
    ASSERT_EQ(0x55, array[3]);
    ASSERT_EQ(0x55, array[4]);
    ASSERT_EQ(0x55, array[5]);
    ASSERT_EQ(0x00, array[6]);
    return res;
}

static const uint8_t array_src[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

bool test_memcpy(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint8_t array[10] = {0};
    memcpy(array, array_src, 6);

    ASSERT_EQ(1, array[0]);
    ASSERT_EQ(2, array[1]);
    ASSERT_EQ(3, array[2]);
    ASSERT_EQ(4, array[3]);
    ASSERT_EQ(5, array[4]);
    ASSERT_EQ(6, array[5]);
    ASSERT_EQ(0, array[6]);
    return res;
}

typedef enum {
    COIL,
    DISCRETE,
    INPUT,
    HOLDING,
} type;

typedef struct {
    uint16_t address;
    uint16_t* data;
    type clas;
    uint8_t size;
} modbus_reg;

typedef struct {
    uint16_t address;
    uint16_t* data;
    type clas;
    uint8_t size;
} __attribute__((packed)) modbus_reg_small;

typedef struct {
    uint16_t* data;
    uint16_t address;
    type clas;
    uint8_t size;
} __attribute__((packed)) modbus_reg_smallest;

bool test_struct_size(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint8_t array[10] = {0};
    memcpy(array, array_src, 6);
    ASSERT_EQ(1, sizeof(uint8_t));
    ASSERT_EQ(2, sizeof(uint16_t));
    ASSERT_EQ(4, sizeof(uint16_t*));
    ASSERT_EQ(1, sizeof(type));
    ASSERT_EQ(12, sizeof(modbus_reg));
    ASSERT_EQ(10, sizeof(modbus_reg_small));
    ASSERT_EQ(8, sizeof(modbus_reg_smallest));

    return res;
}
