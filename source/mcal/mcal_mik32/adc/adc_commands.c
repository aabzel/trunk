#include "adc_commands.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "adc_custom_diag.h"
#include "adc_config.h"
#include "none_blocking_pause.h"
#include "log_utils.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "adc_diag.h"
#include "adc_drv.h"
#include "adc_types.h"
#include "log.h"
#include "log_constants.h"
#include "str_utils.h"
#include "sys_config.h"
#include "table_utils.h"
#include "writer_config.h"

bool adc_read_command(int32_t argc, char* argv[]){
	bool res = false;
	uint8_t adc_num=0;
	uint16_t adc_channel=0;
	if(2==argc) {
        res = try_str2uint8(argv[0], &adc_num);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr adc_num %s", argv[0]);
        }
        res = try_str2uint16(argv[1], &adc_channel);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr AdcChannel %s", argv[1]);
        }
	}
	if(res) {
		res=adc_init_channel(adc_num, (AdcChannel_t) adc_channel);
		if(res) {
            AdcHandle_t* AdcNode = AdcGetNode( adc_num);
            if(AdcNode) {
            	HAL_StatusTypeDef ret=HAL_ADC_Start(&AdcNode->adc_h);
            	if(HAL_OK==ret){
            		res= wait_ms(500);

            		ret = HAL_ADC_PollForConversion(&AdcNode->adc_h, 200);
            	}else{
            		LOG_ERROR(LG_ADC,"%u StartErr",adc_num);
            	}
            	AdcNode->code = HAL_ADC_GetValue(&AdcNode->adc_h);
            	LOG_INFO(LG_ADC,"%u",AdcNode->code);
            }else {
            	LOG_ERROR(LG_ADC,"%u NodeErr",adc_num);
            }
		}else {
			LOG_ERROR(LG_ADC,"init Adc %u Channel %u",adc_num,adc_channel);
		}
	}else {
		LOG_ERROR(LG_ADC,"Usage: adr AdcNum");
	}
    return res;
}

bool adc_diag_command(int32_t argc, char* argv[]){
	bool res = false;
    return res;
}

bool adc_init_command(int32_t argc, char* argv[]){
	bool res = false;
	return res;
}

bool adc_in_diag(char* key_word1, char* key_word2){
    bool res = false;
    static const table_col_t cols[] = {{5, "No"},
                                       {6, "Adc"},
                                       {6, "Channel"},
                                       {6, "Code"},
                                       {8, "Code"},
                                       {6, "Name"}
    };
    uint16_t num = 0;
    uint32_t chan_cnt=adc_channel_get_cnt();
    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    uint8_t i = 0;
    char log_line[120];
    for(i = 0; i < chan_cnt; i++) {
        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, AdcNum2Str(AdcChannels[i].num));
        snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, AdcChannel2Str(AdcChannels[i].channel));
        snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, AdcChannels[i].code);
        snprintf(log_line, sizeof(log_line), "%s 0x%04x " TSEP, log_line, AdcChannels[i].code);
        const AdcChannelConfig_t* AdcChannelCongigNode=AdcChannelGetCongigNode(AdcChannels[i].num, AdcChannels[i].channel);
        if(AdcChannelCongigNode){
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, AdcChannelCongigNode->name);
        }else{
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, "?");
        }
        if(is_contain(log_line, key_word1, key_word2)) {
            cli_printf(TSEP " %3u ", num);
            cli_printf("%s" CRLF, log_line);
            num++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));

    return res;
}

bool adc_inputs_command(int32_t argc, char* argv[]){
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
        res = adc_in_diag(keyWord1, keyWord2);
    }
    return res;
}
