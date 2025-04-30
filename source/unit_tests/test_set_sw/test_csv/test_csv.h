
#ifndef TEST_CSV_H
#define TEST_CSV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

#ifndef HAS_CSV
#error "It is needed HAS_CSV option for that component"
#endif

#ifndef HAS_TEST_SUIT_CSV
#error "It is needed HAS_TEST_SUIT_CSV option for that component"
#endif

bool test_csv_strlen_perf(void);
bool test_csv_cnt(void);
bool test_csv_fetch_text_zeros(void);
bool test_csv_parse_double(void);
bool test_csv_parse_text(void);
bool test_csv_parse_last_text(void);
bool test_csv_perf(void);
bool test_csv_fetch_text(void);
bool test_csv_parse_text_overflow(void);
bool test_csv_cnt_perf(void);
bool test_csv_fetch_text_perf(void);

#define TEST_SUIT_CSV                           \
   {"csv_cnt", test_csv_cnt},                   \
   {"csv_strlen_perf", test_csv_strlen_perf},              \
   {"csv_fetch_text_perf", test_csv_fetch_text_perf},              \
   {"csv_cnt_perf", test_csv_cnt_perf},              \
   {"csv_parse_text_overflow", test_csv_parse_text_overflow},              \
   {"csv_fetch_text", test_csv_fetch_text},              \
   {"csv_parse_last_text", test_csv_parse_last_text},              \
   {"csv_parse_text", test_csv_parse_text},     \
   {"csv_fetch_text_zeros", test_csv_fetch_text_zeros},     \
   {"csv_parse_double", test_csv_parse_double}, \

#ifdef __cplusplus
}
#endif

#endif /* TEST_CSV_H */
