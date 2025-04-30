#ifndef I2S_GENERAL_DRIVER_H
#define I2S_GENERAL_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "i2s_types.h"
#include "i2s_config.h"
#include "i2s_dep.h"


#ifdef USE_HAL_DRIVER
#include "stm32f4xx_hal.h"
#endif /*USE_HAL_DRIVER*/

#define I2S_BYTES_TO_FRAMES(BYTE_SIZE, FRAME_SIZE) ((BYTE_SIZE)/(FRAME_SIZE))

I2sHandle_t* I2sGetNode(uint8_t num);
bool i2s_api_read(uint8_t num, SampleType_t* array, size_t array_len);
bool i2s_api_start(uint8_t num, size_t array_len) ;
bool i2s_api_write(uint8_t num, SampleType_t* array, size_t array_len);
bool i2s_calc_byte_rate(void);
bool i2s_calc_dft(uint8_t num);
bool i2s_config_tx(uint8_t num, uint8_t word_size, uint8_t channels ,uint32_t audio_freq);
bool i2s_dma_pause(uint8_t num);
bool i2s_dma_stop(uint8_t num);
bool i2s_stop(uint8_t num);
#ifdef HAS_I2S_VOLUME
SampleType_t i2s_calc_pcm_max_ll( I2sHandle_t* const Node );
bool i2s_increase_pcms_ll(I2sHandle_t* const Node);
bool i2s_decrease_pcms_ll( I2sHandle_t* const Node);
#endif
bool i2s_init(void);
bool i2s_init_one(uint8_t num);
bool i2s_is_allowed(uint8_t num);
bool i2s_is_init(uint8_t num);
bool i2s_loopback(uint8_t num, size_t words_num);
bool i2s_loopback_shared_memory(uint8_t num, size_t words_num);
bool i2s_play_tx(uint8_t num, uint8_t dac_num, bool status);
bool i2s_play_static_tx(uint8_t num, uint8_t dac_num, bool status);
bool i2s_play_1khz(uint8_t num, uint8_t dac_num, SampleType_t amplitude, uint32_t phase_ms);
bool i2s_proc_one(uint8_t num);
bool i2s_proc(void);
bool i2s_read_sample(uint8_t num, size_t size);
bool i2s_read_write(uint8_t num, uint32_t tx_sample);
bool i2s_send(uint8_t num, bool status);
bool i2s_set_join_write(uint8_t num, uint32_t* array1, uint32_t* array2);
bool i2s_test(uint8_t num);
const I2sConfig_t* I2sGetConfig(uint8_t num);
uint32_t I2sAudioFreq2Hz(AudioFreq_t audio_freq);
uint32_t i2s_err_total(I2sErr_t* Err);
uint32_t i2s_get_sample_rate(uint8_t num);
uint8_t i2s_get_sample_size(uint8_t num);

#ifdef HAS_I2S
bool i2s_common_init(uint8_t num);
#endif /*HAS_I2S*/

#ifdef __cplusplus
}
#endif

#endif /* I2S_GENERAL_DRIVER_H */


