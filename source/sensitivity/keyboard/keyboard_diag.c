#include "keyboard_diag.h"

#include <stdio.h>

#include "keyboard.h"

const char* KeyBoard2Str(const KeyBoard_t* const KeyNode) {
    static char name[80] = "Err";
    if(KeyNode) {
        uint8_t key = KeyCode2Char(KeyNode);
        snprintf(name, sizeof(name), "M:0x%02x: ", KeyNode->modifier.byte);
        uint8_t i = 0;
        for(i = 0; i < 6; i++) {
            if(KeyNode->key_code[i]) {
                snprintf(name, sizeof(name), "%s 0x%02x", name, KeyNode->key_code[i]);
            }
        }
        snprintf(name, sizeof(name), "%s [%c]", name, key);
    }
    return name;
}
