#ifndef DDS_TEST_H
#define DDS_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_HW_TESTS option for that component"
#endif

#ifndef HAS_DDS
#error "It is needed to add HAS_DDS option"
#endif

bool test_dds_chirp_wav(void);
bool test_dds_chirp(void);
bool test_dds_chirp_30ms_wav(void);

#define TEST_SUIT_DDS  \
	{"dds_chirp", test_dds_chirp}, \
	{"dds_chirp_30ms_wav", test_dds_chirp_30ms_wav}, \
	{"dds_chirp_wav", test_dds_chirp_wav},

#ifdef __cplusplus
}
#endif

#endif /* DDS_TEST_H */
