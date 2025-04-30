#ifndef TEST_CIRCULAR_BUFFER_INDEXER_H
#define TEST_CIRCULAR_BUFFER_INDEXER_H

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

bool test_circular_buffer_index_init(void);
bool test_circular_buffer_index_add(void);
bool test_circular_buffer_index_get(void);
bool test_circular_buffer_word_get(void);

#define TEST_SUIT_CIRCULAR_BUFFER                                        \
    {"circular_buffer_word_get", test_circular_buffer_word_get},     \
    {"circular_buffer_index_init", test_circular_buffer_index_init},     \
    {"circular_buffer_index_add", test_circular_buffer_index_add},       \
    {"circular_buffer_index_get", test_circular_buffer_index_get},

#ifdef __cplusplus
}
#endif

#endif /* TEST_CIRCULAR_BUFFER_INDEXER_H */
