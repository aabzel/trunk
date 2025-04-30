#include "test_nvs.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "data_utils.h"
#include "flash_custom_const.h"
#include "flash_mcal.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "nvs_drv.h"
#include "unit_test_check.h"

/*
tsr nvs_write
*/
#define BLOCK_SIZE 129U

static uint8_t DataRead[BLOCK_SIZE] = {0};
static uint8_t DataWrite[BLOCK_SIZE] = {0};

bool test_nvs_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint32_t spare_page_addr = flash_get_first_spare_page();
    LOG_INFO(TEST, "spare_page_addr 0x%x", spare_page_addr);
    ASSERT_NE(0xFFFFFFFF, spare_page_addr);
    LOG_INFO(NVS, "0x%08x", spare_page_addr);
    set_log_level(NVS, LOG_LEVEL_DEBUG);
    set_log_level(LG_FLASH, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(is_flash_spare(spare_page_addr, FlashConfig.page_size));

    memset(DataRead, 0x00, sizeof(DataRead));
    memset(DataWrite, 0x55, sizeof(DataWrite));

    ASSERT_TRUE(nvs_mcal_write(spare_page_addr, DataWrite, BLOCK_SIZE));
    ASSERT_TRUE(wait_in_loop_ms(1000));

    ASSERT_TRUE(nvs_mcal_read(spare_page_addr, DataRead, BLOCK_SIZE));
    memcpy(DataRead, (uint8_t*)spare_page_addr, sizeof(DataRead));

    ASSERT_EQ_MEM(DataRead, DataWrite, BLOCK_SIZE);

    ASSERT_TRUE(nvs_erase_page(spare_page_addr));
    ASSERT_TRUE(wait_in_loop_ms(1000));

    ASSERT_TRUE(is_flash_spare(spare_page_addr, FlashConfig.page_size));
    set_log_level(NVS, LOG_LEVEL_INFO);
    set_log_level(LG_FLASH, LOG_LEVEL_INFO);
    return true;
}
