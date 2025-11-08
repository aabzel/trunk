#ifndef GAME_PAD_PS2_CONST_H
#define GAME_PAD_PS2_CONST_H

#include "time_mcal.h"
#include "game_pad_ps2_dep.h"

#define GAME_PAD_PS2_VERSION "3"
#define GAME_PAD_PS2_POLL_PERIOD_US MSEC_2_USEC(1)
#define GAME_PAD_PS2_PREAMBLE  0x01

#define GAME_PAD_PS2_RX_OK 0x5A


typedef enum {
    GAME_PAD_PS2_MODE_DISCRETE = 0x7C,
    GAME_PAD_PS2_MODE_CONTINUOUS = 0x18 ,
    GAME_PAD_PS2_MODE_UNDEF = 0,
}GamePadPs2Mode_t;



typedef enum {
    GAME_PAD_PS2_MOTOR_LEFT  = 1,
    GAME_PAD_PS2_MOTOR_RIGHT = 2,

    GAME_PAD_PS2_MOTOR_UNDEF = 0,
}GamePadPs2Motor_t;

typedef enum {
    GAME_PAD_PS2_ID_GREEN = 0x41,
    GAME_PAD_PS2_ID_RED = 0x73,
    GAME_PAD_PS2_ID_UNDEF = 0,
}GamePadPs2Id_t;

typedef enum {
    GAME_PAD_PS2_CMD_GET_DATA = 0x42, /*Polling */
    //GAME_PAD_PS2_CMD_GET_DATA = 0x43,
    //GAME_PAD_PS2_CMD_GET_DATA = 0x4D,
    //GAME_PAD_PS2_CMD_GET_DATA = 0x44,
    GAME_PAD_PS2_CMD_UNDEF = 0,
}GamePadPs2Cmd_t;

#endif /* GAME_PAD_PS2_CONST_H */
