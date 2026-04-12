#include "dwt_diag.h"

#include "dwt_mcal.h"
#include "debugger.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

/* Table 9-1 DWT register summary */
const Reg32_t DwtRegs[] = {
    { .num=1, .offset=0xE0001000, .name="DWT_CTRL",       .size=4,  .valid=true, },
    { .num=2, .offset=0xE0001004, .name="DWT_CYCCNT",     .size=4,  .valid=true, },
    { .num=3, .offset=0xE0001008, .name="DWT_CPICNT",     .size=4,  .valid=true, },
    { .num=4, .offset=0xE000100C, .name="DWT_EXCCNT",     .size=4,  .valid=true, },
    { .num=5, .offset=0xE0001010, .name="DWT_SLEEPCNT",   .size=4,  .valid=true, },
    { .num=6, .offset=0xE0001014, .name="DWT_LSUCNT",     .size=4,  .valid=true, },
    { .num=7, .offset=0xE0001018, .name="DWT_FOLDCNT",    .size=4,  .valid=true, },
    { .num=8, .offset=0xE000101C, .name="DWT_PCSR",       .size=4,  .valid=true, },
    { .num=9, .offset=0xE0001020, .name="DWT_COMP0",      .size=4,  .valid=true, },
    { .num=10, .offset=0xE0001024, .name="DWT_MASK0",     .size=4,  .valid=true, },
    { .num=11, .offset=0xE0001028, .name="DWT_FUNCTION0", .size=4,  .valid=true, },
    { .num=12, .offset=0xE0001030, .name="DWT_COMP1",     .size=4,  .valid=true, },
    { .num=13, .offset=0xE0001034, .name="DWT_MASK1",     .size=4,  .valid=true, },
    { .num=14, .offset=0xE0001038, .name="DWT_FUNCTION1", .size=4,  .valid=true, },
    { .num=15, .offset=0xE0001040, .name="DWT_COMP2",     .size=4,  .valid=true, },
    { .num=16, .offset=0xE0001044, .name="DWT_MASK2",     .size=4,  .valid=true, },
    { .num=17, .offset=0xE0001048, .name="DWT_FUNCTION2", .size=4,  .valid=true, },
    { .num=18, .offset=0xE0001050, .name="DWT_COMP3",     .size=4,  .valid=true, },
    { .num=19, .offset=0xE0001054, .name="DWT_MASK3",     .size=4,  .valid=true, },
    { .num=20, .offset=0xE0001058, .name="DWT_FUNCTION3", .size=4,  .valid=true, },
};

const char* DwtConfigToStr(const DwtConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sBaseAddr:0x%08X,", text, Config->DWTx);
        snprintf(text, sizeof(text), "%s[%s],", text, Config->name);
    }
    return text;
}

const char* DwtNodeToStr(const DwtHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        uint32_t time_ms32 = dwt_get_time_ms32(Node->num);
        uint64_t time_us64 = dwt_get_time_us64(Node->num);

        snprintf(text, sizeof(text), "%sUpTime:%u ms,", text, time_ms32);
        snprintf(text, sizeof(text), "%sUpTime:%llu us,", text, time_us64);
        snprintf(text, sizeof(text), "%sUpTimeU32:%u,", text, Node->up_time_u32);
        snprintf(text, sizeof(text), "%sUpTimeU32prev:%u,", text, Node->up_time_u32_prev);
        snprintf(text, sizeof(text), "%sUpTimeU64:%llu,", text, Node->up_time_u64);
        snprintf(text, sizeof(text), "%sDiv1us:%llu,", text, Node->divider_1us);
        snprintf(text, sizeof(text), "%sDiv1ms:%llu,", text, Node->divider_1ms);
        snprintf(text, sizeof(text), "%sWrapCnt:%llu,", text, Node->wrap_counter);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
    }
    return text;
}

bool dwt_diag_one(uint8_t num) {
    bool res = false;
    DwtHandle_t* Node = DwtGetNode(num);
    if(Node) {
       dwt_get_run_time_counter_u64(num) ;
       LOG_INFO(LG_DWT,"%s",DwtNodeToStr(Node) );
       res = true;
    }
    return res;
}

bool dwt_diag(void) {
    bool res = false;
    res = dwt_diag_one(1);
    return res;
}

bool dwt_raw_reg_diag(uint8_t num) {
    bool res = false;
    DwtHandle_t* Node = DwtGetNode(num);
    if(Node) {
        uint32_t reg_cnt = ARRAY_SIZE(DwtRegs);
        res = debug_raw_reg_diag(LG_DWT, (uint32_t) Node->DWTx, DwtRegs, reg_cnt );
    }
    return res;
}
