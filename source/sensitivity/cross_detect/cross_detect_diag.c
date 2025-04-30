#include "cross_detect_diag.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef HAS_BOARD_INFO_DIAG
#include "board_diag.h"
#endif
#include "board_info.h"
#include "common_diag.h"
#include "cross_detect_drv.h"
#include "gpio_diag.h"
#include "log.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

const char* ShortVcc2Str(uint8_t code) {
    const char* name = "";
    if(code) {
        name = "Vcc";
    } else {
        name = "--";
    }
    return name;
}

const char* CdCross2Str(uint8_t code) {
    const char* name = "";
    if(code) {
        name = "Cross";
    } else {
        name = "--";
    }
    return name;
}

char* ShortGnd2Str(uint8_t code) {
    char* text = "";
    if(code) {
        text = "Gnd";
    } else {
        text = "--";
    }
    return text;
}

const char* CrossDetectState2Str(CrossDetectState_t state) {
    const char* name = "?";

    switch((uint8_t)state) {
    case CROSS_DETECT_STATE_LA_RA:
        name = "LA/RA";
        break;

    case CROSS_DETECT_STATE_LU_RA:
        name = "LU/RA";
        break;

    case CROSS_DETECT_STATE_LD_RA:
        name = "LD/RA";
        break;

    case CROSS_DETECT_STATE_LD_RD:
        name = "LD/RD";
        break;

    case CROSS_DETECT_STATE_LD_RU:
        name = "LD/RU";
        break;

    case CROSS_DETECT_STATE_LA_RU:
        name = "LA/RU";
        break;

    case CROSS_DETECT_STATE_LU_RU:
        name = "LU/RU";
        break;

    case CROSS_DETECT_STATE_LU_RD:
        name = "LU/RD";
        break;

    case CROSS_DETECT_STATE_LA_RD:
        name = "LA/RD";
        break;
    }
    return name;
}

const char* CrossDetectRead2Str(CrossDetectGpioRead_t read) {
    const char* name = "?";

    switch((uint8_t)read) {

    case READ_L0_R0:
        name = "L0_R0";
        break;

    case READ_L0_R1:
        name = "L0_R1";
        break;

    case READ_L1_R0:
        name = "L1_R0";
        break;

    case READ_L1_R1:
        name = "L1_R1";
        break;
    }
    return name;
}

const char* CrossDetectSolution2Str(CrossDetectSolution_t solution) {
    const char* name = "?";

    switch((uint8_t)solution) {
    case CROSS_DETECT_SOL_LEFT_SHORT_GND:
        name = "LeftShortGND";
        break;

    case CROSS_DETECT_SOL_LEFT_SHORT_VCC:
        name = "LeftShortVCC";
        break;

    case CROSS_DETECT_SOL_RIGHT_SHORT_GND:
        name = "RightShortGND";
        break;

    case CROSS_DETECT_SOL_RIGHT_SHORT_VCC:
        name = "RightShortVCC";
        break;

    case CROSS_DETECT_SOL_OPEN:
        name = "Open";
        break;

    case CROSS_DETECT_SOL_CROSS:
        name = "Cross";
        break;
    }
    return name;
}

