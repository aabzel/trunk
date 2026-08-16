#include "decimator_diag.h"

#include <stdio.h>
#include <string.h>

#include "decimator_const.h"

const char* DecimatorStateToStr(DecimatorState_t code) {
    const char* name = "?";
    switch(code) {
    case DECIMATOR_STATE_ONE:
        name = "1";
        break;
    case DECIMATOR_STATE_ZERO:
        name = "0";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* DecimatorInputToStr(DecimatorInput_t input) {
    const char* name = "?";
    switch(input) {
    case DECIMATOR_INPUT_ONE:
        name = "1";
        break;
    case DECIMATOR_INPUT_ZERO:
        name = "0";
        break;
    case DECIMATOR_INPUT_OVERFLOW:
        name = "Overflow";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* DecimatorConfigToStr(const DecimatorConfig_t* const Config) {
    static char temp[80] = {0};
    strcpy(temp, "");
    if(Config) {
        snprintf(temp, sizeof(temp), "%sN:%u,", temp, Config->num);
        snprintf(temp, sizeof(temp), "%sSamPerBit:%u Sam,", temp, Config->samples_per_bit);
        snprintf(temp, sizeof(temp), "%s[%s],", temp, Config->name);
    }
    return temp;
}

const char* DecimatorNodeToStr(const DecimatorHandle_t* const Node) {
    static char temp[100] = {0};
    strcpy(temp, "");
    if(Node) {
        snprintf(temp, sizeof(temp), "%sN:%u,", temp, Node->num);
        snprintf(temp, sizeof(temp), "%sSamCnt:%u sam,", temp, Node->samples_cnt);
        snprintf(temp, sizeof(temp), "%sState:%s,", temp, DecimatorStateToStr(Node->state));
        snprintf(temp, sizeof(temp), "%sInput:%s,", temp, DecimatorInputToStr(Node->input));
        snprintf(temp, sizeof(temp), "%sSamPerBit:%u sam,", temp, Node->samples_per_bit);
        snprintf(temp, sizeof(temp), "%sPrevState:%s,", temp, DecimatorStateToStr(Node->prev_state));
        snprintf(temp, sizeof(temp), "%s[%s],", temp, Node->name);
    }
    return temp;
}
