#ifndef TEST_DECAWAVE_PROTO_H
#define TEST_DECAWAVE_PROTO_H

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

bool test_decawave_types(void);
bool test_decawave_proc_final(void);
bool test_decawave_nodes(void);
bool test_decawave_proc_poll(void);
bool test_decawave_proc_resp_poll(void);
bool test_decawave_proc_resp(void);

#define TEST_SUIT_DECAWAVE_PROTO               \
    {"decawave_types", test_decawave_types},   \
    {"decawave_nodes", test_decawave_nodes},    \
    {"decawave_proc_poll", test_decawave_proc_poll},   \
    {"decawave_proc_resp_poll", test_decawave_proc_resp_poll},   \
    {"decawave_proc_resp", test_decawave_proc_resp},   \
    {"decawave_proc_final", test_decawave_proc_final},


#ifdef __cplusplus
}
#endif

#endif /* TEST_DECAWAVE_PROTO_H */
