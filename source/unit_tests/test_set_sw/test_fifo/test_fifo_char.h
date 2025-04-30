#ifndef TEST_FIFO_CHAR_H
#define TEST_FIFO_CHAR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

bool test_fifo_char_overrun(void);
bool test_fifo_char_array_overrun(void);
bool test_fifo_char_array(void);
bool test_fifo_2(void);

#define TEST_SUIT_FIFO_CHAR                                                                                            \
    {"fifo_ch_overrun", test_fifo_char_overrun}, {"fifo_2", test_fifo_2}, {"fifo_ch_array", test_fifo_char_array},     \
        {"fifo_ch_array_overrun", test_fifo_char_array_overrun},

#ifdef __cplusplus
}
#endif

#endif /* TEST_FIFO_CHAR_H */
