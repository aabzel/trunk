#include "timer_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "clock_custom_diag.h"
#include "debugger.h"
#include "log.h"
#include "microcontroller_const.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "timer_custom_drv.h"
#include "timer_mcal.h"
#include "writer_config.h"

const char* TimerInfoToStr(const TimerInfo_t* const Info) {
    static char text[80] = "";
    if(Info) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Info->num);
        snprintf(text, sizeof(text), "%sBase:0x%p,", text, Info->TMRx);
        snprintf(text, sizeof(text), "%sBus:%s,", text, Bus2Str(Info->clock_bus));
        snprintf(text, sizeof(text), "%sBit:%u,", text, Info->resolution_bit);
        snprintf(text, sizeof(text), "%sIrq:%u,", text, Info->irq_n);
        snprintf(text, sizeof(text), "%sCLK:0x%x,", text, Info->clock_type);
    }
    return text;
}

#if 0
static const char* Timer_STIS_ToStr(uint8_t code){
    const char*  name="?";
    switch(code) {
        case xxx: name="?";break;
        case ccc: name="?"; break;
        case vvv: name="?";break;
        case bbb: name="?"; break;
        default: name="?";break;
    }
    return name;
}
#endif

static bool TimerRegDiag_TMRx_CTRL1(tmr_type* TMRx) {
    bool res = false;
    if(TMRx) {
        LOG_WARNING(TIMER, "Parse:TMRx_CTRL1");
        LOG_INFO(TIMER, "tmren:%u", TMRx->ctrl1_bit.tmren);
        LOG_INFO(TIMER, "ovfen:%u", TMRx->ctrl1_bit.ovfen);
        LOG_INFO(TIMER, "ovfs:%u", TMRx->ctrl1_bit.ovfs);
        LOG_INFO(TIMER, "ocmen:%u", TMRx->ctrl1_bit.ocmen);
        LOG_INFO(TIMER, "cnt_dir:%u", TMRx->ctrl1_bit.cnt_dir);
        LOG_INFO(TIMER, "prben:%u", TMRx->ctrl1_bit.prben);
        LOG_INFO(TIMER, "clkdiv:%u", TMRx->ctrl1_bit.clkdiv);
        LOG_INFO(TIMER, "pmen:%u", TMRx->ctrl1_bit.pmen);
        res = true;
    }
    return res;
}

static bool TimerRegDiag_TMRx_CTRL2(tmr_type* TMRx) {
    bool res = false;
    if(TMRx) {
        LOG_WARNING(TIMER, "Parse:TMRx_CTRL2");
        LOG_INFO(TIMER, "cbctrl:%u", TMRx->ctrl2_bit.cbctrl);
        LOG_INFO(TIMER, "ccfs:%u", TMRx->ctrl2_bit.ccfs);
        LOG_INFO(TIMER, "drs:%u", TMRx->ctrl2_bit.drs);
        LOG_INFO(TIMER, "ptos:%u", TMRx->ctrl2_bit.ptos);
        LOG_INFO(TIMER, "c1insel:%u", TMRx->ctrl2_bit.c1insel);
        LOG_INFO(TIMER, "c1ios:%u", TMRx->ctrl2_bit.c1ios);
        LOG_INFO(TIMER, "c1cios:%u", TMRx->ctrl2_bit.c1cios);
        LOG_INFO(TIMER, "c2ios:%u", TMRx->ctrl2_bit.c2ios);
        LOG_INFO(TIMER, "c2cios:%u", TMRx->ctrl2_bit.c2cios);
        LOG_INFO(TIMER, "c3ios:%u", TMRx->ctrl2_bit.c3ios);
        LOG_INFO(TIMER, "c3cios:%u", TMRx->ctrl2_bit.c3cios);
        LOG_INFO(TIMER, "c4ios:%u", TMRx->ctrl2_bit.c4ios);
#ifdef HAS_AT32F43X
        LOG_INFO(TIMER, "trgout2en:%u", TMRx->ctrl2_bit.trgout2en);
#endif // HAS_AT32F43X

        res = true;
    }
    return res;
}

static bool TimerRegDiag_TMRx_STCTRL(tmr_type* TMRx) {
    bool res = false;
    if(TMRx) {
        LOG_WARNING(TIMER, "Parse:TMRx_STCTRL");
        LOG_INFO(TIMER, "smsel:%u", TMRx->stctrl_bit.smsel);
        LOG_INFO(TIMER, "stis:%u", TMRx->stctrl_bit.stis);
        LOG_INFO(TIMER, "sts:%u", TMRx->stctrl_bit.sts);
        LOG_INFO(TIMER, "esf:%u", TMRx->stctrl_bit.esf);
        LOG_INFO(TIMER, "esdiv:%u", TMRx->stctrl_bit.esdiv);
        LOG_INFO(TIMER, "ecmben:%u", TMRx->stctrl_bit.ecmben);
        LOG_INFO(TIMER, "esp:%u", TMRx->stctrl_bit.esp);
        res = true;
    }
    return res;
}