bool cross_detect_pin_diag(const char* const key_word1, const char* const key_word2) {
    bool res = true;
    static const table_col_t cols[] = {
        {5, "Num"},        {6, "LGND"},  {6, "LVCC"},
#ifdef HAS_BOARD_INFO_DIAG
        {14, "LWireName"},
#endif
        {7, "LeftPad"},    {7, "cross"}, {7, "RightPad"},
#ifdef HAS_BOARD_INFO_DIAG
        {14, "RWireName"},
#endif
        {6, "RGND"},       {6, "RVCC"},  {6, "Upda"},
        // error
    };
    char line[250];
    uint32_t cnt = cross_detect_get_pin_cnt();
    uint32_t l, r, num = 0;
    /// Wire_t* WireInfio = NULL;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(l = 0; l < cnt; l++) {
        for(r = 0; r < cnt; r++) {
            if(l != r) {
                Pad_t left = CrossDetectPinConfig[l].pad;
                Pad_t right = CrossDetectPinConfig[r].pad;
                strcpy(line, TSEP);
                snprintf(line, sizeof(line), "%s %4s " TSEP, line,
                         ShortGnd2Str(CrossDetectResult[l][r].Fault.left_short_gnd));
                snprintf(line, sizeof(line), "%s %4s " TSEP, line,
                         ShortVcc2Str(CrossDetectResult[l][r].Fault.left_short_vcc));
#ifdef HAS_BOARD_INFO_DIAG
                snprintf(line, sizeof(line), "%s %12s " TSEP, line, Pad2ValidWireName(left));
#endif
                snprintf(line, sizeof(line), "%s %5s " TSEP, line, GpioPadToStr(left));
                snprintf(line, sizeof(line), "%s %5s " TSEP, line, CdCross2Str(CrossDetectResult[l][r].Fault.cross));
                snprintf(line, sizeof(line), "%s %5s " TSEP, line, GpioPadToStr(right));
#ifdef HAS_BOARD_INFO_DIAG
                snprintf(line, sizeof(line), "%s %12s " TSEP, line, Pad2ValidWireName(right));
#endif
                snprintf(line, sizeof(line), "%s %4s " TSEP, line,
                         ShortGnd2Str(CrossDetectResult[l][r].Fault.right_short_gnd));
                snprintf(line, sizeof(line), "%s %4s " TSEP, line,
                         ShortVcc2Str(CrossDetectResult[l][r].Fault.right_short_vcc));
                snprintf(line, sizeof(line), "%s %4u " TSEP, line, CrossDetectResult[l][r].update_cnt);

                if(is_contain(line, key_word1, key_word2)) {
                    cli_printf(TSEP " %3u ", num);
                    cli_printf("%s" CRLF, line);
                    num++;
                    res = true;
                }
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool cross_detect_diag_lut(const char* const key_word1, const char* const key_word2) {
    bool res = true;
    static const table_col_t cols[] = {
        {5, "Num"},  {7, "State"}, {7, "read"}, {7, "Cross"}, {6, "LGND"}, {6, "LVCC"},
        {6, "RGND"}, {6, "RVCC"},  {6, "Open"}, {5, "Err"},   {4, "Ok"},
    };
    char line[250];
    uint32_t cnt = cross_detect_get_lut_size();
    uint32_t i, num = 0;
    // Wire_t* WireInfio = NULL;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(i = 0; i < cnt; i++) {
        strcpy(line, TSEP);
        snprintf(line, sizeof(line), "%s %5s " TSEP, line, CrossDetectState2Str(CrossDetectSolutionInfo[i].state));
        snprintf(line, sizeof(line), "%s %5s " TSEP, line, CrossDetectRead2Str(CrossDetectSolutionInfo[i].read));
        snprintf(line, sizeof(line), "%s %5s " TSEP, line,
                 (CONF_YES == CrossDetectSolutionInfo[i].cross) ? "Cross" : "");
        snprintf(line, sizeof(line), "%s %4s " TSEP, line,
                 (CONF_YES == CrossDetectSolutionInfo[i].left_short_gnd) ? "LGND" : "");
        snprintf(line, sizeof(line), "%s %4s " TSEP, line,
                 (CONF_YES == CrossDetectSolutionInfo[i].left_short_vcc) ? "LVCC" : "");
        snprintf(line, sizeof(line), "%s %4s " TSEP, line,
                 (CONF_YES == CrossDetectSolutionInfo[i].right_short_gnd) ? "RGND" : "");
        snprintf(line, sizeof(line), "%s %4s " TSEP, line,
                 (CONF_YES == CrossDetectSolutionInfo[i].right_short_vcc) ? "RVCC" : "");
        snprintf(line, sizeof(line), "%s %4s " TSEP, line, (CONF_YES == CrossDetectSolutionInfo[i].open) ? "Open" : "");
        snprintf(line, sizeof(line), "%s %3s " TSEP, line, (CONF_YES == CrossDetectSolutionInfo[i].error) ? "Err" : "");
        snprintf(line, sizeof(line), "%s %2s " TSEP, line, (CONF_YES == CrossDetectSolutionInfo[i].ok) ? "Ok" : "");

        if(is_contain(line, key_word1, key_word2)) {
            cli_printf(TSEP " %3u ", num);
            cli_printf("%s" CRLF, line);
            num++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool cross_detect_diag(void) {
    bool res = false;

    static const table_col_t cols[] = {
        {5, "Num"},     {6, "Left"},    {6, "right"}, {7, "sol"},
#ifdef HAS_BOARD_INFO_DIAG
        {15, "LWName"}, {15, "RWName"},
#endif
    };
    uint32_t i, num = 0;
    char line[250];
    uint32_t cnt = cross_detect_get_cnt();
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(i = 0; i <= cnt; i++) {
        CrossDetectHandle_t* Node = CrossDetectGetNode(i);
        if(Node) {
            Pad_t left = Node->pair.left;
            Pad_t right = Node->pair.right;

            strcpy(line, TSEP);
            cli_printf(TSEP " %3u ", num);
            snprintf(line, sizeof(line), "%s %5s " TSEP, line, GpioPadToStr(left));
            snprintf(line, sizeof(line), "%s %5s " TSEP, line, GpioPadToStr(right));
            snprintf(line, sizeof(line), "%s 0x%x " TSEP, line, Node->pair.Fault.fault_code);
#ifdef HAS_BOARD_INFO_DIAG
            snprintf(line, sizeof(line), "%s %5s " TSEP, line, Pad2ValidWireName(left));
            snprintf(line, sizeof(line), "%s %5s " TSEP, line, Pad2ValidWireName(right));
#endif
            cli_printf("%s" CRLF, line);
            num++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool CrossDetectPair2Str(const CrossDetectPairInfo_t* const pair, char* const text, size_t size) {
    bool res = false;
    if(pair) {
        snprintf(text, size, "%s Left:%s", text, GpioPadToStr(pair->left));
        snprintf(text, size, "%s Right:%s", text, GpioPadToStr(pair->right));
        snprintf(text, size, "%s State:%s", text, CrossDetectState2Str(pair->state));
        snprintf(text, size, "%s Spin:%u", text, pair->spin_cnt);
        res = true;
    }
    return res;
}

bool CrossDetectDiagPair(const CrossDetectPairInfo_t* const pair) {
    bool res = false;
    char text[80] = "";
    res = CrossDetectPair2Str(pair, text, sizeof(text));
    if(res) {
        LOG_NOTICE(CROSS_DETECT, "%s", text);
    }
    return res;
}

const char* LeftShortGnd2Str(uint8_t code) {
    const char* name = "";
    if(code) {
        name = "LeftShortGnd";
    }
    return name;
}

const char* LeftShortVcc2Str(uint8_t code) {
    const char* name = "";
    if(code) {
        name = "LeftShortVcc";
    }
    return name;
}

const char* RightShortGnd2Str(uint8_t code) {
    const char* name = "";
    if(code) {
        name = "RightShortGnd";
    }
    return name;
}

const char* RightShortVcc2Str(uint8_t code) {
    const char* name = "";
    if(code) {
        name = "RightShortVcc";
    }
    return name;
}

const char* CrossDetectFaultToStr(CrossDetectFault_t fault) {
    static char text[80];
    sprintf(text, "%s %s %s %s %s", CdCross2Str(fault.cross), LeftShortGnd2Str(fault.left_short_gnd),
            LeftShortVcc2Str(fault.left_short_vcc), RightShortGnd2Str(fault.right_short_gnd),
            RightShortVcc2Str(fault.right_short_vcc));
    return text;
}

static char* CrossDetectFault2Str(CrossDetectFault_t Fault, Pad_t left, Pad_t right) {
    static char text[100] = "";
    memset(text, 0, sizeof(text));
    strcpy(text, "_");
    if(Fault.cross) {
        snprintf(text, sizeof(text), "Cross %s", GpioPadToStr(left));
        snprintf(text, sizeof(text), "%s-%s", text, GpioPadToStr(right));
#ifdef HAS_BOARD_INFO_DIAG
        snprintf(text, sizeof(text), "%s [%s]", text, Pad2ValidWireName(left));
        snprintf(text, sizeof(text), "%s-[%s]", text, Pad2ValidWireName(right));
#endif
    }
#ifdef HAS_BOARD_INFO_DIAG
    if(Fault.left_short_gnd) {
        snprintf(text, sizeof(text), "%s %s=%s,Gnd,", text, GpioPadToStr(left), Pad2ValidWireName(left));
    }
    if(Fault.left_short_vcc) {
        snprintf(text, sizeof(text), "%s %s=%s,VCC,", text, GpioPadToStr(left), Pad2ValidWireName(left));
    }

    if(Fault.right_short_gnd) {
        snprintf(text, sizeof(text), "%s %s=%s,Gnd,", text, GpioPadToStr(right), Pad2ValidWireName(right));
    }
    if(Fault.right_short_vcc) {
        snprintf(text, sizeof(text), "%s %s=%s,VCC", text, GpioPadToStr(right), Pad2ValidWireName(right));
    }
#endif

    return text;
}

bool CrossDetectDiagFault(const CrossDetectHandle_t* const Node) {
    bool res = false;
    Pad_t left = CrossDetectPinConfig[Node->left_num].pad;
    Pad_t right = CrossDetectPinConfig[Node->right_num].pad;
    if(Node->pair.Fault.fault_code) {
        LOG_WARNING(CROSS_DETECT, "%s", CrossDetectFault2Str(Node->pair.Fault, left, right));
    } else {
        res = true;
    }
    return res;
}
