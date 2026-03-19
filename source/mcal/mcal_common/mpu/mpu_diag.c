#include "mpu_diag.h"

#include "byte_utils.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* MpuPermissionToStr(const MpuPermission_t* const permission) {
    static char lText[30] = {0};
    if(permission) {
        strcpy(lText, "");
        snprintf(lText, sizeof(lText), "%sPerm:0x%X,", lText, permission->byte);
        snprintf(lText, sizeof(lText), "%s%s", lText, ByteNameToStr(permission->read, "R"));
        snprintf(lText, sizeof(lText), "%s%s", lText, ByteNameToStr(permission->write, "W"));
        snprintf(lText, sizeof(lText), "%s%s", lText, ByteNameToStr(permission->execute, "E"));
        snprintf(lText, sizeof(lText), "%s%s", lText, ByteNameToStr(permission->cached, "C"));
        snprintf(lText, sizeof(lText), "%s%s", lText, ByteNameToStr(permission->shareable, "S"));
        snprintf(lText, sizeof(lText), "%s%s", lText, ByteNameToStr(permission->bufferable, "B"));
    }
    return lText;
}

const char* MpuRegionToStr(const MpuRegionConfig_t* const Region) {
    if(Region) {
        uint32_t reg_end = Region->start + Region->size;
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Region->num);
        snprintf(text, sizeof(text), "%s[0x%08X-", text, Region->start);
        snprintf(text, sizeof(text), "%s0x%08X],", text, reg_end);
        snprintf(text, sizeof(text), "%sSize:%u,", text, Region->size);
        snprintf(text, sizeof(text), "%sEn:%s,", text, OnOffToStr(Region->on_off));
        snprintf(text, sizeof(text), "%sPerm:%s,", text, MpuPermissionToStr(&Region->permission));
        snprintf(text, sizeof(text), "%s%s,", text, Region->name);
    }
    return text;
}

const char* MpuConfigToStr(const MpuConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sINT:%s,", text, OnOffToStr(Config->interrupt_on));
        snprintf(text, sizeof(text), "%sRegCnt:%u,", text, Config->region_cnt);
        snprintf(text, sizeof(text), "%s%p,", text, Config->Region);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* MpuNodeToStr(const MpuHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool mpu_diag(void) {
    bool res = false;
    return res;
}
