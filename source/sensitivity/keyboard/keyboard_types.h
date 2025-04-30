#ifndef KEYBOARD_TYPES_H
#define KEYBOARD_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_KEYBOARD
#error "+HAS_KEYBOARD"
#endif

#include <stdbool.h>
#include <stdint.h>

#include "keyboard_const.h"

typedef union {
    uint8_t byte;
    struct {
        uint8_t left_ctrl : 1;   /*bit 0 */
        uint8_t left_shift : 1;  /*bit 1 */
        uint8_t left_alt : 1;    /*bit 2 */
        uint8_t left_gui : 1;    /*bit 3 */
        uint8_t right_ctrl : 1;  /*bit 4 */
        uint8_t right_shift : 1; /*bit 5 */
        uint8_t right_alt : 1;   /*bit 6 */
        uint8_t right_gui : 1;   /*bit 7 */
    };
} KeyModifier_t;

typedef struct {
    KeyModifier_t modifier;
    uint8_t res;
    uint8_t key_code[6];
} KeyBoard_t;

typedef struct {
    char letter;
    char* name;
    uint8_t key_code;
    bool is_upper_case;
} KeyCodeInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* KEYBOARD_TYPES_H */
