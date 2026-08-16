#include "wav_player_isr.h"

bool I2xTxHalfCallbackCustom(I2sHandle_t* const Node) {
    WavPlayerInstance[0].state = WAV_PLAYER_STATE_PLAY_PART2;
    WavPlayerInstance[0].action = WAV_PLAYER_ACTION_LOAD_PART1;
    return true;
}

bool I2xTxDoneCallbackCustom(I2sHandle_t* const Node) {
    WavPlayerInstance[0].state = WAV_PLAYER_STATE_PLAY_PART1;
    WavPlayerInstance[0].action = WAV_PLAYER_ACTION_LOAD_PART2;
    return true;
}

