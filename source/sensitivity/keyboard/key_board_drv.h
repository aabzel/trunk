#ifndef KEY_BOARD_DRV_H
#define KEY_BOARD_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "keyboard_types.h"

extern KeyBoard_t keyBoardCode;
const KeyCodeInfo_t* Ascii2KeyInfo(uint8_t ascii_code);
uint8_t Ascii2KeyCode(uint8_t ascii_code);

#ifdef __cplusplus
}
#endif

#endif /* KEY_BOARD_DRV_H */
