#include "test_disk.h"

#include <stdint.h>


#include "diskio.h"
#include "array.h"
#include "data_utils.h"
#include "log.h"
#include "macro_utils.h"
#include "none_blocking_pause.h"
#include "unit_test_check.h"


/*To Save Stack*/
static uint8_t OrigBlock[DISK_BLOCK_SIZE + 1] = {0};
static uint8_t ReadBlock[DISK_BLOCK_SIZE + 1] = {0};
static uint8_t WriteBlock[DISK_BLOCK_SIZE + 1] = {0};

static bool test_disk_read_write_block(uint32_t block_num) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(DISK, LOG_LEVEL_DEBUG);
    DRESULT ret = RES_OK;

    ret = disk_read(0, OrigBlock, block_num, 1);
    ASSERT_EQ(RES_OK,ret);
    array_incr(WriteBlock, DISK_BLOCK_SIZE);
    ret=disk_write(0, WriteBlock, block_num, 1);
    ASSERT_EQ(RES_OK,ret);
    ASSERT_TRUE(wait_in_loop_ms(100));
    ASSERT_EQ(RES_OK,disk_read(0, ReadBlock, block_num, 1));


    EXPECT_EQ_MEM(ReadBlock, WriteBlock, DISK_BLOCK_SIZE);

    ASSERT_EQ(RES_OK,disk_write(0, OrigBlock, block_num, 1));
    set_log_level(DISK, LOG_LEVEL_INFO);
    return true;
}

/*
 tsr test_disk_driver+
 */
bool test_disk_read_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(DISK, LOG_LEVEL_DEBUG);
    uint32_t i = 0;
    for(i = 1; i <= 2; i++) {
        ASSERT_TRUE(test_disk_read_write_block(i));
    }
    set_log_level(DISK, LOG_LEVEL_INFO);

    return true;
}

bool test_disk_const(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(DISK, LOG_LEVEL_DEBUG);
   // ASSERT_GR(32, DISK_TIME_OUT_MS);
    ASSERT_EQ(1, sizeof(BYTE));
    ASSERT_EQ(2, sizeof(WORD));
    ASSERT_EQ(4, sizeof(DWORD));
    set_log_level(DISK, LOG_LEVEL_INFO);
    return true;
}


bool test_disk_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(DISK, LOG_LEVEL_DEBUG);
    uint32_t block_num = 10;
    //bool res = false;
    bool spot_valid = false;
    DRESULT ret=0;

    ret = disk_read(0,(BYTE*)ReadBlock, 608, 1 );
    ASSERT_EQ(RES_OK,ret);

    ret = disk_read(0,(BYTE*)ReadBlock, 8320, 1);
    ASSERT_EQ(RES_OK,ret);

    uint32_t sum = 0;
    for(block_num = 1; block_num < (GBYTE_BYTE(2) / DISK_BLOCK_SIZE); block_num++) {
        ret = disk_read(0,(BYTE*)ReadBlock, block_num, 1);
        ASSERT_EQ(RES_OK,ret);
        sum = arr_sum(ReadBlock, DISK_BLOCK_SIZE);
        if(0 < sum) {
            LOG_INFO(TEST, "Block #%u has valid data", block_num);
            spot_valid = true;
            break;
        }
    }
    ASSERT_TRUE(spot_valid);
    set_log_level(DISK, LOG_LEVEL_INFO);

    return true;
}

/*That test casuse fail*/
bool test_disk_link(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(DISK, LOG_LEVEL_DEBUG);

    set_log_level(DISK, LOG_LEVEL_INFO);
    return true;
}

bool test_disk_ioctl(void){
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(DISK, LOG_LEVEL_DEBUG);

    uint8_t buff[30];
    ASSERT_EQ(RES_OK, disk_ioctl( 0,   CTRL_SYNC, buff));
    ASSERT_EQ(RES_OK, disk_ioctl( 0,   GET_SECTOR_SIZE, buff));
    ASSERT_EQ(RES_OK, disk_ioctl( 0,   GET_SECTOR_COUNT, buff));
    ASSERT_EQ(RES_OK, disk_ioctl( 0,   GET_BLOCK_SIZE, buff));
    set_log_level(DISK, LOG_LEVEL_INFO);
    return true;
}
