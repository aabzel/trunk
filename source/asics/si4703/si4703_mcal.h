#ifndef SI4703_MCAL_H
#define SI4703_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "si4703_config.h"
#include "si4703_types.h"
#ifdef HAS_SI4703_DIAG
#include "si4703_diag.h"
#endif

/* API */
Si4703Handle_t* Si4703GetNode(uint8_t num);
const Si4703Config_t* Si4703GetConfig(uint8_t num);
bool Si4703IsValidConfig(const Si4703Config_t* const Config);

bool si4703_mcal_init(void);
bool si4703_init_custom(void);
bool si4703_init_one(uint8_t num);
bool si4703_init_common(const Si4703Config_t* const Config, Si4703Handle_t* const Node);

bool si4703_proc_one(uint8_t num);
bool si4703_proc(void);

/*setters*/
bool si4703_volume_down(uint8_t num);
bool si4703_volume_up(uint8_t num);
bool si4703_volume_set(uint8_t num ,uint8_t volume);
bool si4703_write_reg(uint8_t num, Si4703RegAddr_t reg_addr, uint16_t reg_val);
bool si4703_write_lazy_reg(uint8_t num, uint8_t reg_addr, uint16_t reg_val);
bool si4700_set_frequency(uint8_t num, double freq);
bool si4703_reset(uint8_t num);
bool si4703_select_if(const uint8_t num, const InterfaceName_t if_name);
bool si4703_power_up(uint8_t num);
bool si4703_xtall_ctrl(uint8_t num, bool on, uint16_t preserv);
bool si4703_fm_seek_start(uint8_t num, Si4703SeekDir_t seek_dir, Si4703SeekEnd_t seek_end);
bool si4703_set_channel(uint8_t num, uint16_t channel, Si4703Tune_t tune);
bool si4703_seek_clr(uint8_t num);

/*getters*/
bool si4703_volume_get(uint8_t num ,uint8_t * const volume) ;
bool si4703_is_valid_device_id(const Si4703RegDeviceID_t DeviceID );
bool si4703_read_reg(const uint8_t num, const  Si4703RegAddr_t reg_addr, uint16_t* const reg_val);
bool si4703_read_rds(uint8_t num, uint16_t* words);
bool si4703_is_connected(uint8_t num);
bool si4703_is_power_up(uint8_t num);
uint32_t si4703_reg_cnt(void);


#ifdef __cplusplus
}
#endif

#endif /* SI4703_MCAL_H */
