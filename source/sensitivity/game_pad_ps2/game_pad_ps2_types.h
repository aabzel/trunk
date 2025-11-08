#ifndef GAME_PAD_PS2_TYPES_H
#define GAME_PAD_PS2_TYPES_H

#include "std_includes.h"
#include "game_pad_ps2_const.h"
#include "gpio_types.h"

typedef union {
    uint16_t word;
    struct{
        uint8_t R1 :1;       /* bit:0  */
        uint8_t R2 :1;       /* bit:1  */
        uint8_t R3 :1;       /* bit:2  */

        uint8_t L1 :1;       /* bit:3  */
        uint8_t L2 :1;       /* bit:4  */
        uint8_t L3 :1;       /* bit:5  */

        uint8_t UP :1;       /* bit:6  */
        uint8_t DOWN :1;     /* bit:7  */
        uint8_t LEFT :1;     /* bit:8  */
        uint8_t RIGHT :1;    /* bit:9  */

        uint8_t SELECT :1;    /* bit:10  */
        uint8_t START :1;     /* bit:11  */
        uint8_t TRIANGLE :1;  /* bit:12  */
        uint8_t ROUND :1;     /* bit:13  */
        uint8_t SQUARE :1;    /* bit:14  */
        uint8_t X :1;         /* bit:15  */

    };
}GamePadPs2KeyData_t;

typedef struct {
    uint8_t pss_rx;
    uint8_t pss_ry;
    uint8_t pss_lx;
    uint8_t pss_ly;
    GamePadPs2KeyData_t KeyData;
    GamePadPs2Mode_t mode;
}GamePadPs2Data_t;


typedef union {
    uint8_t byte;
    struct {
        uint8_t SELECT :1;
        uint8_t L3 :1;
        uint8_t R3 :1;
        uint8_t START :1;
        uint8_t UP :1;
        uint8_t RIGHT :1;
        uint8_t DOWN :1;
        uint8_t LEFT :1;
    };
}GamePadPs2Data3Doc_t;


/*
 * R2      byte4 bit6
 * L1      byte4 bit7
 * R1      byte5 bit0
 * X        byte5 bit3
 * O        byte5 bit2
 * square   byte5 bit4
 * TRIANGLE byte5 bit2
 * right         byte bit
 * left         byte bit
 * up         byte bit
 * down        byte bit
 *         byte bit
 *         byte bit
 * */
/*real button bit array*/
typedef union {
    uint8_t byte;
    struct {
        uint8_t DOWN :1;     /* bit:0  */
        uint8_t RIGHT :1;    /* bit:1  */
        uint8_t LEFT :1;     /* bit:2  */
        uint8_t UP :1;       /* bit:3  */
        uint8_t SELECT :1;   /* bit:4 real */
        uint8_t L3 :1;       /* bit:5 real */
        uint8_t R3 :1;       /* bit:6 real */
        uint8_t START :1;    /* bit:7 real  */
    };
}GamePadPs2Data3_t;

typedef union {
    uint8_t byte;
    struct{
        uint8_t SQUARE :1;
        uint8_t X :1;
        uint8_t ROUND :1;
        uint8_t TRIANGLE :1;
        uint8_t R1 :1;
        uint8_t L1 :1;
        uint8_t R2 :1;
        uint8_t L2 :1;
    };
}GamePadPs2Data4Doc_t;

/*
 * up         byte4 bit0
 * right         byte4 bit1
 * down        byte4 bit2
 * left         byte4 bit3
 * L2        byte4 bit5
 * R2      byte4 bit6
 * L1      byte4 bit7

 * */
typedef union {
    uint8_t byte;
    struct{
        uint8_t UP :1;      /* bit:0  */
        uint8_t RIGHT :1;   /* bit:1  */
        uint8_t DOWN :1;    /* bit:2  */
        uint8_t LEFT :2;    /* bit:4-3  */
        uint8_t L2 :1;      /* bit:5  */
        uint8_t R2 :1;      /* bit:6  */
        uint8_t L1 :1;      /* bit:7  */
    };
}GamePadPs2Data4_t;


/*
  R1       byte5 bit0
  TRIANGLE byte5 bit1
  O        byte5 bit2
  X        byte5 bit3
  square   byte5 bit4
 */

typedef union {
    uint8_t byte;
    struct{
        uint8_t R1 :1;        /* bit:0  real */
        uint8_t TRIANGLE :1;  /* bit:1  real */
        uint8_t ROUND :1;     /* bit:2  real */
        uint8_t X :1;         /* bit:3   real */
        uint8_t SQUARE :2;    /* bit:5-4  real*/
        uint8_t RES1 :1;      /* bit:6  */
        uint8_t RES2 :1;      /* bit:7  */
    };
}GamePadPs2Data5_t;

typedef union {
    uint8_t byte;
    uint8_t pss_rx;
}GamePadPs2PssRX_t;

typedef union {
    uint8_t byte;
    uint8_t pss_ry;
}GamePadPs2PssRY_t;

typedef union {
    uint8_t byte;
    uint8_t pss_lx;
}GamePadPs2PssLX_t;

typedef union {
    uint8_t byte;
    uint8_t pss_ly;
}GamePadPs2PssLY_t;

typedef union {
    uint8_t buff[9];
    struct {
        uint8_t idle;
        uint8_t ID;
        uint8_t resp;
        GamePadPs2Data3Doc_t Data3;
        GamePadPs2Data4Doc_t Data4;
        uint8_t pss_rx;
        uint8_t pss_ry;
        uint8_t pss_lx;
        uint8_t pss_ly;
    };
}GamePadPs2RxDataDoc_t;

typedef union {
    uint8_t buff[9];
    struct {
        uint8_t idle;
        uint8_t ID;
        uint8_t resp;
        GamePadPs2Data3_t Data3;
        GamePadPs2Data4_t Data4;
        GamePadPs2Data5_t Data5;
        int8_t pss_rx;
        int8_t pss_ry;
        int8_t pss_lx;

        //uint8_t pss_rx;
    };
}GamePadPs2RxData_t;

typedef union {
    uint8_t buff[9];
    struct {
        uint8_t preamble;    /* 0  0x01  */
        uint8_t cmd;         /* 1  0x42 */
        uint8_t idle1;       /* 2  0x00 */
        uint8_t motor_right; /* 3  motor1 */
        uint8_t motor_left;  /* 4  motor2 */
        uint8_t idle4[4];    /*  */
    };
}GamePadPs2TxData_t;

#define GAME_PAD_PS2_COMMON_VARIABLES     \
    char* name;                           \
    uint8_t num;                          \
    uint8_t spi_num;                      \
    Pad_t ChipSelect;                     \
    bool valid;

typedef struct {
    GAME_PAD_PS2_COMMON_VARIABLES
}GamePadPs2Config_t;

typedef struct {
    GAME_PAD_PS2_COMMON_VARIABLES
    bool init;
    GamePadPs2Data_t DataPrev;
    GamePadPs2Data_t Data;
    GamePadPs2TxData_t TxData;
    GamePadPs2RxData_t RxData;
    GamePadPs2RxData_t RxDataPrev;
    uint32_t spin;
}GamePadPs2Handle_t;


#endif /* GAME_PAD_PS2_TYPES_H */
