#include "test_sw_nvram.h"

#include <stdlib.h>

#include "log.h"
#include "sw_nvram.h"
#include "unit_test_check.h"
#include "sw_nvram_diag.h"

bool test_sw_nvram_const(void) {
    LOG_INFO(NVRAM, "%s()", __FUNCTION__);
    set_log_level(NVRAM, LOG_LEVEL_DEBUG);

    ASSERT_EQ(0xFEFEFEFE, NVRAM_PAGE_CODE_ACTIVE);
    ASSERT_EQ(0xFCFCFCFC, NVRAM_PAGE_CODE_PASSIVE);

    set_log_level(NVRAM, LOG_LEVEL_INFO);
    return true;
}


bool test_sw_nvram_types(void) {
    LOG_INFO(NVRAM, "%s()", __FUNCTION__);
    set_log_level(NVRAM, LOG_LEVEL_DEBUG);

    ASSERT_EQ( 1, sizeof(NvRamPage_t));
    ASSERT_EQ( 1, sizeof(NvRamNodeState_t));
    ASSERT_EQ( 8,  sizeof(NvRamAddr_t));
    ASSERT_EQ( 36, sizeof(NvRamHeader_t));

    set_log_level(NVRAM, LOG_LEVEL_INFO);
    return true;
}

#define DOUBLE_WRITE_ADDR 951
bool test_sw_nvram_double_write(void) {
    LOG_INFO(NVRAM, "%s()", __FUNCTION__);
    set_log_level(NVRAM, LOG_LEVEL_DEBUG);
    uint8_t dataDouble[]="DoubleWrite!";
    uint32_t wr_size=strlen( (char*)dataDouble);
    ASSERT_EQ(12, wr_size);

    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;

    sw_nvram_delete(1,DOUBLE_WRITE_ADDR);

    cnt = nvram_entry_cnt(1);

    ASSERT_TRUE( sw_nvram_write(1,DOUBLE_WRITE_ADDR, dataDouble, wr_size));
    cnt1 = nvram_entry_cnt(1);

    ASSERT_EQ( cnt+1, cnt1);
    ASSERT_TRUE( sw_nvram_write(1,DOUBLE_WRITE_ADDR, dataDouble, wr_size));
    cnt2 = nvram_entry_cnt(1);

    ASSERT_EQ( cnt+1, cnt2);

    sw_nvram_delete(1,0xdd);

    set_log_level(NVRAM, LOG_LEVEL_INFO);
    return true;
}


#define TEST_ADDR_WDW 789
bool test_sw_nvram_write_delete_write(void){
    LOG_INFO(NVRAM, "%s()", __FUNCTION__);
    set_log_level(NVRAM, LOG_LEVEL_DEBUG);
    uint8_t data2[2]={3,23};
    uint8_t data3[3]={65,76,78};
    uint8_t rx_data[10];
    uint32_t rx_size = 0;

    ASSERT_TRUE( sw_nvram_write(1,TEST_ADDR_WDW,   data2, 2));
    ASSERT_TRUE( sw_nvram_read(1, TEST_ADDR_WDW,  rx_data, &rx_size));
    ASSERT_EQ( 2, rx_size);

    ASSERT_TRUE( sw_nvram_delete(1,TEST_ADDR_WDW   ));

    ASSERT_TRUE( sw_nvram_write(1,TEST_ADDR_WDW,   data3, 3));

    ASSERT_TRUE( sw_nvram_read(1,TEST_ADDR_WDW,  rx_data, &rx_size));
    ASSERT_EQ( 3, rx_size);

    set_log_level(NVRAM, LOG_LEVEL_INFO);
    return true;
}

bool test_sw_nvram_write(void){
    LOG_INFO(NVRAM, "%s()", __FUNCTION__);
    set_log_level(NVRAM, LOG_LEVEL_DEBUG);
    uint8_t data2[2]={1,2};
    uint8_t data3[3]={1,2,3};

    ASSERT_TRUE( sw_nvram_write(1,1,   data2, 2));

    ASSERT_TRUE( sw_nvram_write(1,1,   data3, 3));

    set_log_level(NVRAM, LOG_LEVEL_INFO);
    return true;
}


