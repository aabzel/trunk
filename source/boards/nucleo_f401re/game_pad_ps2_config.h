#ifndef GAME_PAD_PS2_CONFIG_H
#define GAME_PAD_PS2_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "game_pad_ps2_types.h"
#include "game_pad_ps2_dep.h"

extern const GamePadPs2Config_t GamePadPs2Config[];
extern GamePadPs2Handle_t GamePadPs2Instance[];

uint32_t game_pad_ps2_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* GAME_PAD_PS2_CONFIG_H */
