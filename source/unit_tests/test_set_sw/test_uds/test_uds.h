#ifndef TEST_UDS_H
#define TEST_UDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif


bool test_uds_send(void);
bool test_uds_write_data_by_identifier(void);
bool test_uds_board_voltage_get(void);
bool test_uds_input_states_get(void);
bool test_uds_output_states_get(void);
bool test_uds_read_data_by_id(void);
bool test_uds_sos1_button_hold_time_get(void);
bool test_uds_sos2_button_hold_time_get(void);
bool test_uds_system_state_get(void);
bool test_uds_service_button_hold_time_get(void);
bool test_uds_time_stamp_get(void);
bool test_uds_types(void);

#define TEST_SUIT_UDS                                                                 \
    {"uds_types", test_uds_types },                                                   \
    {"uds_input_states_get", test_uds_input_states_get },                             \
    {"uds_output_states_get", test_uds_output_states_get },                           \
    {"uds_board_voltage_get", test_uds_board_voltage_get },                           \
    {"uds_system_state_get", test_uds_system_state_get },                             \
    {"uds_time_stamp_get", test_uds_time_stamp_get },                                 \
    {"uds_sos1_button_hold_time_get", test_uds_sos1_button_hold_time_get },           \
    {"uds_write_data_by_identifier", test_uds_write_data_by_identifier },           \
    {"uds_sos2_button_hold_time_get", test_uds_sos2_button_hold_time_get },           \
    {"uds_service_button_hold_time_get", test_uds_service_button_hold_time_get },     \
    {"uds_read_data_by_id", test_uds_read_data_by_id },                               \
    {"uds_time_stamp_get", test_uds_time_stamp_get },

#ifdef __cplusplus
}
#endif

#endif /* TEST_UDS_H */
