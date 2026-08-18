#include "mic2026_commands.h"

#include <stdbool.h>
#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "gpio_diag.h"
#include "log.h"
#include "mic2026_diag.h"
#include "mic2026_drv.h"
#include "table_utils.h"
#include "writer_config.h"

bool cmd_mic2026_get_channel(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t channel = 0;
    if(1 == argc) {
        res = try_str2uint8(argv[0], &channel);
        if(false == res) {
            LOG_ERROR(MIC2026, "ParseErr", argv[0]);
        }
    }
    if(res) {
        GpioLogicLevel_t ll = mic2026_get_channel_ctrl(channel);
        LOG_INFO(MIC2026, "Get Ch:%u LL %u", channel, ll);
    } else {
        LOG_ERROR(MIC2026, "Usage: mig channel");
    }
    return res;
}

bool cmd_mic2026_set_channel(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t channel = 0;
    bool on_off = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &channel);
    }
    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
    }
    if(res) {
        res = mic2026_set_channel_ctrl(channel, on_off);
        if(res) {
            LOG_INFO(MIC2026, "Set Ch:%u  %u", channel, on_off);
        }
    } else {
        LOG_ERROR(MIC2026, "Usage: mis channel OnOff");
    }
    return res;
}

bool cmd_mic2026_diag(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        static const table_col_t cols[] = {
            {5, "Chan"}, {6, "PadCtr"}, {6, "PadFb"}, {5, "Set"}, {5, "Real"}, {5, "Fb"},
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        uint8_t chan = 0;
        char log_line[120];
        for(chan = 0; chan <= MIC2026_CHAN_CNT; chan++) {
            Mic2026ChannelConfig_t* ConfNode = GetConfigRelyNode((Mic2026Channel_t)chan);
            Mic2026ChannelVal_t* RelyNode = GetRelyNode((Mic2026Channel_t)chan);
            if(RelyNode) {
                if(ConfNode) {
                    strcpy(log_line, TSEP);
                    snprintf(log_line, sizeof(log_line), "%s %2s  " TSEP, log_line, Mic2026ChanToStr(chan));
                    snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, GpioPadToStr(ConfNode->CtrlPad.byte));
                    snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, GpioPadToStr(ConfNode->FbPad.byte));
                    snprintf(log_line, sizeof(log_line), "%s %2s  " TSEP, log_line,
                             GpioLevelToStr(RelyNode->CtrlPad.Set));
                    snprintf(log_line, sizeof(log_line), "%s %2s  " TSEP, log_line,
                             GpioLevelToStr(RelyNode->CtrlPad.Real));
                    snprintf(log_line, sizeof(log_line), "%s %2s  " TSEP, log_line, GpioLevelToStr(RelyNode->FbPadVal));
                    cli_printf("%s" CRLF, log_line);
                    res = true;
                }
            }
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    } else {
        LOG_ERROR(MIC2026, "Usage: mid");
    }
    return res;
}

bool cmd_mic2026_init(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = mic2026_init();
        if(false == res) {
            LOG_ERROR(MIC2026, "InitErr");
        } else {
            LOG_INFO(MIC2026, "InitOk");
        }
    } else {
        LOG_ERROR(MIC2026, "Usage: mii");
    }
    return res;
}
