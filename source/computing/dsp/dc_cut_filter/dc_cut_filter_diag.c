#include "dc_cut_filter_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* DcCutFilterConfigToStr(const DcCutFilterConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sAlfa:%f,", text,  Config->alfa);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* DcCutFilterNodeToStr(const DcCutFilterHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sA_{n-1}:%d,", text, Node->a_n_1);
        snprintf(text, sizeof(text), "%sAlfa:%f=", text, Node->alfa);
        snprintf(text, sizeof(text), "%s%d/", text, Node->numerator);
        snprintf(text, sizeof(text), "%s%d,", text, Node->denominator);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool dc_cut_filter_diag(void) {
    bool res = false;
    return res;
}

bool dc_cut_filter_diag_one(uint8_t num) {
    bool res = false;
    return res;
}
