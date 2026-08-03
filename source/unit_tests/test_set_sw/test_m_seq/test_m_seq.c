#include "test_m_seq.h"

#include "log.h"
#include "m_seq_mcal.h"
#include "std_includes.h"
#include "unit_test_check.h"
#include "win_utils.h"

#define M_SEQ_2_CORR_FILE "TwoDiffMsecs.csv"
bool test_m_seq_diff_seq_corr(void) {
    bool res = true;
    int8_t seq1[128] = {0};
    int8_t seq2[128] = {0};
    uint32_t written1 = 0;
    uint32_t written2 = 0;
    ASSERT_TRUE(m_seq_get_code(1, seq1, sizeof(seq1), &written1));
    ASSERT_TRUE(m_seq_get_code(2, seq2, sizeof(seq2), &written2));
    ASSERT_EQ(written1, written2);
    ASSERT_TRUE(m_seq_calc_correlation_2(seq1, seq2, written1, M_SEQ_2_CORR_FILE));
    ASSERT_TRUE(csv_plot_line(M_SEQ_2_CORR_FILE, 1, 3));
    ASSERT_TRUE(csv_plot_line(M_SEQ_2_CORR_FILE, 1, 5));
    return res;
}

bool test_m_seq_same_seq_corr(void) {
    bool res = true;
    int8_t seq1[128] = {0};
    uint32_t written1 = 0;
    ASSERT_TRUE(m_seq_get_code(1, seq1, sizeof(seq1), &written1));
    ASSERT_TRUE(m_seq_calc_correlation_2(seq1, seq1, written1, M_SEQ_2_CORR_FILE));
    ASSERT_TRUE(csv_plot_line(M_SEQ_2_CORR_FILE, 1, 3));
    // ASSERT_TRUE(csv_plot_line(M_SEQ_2_CORR_FILE, 1, 5));
    return res;
}

bool test_m_seq_auto_corr(void) {
    bool res = true;
    ASSERT_TRUE(m_seq_calc_acf(1, 6, M_SEQ_2_CORR_FILE));
    ASSERT_TRUE(csv_plot_line(M_SEQ_2_CORR_FILE, 1, 3));

    ASSERT_TRUE(m_seq_calc_acf(2, 6, M_SEQ_2_CORR_FILE));
    ASSERT_TRUE(csv_plot_line(M_SEQ_2_CORR_FILE, 1, 3));
    return res;
}

bool test_m_seq_generate(void) {
    bool res = true;

    ASSERT_TRUE(m_seq_generate(1));
    ASSERT_TRUE(m_seq_generate(2));

    ASSERT_TRUE(m_seq_generate(1));
    ASSERT_TRUE(m_seq_generate(2));

    ASSERT_TRUE(m_seq_generate(1));
    ASSERT_TRUE(m_seq_generate(2));

    return res;
}

bool test_m_find_feedback(void) {
    bool res = true;
    ASSERT_TRUE(m_seq_find_feedback(2));
    return res;
}
