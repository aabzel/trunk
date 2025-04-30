#include "test_flash_fs.h"

#include "data_utils.h"
#include "flash_fs.h"
#include "log_utils.h"
#include "none_blocking_pause.h"
#include "std_includes.h"
#ifndef ESP32
//#include "memory_layout.h"
#endif
//#include "param_drv.h"
#include "unit_test_check.h"

#ifdef HAS_RNG
#include "rng_drv.h"
#endif /*HAS_RNG*/

/*
tsr flash_fs+
*/

bool test_flash_fs_set_get_const(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
#ifdef HAS_TEST_SUIT_FLASH_FS_EXT
    ASSERT_EQ(7, sizeof(mmItem_t));
#endif
    uint16_t data_id = PAR_ID_TEST_START;
    uint16_t write_value = 0xAA55;
    uint16_t read_value = 0;
    uint16_t read_value_len = 0;
    ASSERT_TRUE(flash_fs_set(data_id, (unsigned char*)&write_value, sizeof(write_value)));
    ASSERT_TRUE(flash_fs_get(data_id, (unsigned char*)&read_value, sizeof(read_value), &read_value_len));
    ASSERT_EQ(2, read_value_len);
    ASSERT_EQ(write_value, read_value);
    wait_in_loop_ms(100);
    return true;
}

bool test_flash_fs_inval(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
#ifdef HAS_TEST_SUIT_FLASH_FS_EXT
    ASSERT_EQ(7, sizeof(mmItem_t));
#endif
    uint16_t data_id = PAR_ID_TEST_START + 1;
    uint16_t write_value = 0x55AA;
    uint16_t read_value = 0;
    uint16_t read_value_len = 0;
    ASSERT_TRUE(flash_fs_set(data_id, (unsigned char*)&write_value, sizeof(write_value)));
    ASSERT_TRUE(flash_fs_get(data_id, (unsigned char*)&read_value, sizeof(read_value), &read_value_len));
    ASSERT_EQ(2, read_value_len);
    ASSERT_EQ(write_value, read_value);

    ASSERT_TRUE(flash_fs_invalidate(data_id));
    wait_in_loop_ms(200);

    ASSERT_FALSE(flash_fs_get(data_id, (unsigned char*)&read_value, sizeof(read_value), &read_value_len));
    return true;
}

bool test_flash_fs_set_get_set(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint16_t data_id = PAR_ID_TEST_START + 2;
    uint16_t write_value = 34;
    uint16_t read_value = 0;
    uint16_t read_value_len = 0;

    wait_in_loop_ms(100);

    ASSERT_TRUE(flash_fs_set(data_id, (unsigned char*)&write_value, sizeof(write_value)));

    ASSERT_TRUE(flash_fs_get(data_id, (unsigned char*)&read_value, sizeof(read_value), &read_value_len));
    ASSERT_EQ(2, read_value_len);
    ASSERT_EQ(write_value, read_value);

    write_value = 35;
    read_value = 0;
    read_value_len = 0;
    ASSERT_TRUE(flash_fs_set(data_id, (unsigned char*)&write_value, sizeof(write_value)));

    ASSERT_TRUE(flash_fs_get(data_id, (unsigned char*)&read_value, sizeof(read_value), &read_value_len));
    ASSERT_EQ(2, read_value_len);
    ASSERT_EQ(write_value, read_value);
    wait_in_loop_ms(100);
    return true;
}

#ifdef HAS_TEST_SUIT_FLASH_FS_EXT
static uint32_t calc_toggle_exp_page(uint32_t page) {
    uint32_t exp_page = 0;
    if(MEMORY_MANAGER1_OFFSET == page) {
        exp_page = MEMORY_MANAGER2_OFFSET;
    } else if(MEMORY_MANAGER2_OFFSET == page) {
        exp_page = MEMORY_MANAGER1_OFFSET;
    }
    return exp_page;
}
#endif

#ifdef HAS_TEST_SUIT_FLASH_FS_EXT
bool test_flash_fs_toggle(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint32_t read_flash_fs_page_start = 0;
    uint32_t read_flash_fs_page_len = 1;
    uint32_t origin_file_cnt = 0;
    uint32_t new_file_cnt = 0;
    uint32_t exp_flash_fs_page_start = 0;
    uint32_t spare_cnt = 0;

    ASSERT_TRUE(flash_fs_get_active_page(&read_flash_fs_page_start, &read_flash_fs_page_len));
    ASSERT_GR(MEMORY_MANAGER1_LENGTH / 2, read_flash_fs_page_len);
    origin_file_cnt = flash_fs_cnt_files(read_flash_fs_page_start, read_flash_fs_page_len, &spare_cnt);

    exp_flash_fs_page_start = calc_toggle_exp_page(read_flash_fs_page_start);
    ASSERT_TRUE(flash_fs_turn_page());

    ASSERT_TRUE(flash_fs_get_active_page(&read_flash_fs_page_start, &read_flash_fs_page_len));
    ASSERT_EQ(exp_flash_fs_page_start, read_flash_fs_page_start);
    ASSERT_GR(MEMORY_MANAGER1_LENGTH / 2, read_flash_fs_page_len);

    new_file_cnt = flash_fs_cnt_files(read_flash_fs_page_start, read_flash_fs_page_len, &spare_cnt);
    ASSERT_EQ(new_file_cnt, origin_file_cnt);
    wait_in_loop_ms(100);
    return true;
}
#endif

bool test_flash_fs_types(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_EQ(FLASH_FS_ACTIV_PAGE_DWORD, active_page_token);
    ASSERT_EQ(7, sizeof(FlashFsHeader_t));
    ASSERT_EQ(4, sizeof(active_page_token));
    return true;
}
