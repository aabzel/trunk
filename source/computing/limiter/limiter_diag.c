#include "limiter_diag.h"

#include <stdio.h>
#include <string.h>

#include "shared_array.h"

const char* LimiterToStr(const Limiter_t* const Node) {
    static char lText[400] = {0};
    strcpy(lText, "");
    if(Node) {
        snprintf(lText, sizeof(lText), "%sFoo:0x%p", lText, Node->function);
        snprintf(lText, sizeof(lText), "%sCall:%u", lText, Node->call_cnt);
        snprintf(lText, sizeof(lText), "%sEn:%u", lText, Node->on_off);
        snprintf(lText, sizeof(lText), "%sInit:%u", lText, Node->init);
#if 0
        snprintf(lText, sizeof(lText), "%sNext:%llu", lText, Node->start_time_next_us);
        snprintf(lText, sizeof(lText), "%sPha:%llu", lText, Node->phase_us);
        snprintf(lText, sizeof(lText), "%sTotal:%llu", lText, Node->run_time_total_us);
#endif
    }
    return lText;
}
