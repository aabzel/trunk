#include "dac_custom_commands.h"

#include <stdio.h>
#include <string.h>

#include "dac_config.h"
#include "dac_custom_diag.h"
#include "dac_mcal.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "log_utils.h"
#include "none_blocking_pause.h"
#include "std_includes.h"
#include "str_utils.h"
#include "sys_config.h"
#include "table_utils.h"
#include "writer_config.h"

bool dac_custom_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t dac_num = 0;
    uint16_t dac_channel = 0;
    if(2 == argc) {
        res = try_str2uint8(argv[0], &dac_num);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr dac_num %s", argv[0]);
        }
        res = try_str2uint16(argv[1], &dac_channel);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr DacChannel %s", argv[1]);
        }
    }
    if(res) {
        res = dac_init_channel(dac_num, (DacChannel_t)dac_channel);
        if(res) {
            DacHandle_t* DacNode = DacGetNode(dac_num);
            if(DacNode) {
                HAL_StatusTypeDef ret = HAL_DAC_Start(&DacNode->dac_h);
                if(HAL_OK == ret) {
                    res = wait_ms(500);

                    ret = HAL_DAC_PollForConversion(&DacNode->dac_h, 200);
                } else {
                    LOG_ERROR(LG_DAC, "%u StartErr", dac_num);
                }
                DacNode->code = HAL_DAC_GetValue(&DacNode->dac_h);
                LOG_INFO(LG_DAC, "%u", DacNode->code);
            } else {
                LOG_ERROR(LG_DAC, "%u NodeErr", dac_num);
            }
        } else {
            LOG_ERROR(LG_DAC, "init Dac %u Channel %u", dac_num, dac_channel);
        }
    } else {
        LOG_ERROR(LG_DAC, "Usage: adr DacNum");
    }
    return res;
}

bool dac_custom_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool dac_custom_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool dac_custom_in_diag(char* key_word1, char* key_word2) {
    bool res = false;
    static const table_col_t cols[] = {{5, "No"}, {6, "Dac"}, {6, "Channel"}, {6, "Code"}, {8, "Code"}, {6, "Name"}};
    uint16_t num = 0;
    uint32_t chan_cnt = dac_channel_get_cnt();
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i = 0;
    for(i = 0; i < chan_cnt; i++) {
        char log_line[120];
        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, DacNumToStr(DacChannelInstance[i].num));
        snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, DacChannelToStr(DacChannelInstance[i].channel));
        snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, DacChannelInstance[i].code);
        snprintf(log_line, sizeof(log_line), "%s 0x%04x " TSEP, log_line, DacChannelInstance[i].code);
        const DacChannelConfig_t* DacChannelConfig =
            DacChannelGetConfigV2(DacChannelInstance[i].num, DacChannelInstance[i].channel);
        if(DacChannelConfig) {
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, DacChannelConfig->name);
        } else {
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, "?");
        }
        if(is_contain(log_line, key_word1, key_word2)) {
            cli_printf(TSEP " %3u ", num);
            cli_printf("%s" CRLF, log_line);
            num++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

#if 0
bool dac_custom_inputs_command(int32_t argc, char* argv[]){
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";
    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }
    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }
    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(2 < argc) {
        LOG_ERROR(GPIO, "Usage: ain keyWord");
    }
    if(res) {
        res = dac_in_diag(keyWord1, keyWord2);
    }
    return res;
}
#endif
