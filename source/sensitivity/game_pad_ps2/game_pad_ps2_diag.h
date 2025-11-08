#ifndef GAME_PAD_PS2_DIAG_H
#define GAME_PAD_PS2_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "game_pad_ps2_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_GAME_PAD_PS2
#error "+HAS_GAME_PAD_PS2"
#endif

#ifndef HAS_GAME_PAD_PS2_DIAG
#error "+HAS_GAME_PAD_PS2_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool game_pad_ps2_diag_one(uint8_t num);
bool game_pad_ps2_raw_reg_diag(uint8_t num);
bool game_pad_ps2_diag(void);
const char* GamePadPs2MotorToStr(const GamePadPs2Motor_t motor);
const char* GamePadPs2ConfigToStr(const GamePadPs2Config_t* const Config);
const char* GamePadPs2NodeToStr(const GamePadPs2Handle_t* const Node);
const char* GamePadPs2DataToStr(const GamePadPs2Data_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* GAME_PAD_PS2_DIAG_H  */
