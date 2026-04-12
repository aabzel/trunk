#include "bin_heap_diag.h"

#include "diag_inc.h"

const char* BinHeapToStr(const BinHeapHandle_t* const Node) {
    static char lText[100] = {0};
    if(Node) {
        strcpy(lText, "");
        uint32_t i = 0;
        for(i = 0; i < Node->size; i++) {
            snprintf(lText, sizeof(lText), "%s;%d", lText, Node->array[i]);
        }
    }
    return lText;
}
