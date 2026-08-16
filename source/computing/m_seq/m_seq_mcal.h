#ifndef M_SEQ_MCAL_H
#define M_SEQ_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "m_seq_config.h"
#include "m_seq_types.h"

#ifdef HAS_M_SEQ_DIAG
#include "m_seq_diag.h"
#endif

/* API */
MseqHandle_t* MseqGetNode(uint8_t num);
const MseqConfig_t* MseqGetConfig(uint8_t num);
bool MseqIsValidConfig(const MseqConfig_t* const Config);

#ifdef HAS_M_SEQ_CUSTOM
const MseqInfo_t* MseqGetInfo(uint8_t num);
#endif

bool m_seq_mcal_init(void);
bool m_seq_init_custom(void);
bool m_seq_init_common(const MseqConfig_t* const Config, MseqHandle_t* const Node);
bool m_seq_init_node(MseqHandle_t* const Node);
bool m_seq_init_one(uint8_t num);

bool m_seq_proc_one(uint8_t num);
bool m_seq_proc(void);

/*setters*/
bool m_sec_to_signal(uint8_t* m_seq, int16_t* signal, uint32_t size) ;
bool m_seq_find_first_feedback(uint8_t num) ;
bool m_seq_calc_correlation_2( uint8_t* seq1, uint8_t* seq2, uint32_t size, char * CorrelationFileName) ;
bool m_seq_reinit_one(uint8_t num, uint32_t shift_reg_num);
bool m_seq_seed_set(uint8_t num, uint8_t offset, uint8_t value) ;
bool m_seq_feedback(uint8_t num, uint8_t offset, uint8_t value) ;
bool m_seq_find_feedback(uint8_t num) ;
bool m_seq_calc_acf(uint8_t num, uint32_t shift_reg_num, char * CorrelationFileName);
bool m_seq_calc_periodic_acf(uint8_t num,
                                               uint32_t shift_reg_num,
                                               char * CorrelationFileName) ;

float m_seq_calc_sample(uint8_t num,
                        float up_time_s,
                        float amplitude,
                        float frequency,
                        uint32_t periods_per_chip);

/*getters*/
float m_seq_signal_duration(uint8_t num, float carrier_frequency_hz, uint32_t periods_per_chip);
bool m_seq_generate(uint8_t num);
int8_t m_seq_get_sample(uint8_t num);
uint32_t m_seq_get_len(uint32_t shift_reg_num);
bool m_seq_get_code(uint8_t num,
                    int8_t* const code,
                    uint32_t size,
                    uint32_t* written
                    );
bool m_seq_is_valid_num(const uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* M_SEQ_MCAL_H */
