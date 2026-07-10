#ifndef WM8731_ASIC_DRV_H
#define WM8731_ASIC_DRV_H

#include "audio_types.h"
#include "std_includes.h"
#include "wm8731_config.h"
#include "wm8731_diag.h"
#include "wm8731_types.h"

extern const Wm8731Reg_t Wm8731RegMap[];
/*API*/

Wm8731Handle_t* Wm8731GetNode(uint8_t num);
const Wm8731Config_t* Wm8731GetConfig(uint8_t num);
const Wm8731RegConfig_t* Wm8731GetRegConfig(uint8_t num, uint8_t reg_addr);

bool wm8731_mcal_init(void);
bool wm8731_init_one(uint8_t num);
bool wm8731_proc_one(uint8_t num);
bool wm8731_proc_one_ll(Wm8731Handle_t* Node);
bool wm8731_check(uint8_t num);
bool wm8731_proc(void);
bool wm8731_is_valid_volume(int8_t vol_db);

/*setters*/
bool wm8731_sample_rate(const uint8_t num, const AudioFreq_t audio_freq_hz);
bool wm8731_bypass(uint8_t num);
bool wm8731_mute(uint8_t num);
bool wm8731_play_freq(uint8_t num, double freq, SampleType_t amplitude);
bool wm8731_play_1khz_con(uint8_t num, SampleType_t amplitude);
bool wm8731_play_1khz(uint8_t num, SampleType_t amplitude, int32_t duratin_ms);
bool wm8731_reset(uint8_t num);
bool wm8731_set_reg(uint8_t num, uint8_t reg_addr, uint8_t reg_val);

/*getters*/
bool wm8731_listen(uint8_t num, uint32_t duration_ms);
bool wm8731_get_reg(uint8_t num, uint8_t reg_addr, uint8_t* reg_val);

// misc
int8_t wm8731_volume_limiter( int8_t vol_db);
uint8_t wm8731_vol_code(int8_t vol);
uint32_t wm8731_pcm_2_32bit_sample(int32_t tx_sample);
uint16_t wm8731_pcm_2_16bit_sample(int32_t tx_sample);

// uint16_t wm8731_vol_code(int8_t vol);
bool wm8731_set_sidetone(uint8_t num, bool state);
bool wm8731_set_volume(uint8_t num, int8_t left, int8_t right);
uint8_t wm8731_get_reg_cnt(void);

#endif /* WM8731_ASIC_DRV_H */
