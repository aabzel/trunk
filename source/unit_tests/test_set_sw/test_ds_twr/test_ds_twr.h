#ifndef TEST_DS_TWR_H
#define TEST_DS_TWR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_DS_TWR
#error "It is needed HAS_DS_TWR option for that component"
#endif

bool test_ds_twr_types(void);
bool test_ds_twr_const(void);
bool test_ds_twr_initiator(void);
bool test_ds_twr_responder_poll(void);
bool test_ds_twr_responder(void);

#define TEST_SUIT_DS_TWR                                    \
    {"ds_twr_const", test_ds_twr_const},            \
    {"ds_twr_types", test_ds_twr_types},            \
    {"ds_twr_initiator", test_ds_twr_initiator},            \
    {"ds_twr_responder_poll", test_ds_twr_responder_poll},            \
    {"ds_twr_responder", test_ds_twr_responder},

#ifdef __cplusplus
}
#endif

#endif /* TEST_DS_TWR_H */
