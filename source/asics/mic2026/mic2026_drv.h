
#ifndef MIC2026_DRV_H
#define MIC2026_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "mic2026_types.h"
#include "mic2026_config.h"

#ifdef HAS_MIC2026_DIAG
#include "mic2026_diag.h"
#endif

#ifndef HAS_MIC2026
#error "+HAS_MIC2026"
#endif

Mic2026ChannelVal_t* GetRelyNode(Mic2026Channel_t ChanId);
Mic2026ChannelConfig_t* GetConfigRelyNode(Mic2026Channel_t ChanId);
GpioLogicLevel_t mic2026_get_channel_ctrl(Mic2026Channel_t chan);
bool mic2026_set_channel_ctrl(Mic2026Channel_t chan, GpioLogicLevel_t on);
bool mic2026_init(void);
bool mic2026_proc(void);

#endif /* MIC2026_DRV_H */
