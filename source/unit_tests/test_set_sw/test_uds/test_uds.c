#include "test_uds.h"

#include <stdio.h>

#include "board_custom_const.h"
#include "byte_utils.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "num_to_str.h"
#include "super_cycle.h"
#include "uds.h"
#include "unit_test_check.h"

bool test_uds_types(void) {
    bool res = true;
    LOG_DEBUG(UDS, "%s():", __FUNCTION__);
    set_log_level(UDS, LOG_LEVEL_DEBUG);

    EXPECT_EQ(3, sizeof(UdsReadDataByIdFrame_t));
    EXPECT_EQ(2, sizeof(UdsDid_t));

    set_log_level(UDS, LOG_LEVEL_INFO);
    return res;
}

bool test_uds_send(void) {

    LOG_DEBUG(UDS, "%s():", __FUNCTION__);
    set_log_level(UDS, LOG_LEVEL_DEBUG);

    set_log_level(UDS, LOG_LEVEL_INFO);
    return true;
}

bool test_uds_read_data_by_id(void) {
    LOG_DEBUG(UDS, "%s():", __FUNCTION__);

    set_log_level(UDS, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(uds_read_data_by_identifier(1, 0x0001));

    set_log_level(UDS, LOG_LEVEL_INFO);
    return true;
}

bool test_uds_input_states_get(void) {
    LOG_DEBUG(UDS, "%s():", __FUNCTION__);
    set_log_level(UDS, LOG_LEVEL_DEBUG);
    uint8_t RxFrame[] = {0x22, 0x00, 0x01};
    ASSERT_TRUE(uds_proc_rx_data(1, RxFrame, sizeof(RxFrame)));

    set_log_level(UDS, LOG_LEVEL_INFO);
    return true;
}

bool test_uds_output_states_get(void) {
    LOG_DEBUG(UDS, "%s():", __FUNCTION__);
    set_log_level(UDS, LOG_LEVEL_DEBUG);
    uint8_t RxFrame[] = {0x22, 0x00, 0x02};
    ASSERT_TRUE(uds_proc_rx_data(1, RxFrame, sizeof(RxFrame)));

    set_log_level(UDS, LOG_LEVEL_INFO);
    return true;
}

bool test_uds_board_voltage_get(void) {
    LOG_DEBUG(UDS, "%s():", __FUNCTION__);
    set_log_level(UDS, LOG_LEVEL_DEBUG);
    uint8_t RxFrame[] = {0x22, 0x00, 0x03};
    ASSERT_TRUE(uds_proc_rx_data(1, RxFrame, sizeof(RxFrame)));

    set_log_level(UDS, LOG_LEVEL_INFO);
    return true;
}

bool test_uds_system_state_get(void) {
    LOG_DEBUG(UDS, "%s():", __FUNCTION__);
    set_log_level(UDS, LOG_LEVEL_DEBUG);
    uint8_t RxFrame[] = {0x22, 0x00, 0x06};
    ASSERT_TRUE(uds_proc_rx_data(1, RxFrame, sizeof(RxFrame)));

    set_log_level(UDS, LOG_LEVEL_INFO);
    return true;
}

bool test_uds_time_stamp_get(void) {
    LOG_DEBUG(UDS, "%s():", __FUNCTION__);
    set_log_level(UDS, LOG_LEVEL_DEBUG);
    uint8_t RxFrame[] = {0x22, 0x00, 0x0B};
    ASSERT_TRUE(uds_proc_rx_data(1, RxFrame, sizeof(RxFrame)));

    set_log_level(UDS, LOG_LEVEL_INFO);
    return true;
}

bool test_uds_sos1_button_hold_time_get(void) {
    LOG_DEBUG(UDS, "%s():", __FUNCTION__);
    set_log_level(UDS, LOG_LEVEL_DEBUG);
    uint8_t RxFrame[] = {0x22, 0x01, 0x01};
    ASSERT_TRUE(uds_proc_rx_data(1, RxFrame, sizeof(RxFrame)));

    set_log_level(UDS, LOG_LEVEL_INFO);
    return true;
}

bool test_uds_sos2_button_hold_time_get(void) {
    LOG_DEBUG(UDS, "%s():", __FUNCTION__);
    set_log_level(UDS, LOG_LEVEL_DEBUG);
    uint8_t RxFrame[] = {0x22, 0x01, 0x02};
    ASSERT_TRUE(uds_proc_rx_data(1, RxFrame, sizeof(RxFrame)));

    set_log_level(UDS, LOG_LEVEL_INFO);
    return true;
}

bool test_uds_service_button_hold_time_get(void) {
    LOG_DEBUG(UDS, "%s():", __FUNCTION__);
    set_log_level(UDS, LOG_LEVEL_DEBUG);
    uint8_t RxFrame[] = {0x22, 0x01, 0x03};
    ASSERT_TRUE(uds_proc_rx_data(1, RxFrame, sizeof(RxFrame)));

    set_log_level(UDS, LOG_LEVEL_INFO);
    return true;
}

bool test_uds_write_data_by_identifier(void) {
    LOG_DEBUG(UDS, "%s():", __FUNCTION__);
    set_log_level(UDS, LOG_LEVEL_DEBUG);
    /*Write in DID:0102 value:1000*/
    uint8_t RxFrame[] = {0x2E, 0x01, 0x02, 0x03, 0xe8};
    ASSERT_TRUE(uds_proc_rx_data(1, RxFrame, sizeof(RxFrame)));

    set_log_level(UDS, LOG_LEVEL_INFO);
    return true;
}
