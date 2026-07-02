#ifndef TEST_BIT_FIFO_H
#define TEST_BIT_FIFO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

bool test_bit_fifo_init(void);
bool test_bit_fifo_overrun(void);

bool test_bit_fifo_array_overrun(void);
bool test_bit_fifo_array(void);

#define TEST_SUIT_BIT_FIFO                                   \
    {"bit_fifo_init", test_bit_fifo_init},                   \
    {"bit_fifo_array", test_bit_fifo_array},                 \
    {"bit_fifo_overrun", test_bit_fifo_overrun},             \
    {"bit_fifo_array_overrun", test_bit_fifo_array_overrun},

#ifdef __cplusplus
}
#endif

#endif /* TEST_BIT_FIFO_H */
