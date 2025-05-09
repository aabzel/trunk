#include "test_hex_bin.h"

#include <string.h>

#include "hex_bin.h"
#include "log.h"
#include "unit_test_check.h"
#include "utils_math.h"

static bool hex_proc_one(const char* const line, uint8_t rec_len, uint16_t load_offset, uint8_t rec_type,
                         uint8_t crc8) {
    bool res = true;
    HexBinHandle_t Item = {0};
    strcpy(Item.hex_line, line);
    ASSERT_TRUE(hex_proc_line(&Item, false));
    ASSERT_EQ(Item.frame.rec_len, rec_len);
    ASSERT_EQ(Item.frame.rec_type, rec_type);
    ASSERT_EQ(Item.frame.load_offset, load_offset);
    ASSERT_EQ(Item.frame.crc8.read, crc8);

    return res;
}

bool test_hex_bin_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    log_level_t orig_ll = log_level_get_set(HEX_BIN, LOG_LEVEL_DEBUG);
    ASSERT_EQ(2, sizeof(Crc8_t));
    ASSERT_EQ(1, sizeof(HexRecType_t));

    double percent = calc_percent_s(10658, 23879);
    ASSERT_EQ_DOUBLE(44.633359855940363, percent);
    log_level_get_set(HEX_BIN, orig_ll);

    return true;
}

bool test_hex_bin_is_hex_file(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    log_level_t orig_ll = log_level_get_set(HEX_BIN, LOG_LEVEL_DEBUG);

    ASSERT_TRUE(is_hex_file("start_mik32_v1_generic_gcc_m.hex"));

    log_level_get_set(HEX_BIN, orig_ll);

    return true;
}


bool test_hex_bin_proc_4(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    log_level_t orig_ll = log_level_get_set(HEX_BIN, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(hex_proc_one(":020000040801F1", 2, 0x0000, 4, 0xF1));

    HexBinHandle_t Item = {0};
    strcpy(Item.hex_line, ":020000040801F1");
    ASSERT_TRUE(hex_proc_line(&Item, false));
    ASSERT_EQ(Item.frame.load_offset, 0);
    ASSERT_EQ(Item.address.u16[1], 0x0801);
    ASSERT_EQ(Item.address.u32, 0x08010000);

    log_level_get_set(HEX_BIN, orig_ll);

    return true;
}

bool test_hex_bin_proc(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    log_level_t orig_ll = log_level_get_set(HEX_BIN, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(hex_proc_one(":020000040801F1", 2, 0x0000, 4, 0xF1));
    ASSERT_TRUE(hex_proc_one(":103800005CC000008FC0000073C0000071C00000E9", 16, 0x3800, 0, 0xE9));

    log_level_get_set(HEX_BIN, orig_ll);

    return true;
}
