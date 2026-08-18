
#ifndef AD9833_TYPES_H
#define AD9833_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "ad9833_const.h"
#include "gpio_types.h"

typedef union {
    uint16_t word;
    struct {
        uint16_t d0 : 1;  /*d0 */
        uint16_t d1 : 1;  /*d1 */
        uint16_t d2 : 1;  /*d2 */
        uint16_t d3 : 1;  /*d3 */
        uint16_t d4 : 1;  /*d4 */
        uint16_t d5 : 1;  /*d5 */
        uint16_t d6 : 1;  /*d6 */
        uint16_t d7 : 1;  /*d7 */
        uint16_t d8 : 1;  /*d8*/
        uint16_t d9 : 1;  /*d9 */
        uint16_t d10 : 1; /*d10 */
        uint16_t d11 : 1; /*d11 */
        uint16_t d12 : 1; /*d12 */
        uint16_t d13 : 1; /*d13 */
        uint16_t d14 : 1; /*d14 */
        uint16_t d15 : 1; /*d15 */
    };

    struct {
        uint16_t freq_code14bit : 14; /* D0-D13 */
        uint16_t content : 2;         /* D14-15 */
    };

    struct {
        uint16_t res1 : 1;    /*D0 */
        uint16_t mode : 1;    /*D1 */
        uint16_t res2 : 1;    /*D2 */
        uint16_t div2 : 1;    /*D3 */
        uint16_t res3 : 1;    /*D4 */
        uint16_t opbiten : 1; /*D5 */
        uint16_t sleep12 : 1; /*D6 */
        uint16_t sleep1 : 1;  /*D7 */
        uint16_t reset : 1;   /*D8*/
        uint16_t res4 : 1;    /*D9 */
        uint16_t pselect : 1; /*D10 */
        uint16_t fselect : 1; /*D11 */
        uint16_t hlb : 1;     /*D12 */
        uint16_t b28 : 1;     /*D13 */
        uint16_t cmd : 2;     /*D14-15 */
    };

    struct {
        uint16_t code13bit : 13;            /*D12 */
        uint16_t phase_register_select : 3; /*D13-15 */
    };
} Ad9833Reg_t;

typedef struct {
    uint8_t num;
    uint8_t spi_num;
    Ad9833Reg_t RegDefault;
    Pad_t chip_select;
    bool valid;
    SignalForm_t signal_form;
    double freq_hz;
    double phase;
} Ad9833Config_t;

typedef struct {
    uint32_t freq;
    uint32_t phase;
} Ad9833Regs_t;

typedef struct {
    uint8_t num;
    uint8_t spi_num;
    SignalForm_t signal_form;
    Ad9833Regs_t Regs[2];
    bool init;
    bool valid;
    Ad9833Reg_t Reg;
} Ad9833Handle_t;

#endif /* AD9833_TYPES_H */
