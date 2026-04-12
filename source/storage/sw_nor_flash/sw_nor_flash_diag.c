#include "sw_nor_flash_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* SwNorFlashConfigToStr(const SwNorFlashConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sSz:%u,", text, Config->size);
        snprintf(text, sizeof(text), "%sMem:0x%p,", text, Config->memory);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sBlock:%u,", text, Config->block_size);
        snprintf(text, sizeof(text), "%sPage:%u,", text, Config->page_size);
        snprintf(text, sizeof(text), "%sSector:%u,", text, Config->sector_size);
        snprintf(text, sizeof(text), "%sReRec:%u,", text, Config->re_record);
    }
    return text;
}

const char* SwNorFlashNodeToStr(const SwNorFlashHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));

        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sSz:%u,", text, Node->size);
        snprintf(text, sizeof(text), "%s%s,", text, Node->name);
        snprintf(text, sizeof(text), "%sBlock:%u,", text, Node->block_size);
        snprintf(text, sizeof(text), "%sPage:%u,", text, Node->page_size);
        snprintf(text, sizeof(text), "%sSector:%u,", text, Node->sector_size);
        snprintf(text, sizeof(text), "%sReRec:%u,", text, Node->re_record);
        snprintf(text, sizeof(text), "%sMem:0x%p,", text, Node->memory);
    }
    return text;
}

bool sw_nor_flash_diag(void) {
    bool res = false;
    return res;
}
