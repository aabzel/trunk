#ifndef ALLOCATOR_TEST_H
#define ALLOCATOR_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_TEST_HEAP
#error "It is needed HAS_TEST_HEAP option for that component"
#endif

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

bool test_allocator_malloc_zero(void);
bool test_allocator_stress(void);
bool test_allocator_malloc(void);
bool test_allocator_malloc_over(void);
bool test_allocator_types(void);
bool test_allocator_malloc_several(void);

/*the order in which tests are run matters*/
#define TEST_SUIT_ALLOCATOR_BASE                            \
    {"allocator_types", test_allocator_types},              \
    {"allocator_malloc_0", test_allocator_malloc_zero},     \
    {"allocator_malloc", test_allocator_malloc},                 \
    {"allocator_malloc_over", test_allocator_malloc_over},       \
    {"allocator_malloc_several", test_allocator_malloc_several}, \
    {"allocator_stress", test_allocator_stress},



#define TEST_SUIT_ALLOCATOR      \
        TEST_SUIT_ALLOCATOR_BASE \
        

#ifdef __cplusplus
}
#endif

#endif /* ALLOCATOR_TEST_H */
