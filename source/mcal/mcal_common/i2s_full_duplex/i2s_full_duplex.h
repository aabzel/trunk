#ifndef I2S_FULL_DUPLEX_DRIVER_H
#define I2S_FULL_DUPLEX_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "i2s_full_duplex_types.h"
#include "i2s_full_duplex_config.h"
#include "i2s_full_duplex_diag.h"
#include "i2s_full_duplex_isr.h"
#include "dma_types.h"

/* API*/
DmaChannelHandle_t* I2sNumToDmaChannel(uint32_t i2s_num);
const I2sFullDuplexConfig_t* I2sFullDuplexGetConfig(uint8_t num);
I2sFullDuplexHandle_t* I2sFullDuplexGetNode(uint8_t num);
bool i2s_full_duplex_mcal_init(void);
bool i2s_full_duplex_data_proc_ll(I2sFullDuplexHandle_t* Node, uint32_t part);
bool i2s_full_duplex_proc_one(uint8_t num);
bool i2s_full_duplex_init_one(uint8_t num);
bool i2s_full_duplex_proc(void);

/* settes*/
bool i2s_full_duplex_ctrl(uint8_t num, bool on_off);
bool i2s_full_duplex_start_ll(I2sFullDuplexHandle_t* Node) ;
bool i2s_full_duplex_start(uint8_t num) ;
bool i2s_full_duplex_stop_ll(I2sFullDuplexHandle_t* Node) ;
bool i2s_full_duplex_stop(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* I2S_FULL_DUPLEX_DRIVER_H */


