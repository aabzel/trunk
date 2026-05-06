#ifndef BPSK_4FS_H
#define BPSK_4FS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dsp_types.h"
#include "bpsk_4fs_types.h"
#include "bpsk_4fs_config.h"
#include "bpsk_4fs_diag.h"

#ifdef HAS_ADC
#include "adc_types.h"
#endif

Bpsk4fsHandle_t* Bpsk4fsGetNode(uint8_t num);
const Bpsk4fsConfig_t* Bpsk4fsGetConfig(uint8_t num);

#ifdef HAS_BPSK_4FS_PHASE_ERROR_ASIN
float bpsk_4fs_calc_phase_error_asin(Bpsk4fsHandle_t* const Node);
#endif

bool bpsk_4fs_proc(void);
bool bpsk_4fs_proc_one(uint8_t num);

bool bpsk_4fs_mcal_init(void);
bool bpsk_4fs_init_one(uint8_t num);
bool bpsk_4fs_reinit_node(uint8_t num) ;

float bpsk_4fs_calc_phase_error_atan(Bpsk4fsHandle_t* const Node);

#ifdef HAS_WAV
bool bpsk_4fs_decode_wav(uint8_t num, const char* const file_name);

bool bpsk_4fs_encode_to_wav(uint8_t num,
                        const uint8_t* const data_to_encode,
                        const uint32_t data_size, const uint32_t repetition);
#endif

bool proc_samples_to_mem(Bpsk4fsHandle_t* Bpsk, uint16_t *mem, uint32_t start, uint32_t end);

bool bpsk_4fs_encode(uint8_t num,
                     const uint8_t* const message,
                     const uint32_t message_size,
                     int32_t* const sample,
                     uint32_t sample_cnt,
                     uint32_t *const sample_len);

/*setters*/
bool bpsk_4fs_rx_bit_phase(const uint8_t num,const  int32_t rx_bit_phase);

bool bpsk_4fs_proc_from_adc_fifo(Bpsk4fsHandle_t* Node) ;
bool bpsk_4fs_decode(uint8_t num,
                     const int32_t* const sample,
                     uint32_t sample_cnt,
                     uint8_t* const raw_data,
                     const uint32_t raw_data_size,
                     uint32_t* data_size);

/* getter */
float bpsk_4fs_calc_carrier_phase_err_rad(float i_val, float q_val);
bool bpsk_4fs_phase_error_calc_ll(Bpsk4fsHandle_t* const Node);
int32_t Bpsk4fskRadToSample(float phase_error_rad) ;

#ifdef __cplusplus
}
#endif

#endif /* BPSK_4FS_H */
