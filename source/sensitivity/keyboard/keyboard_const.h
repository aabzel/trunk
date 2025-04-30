#ifndef KEYBOARD_CONST_H
#define KEYBOARD_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
    KEY_CODE_NO =0x00,
    KEY_CODE_BACKSPACE= 0x2A,
    KEY_CODE_DOWN =0x51,
    KEY_CODE_ESCAPE= 0x29,
    KEY_CODE_ENTER_LEFT =0x28,
    KEY_CODE_ENTER_RIGHT= 0x58,
    KEY_CODE_TAB =0x2b,
    KEY_CODE_TILDE =0x35,
    KEY_CODE_PAGE_UP =0x4b,
    KEY_CODE_PAGE_DOWN= 0x4e,
    KEY_CODE_UP =0x52,
}KeyBoardKeyCode_t;

#ifdef __cplusplus
}
#endif

#endif /* KEYBOARD_CONST_H */
