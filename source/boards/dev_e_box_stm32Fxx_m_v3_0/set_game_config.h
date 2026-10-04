#ifndef SET_GAME_BOARD_H
#define SET_GAME_BOARD_H

#include "set_game_types.h"

extern const SetGameConfig_t SetGameConfig[];
extern SetGameHandle_t SetGameInstance[];

uint32_t set_game_get_cnt(void);

#endif /*SET_GAME_BOARD_H*/
