#ifndef TEST_ISO_TP_H
#define TEST_ISO_TP_H

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

bool test_iso_tp_types(void);
bool test_iso_tp_diag(void);
bool test_iso_tp_send_single_frame(void);
bool test_iso_tp_send(void);
bool test_iso_tp_send_3(void);
bool test_iso_tp_send_jumbo(void);
bool test_iso_tp_send_4095(void);

#define TEST_SUIT_ISO_TP                                           \
    {"iso_tp_types", test_iso_tp_types },                            \
    {"iso_tp_diag", test_iso_tp_diag },                            \
    {"iso_tp_send_single_frame", test_iso_tp_send_single_frame},      \
    {"iso_tp_send", test_iso_tp_send},                                        \
    {"iso_tp_send_3", test_iso_tp_send_3},                                        \
    {"iso_tp_send_jumbo", test_iso_tp_send_jumbo },\
    {"iso_tp_send_4095", test_iso_tp_send_4095 },

#ifdef __cplusplus
}
#endif

#endif /* TEST_ISO_TP_H */
