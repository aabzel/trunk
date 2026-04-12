#include "max_heap_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"
#include "max_heap.h"

const char* MaxHeapConfigToStr(const MaxHeapConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sCap:%u,", text, Config->capacity);
        snprintf(text, sizeof(text), "%sArray:0x%x,", text, Config->array);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* MaxHeapNodeToStr(const MaxHeapHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSize:%u,", text, Node->size);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool max_heap_diag(uint8_t num) {
    bool res = false;
    int32_t out_val = 0;
    res = max_heap_peek_h(num, &out_val);
    LOG_DEBUG(MAX_HEAP, "mHeap_%u,Root:%d", num, out_val);

    const MaxHeapConfig_t* Config = MaxHeapGetConfig(num);
    if(Config) {
        LOG_DEBUG(MAX_HEAP, "%s", MaxHeapConfigToStr(Config));
    }

    MaxHeapHandle_t* Node = MaxHeapGetNode(num);
    if(Node) {
        LOG_DEBUG(MAX_HEAP, "%s", MaxHeapNodeToStr(Node));
    }
    return res;
}
