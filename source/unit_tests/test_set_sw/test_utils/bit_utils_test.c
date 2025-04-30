#include "bit_utils_test.h"

#include "bit_utils.h"
#include "data_types.h"
#include "log.h"
#include "unit_test_check.h"

bool test_nimble_set(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    Type8Union_t Un8;
    Un8.u8 = 0;
    Un8.nibble_h = 0x5;
    Un8.nibble_l = 0x1;
    EXPECT_EQ(0x51, Un8.u8);

    Un8.nibble_h = 0x5;
    Un8.nibble_l = 0x8;
    EXPECT_EQ(0x58, Un8.u8);
    return res;
}

bool test_bit_adjust_mask(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE(is_valid_bit_mask_u8("1xx0_1x10"));
    ASSERT_TRUE(is_valid_bit_mask_u8("xxxx_xxxx"));
    ASSERT_TRUE(is_valid_bit_mask_u8("1111_1111"));
    ASSERT_TRUE(is_valid_bit_mask_u8("XXXX_1111"));
    EXPECT_FALSE(is_valid_bit_mask_u8("XXXX_1311"));

    EXPECT_EQ(0xAA, adjust_bits_u8(0xBB, "1xx0_1x10"));
    EXPECT_EQ(0x01, adjust_bits_u8(0x01, "xxxx_xxxx"));
    EXPECT_EQ(0xFF, adjust_bits_u8(0x00, "1111_1111"));
    EXPECT_EQ(0xAF, adjust_bits_u8(0xAA, "XXXX_1111"));
    return res;
}

static bool test_generate_custom_mask(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ(0x0000000F, generate_32bit_custom_mask(3, 0));
    EXPECT_EQ(0x000000F0, generate_32bit_custom_mask(7, 4));
    EXPECT_EQ(0x00FFFF00, generate_32bit_custom_mask(8 + 16 - 1, 8));
    return res;
}

static bool test_insert_subval_utils32(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint32_t val = 0x00000000;
    bool res = true;
    /*TODO: Add more tests*/
    val = insert_subval_in_32bit(val, 0xD0, 31, 21);
    EXPECT_EQ(0x00D0, extract_subval_from_32bit(val, 31, 21));

    val = insert_subval_in_32bit(val, 0xC6, 15, 5);
    EXPECT_EQ(0x00C6, extract_subval_from_32bit(val, 15, 5));
    EXPECT_EQ(0x00D0, extract_subval_from_32bit(val, 31, 21));

    return res;
}

static bool test_extract_subval_utils8(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ(0x07, extract_subval_from_8bit(0x0E, 3, 1));
    EXPECT_EQ(0x06, extract_subval_from_8bit(0xEF, 6, 4));
    return res;
}

static bool test_extract_subval_utils32(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ(0x0034, extract_subval_from_32bit(0x5344, 11, 4));
    EXPECT_EQ(0x000f, extract_subval_from_32bit(0xF000, 15, 12));
    EXPECT_EQ(0x000f, extract_subval_from_32bit(0x0F00, 11, 8));
    EXPECT_EQ(0x000f, extract_subval_from_32bit(0x000F, 3, 0));
    return res;
}

static bool test_extract_subval_utils64(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ(0x0034, extract_subval_from_64bit(0x5344, 11, 4));
    EXPECT_EQ(0x000f, extract_subval_from_64bit(0xF000, 15, 12));
    EXPECT_EQ(0x000f, extract_subval_from_64bit(0x0F00, 11, 8));
    EXPECT_EQ(0x000f, extract_subval_from_64bit(0x000F, 3, 0));
    return res;
}

static bool test_bit_ctl(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint32_t arr[64] = {0};
    bool res = true;
    EXPECT_FALSE(bit32_control_proc(&arr[0], 's', 44));

    arr[0] = 0;
    ASSERT_TRUE(bit32_control_proc(&arr[0], 's', 0));
    EXPECT_EQ(1, arr[0]);

    arr[0] = 0;
    ASSERT_TRUE(bit32_control_proc(&arr[0], 's', 1));
    EXPECT_EQ(2, arr[0]);

    arr[0] = 0;
    ASSERT_TRUE(bit32_control_proc((uint32_t*)&arr[0], 's', 2));
    EXPECT_EQ(4, arr[0]);

    arr[0] = 0;
    ASSERT_TRUE(bit32_control_proc((uint32_t*)&arr[0], 's', 4));
    EXPECT_EQ(16, arr[0]);
    return res;
}

