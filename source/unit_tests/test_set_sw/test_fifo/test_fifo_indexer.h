#ifndef TEST_FIFO_INDEXER_H
#define TEST_FIFO_INDEXER_H

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

#define RI_SIZE 10

bool test_fifo_inexer(void);

bool test_fifo_index_init(void);
bool test_fifo_index_add(void);
bool test_fifo_index_get(void);
bool test_fifo_index_continuus_used(void);
bool test_fifo_index_free(void);

#define TEST_SUIT_FIFO_INDEXER                                                                                         \
    {"fifo_index_init", test_fifo_index_init}, {"fifo_index_add", test_fifo_index_add},                                \
        {"fifo_index_get", test_fifo_index_get}, {"fifo_index_conti_used", test_fifo_index_continuus_used},            \
        {"fifo_index_free", test_fifo_index_free},

#ifdef __cplusplus
}
#endif

#endif /* TEST_FIFO_INDEXER_H */
