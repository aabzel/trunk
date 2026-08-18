#ifndef NAU8814_TYPES_H
#define NAU8814_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "nau8814_registers_types.h"
#include "nau8814_const.h"
#include "storage_const.h"
#include "connectivity_const.h"
#ifdef HAS_AUDIO
#include "audio_types.h"
#endif

//MCLKSEL Master Clock Selection  in Reg:0x06
typedef struct{
    uint8_t mclksel; // [1....7]
    float divider; // 1; 1.5; 2; 3; 4; 6; 8; 12
}Nau8814MasterClockSelInfo_t;

typedef struct {
    float f_pll ;
    float f_1 ;
    float f_2 ;
    float i_mclk ;
    float R ;
    uint32_t mclk_hz;//input
    uint32_t fs_hz;//need
    uint32_t N;
    uint32_t K;
    uint32_t D;
    float fraction ;
}Nau8814PllInfo_t;

/*Figure 27: Byte Write Sequence*/
typedef union{
    uint8_t buff[2];
    uint16_t word;
    struct{
        uint16_t reg_value :9;
        uint16_t reg_addr : 7;
    };
}Nau8814WriteFrame_t;

typedef struct {
    Nau8814RegAddr_t addr;
    Nau8814RegUniversal_t Reg; /*register value*/
}Nau8814RegVal_t;

typedef struct {
    Nau8814RegAddr_t addr;
    char* name;
    StorageAccess_t access;
    bool valid;
}Nau8814RegInfo_t;

#define NAU8814_IN_GAINS             \
    Gain_t aux_gain;              \
    Gain_t p_mic_gain;


#define NAU8814_OUT_GAINS             \
    Gain_t spk_gain;              \
    fGain_t dac_gain;

#define NAU8814_GAINS             \
    NAU8814_IN_GAINS         \
    NAU8814_OUT_GAINS        \
    float pga_gain;

#define NAU8814_COMMON_VARIABLE   \
    NAU8814_GAINS                 \
    double mclk_freq_hz;          \
    bool adc_on;                  \
    bool dac_on;                  \
    bool valid ;                  \
    uint8_t chip_addr ;           \
    uint8_t num ;                 \
    uint8_t pll_d;                \
    uint8_t pll_n;                \
    uint32_t pll_k;               \
    uint8_t i2c_num;              \
    uint8_t i2s_num;              \
    uint8_t dac_num;              \
    IfBusRole_t i2s_role;

typedef struct{
    NAU8814_COMMON_VARIABLE
    Nau8814RegVal_t* RegVals;
    uint32_t reg_val_cnt;
    char *name;
}Nau8814Config_t;

typedef struct{
    NAU8814_COMMON_VARIABLE

    bool init;
}Nau8814Handle_t;

/*
 * 13.9.2. Phase Lock Loop Control (PLL) Registers
 */
typedef union{
    uint32_t pll_k;
    struct{
        uint32_t pll_k_8_0 : 9; /*bit: [8:0]*/
        uint32_t pll_k_17_9 : 9; /*bit:  [17:9]*/
        uint32_t pll_k_23_18 : 6;  /*bit: K[23:18]*/
        uint32_t res : 8; /*bit:[31..24]*/
    };
}Nau8814Pllk_t;

#endif /* NAU8814_TYPES_H */
