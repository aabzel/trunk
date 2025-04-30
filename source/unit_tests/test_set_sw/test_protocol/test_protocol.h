#ifndef TEST_PROTOCOL_H
#define TEST_PROTOCOL_H

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

bool test_protocol_flow_ctrl(void);
bool test_protocol_flow_ctrl2(void);
bool test_protocol_types(void);
bool test_protocol_diag(void);

#define TEST_SUIT_PROTOCOL                                        \
    {"protocol_types", test_protocol_types},                      \
    {"protocol_diag", test_protocol_diag},                      \
    {"protocol_flow_ctrl2", test_protocol_flow_ctrl2},        \
    {"protocol_flow_ctrl", test_protocol_flow_ctrl},        \

#ifdef __cplusplus
}
#endif

#endif /* TEST_PROTOCOL_H */
