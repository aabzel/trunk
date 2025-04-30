#include "crc_diag.h"

#include <stdio.h>

static const char* CompU162Str(uint16_t vala, uint16_t valb) {
    const char* text = "?";
    if(vala == valb) {
        text = "Match";
    } else {
        text = "Diff";
    }

    return text;
}

const char* Crc16ToStr(const Crc16_t* const Node) {
    static char text[40];
    if(Node) {
        snprintf(text, sizeof(text), "Read:0x%04x,Calc:0x%04x,%s", Node->read, Node->calc,
                 CompU162Str(Node->read, Node->calc));
    }
    return text;
}
