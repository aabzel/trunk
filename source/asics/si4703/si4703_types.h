#ifndef SI4703_TYPES_H
#define SI4703_TYPES_H

#include "std_includes.h"
#include "si4703_const.h"
#include "gpio_types.h"
#include "si4703_register_types.h"
#include "interfaces_types.h"

#ifdef HAS_SPI
#include "si4703_spi_types.h"
#endif

#ifdef HAS_I2C
#include "si4703_i2c_types.h"
#endif




#define  SI4703_GPIO_VARIABLES            \
    Pad_t PadReset;                       \
    Pad_t PadSen;                         \
    Pad_t PadGpio1;                       \
    Pad_t PadGpio2;                       \
    Pad_t PadSdio;                        \
    Pad_t PadSclk;

#define SI4703_COMMON_VARIABLES                       \
    SI4703_GPIO_VARIABLES                             \
    uint8_t i2c_addr;                                 \
    InterfaceCode_t if_code;                          \
    double fm_freq_mhz;                               \
    char* name;                                       \
    uint8_t num;                                      \
    bool valid;

typedef struct {
    SI4703_COMMON_VARIABLES
    Si4703RegSysCfg1_t SysCfg1;
    Si4703RegSysCfg2_t SysCfg2;
    Si4703RegSysCfg3_t SysCfg3;
    uint8_t rds_int_fifo_cnt;
    bool rds_en;
}Si4703Config_t;

#define SI4703_SIGNAL_VARIABLES              \
    int32_t volume ;                         \
    double fm_freq_read_mhz ;                \
    Si4703Pwr_t power;                       \
    uint16_t  rx_volume;                     \
    uint8_t rssi;/*Received Signal Strength Indicator.*/          \
    uint8_t snr;/* dB*/

#define SI4703_COUNTER_VARIABLES             \
    uint32_t err_cnt;                        \
    uint32_t rds_int_cnt;                    \
    uint32_t asq_cnt;                        \
    uint32_t stc_int_cnt;                    \
    uint32_t rsq_int_cnt;                    \
    uint32_t rds_recv_cnt;                   \
    uint32_t valid_cnt;                      \
    uint32_t pilot_cnt;                      \
    uint32_t rds_sync_cnt;                   \
    uint32_t cts_cnt;                        \
    uint8_t rds_fifo_cnt;

typedef struct {
    SI4703_COMMON_VARIABLES
    SI4703_SIGNAL_VARIABLES
    SI4703_COUNTER_VARIABLES
    uint8_t mult;
    uint8_t out_size_bit; /*Digital Output Audio Sample Precision*/
    uint32_t spin;
    uint32_t reg_val_disaccord;
    bool connected;
    bool init;
    bool stc_int;
    bool rds_int;
    bool rsq_int;
    bool clear_seek;
    bool fetch_freq;
    bool stereo;
    bool tune_start;
    Si4703BandSel_t band_sel;
    double freq_offset; /*Hz*/
    double channel_spacing_mhz ;
    double band_start_mhz ;
    double fm_freq_set; /*Hz*/
    double fm_freq_set_real; /*Hz*/
    uint8_t seekth ;
    uint16_t RegWrite[SI4703_REG_CNT] ;
    uint16_t RegRead[SI4703_REG_CNT] ;
}Si4703Handle_t;


#endif /* SI4703_TYPES_H */
