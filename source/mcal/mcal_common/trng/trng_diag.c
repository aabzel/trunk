#include "trng_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* tRngConfigToStr(const tRngConfig_t* const Config) {
    static char temp[100]={0};
    strcpy(temp, "");
    if(Config) {
        snprintf(temp, sizeof(temp), "%sN:%u,", temp, Config->num);
        snprintf(temp, sizeof(temp), "%sINT:%s,", temp, OnOffToStr(Config->interrupt_on));
        snprintf(temp, sizeof(temp), "%s%s,", temp, Config->name);
    }
    return temp;
}

const char* tRngNodeToStr(const tRngHandle_t* const Node) {
    static char temp[100]={0};
    strcpy(temp, "");
    if(Node) {
        snprintf(temp, sizeof(temp), "%sSpin:%8u,", temp, Node->spin);
        snprintf(temp, sizeof(temp), "%sU8:%3u,", temp, Node->byte);
        snprintf(temp, sizeof(temp), "%sU16:%5u,", temp, Node->word);
        snprintf(temp, sizeof(temp), "%sU32:%10u,", temp, Node->dword);
        snprintf(temp, sizeof(temp), "%sU64:%llu,", temp, Node->qword);
        snprintf(temp, sizeof(temp), "%sInit:%3s,", temp, OnOffToStr(Node->init));
    }
    return temp;
}

bool trng_diag(void) {
    bool res = false;
    return res;
}

bool trng_diag_one(uint8_t num) {
    bool res = false;
    return res;
}
