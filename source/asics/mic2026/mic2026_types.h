#ifndef MIC2026_TYPES_H
#define MIC2026_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "mic2026_const.h"
#include "gpio_const.h"
#include "gpio_types.h"

#ifndef HAS_MIC2026
#error "+HAS_MIC2026"
#endif

typedef struct  {
    Pad_t CtrlPad;
    Pad_t FbPad;
    GpioLogicLevel_t CtrlDflt;
	Mic2026Channel_t ChanId;
    bool valid;
    char name[CHAN_NAME_SIZE];
} Mic2026ChannelConfig_t;

typedef struct  {
    GpioLogicLevelState_t CtrlPad;
    GpioLogicLevel_t FbPadVal;
    Mic2026Channel_t ChanId;
    bool valid;
} Mic2026ChannelVal_t;

typedef struct  {
	Mic2026ChannelConfig_t Chan[2];
    uint8_t num;
    bool valid;
} Mic2026Config_t;

typedef struct  {
    Mic2026ChannelVal_t ChanVal[2];
    uint8_t num;
    bool valid;
} Mic2026Handle_t;

#endif /* MIC2026_TYPES_H */
