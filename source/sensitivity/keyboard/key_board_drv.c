#include "key_board_drv.h"

#include "data_utils.h"
#include "keyboard_types.h"
#include "log.h"

KeyBoard_t keyBoardCode = {
    .modifier.byte = 0,
    .res = 0,
    .key_code[0] = 0,
    .key_code[1] = 0,
    .key_code[2] = 0,
    .key_code[3] = 0,
    .key_code[4] = 0,
    .key_code[5] = 0,
};

static const KeyCodeInfo_t KeyCodeInfo[] = {
    {
        .key_code = 4,
        .letter = 'a',
        .name = "a",
    },
    {
        .key_code = 5,
        .letter = 'b',
        .name = "",
    },
    {
        .key_code = 6,
        .letter = 'c',
        .name = "",
    },
    {
        .key_code = 7,
        .letter = 'd',
        .name = "",
    },
    {
        .key_code = 8,
        .letter = 'e',
        .name = "",
    },
    {
        .key_code = 9,
        .letter = 'f',
        .name = "",
    },
    {
        .key_code = 0xA,
        .letter = 'g',
        .name = "",
    },
    {
        .key_code = 0xB,
        .letter = 'h',
        .name = "",
    },
    {
        .key_code = 0xC,
        .letter = 'i',
        .name = "",
    },

    {
        .key_code = 0x0d,
        .letter = 'j',
        .name = "",
    },
    {
        .key_code = 0xE,
        .letter = 'k',
        .name = "",
    },
    {
        .key_code = 0xF,
        .letter = 'l',
        .name = "",
    },
    {
        .key_code = 0x10,
        .letter = 'm',
        .name = "",
    },
    {
        .key_code = 0x11,
        .letter = 'n',
        .name = "",
    },
    {
        .key_code = 0x12,
        .letter = 'o',
        .name = "",
    },
    {
        .key_code = 0x13,
        .letter = 'p',
        .name = "",
    },
    {
        .key_code = 0x14,
        .letter = 'q',
        .name = "",
    },
    {
        .key_code = 0x15,
        .letter = 'r',
        .name = "",
    },
    {
        .key_code = 0x16,
        .letter = 's',
        .name = "",
    },
    {
        .key_code = 0x17,
        .letter = 't',
        .name = "",
    },
    {
        .key_code = 0x18,
        .letter = 'u',
        .name = "",
    },
    {
        .key_code = 0x19,
        .letter = 'v',
        .name = "",
    },
    {
        .key_code = 0x1a,
        .letter = 'w',
        .name = "",
    },
    {
        .key_code = 0x1b,
        .letter = 'x',
        .name = "",
    },
    {
        .key_code = 0x1c,
        .letter = 'y',
        .name = "",
    },
    {
        .key_code = 0x1d,
        .letter = 'z',
        .name = "",
    },
    {
        .key_code = 0x1e,
        .letter = '1',
        .name = "",
    },
    {
        .key_code = 0x1e,
        .letter = '!',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x1f,
        .letter = '2',
        .name = "",
    },
    {
        .key_code = 0x1f,
        .letter = '@',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x20,
        .letter = '3',
        .name = "",
    },
    {
        .key_code = 0x20,
        .letter = '#',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x21,
        .letter = '4',
        .name = "",
    },
    {
        .key_code = 0x21,
        .letter = '$',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x22,
        .letter = '5',
        .name = "",
    },
    {
        .key_code = 0x22,
        .letter = '%',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x23,
        .letter = '6',
        .name = "",
    },
    {
        .key_code = 0x23,
        .letter = '^',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x24,
        .letter = '7',
        .name = "",
    },
    {
        .key_code = 0x24,
        .letter = '&',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x25,
        .letter = '8',
        .name = "",
    },
    {
        .key_code = 0x25,
        .letter = '*',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x26,
        .letter = '(',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x26,
        .letter = '9',
        .name = "",
    },
    {
        .key_code = 0x27,
        .letter = ')',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x28,
        .letter = 0x0A,
        .name = "Enter",
    }, /**/
    {
        .key_code = 0x29,
        .letter = 0x1B,
        .name = "Esc",
    },
    {
        .key_code = 0x2A,
        .letter = 0x08,
        .name = "BackSpace",
    },
    {
        .key_code = 0x2B,
        .letter = 0x09,
        .name = "Tab",
    },
    {
        .key_code = 0x2C,
        .letter = 0x20,
        .name = "Spacebar",
    },
    {
        .key_code = 0x2D,
        .letter = '-',
        .name = "",
    },
    {
        .key_code = 0x2d,
        .letter = '_',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x2e,
        .letter = '+',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x2E,
        .letter = '=',
        .name = "",
    },
    {
        .key_code = 0x2F,
        .letter = '[',
        .name = "",
    },
    {
        .key_code = 0x2f,
        .letter = '{',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x30,
        .letter = ']',
        .name = "",
    },
    {
        .key_code = 0x30,
        .letter = '}',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x31,
        .letter = '\\',
        .name = "",
    },
    {
        .key_code = 0x35,
        .letter = '~',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x32,
        .letter = '|',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x33,
        .letter = ';',
        .name = "",
    },
    {
        .key_code = 0x34,
        .letter = '"',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x34,
        .letter = '\'',
        .name = "",
    },
    //{.key_code=0x35, .letter='\'',  .name="", },
    {
        .key_code = 0x33,
        .letter = ':',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x38,
        .letter = '?',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x36,
        .letter = '<',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x36,
        .letter = ',',
        .name = "",
    },
    {
        .key_code = 0x37,
        .letter = '.',
        .name = "",
    },
    {
        .key_code = 0x37,
        .letter = '>',
        .name = "",
        .is_upper_case = true,
    },
    {
        .key_code = 0x38,
        .letter = '/',
        .name = "",
    },
//{.key_code=0x39, .letter=,  .name="Caps Lock", },
//{.key_code=0x3a, .letter=,  .name="F1", },
#if 0
{.key_code=0x3b, .letter=,  .name="F2", },
{.key_code=0x3c, .letter=,  .name="F3", },
{.key_code=0x3d, .letter=,  .name="F4", },
{.key_code=0x3e, .letter=,  .name="F5", },
{.key_code=0x3f, .letter=,  .name="F6", },
{.key_code=0x40, .letter=,  .name="F7", },
{.key_code=0x41, .letter=,  .name="F8", },
{.key_code=0x42, .letter=,  .name="F9", },
{.key_code=0x43, .letter=,  .name="F10", },
{.key_code=0x44, .letter=,  .name="F11", },
{.key_code=0x45, .letter=,  .name="F12", },
{.key_code=0x46, .letter=,  .name="PrintScree", },
{.key_code=0x47, .letter=,  .name="ScrollLock", },
{.key_code=0x48, .letter=,  .name="Pause", },
{.key_code=0x49, .letter=,  .name="Insert", },
{.key_code=0x4a, .letter=,  .name="Home", },
{.key_code=0x4b, .letter=,  .name="PageUp", },
{.key_code=0x4c, .letter=,  .name="Delete", },
{.key_code=0x4d, .letter=,  .name="End", },
{.key_code=0x4e, .letter=,  .name="PageDown", },
{.key_code=0x4f, .letter=,  .name="RightArrow", },
{.key_code=0x50, .letter=,  .name="LeftArrow", },
{.key_code=0x51, .letter=,  .name="DownArrow", },
{.key_code=0x52, .letter=,  .name="UpArrow", },
{.key_code=0x53, .letter=,  .name="NumLock", },
#endif
    {
        .key_code = 0x54,
        .letter = '/',
        .name = "",
    },
    {
        .key_code = 0x55,
        .letter = '*',
        .name = "",
    },
    {
        .key_code = 0x56,
        .letter = '-',
        .name = "",
    },
    {
        .key_code = 0x57,
        .letter = '+',
        .name = "",
    },
    {
        .key_code = 0x58,
        .letter = 0x0A,
        .name = "Enter",
    },
    {
        .key_code = 0x59,
        .letter = '1',
        .name = "",
    },
    {
        .key_code = 0x5A,
        .letter = '2',
        .name = "",
    },
    {
        .key_code = 0x5b,
        .letter = '3',
        .name = "",
    },
    {
        .key_code = 0x5c,
        .letter = '4',
        .name = "",
    },
    {
        .key_code = 0x5d,
        .letter = '5',
        .name = "",
    },
    {
        .key_code = 0x5e,
        .letter = '6',
        .name = "",
    },
    {
        .key_code = 0x2d,
        .letter = '_',
        .name = "UnderScore)",
        .is_upper_case = true,
    },
    {
        .key_code = 0x5f,
        .letter = '7',
        .name = "",
    },
    {
        .key_code = 0x60,
        .letter = '8',
        .name = "",
    },
    {
        .key_code = 0x61,
        .letter = '9',
        .name = "",
    },
    {
        .key_code = 0x62,
        .letter = '0',
        .name = "",
    },
    {
        .key_code = 0x63,
        .letter = ',',
        .name = "",
    },
    {
        .key_code = 0x64,
        .letter = '|',
        .name = "",
        .is_upper_case = true,
    },
    //{.key_code=0x64, .letter=,  .name="", },
};

