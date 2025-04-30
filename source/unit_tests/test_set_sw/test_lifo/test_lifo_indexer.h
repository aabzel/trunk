#ifndef TEST_LIFO_INDEXER_H
#define TEST_LIFO_INDEXER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_LIFO
#error "It is needed HAS_LIFO option for that component"
#endif

#define RI_SIZE 10

bool test_lifo_index_get_empty(void);
bool test_lifo_index_init(void);
bool test_lifo_index_add(void);
bool test_lifo_index_overflow(void);

#define TEST_SUIT_LIFO_INDEXER                  \
    {"lifo_index_overflow", test_lifo_index_overflow},  \
    {"lifo_index_init", test_lifo_index_init},  \
    {"lifo_index_get_empty", test_lifo_index_get_empty},  \
    {"lifo_index_add", test_lifo_index_add},

#ifdef __cplusplus
}
#endif

#endif /* TEST_LIFO_INDEXER_H */
