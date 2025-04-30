#ifndef TEST_AUTO_VERSION_H
#define TEST_AUTO_VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_AUTO_VERSION
#error "+HAS_AUTO_VERSION"
#endif


#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

bool test_auto_version_types(void);
bool test_auto_version_parse_line(void);

#define TEST_SUIT_AUTO_VERSION                                 \
    {"auto_version_parse_line", test_auto_version_parse_line}, \
    {"auto_version_types", test_auto_version_types},

#ifdef __cplusplus
}
#endif

#endif /* TEST_AUTO_VERSION_H */
