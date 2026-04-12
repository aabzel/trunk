#include "min_heap_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"
#include "min_heap.h"

const char* MinHeapConfigToStr(const BinHeapConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sCap:%u,", text, Config->capacity);
        snprintf(text, sizeof(text), "%sArray:0x%x,", text, Config->array);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* MinHeapNodeToStr(const BinHeapHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSize:%u,", text, Node->size);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool min_heap_diag(uint8_t num) {
    bool res = false;
    int32_t out_val = 0;
    res = min_heap_peek_h(num, &out_val);
    LOG_DEBUG(MIN_HEAP, "mHeap_%u,Root:%d", num, out_val);

    const BinHeapConfig_t* Config = MinHeapGetConfig(num);
    if(Config) {
        LOG_DEBUG(MIN_HEAP, "%s", MinHeapConfigToStr(Config));
    }

    BinHeapHandle_t* Node = MinHeapGetNode(num);
    if(Node) {
        LOG_DEBUG(MIN_HEAP, "%s", MinHeapNodeToStr(Node));
    }
    return res;
}
