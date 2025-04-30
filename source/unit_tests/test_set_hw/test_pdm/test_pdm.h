#ifndef TEST_PDM_H
#define TEST_PDM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

#ifndef HAS_PDM
#error "+HAS_PDM"
#endif

#ifndef HAS_TEST_PDM
#error "+HAS_TEST_PDM"
#endif

bool test_pdm_hash_tables(void);
bool test_pdm_types(void);
bool test_pdm_start_stop(void);
bool test_pdm_reinit(void);
bool test_pdm_listen(void);

#define TEST_INTERGATION_PDM                    \
    {"pdm_listen", test_pdm_listen},

#define TEST_SUIT_PDM                            \
    {"pdm_types", test_pdm_types},               \
    {"pdm_hash_tables", test_pdm_hash_tables},   \
    {"pdm_start_stop", test_pdm_start_stop},     \
    {"pdm_reinit", test_pdm_reinit},             \
    TEST_INTERGATION_PDM


#ifdef __cplusplus
}
#endif

#endif /* TEST_PDM_H */
