#ifndef I2S_GENERAL_DRIVER_H
#define I2S_GENERAL_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "std_includes.h"
#include "i2s_types.h"
#include "i2s_config.h"
#include "i2s_isr.h"

#ifdef HAS_I2S_DIAG
#include "i2s_diag.h"
#endif

#ifdef USE_HAL_DRIVER
#include "stm32fx_hal.h"
#endif /**/

#define I2S_BYTES_TO_FRAMES(BYTE_SIZE, FRAME_SIZE) ((BYTE_SIZE)/(FRAME_SIZE))



/*API*/
I2sHandle_t* I2sGetNode(uint8_t num);
const I2sConfig_t* I2sGetConfig(uint8_t num);

bool i2s_mcal_init(void);
bool i2s_init_one(const uint8_t num);
bool i2s_init_node(I2sHandle_t* const Node );
bool i2s_init_custom(void);
bool i2s_proc_one(uint8_t num);
bool i2s_is_valid_config(const I2sConfig_t* const Config);
bool i2s_init_common(const I2sConfig_t* const Config, I2sHandle_t* const Node);
bool i2s_clock_init(uint8_t num);
bool i2s_proc(void);
bool i2s_common_init(uint8_t num);

bool i2s_wait_tx_done_ll(I2sHandle_t* Node, uint32_t time_out_ms);

/*getters*/
uint32_t i2s_get_sample_rate(uint8_t num);
uint32_t I2sAudioFreq2Hz(AudioFreq_t audio_freq);
uint8_t i2s_get_sample_size(uint8_t num);
uint8_t i2s_sample_size_get(uint8_t num);
bool i2s_listen(uint8_t num, uint32_t duration_ms);
bool i2s_data_format_get(uint8_t num, I2sDataFormat_t * data_format);
bool i2s_mcal_read(uint8_t num, uint16_t* array, uint32_t words) ;
bool i2s_calc_byte_rate(void);
bool i2s_is_valid_audio_frequency(const uint32_t audio_frequency_hz);
bool i2s_calc_dft(uint8_t num);
bool i2s_is_valid_num(uint8_t num);
bool i2s_sample_freq_get(uint8_t num, uint32_t * audio_freq_hz);
bool i2s_is_init(uint8_t num);
bool i2s_read_sample(uint8_t num, uint32_t size);
bool i2s_dir_bus_role_get(uint8_t num, IfBusRole_t *bus_role);
bool i2s_load_params(I2sConfig_t* Config);

/*setters*/
bool i2s_dir_bus_role_set(uint8_t num, IfBusRole_t bus_role);
bool i2s_send(uint8_t num, bool status);
bool i2s_mcal_start(uint8_t num, uint32_t array_len) ;
bool i2s_mcal_write(uint8_t num, const  uint16_t* const  array, const  uint32_t array_len);
bool i2s_config_tx(uint8_t num, uint8_t word_size, uint8_t channels ,uint32_t audio_freq);
bool i2s_dma_write(uint8_t num, const  uint16_t* const array, const uint16_t words) ;
bool i2s_dma_pause(uint8_t num);
bool i2s_dma_stop(uint8_t num);
bool i2s_stop(uint8_t num);
bool i2s_loopback(uint8_t num, uint32_t words_num);
bool i2s_play_static_tx(uint8_t num, uint8_t dac_num, bool status);
bool i2s_play_tx(uint8_t num, uint8_t dac_num, bool status);
bool i2s_play_1khz(uint8_t num, uint8_t dac_num, SampleType_t amplitude, uint32_t phase_ms);
bool i2s_read_write(uint8_t num, uint32_t tx_sample);
bool i2s_clock_init(const uint8_t num);
bool i2s_set_join_write(uint8_t num, uint32_t* array1, uint32_t* array2);
bool i2s_rec_reverse_byte_order(uint8_t num);
bool i2s_audio_frequency_set(const uint8_t num, const uint32_t audio_frequency_hz);
bool i2s_test(uint8_t num);

bool i2s_loopback_shared_memory(uint8_t num, uint32_t words_num);
uint32_t i2s_err_total(I2sErr_t* Err);

#ifdef HAS_I2S_VOLUME
SampleType_t i2s_calc_pcm_max_ll( I2sHandle_t* const Node );
bool i2s_increase_pcms_ll(I2sHandle_t* const Node);
bool i2s_decrease_pcms_ll( I2sHandle_t* const Node);
#endif


#ifdef __cplusplus
}
#endif

#endif /* I2S_GENERAL_DRIVER_H */


