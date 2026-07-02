#ifndef WAV_PLAYER_CONST_H
#define WAV_PLAYER_CONST_H

#include "time_mcal.h"
#include "wav_player_dep.h"

#define WAV_PLAYER_VERSION 2
#define WAV_PLAYER_POLL_PERIOD_US 1

typedef enum {
    WAV_PLAYER_STATE_UNDEF = 0,
    WAV_PLAYER_STATE_IDLE ,
    WAV_PLAYER_STATE_PLAY_PART1 ,
    WAV_PLAYER_STATE_PLAY_PART2 ,
    WAV_PLAYER_STATE_CNT,
}WavPlayerState_t;

#endif /* WAV_PLAYER_CONST_H */
