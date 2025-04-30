#include "string_reader_diag.h"

#include <stdio.h>
#include <string.h>


const char* StringReaderConfigToStr(const StringReaderConfig_t* const Config) {
    static char text[180] = "";
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sIF:%u,", text, Config->interface_if);
        snprintf(text, sizeof(text), "%sCLI:%u,", text, Config->cli_num);
        snprintf(text, sizeof(text), "%sSEC:%u,", text, Config->secure_echo);
        snprintf(text, sizeof(text), "%sLED:%u,", text, Config->feedback_led);
        snprintf(text, sizeof(text), "%sSize:%d,", text, Config->string_size);
        snprintf(text, sizeof(text), "%sText:[%s],", text, Config->string);
       // snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* StringReaderNodeToStr(const StringReaderHandle_t* const Node)   {
    static char text[180] = "";
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sLen:%d,", text, Node->string_len);
        snprintf(text, sizeof(text), "%sSize:%d,", text, Node->string_size);
        snprintf(text, sizeof(text), "%sText:[%s],", text, Node->string);
        //snprintf(text, sizeof(text), "%s%s,", text, Node->name);
    }
    return text;
}