/*tsr bit_utils+*/
bool test_bit_utils(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE(test_extract_subval_utils8());
    ASSERT_TRUE(test_bit_ctl());
    ASSERT_TRUE(test_extract_subval_utils32());
    ASSERT_TRUE(test_extract_subval_utils64());
    ASSERT_TRUE(test_insert_subval_utils32());
    return res;
}

bool test_bit_type_size(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ(1, sizeof(BitField8_t));
    EXPECT_EQ(2, sizeof(BitField16_t));
    EXPECT_EQ(3, sizeof(BitField24_t));
    EXPECT_EQ(4, sizeof(BitField32_t));
    EXPECT_EQ(8, sizeof(BitField64_t));
    return res;
}

bool test_bit_macro(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE(IS_BIT_RESET(2, 0));
    EXPECT_FALSE(IS_BIT_RESET(2, 1));
    EXPECT_EQ(1, GET_BIT_NUM(2, 1));
    EXPECT_EQ(0, GET_BIT_NUM(2, 0));
    return res;
}

bool test_bit_mask(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ(MASK_1BIT, generate_8bit_mask(1));
    EXPECT_EQ(MASK_3BIT, generate_8bit_mask(3));
    EXPECT_EQ(MASK_8BIT, generate_8bit_mask(8));

    EXPECT_EQ(MASK_1BIT, generate_32bit_mask(1));
    EXPECT_EQ(MASK_2BIT, generate_32bit_mask(2));
    EXPECT_EQ(MASK_4BIT, generate_32bit_mask(4));
    EXPECT_EQ(MASK_25BIT, generate_32bit_mask(25));

    EXPECT_EQ(MASK_1BIT, generate_64bit_mask(1));
    EXPECT_EQ(MASK_2BIT, generate_64bit_mask(2));
    EXPECT_EQ(MASK_4BIT, generate_64bit_mask(4));
    EXPECT_EQ(MASK_25BIT, generate_64bit_mask(25));
    EXPECT_EQ(MASK_30BIT, generate_64bit_mask(30));

    ASSERT_TRUE(test_generate_custom_mask());
    return res;
}

bool test_bit8_swap(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ(0x80, swap_bits_u8(0x01));
    EXPECT_EQ(0x55, swap_bits_u8(0xaa));
    EXPECT_EQ(0xF0, swap_bits_u8(0x0F));
    EXPECT_EQ(0x0F, swap_bits_u8(0xF0));
    return res;
}

bool test_bit16_swap(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ(0x8000, swap_bits_u16(0x0001));
    EXPECT_EQ(0x5500, swap_bits_u16(0x00aa));
    EXPECT_EQ(0xF000, swap_bits_u16(0x000F));
    EXPECT_EQ(0x2C48, swap_bits_u16(0x1234));
    return res;
}

bool test_bit32_swap(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ(0x80000000, swap_bits_u32(0x00000001));
    EXPECT_EQ(0x55000000, swap_bits_u32(0x000000aa));
    EXPECT_EQ(0xF0000000, swap_bits_u32(0x0000000F));
    return res;
}

bool test_bit32_fields(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    ASSERT_EQ(4, sizeof(BitField32_t));
    BitField32_t Field32;
    Field32.dword = 0;
    Field32.bit13 = 1;
    EXPECT_EQ(0x2000, Field32.dword);
    return res;
}

bool test_bit64_swap(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ_U64(0x8000000000000000, swap_bits_u64_v2(0x0000000000000001));
    EXPECT_EQ_U64(0x5500000000000000, swap_bits_u64_v2(0x00000000000000aa));
    EXPECT_EQ_U64(0xF000000000000000, swap_bits_u64_v2(0x000000000000000F));
    EXPECT_EQ_U64(0x8000000000000000, swap_bits_u64(0x0000000000000001));
    EXPECT_EQ_U64(0x5500000000000000, swap_bits_u64(0x00000000000000aa));
    EXPECT_EQ_U64(0xF000000000000000, swap_bits_u64(0x000000000000000F));
    return res;
}

bool test_parse_n_bit_signed(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ(0, parse_n_bit_signed(0, 4));
    EXPECT_EQ(-1, parse_n_bit_signed(0xF, 4));
    EXPECT_EQ(-3, parse_n_bit_signed(0xD, 4));
    EXPECT_EQ(-8, parse_n_bit_signed(0x8, 4));
    EXPECT_EQ(1, parse_n_bit_signed(1, 4));
    EXPECT_EQ(-4, parse_n_bit_signed(0xc, 4));
    return res;
}
