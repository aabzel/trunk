#ifndef PLL_CALC_TYPES_H
#define PLL_CALC_TYPES_H

#include <stdint.h>

#include "pll_calc_const.h"


/*
CAN bit timing register (CAN_BTR) offset: 0x1C Reset value: 0x0123 0000
This register can only be accessed by the software when the CAN hardware is in
initialization mode.
 */
typedef union  {
    uint32_t dword;
    struct {
        uint32_t BRP : 10; /*Bits 9:0 BRP[9:0]: Baud rate prescaler*/
        uint32_t RES1: 6;  /*Reserved*/
        uint32_t TS1 : 4;  /*Bits 19:16 TS1[3:0]: Time segment 1*/
        uint32_t TS2 : 3;  /*Bits 22:20 TS2[2:0]: Time segment 2*/
        uint32_t RES2 : 1; /*Reserved*/
        uint32_t SJW : 2;  /*Bits 25:24 SJW[1:0]: Resynchronization jump width*/
        uint32_t RES3 : 6; /*31:25 Reserved*/
    };
} CanRegBTR_t;

typedef struct {
    int32_t error;
    CanRegBTR_t CAN_BTR ;
}CanBestRegBtr_t;


typedef struct {
    int32_t error_freq_hz; /* Frequency setting error   */
    uint32_t xtall_freq_hz; /* HSE   */
    uint32_t best_core_freq_hz; /*    */
    int32_t core_freq_hz; /*    SYSCLK */
    uint32_t M; /*  HSE/M M=[2...63] */
    uint32_t N; /*  N*(HSE/M)  N=[50.....432]   */
    uint32_t P; /*  (N*(HSE/M))/P P=[2; 4; 6; 8]*/
    uint32_t Q; /*  (N*(HSE/M))/Q (must be 48MHz) Q=[2...15] */
}PllStm32Config_t;


typedef struct {
    uint32_t xtall_freq_hz;
    uint32_t core_freq_hz;
//#ifdef HAS_AT32F43X
    uint32_t ms; //
    uint32_t ns; //
    uint32_t fr;
//#endif

//#ifdef HAS_AT32F413
    uint32_t pllhexdiv; // divider
    uint32_t pllmult; // mult
//#endif
}PllArtety_t;


typedef struct {
    /*SCG_PLL0CFG  SOURCE  Configures the input clock source for PLL   0 1*/
    uint8_t source;

    /*PLL Reference Clock Divider 0...31*/
    uint8_t pre_div;

    /*PLL Post Divider 0, 1, 2, 3*/
    uint8_t post_div;

    /*PLL Multiplier Multiplier = MULT bits + 1 Note: Multiplier needs to be greater than 96 (MULT needs to be greater than 95).*/
    uint16_t mult;

    /*DIVCORE After main clock select mux (2bit) Valid */
    uint8_t div_core;

    /*frequency setting error*/
    uint32_t error_hz;
}PllFc7300Config_t;


#endif /* PLL_CALC_TYPES_H */
