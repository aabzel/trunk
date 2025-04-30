#ifndef TEST_HARDWARE_DEPEN_CHECK_H
#define TEST_HARDWARE_DEPEN_CHECK_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_STREAM
#error "It is needed HAS_STREAM option for that component"
#endif

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_HW_TESTS
#error "It is needed HAS_HW_TESTS option for that component"
#endif


#ifdef __cplusplus
}
#endif

#endif /*TEST_HARDWARE_DEPEN_CHECK_H*/
