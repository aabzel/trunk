#ifndef TEST_TBFP_PROTO_H
#define TEST_TBFP_PROTO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

bool tbfp_test_genegare_storage_read(uint8_t num, uint8_t* const frame) ;
bool tbfp_test_genegare_storage_write( const uint8_t num,   uint8_t* const frame) ;

bool test_tbfp_proto_flow_ctrl(void);
bool test_tbfp_storage_read(void);
bool test_tbfp_storage_write(void);
bool test_tbfp_proto_flow_ctrl2(void);
bool test_tbfp_proto_29(void);
bool test_tbfp_proto_auto(void);
bool test_tbfp_proto_0(void);
bool test_tbfp_proto_1(void);
bool test_tbfp_proto_2(void);
bool test_tbfp_proto_overlen(void);
bool test_tbfp_types(void);
bool test_tbfp_interfaces(void);

#define TEST_SUIT_TBFP_ALL                                    \
    {"tbfp_types", test_tbfp_types},                          \
	{"tbfp_proto_1", test_tbfp_proto_1},                      \
	{"tbfp_interfaces", test_tbfp_interfaces},                \
    {"tbfp_storage_read", test_tbfp_storage_read},            \
    {"tbfp_storage_write", test_tbfp_storage_write},          \
    {"tbfp_proto_0", test_tbfp_proto_0},                      \
    {"tbfp_proto_2", test_tbfp_proto_2},                      \
    {"tbfp_proto_29", test_tbfp_proto_29},                    \
	{"tbfp_proto_flow_ctrl2", test_tbfp_proto_flow_ctrl2},    \
    {"tbfp_proto_auto", test_tbfp_proto_auto},                \
	{"tbfp_proto_flow_ctrl", test_tbfp_proto_flow_ctrl},

#define TEST_SUIT_TBFP TEST_SUIT_TBFP_ALL

#ifdef __cplusplus
}
#endif

#endif /* TEST_TBFP_PROTO_H */