static bool TimerRegDiag_TMRx_CM1(tmr_type* TMRx) {
    bool res = false;
    if(TMRx) {
        LOG_WARNING(TIMER, "Parse:TMRx_CM1");
        LOG_INFO(TIMER, "c2osen:%u", TMRx->cm1_output_bit.c2osen);
        LOG_INFO(TIMER, "c2octrl:%u", TMRx->cm1_output_bit.c2octrl);
        LOG_INFO(TIMER, "c2oben:%u", TMRx->cm1_output_bit.c2oben);
        LOG_INFO(TIMER, "c2oien:%u", TMRx->cm1_output_bit.c2oien);
        LOG_INFO(TIMER, "c2c:%u", TMRx->cm1_output_bit.c2c);
        LOG_INFO(TIMER, "c1osen:%u", TMRx->cm1_output_bit.c1osen);
        LOG_INFO(TIMER, "c1octrl:%u", TMRx->cm1_output_bit.c1octrl);
        LOG_INFO(TIMER, "c1oben:%u", TMRx->cm1_output_bit.c1oben);
        LOG_INFO(TIMER, "c1oien:%u", TMRx->cm1_output_bit.c1oien);
        LOG_INFO(TIMER, "c1c:%u", TMRx->cm1_output_bit.c1c);
        res = true;
    }
    return res;
}

static bool TimerRegDiag_TMRx_CCTRL(tmr_type* TMRx) {
    bool res = false;
    if(TMRx) {
        LOG_WARNING(TIMER, "Parse:TMRx_CCTRL");
        LOG_INFO(TIMER, "c4p:%u", TMRx->cctrl_bit.c4p);
        LOG_INFO(TIMER, "c4en:%u", TMRx->cctrl_bit.c4en);

        LOG_INFO(TIMER, "c3cp:%u", TMRx->cctrl_bit.c3cp);
        LOG_INFO(TIMER, "c3cen:%u", TMRx->cctrl_bit.c3cen);

        LOG_INFO(TIMER, "c2p:%u", TMRx->cctrl_bit.c2p);
        LOG_INFO(TIMER, "c2en:%u", TMRx->cctrl_bit.c2en);

        LOG_INFO(TIMER, "c1p:%u", TMRx->cctrl_bit.c1p);
        LOG_INFO(TIMER, "c1en:%u", TMRx->cctrl_bit.c1en);

        res = true;
    }
    return res;
}

static bool TimerRegDiag_TMRx_CVAL(tmr_type* TMRx) {
    bool res = false;
    if(TMRx) {
        LOG_WARNING(TIMER, "Parse:TMRx_CVAL");
        LOG_INFO(TIMER, "cval:%u", TMRx->cval_bit.cval);
        res = true;
    }
    return res;
}

static bool TimerRegDiag_TMRx_DIV(tmr_type* TMRx) {
    bool res = false;
    if(TMRx) {
        LOG_WARNING(TIMER, "Parse:TMRx_DIV");
        LOG_INFO(TIMER, "div:%u", TMRx->div_bit.div);
        res = true;
    }
    return res;
}

static bool TimerRegDiag_TMRx_PR(tmr_type* TMRx) {
    bool res = false;
    if(TMRx) {
        LOG_WARNING(TIMER, "Parse:TMRx_PR");
        LOG_INFO(TIMER, "pr:%u", TMRx->pr_bit.pr);
        res = true;
    }
    return res;
}

static bool TimerRegDiag_TMRx_C2DT(tmr_type* TMRx) {
    bool res = false;
    if(TMRx) {
        LOG_WARNING(TIMER, "Parse:TMRx_C2DT");
        LOG_INFO(TIMER, "c2dt:%u", TMRx->c2dt_bit.c2dt);
        res = true;
    }
    return res;
}

bool timer_reg_parse(uint8_t num) {
    bool res = false;
    const TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        log_level_time_stamp(false);
        LOG_INFO(TIMER, "TRM%u,Base:0x%p", num, Info->TMRx);
        res = TimerRegDiag_TMRx_CTRL1(Info->TMRx);
        res = TimerRegDiag_TMRx_CTRL2(Info->TMRx);
        res = TimerRegDiag_TMRx_STCTRL(Info->TMRx);
        res = TimerRegDiag_TMRx_CM1(Info->TMRx);
        res = TimerRegDiag_TMRx_CCTRL(Info->TMRx);
        res = TimerRegDiag_TMRx_CVAL(Info->TMRx);
        res = TimerRegDiag_TMRx_DIV(Info->TMRx);
        res = TimerRegDiag_TMRx_PR(Info->TMRx);
        res = TimerRegDiag_TMRx_C2DT(Info->TMRx);
        log_level_time_stamp(true);
    }
    return res;
}

bool timer_raw_reg_diag(uint8_t num) {
    bool res = false;
    const TimerInfo_t* Info = TimerGetInfo(num);
    if(Info) {
        uint32_t reg_cnt = timer_reg_cnt();
        res = debug_raw_reg_diag(TIMER, (uint32_t)Info->TMRx, TimerReg, reg_cnt);
    }

    return res;
}
