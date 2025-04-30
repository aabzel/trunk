#ifndef TEST_MIC2026_H
#define TEST_MIC2026_H

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_MIC2026
#error "+HAS_MIC2026"
#endif

#include "test_hw_dep_check.h"

bool test_mic2026_write(void);
bool test_mic2026_read(void);

#define TEST_SUIT_MIC2026                \
    {"Mic2026Write", test_mic2026_write}, \
    {"Mic2026Read", test_mic2026_read},

#endif /* TEST_MIC2026_H */
