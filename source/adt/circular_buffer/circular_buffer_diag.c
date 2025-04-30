#include "circular_buffer_diag.h"

#include <stdio.h>
#include <string.h>

#include "common_diag.h"

const char* CircularBufferStateToStr(const CircularBufferIndexInfo_t* const Node) {
    static char text[350] = "";
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%s%u/", text, Node->cur);
        snprintf(text, sizeof(text), "%s%u,", text, Node->size);
        snprintf(text, sizeof(text), "%sInit:%s", text, OnOffToStr(Node->init));
    }
    return text;
}

const char* CircularBufferNodeToStr(const CircularBufferWord_t* const Node) {
    static char text[350] = "";
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%s{%s},", text, CircularBufferStateToStr(&Node->state));
        snprintf(text, sizeof(text), "%sMem:%p,", text, Node->array);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init_done));
        snprintf(text, sizeof(text), "%sErr:%u", text, Node->err_cnt);
    }
    return text;
}
