#include "circular_buffer_diag.h"

#include <stdio.h>
#include <string.h>

#include "common_diag.h"

const char* CircularBufferStateToStr(const CircularBufferIndexInfo_t* const Node) {
    static char lText[350] = "";
    if(Node) {
        strcpy(lText, "");
        snprintf(lText, sizeof(lText), "%s%u/", lText, Node->cur);
        snprintf(lText, sizeof(lText), "%s%u,", lText, Node->size);
        snprintf(lText, sizeof(lText), "%sInit:%s", lText, OnOffToStr(Node->init));
    }
    return lText;
}

const char* CircularBufferNodeToStr(const CircularBufferWord_t* const Node) {
    static char lText[350] = "";
    if(Node) {
        strcpy(lText, "");
        snprintf(lText, sizeof(lText), "%s{%s},", lText, CircularBufferStateToStr(&Node->state));
        snprintf(lText, sizeof(lText), "%sMem:%p,", lText, Node->array);
        snprintf(lText, sizeof(lText), "%sInit:%s,", lText, OnOffToStr(Node->init_done));
        snprintf(lText, sizeof(lText), "%sErr:%u", lText, Node->err_cnt);
    }
    return lText;
}
