#ifndef M_SEQ_TEST_H
#define M_SEQ_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

bool test_m_seq_diff_seq_corr(void);
bool test_m_seq_same_seq_corr(void) ;
bool test_m_seq_generate(void);
bool test_m_find_feedback(void) ;
bool test_m_seq_auto_corr(void);

#define TEST_SUIT_M_SEQ                                   \
     {"m_find_feedback", test_m_find_feedback},           \
     {"m_seq_generate", test_m_seq_generate},             \
     {"m_seq_auto_corr", test_m_seq_auto_corr},           \
     {"m_seq_same_seq_corr", test_m_seq_same_seq_corr},   \
     {"m_seq_diff_seq_corr", test_m_seq_diff_seq_corr},   \

#ifdef __cplusplus
}
#endif

#endif /* M_SEQ_TEST_H */
