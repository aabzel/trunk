#ifndef LTR390_REGISTER_TYPES_H
#define LTR390_REGISTER_TYPES_H

#include <stdint.h>

typedef union {
    uint8_t byte;
    struct {
        uint8_t res1 : 1;  /*reserved*/
        uint8_t enable : 1;  /*ENAble*/
        uint8_t res2 : 1;  /*SDOUT High-Impedance Mode*/
        uint8_t uvs_mode : 1; /*uvs_mode*/
        uint8_t soft_reset : 1; /**/
        uint8_t res3 :3;  /*LRCLK Invert*/
    };
} Ltr390RegMainCtrl_t;


typedef union {
    uint8_t byte;
    struct {
        uint8_t rate : 3;  /* */
        uint8_t res1 : 1;  /*res*/
        uint8_t resolution : 3;  /**/
        uint8_t res2 : 1; /* */
    };
} Ltr390RegMeasRate_t;


typedef union {
    uint8_t byte;
    struct {
        uint8_t gain : 3;  /**/
        uint8_t res : 5;  /**/
    };
} Ltr390RegAlsUvsGain_t;

typedef union {
    uint8_t byte;
    struct {
        uint8_t revision : 4;  /**/
        uint8_t part_number : 4;  /**/
    };
} Ltr390RegPatrId_t;

typedef union {
    uint8_t byte;
    struct {
        uint8_t res1 : 3;  /**/
        uint8_t data_status: 1;  /**/
        uint8_t interrupt_status: 1;  /**/
        uint8_t power_on_status: 1;  /**/
        uint8_t res2: 2;  /**/
    };
} Ltr390RegMainStatus_t;

typedef union {
    uint8_t byte;
    struct {
        uint8_t res1 : 2;  /**/
        uint8_t ls_int_len: 1;  /**/
        uint8_t res2: 1;  /**/
        uint8_t ls_int_sel: 2;  /**/
        uint8_t res3: 2;  /**/
    };
} Ltr390RegIntStatus_t;


typedef union {
    uint8_t byte;
    struct {
        uint8_t res1 : 2;  /**/
        uint8_t ls_int_en: 1;  /**/
        uint8_t res2: 1;  /**/
        uint8_t ls_int_sel: 2;  /**/
        uint8_t res3: 2;  /**/
    };
} Ltr390RegIntCfg_t;

typedef union {
    uint8_t byte;
    struct {
        uint8_t res1 : 4;  /**/
        uint8_t als_uv_persist: 4;  /**/
    };
} Ltr390RegIntRst_t;


typedef union {
    uint8_t byte;
    Ltr390RegMainCtrl_t MainCtrl;
    Ltr390RegMeasRate_t MeasRate;
    Ltr390RegAlsUvsGain_t AlsUvsGain;
    Ltr390RegPatrId_t PatrId;
    Ltr390RegMainStatus_t MainStatus;
    Ltr390RegIntStatus_t IntStatus;
    Ltr390RegIntRst_t IntRst;
    Ltr390RegIntCfg_t IntCfg;
}Ltr390RegGeneral_t;

#endif /* LTR390_REGISTER_TYPES_H */
