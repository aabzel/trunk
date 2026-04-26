#ifndef DAC_CHANNEL_DRIVER_GENERAL_API_H
#define DAC_CHANNEL_DRIVER_GENERAL_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dac_channel_types.h"
#include "dac_channel_config.h"
#include "gpio_types.h"

#ifdef HAS_DAC_CHANNEL_DIAG
#include "dac_channel_diag.h"
#endif

#ifdef HAS_DAC_CHANNEL_CUSTOM
#include "dac_custom_types.h"
#include "dac_channel_custom_drv.h"
#endif

/*API*/
bool dac_channel_proc(void);
bool dac_channel_proc_one(uint8_t num);
bool DacChannelIsValidConfig(const DacChannelConfig_t* const Config);

#ifdef HAS_DAC_CHANNEL_CUSTOM
const DacChannelInfo_t* DacChannelToInfo(uint8_t dac_num, DacChannel_t channel) ;
#endif

DacChannelHandle_t* DacChannelGetNode(uint8_t num);
DacChannelHandle_t* DacChannelGetNodeV2(uint8_t dac_num, DacChannel_t channel);

const DacChannelConfig_t* DacChannelGetConfig(uint8_t num);
const DacChannelConfig_t* DacChannelGetConfigV2(uint8_t dac_num, DacChannel_t channel);
bool DacChannelGetVoltage(uint8_t node_num, float* const voltage_scale);

/*init */
bool dac_channel_init_common(const DacChannelConfig_t* const Config, DacChannelHandle_t*  const Node);
bool dac_channel_init_node(DacChannelHandle_t*  const Node);
bool dac_channel_init_custom(void);
bool dac_channel_init_one(uint8_t num);
bool dac_channel_init(uint8_t dac_num, DacChannel_t channel);
bool dac_channel_mcal_init(void);

Pad_t DacChannelToPad(uint8_t dac_num, DacChannel_t channel);
uint32_t DacChanneCode2mV(uint8_t dac_num, DacChannel_t channel, int32_t code);

/*setter*/
bool dac_channel_proc_from_fifo(DacChannelHandle_t* Node);
bool dac_channel_code_set(const uint8_t dac_num, DacChannel_t channel, const uint16_t code);
bool dac_channel_voltage_set(uint8_t dac_num, DacChannel_t channel,  const float voltage);

/*Get*/
bool dac_channel_code_read(uint8_t dac_num, DacChannel_t channel, int32_t* const code);
bool dac_channel_voltage_read(uint8_t dac_num, DacChannel_t channel, float* const voltage);
bool dac_channel_pad_voltage_read(Pad_t pad, float* const voltage);
bool dac_channel_code_to_params(DacChannelHandle_t* const Channel) ;
bool dac_channel_is_valid(DacChannel_t channel);
bool dac_channel_pad_code_read(Pad_t pad, int32_t* code);
float dac_channel_voltage_read_short(uint8_t dac_num, DacChannel_t channel);
float dac_channel_voltage_scale_get(uint8_t num);
float dac_channel_pad_voltage_read_short(Pad_t pad);
DacChannel_t DacChannelPadToChannel(Pad_t pad);


#ifdef __cplusplus
}
#endif

#endif /* DAC_DRIVER_GENERAL_API_H */
