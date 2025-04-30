#ifndef TEST_RDS_PROTO_H
#define TEST_RDS_PROTO_H

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

#ifndef HAS_RDS
#error "It is needed HAS_RDS option for that component"
#endif

bool test_rds_types(void);
bool test_rds_prog_type_name0(void);
bool test_rds_prog_type_name1(void);

#define TEST_SUIT_RDS             \
    {"rdsTypes", test_rds_types}, \
    {"rdsProgTypeName0", test_rds_prog_type_name0}, \
    {"rdsProgTypeName1", test_rds_prog_type_name1},

#ifdef __cplusplus
}
#endif

#endif /* TEST_RDS_PROTO_H */