uint8_t Ascii2KeyCode(uint8_t ascii_code) {
    uint8_t key_code = 0x38;
    uint32_t i = 0;
    bool res = false;
    for(i = 0; i < ARRAY_SIZE(KeyCodeInfo); i++) {
        if(KeyCodeInfo[i].letter == ascii_code) {
            key_code = KeyCodeInfo[i].key_code;
            res = true;
            LOG_DEBUG(KEYBOARD, "Spot cod [%c]=0x%x->0x%x", ascii_code, ascii_code, key_code);
            break;
        }
    }
    if(false == res) {
        LOG_ERROR(KEYBOARD, "LackKeyCode [%c]=0x%x", ascii_code, ascii_code);
    }
    return key_code;
}

const KeyCodeInfo_t* Ascii2KeyInfo(uint8_t ascii_code) {
    const KeyCodeInfo_t* pKeyCodeInfo = NULL;
    uint32_t i = 0;
    bool res = false;
    for(i = 0; i < ARRAY_SIZE(KeyCodeInfo); i++) {
        if(KeyCodeInfo[i].letter == ascii_code) {
            pKeyCodeInfo = &KeyCodeInfo[i];
            LOG_DEBUG(KEYBOARD, "Spot cod [%c]=0x%x->0x%x", ascii_code, ascii_code, KeyCodeInfo[i].key_code);
            res = true;
            break;
        }
    }
    if(false == res) {
        LOG_ERROR(KEYBOARD, "LackKeyCode [%c]=0x%x", ascii_code, ascii_code);
    }
    return pKeyCodeInfo;
}
