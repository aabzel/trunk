#include "sound_recorder_isr.h"
#include "sound_recorder_config.h"

bool I2xRxHalfCallbackCustom(I2sHandle_t* const Node) {
    SoundRecorderInstance[0].state = SOUND_RECORDER_STATE_REC_PART_2;
    SoundRecorderInstance[0].action = SOUND_RECORDER_ACTION_SAVE_PART_1;
    return true;
}

bool I2xRxDoneCallbackCustom(I2sHandle_t* const Node) {
    SoundRecorderInstance[0].state = SOUND_RECORDER_STATE_REC_PART_1;
    SoundRecorderInstance[0].action = SOUND_RECORDER_ACTION_SAVE_PART_2;
    return true;
}
