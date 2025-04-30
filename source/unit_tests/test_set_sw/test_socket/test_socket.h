#ifndef TEST_SOCKET_H
#define TEST_SOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_SOCKET
#error "It is needed HAS_SOCKET option for that component"
#endif

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

bool test_socket(void);

#define TEST_SUIT_SOCKET        \
     {"socket", test_socket},

#ifdef __cplusplus
}
#endif

#endif /* TEST_SOCKET_H */
