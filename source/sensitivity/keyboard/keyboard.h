#ifndef KEYBOARD_H
#define KEYBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>


#include "keyboard_types.h"
#ifdef HAS_KEYBOARD_DIAG
#include "keyboard_diag.h"
#endif

#ifndef HAS_KEYBOARD
#error "+HAS_KEYBOARD"
#endif

KeyBoard_t Char2KeyCode(uint8_t letter);
uint8_t KeyCode2Char(const KeyBoard_t*const  key_code);
bool key_is_valid(const KeyBoard_t*const  key_code);
KeyBoardKeyCode_t AsicCodeToKeyBoardKeyCode(uint8_t ascii_code);
bool char_is_upper_case(uint8_t letter);
bool keyboard_init(void);
bool keyboard_proc(void);
bool key_board_backspace(uint32_t num, uint32_t time_out);
bool keyboard_press_code(uint8_t keycode, uint32_t time_out);

#ifdef __cplusplus
}
#endif

#endif /* KEYBOARD_H */
