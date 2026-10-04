#include "bts724g_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "gpio_mcal.h"
#include "gpio_diag.h"
#include "log.h"
#include "control_diag.h"
#include "float_diag.h"
#include "bts724g_mcal.h"
#include "str_utils.h"

static char lText[150] = {0};

const char* Bts724gModeToStr(Bts724gPinMode_t mode) {
    const char* name = "?";
    switch(mode) {
        case BTS724G_MODE_OFF: {       name = "Off";    } break;
        case BTS724G_MODE_ON:  {       name = "On";    } break;
        case BTS724G_MODE_BLINK: {     name = "Blink";    } break;
        case BTS724G_MODE_PWM: {       name = "Pwm";    } break;
        case BTS724G_MODE_PULSE_TRAIN: {        name = "Train";        } break;
        default: { name = "?";} break;
    }
    return name;
}

const char* Bts724gConfigToStr(const Bts724gConfig_t* const Config) {
    strcpy(lText, "");
    if(Config) {
        snprintf(lText, sizeof(lText), "%sN:%u,", lText, Config->num);
        snprintf(lText, sizeof(lText), "%sPWMnum:%u,", lText, Config->pwm_num);
        snprintf(lText, sizeof(lText), "%sNs:%u,", lText, Config->shared_num);
        snprintf(lText, sizeof(lText), "%s%s,", lText, Config->name);
        snprintf(lText, sizeof(lText), "%sDuty:%s %%,", lText, FloatBigToStr(Config->duty));
        snprintf(lText, sizeof(lText), "%sFreq:%s Hz,", lText, FloatBigToStr(Config->frequency_hz));
        snprintf(lText, sizeof(lText), "%sPha:%s s,", lText, FloatBigToStr(Config->phase_s));
        snprintf(lText, sizeof(lText), "%sSet:%s,", lText, GpioPadToStr(Config->pad_set));
        snprintf(lText, sizeof(lText), "%sDiag:%s,", lText, GpioPadToStr(Config->pad_set));
        snprintf(lText, sizeof(lText), "%sMode:%s,", lText, Bts724gModeToStr(Config->mode));
    }
    return lText;
}

const char* Bts724gNodeToStr(const Bts724gHandle_t* const Node) {
    strcpy(lText, "");
    if(Node) {
        snprintf(lText, sizeof(lText), "%sN:%u,", lText, Node->num);
        snprintf(lText, sizeof(lText), "%s%s,", lText, Node->name);
        snprintf(lText, sizeof(lText), "%sSet:%s,", lText, GpioPadToStr(Node->pad_set));
        snprintf(lText, sizeof(lText), "%sDiag:%s,", lText, GpioPadToStr(Node->pad_diag));
        snprintf(lText, sizeof(lText), "%sSpin:%u,", lText, Node->spin);
        snprintf(lText, sizeof(lText), "%sInit:%s,", lText, OnOffToStr(Node->init));
        snprintf(lText, sizeof(lText), "%sMode:%s,", lText, Bts724gModeToStr(Node->mode));
        snprintf(lText, sizeof(lText), "%sllMode:%s,", lText, ControlModeToStr(Node->ctrl_mode));
        snprintf(lText, sizeof(lText), "%sNsh:%u,", lText, Node->shared_num);
        snprintf(lText, sizeof(lText), "%sPWMn:%u,", lText, Node->pwm_num);
        snprintf(lText, sizeof(lText), "%sDuty:%s %%,", lText, FloatBigToStr(Node->duty));
        snprintf(lText, sizeof(lText), "%sFreq:%s Hz,", lText, FloatBigToStr(Node->frequency_hz));
        snprintf(lText, sizeof(lText), "%sOpposN:%u,", lText, Node->opposite_num);
    }
    return lText;
}


const char* Bts724gNumToStr(uint8_t num){
    const char* name= "?";
    Bts724gHandle_t* Node=Bts724gGetNode(num);
    if(Node){
        name=Bts724gNodeToStr(Node);
    }
    return name;
}

const char* Bts724gNodeToStrShort(const Bts724gHandle_t* const Node){
    strcpy(lText, "");
    if(Node) {
        snprintf(lText, sizeof(lText), "%sN:%u,", lText, Node->num);
        snprintf(lText, sizeof(lText), "%sName:%s,", lText, Node->name);
        snprintf(lText, sizeof(lText), "%sSet:%s,", lText, GpioPadToStr(Node->pad_set));
        snprintf(lText, sizeof(lText), "%sDiag:%s,", lText, GpioPadToStr(Node->pad_diag));
    }
    return lText;
}


bool bts724g_diag(char* key_word1, char* key_word2) {
    bool res = false;
    //replace_char(key_word1, '_', ' ');
    //replace_char(key_word2, '_', ' ');
    uint32_t cnt = bts724g_get_cnt();
    LOG_INFO(BTS724G, "Cnt:%u", cnt);

    static const table_col_t cols[] = {
            {5, "Num"},
            {11, "name"},
            {8, "CON"},
            {6, "Ena"},
            {5, "Flt"},
            {7, "mode"},
            {7, "LowL"},
            {6, "PadS"},
            {6, "PadG"},
            {4, "PWM"},
//              {6, "init"},
              {6, "err"},
              {8, "restMs"},
              {8, "DurationMs"},
              {8, "spin"}
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint8_t i = 0;
    for(i = 0; i <= cnt; i++) {
        const Bts724gConfig_t* Config = Bts724gGetConfig(i);
        if(Config) {
            Bts724gHandle_t* Node = Bts724gGetNode(i);
            if(Node) {
                bool on_off = false;
                on_off = bts724g_state_get(Node->num);

                GpioLogicLevel_t eff= gpio_get_state_short(Node->pad_diag);

                char temp[250] = {0};
                strcpy(temp, TSEP);
                sprintf(temp, "%s %3u " TSEP, temp, Node->num);
                sprintf(temp, "%s %9s " TSEP, temp, Node->name);
                sprintf(temp, "%s %6s " TSEP, temp, Node->con_name);
                sprintf(temp, "%s %4s " TSEP, temp, OnOffToStr(on_off));
                sprintf(temp, "%s %3u " TSEP, temp, eff);
                sprintf(temp, "%s %5s " TSEP, temp, Bts724gModeToStr(Node->mode));
                sprintf(temp, "%s %5s " TSEP, temp, ControlModeToStr(Node->ctrl_mode));
                sprintf(temp, "%s %4s " TSEP, temp, GpioPadToStr(Node->pad_set));
                sprintf(temp, "%s %4s " TSEP, temp, GpioPadToStr(Node->pad_diag));
                sprintf(temp, "%s %2u " TSEP, temp, Node->pwm_num);
                //sprintf(temp, "%s %3u " TSEP, temp, Node->init);
                sprintf(temp, "%s %4u " TSEP, temp, Node->error_cnt);
                sprintf(temp, "%s %6d " TSEP, temp, Node->rest_duration_ms);
                sprintf(temp, "%s %6d " TSEP, temp, Node->duration_ms);
                sprintf(temp, "%s %6u " TSEP, temp, Node->spin);
                res = is_contain(temp, key_word1, key_word2);
                if(res) {
                    cli_printf("%s" CRLF, temp);
                }
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool bts724g_diag_one(uint8_t num) {
    bool res = false;
    return res;
}
