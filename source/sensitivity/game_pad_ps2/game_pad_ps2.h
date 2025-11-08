#ifndef GAME_PAD_PS2_MCAL_H
#define GAME_PAD_PS2_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "game_pad_ps2_config.h"
#include "game_pad_ps2_types.h"
#ifdef HAS_GAME_PAD_PS2_DIAG
#include "game_pad_ps2_diag.h"
#endif

/* API */
GamePadPs2Handle_t* GamePadPs2GetNode(uint8_t num);
const GamePadPs2Config_t* GamePadPs2GetConfig(uint8_t num);
bool GamePadPs2IsValidConfig(const GamePadPs2Config_t* const Config);

#ifdef HAS_GAME_PAD_PS2_CUSTOM
const GamePadPs2Info_t* GamePadPs2GetInfo(uint8_t num);
#endif

bool game_pad_ps2_mcal_init(void);
bool game_pad_ps2_init_custom(void);
bool game_pad_ps2_init_one(uint8_t num);
bool game_pad_ps2_init_common(const GamePadPs2Config_t* const Config,
                              GamePadPs2Handle_t* const Node);

bool game_pad_ps2_proc_one(uint8_t num);
bool game_pad_ps2_proc(void);

/*setters*/
bool game_pad_ps2_init_hw( uint8_t num);
bool game_pad_ps2_vibration( uint8_t num, uint8_t motor1, uint8_t motor2);
bool game_pad_ps2_write_data(uint8_t num, const uint8_t* const data, uint32_t size) ;
bool game_pad_ps2_motor_set(uint8_t num, GamePadPs2Motor_t motor, uint8_t level );
bool game_pad_ps2_tx_set(uint8_t num, uint8_t offset, uint8_t value) ;

/*getters*/

#ifdef __cplusplus
}
#endif

#endif /* GAME_PAD_PS2_MCAL_H */
