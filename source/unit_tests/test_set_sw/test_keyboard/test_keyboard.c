#include "test_keyboard.h"

#include <string.h>

#include "key_board_drv.h"
#include "keyboard.h"
#include "log.h"
#include "unit_test_check.h"

bool test_keyboard_special_codes(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(KEYBOARD, LOG_LEVEL_DEBUG);
    KeyBoard_t KeyCode;

    KeyCode = Char2KeyCode('\n');
    EXPECT_EQ(0x28, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('?');
    EXPECT_EQ(0x38, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('/');
    EXPECT_EQ(0x38, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('<');
    EXPECT_EQ(0x36, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('>');
    EXPECT_EQ(0x37, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('.');
    EXPECT_EQ(0x37, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode(',');
    EXPECT_EQ(0x36, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('"');
    EXPECT_EQ(0x34, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('\'');
    EXPECT_EQ(0x34, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode(':');
    EXPECT_EQ(0x33, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode(';');
    EXPECT_EQ(0x33, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('|');
    EXPECT_EQ(0x31, KeyCode.key_code[0]);

    char quote[] = "'";
    KeyCode = Char2KeyCode(quote[0]);
    EXPECT_EQ(0x34, KeyCode.key_code[0]);

    char text[] = "\\";
    KeyCode = Char2KeyCode(text[0]);
    EXPECT_EQ(0x32, KeyCode.key_code[0]); /*Explore It*/

    KeyCode = Char2KeyCode('}');
    EXPECT_EQ(0x30, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode(']');
    EXPECT_EQ(0x30, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('{');
    EXPECT_EQ(0x2F, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('[');
    EXPECT_EQ(0x2F, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('+');
    EXPECT_EQ(0x2E, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('=');
    EXPECT_EQ(0x2E, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('-');
    EXPECT_EQ(0x2d, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('_');
    EXPECT_EQ(0x2D, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode(' ');
    EXPECT_EQ(0x2C, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('\t');
    EXPECT_EQ(0x2B, KeyCode.key_code[0]);

    set_log_level(KEYBOARD, LOG_LEVEL_INFO);
    return res;
}

bool test_keyboard_lower_codes(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(KEYBOARD, LOG_LEVEL_DEBUG);
    bool res = true;
    KeyBoard_t KeyCode;

    KeyCode = Char2KeyCode('a');
    EXPECT_EQ(0x04, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('b');
    EXPECT_EQ(0x05, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('c');
    EXPECT_EQ(0x06, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('d');
    EXPECT_EQ(0x07, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('e');
    EXPECT_EQ(0x08, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('f');
    EXPECT_EQ(0x09, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('g');
    EXPECT_EQ(0x0a, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('h');
    EXPECT_EQ(0x0b, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('i');
    EXPECT_EQ(0x0c, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('j');
    EXPECT_EQ(0x0d, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('k');
    EXPECT_EQ(0x0e, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('l');
    EXPECT_EQ(0x0f, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('m');
    EXPECT_EQ(0x10, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('n');
    EXPECT_EQ(0x11, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('o');
    EXPECT_EQ(0x12, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('p');
    EXPECT_EQ(0x13, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('q');
    EXPECT_EQ(0x14, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('r');
    EXPECT_EQ(0x15, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('s');
    EXPECT_EQ(0x16, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('t');
    EXPECT_EQ(0x17, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('u');
    EXPECT_EQ(0x18, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('v');
    EXPECT_EQ(0x19, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('w');
    EXPECT_EQ(0x1a, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('x');
    EXPECT_EQ(0x1b, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('y');
    EXPECT_EQ(0x1c, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('z');
    EXPECT_EQ(0x1d, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('1');
    EXPECT_EQ(0x1e, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('2');
    EXPECT_EQ(0x1f, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('3');
    EXPECT_EQ(0x20, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('4');
    EXPECT_EQ(0x21, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('5');
    EXPECT_EQ(0x22, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('6');
    EXPECT_EQ(0x23, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('7');
    EXPECT_EQ(0x24, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('8');
    EXPECT_EQ(0x25, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('9');
    EXPECT_EQ(0x26, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('0');
    EXPECT_EQ(0x27, KeyCode.key_code[0]);

    set_log_level(KEYBOARD, LOG_LEVEL_INFO);
    return res;
}

bool test_keyboard_upper_codes(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(KEYBOARD, LOG_LEVEL_DEBUG);
    bool res = true;
    KeyBoard_t KeyCode;

    KeyCode = Char2KeyCode('A');
    EXPECT_EQ(0x04, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('B');
    EXPECT_EQ(0x05, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('C');
    EXPECT_EQ(0x06, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('D');
    EXPECT_EQ(0x07, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('E');
    EXPECT_EQ(0x08, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('F');
    EXPECT_EQ(0x09, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('G');
    EXPECT_EQ(0x0A, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('H');
    EXPECT_EQ(0x0B, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('I');
    EXPECT_EQ(0x0C, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('J');
    EXPECT_EQ(0x0D, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('K');
    EXPECT_EQ(0x0E, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('L');
    EXPECT_EQ(0x0F, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('M');
    EXPECT_EQ(0x10, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('N');
    EXPECT_EQ(0x11, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('O');
    EXPECT_EQ(0x12, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('P');
    EXPECT_EQ(0x13, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('Q');
    EXPECT_EQ(0x14, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('R');
    EXPECT_EQ(0x15, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('S');
    EXPECT_EQ(0x16, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('T');
    EXPECT_EQ(0x17, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('U');
    EXPECT_EQ(0x18, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('V');
    EXPECT_EQ(0x19, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('W');
    EXPECT_EQ(0x1A, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('X');
    EXPECT_EQ(0x1B, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('Y');
    EXPECT_EQ(0x1C, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('Z');
    EXPECT_EQ(0x1D, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('\t');
    EXPECT_EQ(0x2B, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode(' ');
    EXPECT_EQ(0x2C, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('_');
    EXPECT_EQ(0x2D, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('=');
    EXPECT_EQ(0x2E, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('!');
    EXPECT_EQ(0x1E, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('@');
    EXPECT_EQ(0x1F, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('#');
    EXPECT_EQ(0x20, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('$');
    EXPECT_EQ(0x21, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('%');
    EXPECT_EQ(0x22, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('^');
    EXPECT_EQ(0x23, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('&');
    EXPECT_EQ(0x24, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('*');
    EXPECT_EQ(0x25, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('(');
    EXPECT_EQ(0x26, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode(')');
    EXPECT_EQ(0x27, KeyCode.key_code[0]);

    set_log_level(KEYBOARD, LOG_LEVEL_INFO);
    return res;
}

bool test_keyboard_codes(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(KEYBOARD, LOG_LEVEL_DEBUG);
    bool res = true;
    KeyBoard_t KeyCode;

    KeyCode = Char2KeyCode('\t');
    EXPECT_EQ(0x2B, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode(' ');
    EXPECT_EQ(0x2C, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('_');
    EXPECT_EQ(0x2D, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('=');
    EXPECT_EQ(0x2E, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('!');
    EXPECT_EQ(0x1E, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('@');
    EXPECT_EQ(0x1F, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('#');
    EXPECT_EQ(0x20, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('$');
    EXPECT_EQ(0x21, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('%');
    EXPECT_EQ(0x22, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('^');
    EXPECT_EQ(0x23, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('&');
    EXPECT_EQ(0x24, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('*');
    EXPECT_EQ(0x25, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode('(');
    EXPECT_EQ(0x26, KeyCode.key_code[0]);

    KeyCode = Char2KeyCode(')');
    EXPECT_EQ(0x27, KeyCode.key_code[0]);

    set_log_level(KEYBOARD, LOG_LEVEL_INFO);
    return res;
}

bool test_keyboard_codes2(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(KEYBOARD, LOG_LEVEL_DEBUG);
    bool res = true;

    KeyCodeInfo_t* KeyCodeInfo = NULL;
    KeyCodeInfo = Ascii2KeyInfo('(');
    EXPECT_NE(NULL, KeyCodeInfo);
    EXPECT_EQ(0x26, KeyCodeInfo->key_code);

    KeyCodeInfo = Ascii2KeyInfo(')');
    EXPECT_NE(NULL, KeyCodeInfo);
    EXPECT_EQ(0x27, KeyCodeInfo->key_code);

    set_log_level(KEYBOARD, LOG_LEVEL_INFO);
    return res;
}

bool test_keyboard_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(KEYBOARD, LOG_LEVEL_DEBUG);
    EXPECT_EQ(8, sizeof(KeyBoard_t));
    set_log_level(KEYBOARD, LOG_LEVEL_INFO);
    return res;
}
