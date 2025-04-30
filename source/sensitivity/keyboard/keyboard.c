#include "keyboard.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "data_utils.h"
#include "fifo_array.h"
#include "log.h"
#include "ascii_const.h"
#include "utils_math.h"

#ifdef HAS_USB_DEVICE
#include "usb_device.h"
#endif

static const uint8_t KeyBoardShiftKey[] = {
    '\0', '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\0', '\0', '\0', 'Q', 'W',
    'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '|', '\0', 'A', 'S', 'D', 'F', 'G', 'H', 'J',
    'K', 'L', ':', '"', '\0', '\n', '\0', '\0', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};

static const uint8_t KeyBoardKey[] = {
    '\0',
    '`',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '-',
    '=',
    '\0',
    '\b',// '\r'
    '\t', 'q',
    'w',
    'e', 'r', 't', 'y', 'u', 'i', 'o',
    'p', '[', ']', '\0', '\0', 'a', 's',
    'd', 'f', 'g', 'h', 'j',
    'k', 'l', ';', '\'', '\\', '\n', '\0',
    '\0', 'z', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '/', '\0',
    '\0', '\0', '\0', '\0', ' ', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\r', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '7', '4', '1', '\0',
    '/', '8', '5', '2', '0', '*', '9',
    '6', '3', '.', '-', '+', '\0', '\n',
    '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0'};

static const char UpperCaseCharsLUT[] = {'~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 'Q', 'W', 'E',
                                         'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 'A', 'S', 'D', 'F', 'G', 'H', 'J',
                                         'K', 'L', ':', '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', '"'};

bool char_is_upper_case(uint8_t letter) {
    bool res = false;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(UpperCaseCharsLUT);
    for(i = 0; i < cnt; i++) {
        if(letter == UpperCaseCharsLUT[i]) {
            res = true;
            break;
        }
    }
    return res;
}

static const uint8_t KeyBoardCodes[] = {
    0, 0, 0, 0, 31, 50, 48, 33, 19, 34, 35,
    36, 24, 37, 38, 39, 52, 51, 25, 26, 17,
    20, 32, 21, 23, 49, 18, 47, 22, 46, 2,
    3, /* 0x10 - 0x1F */    4, 5, 6, 7, 8, 9, 10, 11, 43,
    110, 15, 16, 61, 12, 13, 27, /* 0x20 - 0x2F */  28, 29, 42,
	40, 41, 1, 53, 54, 55, 30, 112, 113, 114, 115, 116, 117, /* 0x30 - 0x3F */
    118, 119, 120, 121, 122, 123, 124, 125, 126, 75, 80, 85, 76, 81, 86, 89, /* 0x40 - 0x4F */
    79, 84, 83, 90, 95, 100, 105, 106, 108, 93, 98, 103, 92, 97, 102, 91, /* 0x50 - 0x5F */
    96, 101, 99, 104, 45, 129, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 0x60 - 0x6F */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 0x70 - 0x7F */
    0, 0, 0, 0, 0, 107, 0, 56, 0, 0, 0, 0, 0, 0, 0, 0, /* 0x80 - 0x8F */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 0x90 - 0x9F */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 0xA0 - 0xAF */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 0xB0 - 0xBF */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 0xC0 - 0xCF */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 0xD0 - 0xDF */
    58, 44, 60, 127, 64, 57, 62, 128                                          /* 0xE0 - 0xE7 */
};

// Tesr in 2a=42-> backspase ASCII_BACKSPACE 0x08
uint8_t KeyCode2Char(const KeyBoard_t* const info) {
    uint8_t output =0;
    uint8_t temp = 0;
    if((info->modifier.left_shift != 0U) || (info->modifier.right_shift != 0U)) {
        temp =    KeyBoardCodes[info->key_code[0]] ;
        output = KeyBoardShiftKey[      temp   ];
    } else {
        temp = KeyBoardCodes[info->key_code[0]];
        output = KeyBoardKey[temp];
    }
    LOG_DEBUG(SYS, "KeyCode:0x%x,Temp:0x%x,Ascii:0x%x", info->key_code[0],temp,output);
    return output;
}

bool key_is_valid(const KeyBoard_t* const key_code) {
    bool res = false;
    if(key_code) {
        uint32_t sum = sum_calc_u8(key_code->key_code, 6);
        if(sum) {
            res = true;
        } else {
            if(key_code->modifier.byte) {
                res = true;
            }
        }
    }
    return res;
}

/*Just for test*/
KeyBoard_t Char2KeyCode(uint8_t letter) {
    KeyBoard_t key_code = {0};
    uint32_t try_code = 0;
    LOG_DEBUG(KEYBOARD, "Convert [%c] to KeyBoardKey", letter);

    key_code.modifier.left_shift = char_is_upper_case((int)letter);
    for(try_code = 0; try_code < 256; try_code++) {
        key_code.key_code[0] = (uint8_t)try_code;
        uint8_t try_letter = KeyCode2Char(&key_code);
        if(try_letter == letter) {
            break;
        }
    }
    return key_code;
}

bool keyboard_press_code(uint8_t keycode, uint32_t time_out_ms) {
    bool res = false;
#ifdef HAS_USB_DEVICE
    KeyBoard_t keyCode = {0};
    keyCode.modifier.byte = 0;
    keyCode.key_code[0] = keycode;

    res = usb_dev_press_key(keyCode, time_out_ms);
    if(false == res) {
        LOG_ERROR(KEYBOARD, "SendKeyCodeErr");
    }
#endif
    return res;
}

bool key_board_backspace(uint32_t num, uint32_t time_out_ms) {
    bool res = false;
    if(num) {
        res = true;
        uint32_t i = 0;
        for(i = 0; i < num; i++) {
            res = keyboard_press_code(KEY_CODE_BACKSPACE, time_out_ms) && res;
            if(false == res) {
                LOG_ERROR(KEYBOARD, "SendBackSpaceErr %u", i);
            }
        }
    }
    return res;
}

bool keyboard_init(void) {
    bool res = true;
    LOG_INFO(KEYBOARD, "Init");
    return res;
}

bool keyboard_proc(void) {
    bool res = true;
    LOG_PARN(KEYBOARD, "Proc");
    /*Contol 3 xxxxLock LEDS*/
    return res;
}


KeyBoardKeyCode_t AsicCodeToKeyBoardKeyCode(uint8_t ascii_code){
    KeyBoardKeyCode_t KeyCode=KEY_CODE_NO;
     switch(ascii_code){
        case ASCII_ESC: KeyCode=KEY_CODE_ESCAPE;break;
        case ASCII_ENTER: KeyCode=KEY_CODE_ENTER_LEFT ;break;
        case ASCII_LINE_FEED: KeyCode=KEY_CODE_ENTER_RIGHT;break;
        case ASCII_BACKSPACE: KeyCode=KEY_CODE_BACKSPACE; break;
        case ASCII_TAB: KeyCode=KEY_CODE_TAB ;break;
    }
     return KeyCode;
}