#define WRITE_READ_ADDR 89
bool test_sw_nvram_read(void){
    LOG_INFO(NVRAM, "%s()", __FUNCTION__);
    set_log_level(NVRAM, LOG_LEVEL_DEBUG);
    uint32_t rx_size = 0;

    uint8_t data5[5]={1,2,3,4,5};
    ASSERT_TRUE( sw_nvram_write(1,WRITE_READ_ADDR,   data5, 5));

    uint8_t rx_data[10];
    memset(rx_data, 0, sizeof(rx_data));
    rx_size = 0;

    ASSERT_TRUE( sw_nvram_read(1,WRITE_READ_ADDR,  rx_data, &rx_size));
    ASSERT_EQ( 5, rx_size);

    ASSERT_TRUE( array_is_equal( rx_data, data5, 5));

    set_log_level(NVRAM, LOG_LEVEL_INFO);
    return true;
}

bool test_sw_nvram_delete(void){
    LOG_INFO(NVRAM, "%s()", __FUNCTION__);
    set_log_level(NVRAM, LOG_LEVEL_DEBUG);
    uint8_t data4[4]={1,2,3,4};
    ASSERT_TRUE( sw_nvram_write(1,4,   data4, 4));

    uint8_t rx_data[10];
    uint32_t rx_size = 0;
    memset(rx_data,0,sizeof(rx_data));
    ASSERT_TRUE( sw_nvram_read(1, 4, rx_data, &rx_size));
    ASSERT_EQ( 4, rx_size);

    ASSERT_TRUE( sw_nvram_delete(1,4));

    ASSERT_TRUE( sw_nvram_read(1,4,  rx_data, &rx_size));
    ASSERT_EQ( 0, rx_size);

    set_log_level(NVRAM, LOG_LEVEL_INFO);
    return true;
}

#define STRESS_TEST_WR_CNT 10
bool test_sw_nvram_write_stress(void){
    LOG_INFO(NVRAM, "%s()", __FUNCTION__);
    set_log_level(NVRAM, LOG_LEVEL_INFO);
    uint8_t rand_data[120];
    uint8_t read_data[120];
    uint32_t addr = 0;
    uint32_t size = 0;
    uint32_t read_size = 0;
    uint32_t i = 0 ;
    for(i=0;i<STRESS_TEST_WR_CNT;i++) {
        addr = rand() % 10 + 1;
        size = rand() % 50 + 1;
        ASSERT_TRUE(  array_rand(rand_data, size));
        ASSERT_TRUE( sw_nvram_write(1,addr, rand_data, size));

        read_size = 0;
        ASSERT_TRUE( sw_nvram_read( 1, addr, read_data, &read_size));
        ASSERT_EQ(size, read_size);
    }
    sw_nvram_diag();
    sw_nvram_draw_tree_compose("rand_tree.gv");

    set_log_level(NVRAM, LOG_LEVEL_INFO);
    return true;
}

bool test_sw_nvram_write_same(void){
    LOG_INFO(NVRAM, "%s()", __FUNCTION__);
    set_log_level(NVRAM, LOG_LEVEL_INFO);
    uint8_t rand_data[120];
    uint8_t read_data[120];
    uint32_t addr = 0;
    uint32_t size = 0;
    uint32_t read_size = 0;
    uint32_t i = 0 ;
    addr = rand() % 10 + 1;
    for(i=0;i<10;i++) {
        size = rand() % 50 + 1;
        ASSERT_TRUE(  array_rand(rand_data, size));
        ASSERT_TRUE( sw_nvram_write(1,addr, rand_data, size));

        read_size = 0;
        ASSERT_TRUE( sw_nvram_read(1,  addr, read_data, &read_size));
        ASSERT_EQ(size, read_size);
    }
    sw_nvram_diag();
    sw_nvram_draw_tree_compose("rand_tree.gv");

    set_log_level(NVRAM, LOG_LEVEL_INFO);
    return true;
}

