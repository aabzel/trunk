#ifndef BPSK_H
#define BPSK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "audio_types.h"
#include "bpsk_types.h"
#include "bpsk_config.h"
#include "bpsk_diag.h"

BpskHandle_t* BpskGetNode(uint8_t num);
const BpskConfig_t* BpskGetConfig(uint8_t num);

#ifdef HAS_BPSK_PHASE_ERROR_ASIN
double bpsk_calc_phase_error_asin(BpskHandle_t* const Node);
#endif

double bpsk_calc_phase_error_atan(BpskHandle_t* const Node);

bool bpsk_decode_wav(uint8_t num, const char* const file_name);

bool bpsk_encode_to_wav(uint8_t num,
                        const uint8_t* const data_to_encode,
                        const uint32_t data_size, const uint32_t repetition);

bool bpsk_reinit_node(uint8_t num) ;
bool bpsk_init_one(uint8_t num);

bool bpsk_mcal_init(void);

bool bpsk_encode(uint8_t num,
                 const uint8_t* const raw_data, uint32_t data_size,
                 SampleType_t* const sample, uint32_t sample_cnt);

/**/
bool bpsk_decode(uint8_t num,
                 const SampleType_t* const sample, uint32_t sample_cnt,
                 uint8_t* const raw_data, uint32_t* data_size);


#ifdef __cplusplus
}
#endif

#endif /* BPSK_H */
