#ifndef TEST_TBFP_TBFP_PROTO_H
#define TEST_TBFP_TBFP_PROTO_H

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


bool test_tbfp_rtcm_path(void);
bool test_tbfp_tunnel(void);

#define TEST_SUIT_TBFP_RTCM_STACK      \
    {"tbfp_tunnel", test_tbfp_tunnel}, \
    {"tbfp_rtcm_path", test_tbfp_rtcm_path},
#ifdef __cplusplus
}
#endif

#endif /* TEST_TBFP_TBFP_PROTO_H */
