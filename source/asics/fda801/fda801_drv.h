#ifndef FDA801_DRV_H
#define FDA801_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "fda801_const.h"
#include "fda801_types.h"

#ifdef HAS_TIMER
#include "timer_utils.h"
#endif

#ifndef HAS_I2C
#error "FDA801 Needs HAS_I2C"
#endif

#ifndef HAS_I2S
#error "FDA801 Needs HAS_I2S"
#endif

#ifndef HAS_GPIO
#error "FDA801 Needs HAS_GPIO"
#endif

#ifndef HAS_FDA801
#error "FDA801 Needs HAS_FDA801"
#endif

#define FDA801_POLL_PERIOD_US SEC_2_USEC(FDA801_POLL_PERIOD_S)

extern const Fda801I2cAddr_t Fda801I2cAddr[4];
extern const Fda801Reg_t Fda801RegMap[FDA801_REG_CNT];

Fda801ChannelPwm_t fda801_get_channel_pwm(Fda801ChannelNum_t Channel);
Fda801ChannelState_t fda801_get_state(Fda801ChannelNum_t Channel);
Fda801Channel_t* fda801_get_channel_node(Fda801ChannelNum_t Channel);
Fda801Handle_t* Fda801GetNode(uint8_t id_num);
bool fda801_channel_dc_diag_start(Fda801ChannelNum_t Channel);
bool fda801_check(void);
bool fda801_clock(bool on_off);
bool fda801_init(void);
bool fda801_is_valid_channel(Fda801ChannelNum_t Channel);
bool fda801_is_valid_gain(Fda801ChannelGain_t gain);
bool fda801_set_channel_gain(Fda801ChannelNum_t Channel, Fda801ChannelGain_t Gain);
bool fda801_get_channel_gain(Fda801ChannelNum_t Channel, Fda801ChannelGain_t* Gain);
bool fda801_proc(void);
bool fda801_read_reg(uint8_t reg_addr, uint8_t* reg_val);
bool fda801_reset(void);
bool fda801_watchdog_set(bool on);
bool fda801_watchdog_get(void);
bool fda801_set_channel_play(Fda801ChannelNum_t Channel, bool on_off);
bool fda801_set_channel_pwm(Fda801ChannelNum_t Channel, Fda801ChannelPwm_t pwm_state);
bool fda801_set_chip_addr(uint8_t addr);
bool fda801_set_state(Fda801ChannelNum_t Channel, Fda801ChannelState_t State);
bool fda801_write_lazy_reg(uint8_t reg_addr, uint8_t reg_val);
bool fda801_write_reg(uint8_t reg_addr, uint8_t reg_val);
bool fda801_write_reg_by_bitmask(uint8_t reg_addr, char* bit_mask);
const Fda801Config_t* Fda801GetConfNode(uint8_t id_num);
uint32_t fda801_get_sample_rate(void);
uint32_t fda801_reg_cnt(void);
uint8_t fda801_get_chip_addr(uint8_t id_num);

#endif /* FDA801_DRV_H */
