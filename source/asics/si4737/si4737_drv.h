#ifndef SI4737_DRV_H
#define SI4737_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "si4737_types.h"

#ifndef HAS_I2C
#error "SI4737 Needs HAS_I2C"
#endif

#ifndef HAS_GPIO
#error "SI4737 Needs HAS_GPIO"
#endif

#ifndef HAS_SI4737
#error "SI4737 Needs HAS_SI4737"
#endif

extern Si4737Property_t Si4737Property[];

bool fm_stations_set(char* station_name);
bool si4737_set_mute(bool left, bool right);
bool si4737_fm_seek_start(SeekDir_t SeekDir, SeekEnd_t SeekEnd, Si4737Handler_t* instance);
bool si4737_get_fm_tune_freq(Si4737Handler_t* instance, SeekCancel_t Seek, SeekTuneIntClear_t SeekTuneInt);
bool si4737_get_int_status(Si4737Handler_t* instance);
bool si4737_get_property(uint16_t property, uint16_t* val);
bool si4737_get_resp(uint8_t* resp, uint8_t len);
bool si4737_get_rev(Si4737FullRevResp_t* FullRevResp);
bool si4737_get_rsq_status(Si4737Handler_t* instance);
bool si4737_get_digital_output_format(Si4737Handler_t* instance);
bool si4737_set_digital_ouput_format(Si4737Handler_t* instance);
bool si4737_get_rx_volume(uint16_t* rx_volume);
bool si4737_init(void);
bool si4737_set_gpo_ien(void);
bool si4737_is_connected(void);
bool si4737_proc_status(uint8_t status, Si4737Handler_t* instance);
bool si4737_power_up(uint8_t opmode, Si4737Handler_t* instance);
bool si4737_power_down(void);
bool si4737_proc(void);
bool si4737_reset(void);
bool si4737_set_command(uint8_t cmd, uint8_t* arg, uint8_t arg_cnt);
bool si4737_set_fm_tune_freq(double freq_mhz);
bool si4737_set_property(uint16_t property, uint16_t val);
bool si4737_set_rx_volume(uint16_t rx_volume);
uint32_t si4737_get_prop_cnt(void);

#endif /* SI4737_DRV_H */
