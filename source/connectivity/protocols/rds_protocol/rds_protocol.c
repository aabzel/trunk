#include "rds_protocol.h"

#include <stdio.h>
#include <string.h>

#include "bit_const.h"
#include "byte_utils.h"
//#include "cli_utils.h"
#include "data_utils.h"
#include "debug_info.h"
#include "fat_fs_drv.h"

#ifdef HAS_MCU
#include "clock.h"
#include "common_functions.h"
#include "task_info.h"
#include "time_mcal.h"
#endif

#include "log.h"

#include "rds_diag.h"

RdsProtocol_t RdsProtocol = {0};

bool rds_protocol_init(void) {
    LOG_INFO(RDS, "Init");
    set_log_level(RDS, LOG_LEVEL_NOTICE);

    RdsProtocol.time_cnt = 0;
    RdsProtocol.text_cnt = 0;
    RdsProtocol.rx_pkt_cnt = 0;
    memset(RdsProtocol.RadioText, '_', 64);
    RdsProtocol.RadioText[64] = 0x00;

    memset(RdsProtocol.ProgServiceName, '_', 8);
    RdsProtocol.ProgServiceName[9] = 0x00;

    memset(RdsProtocol.ProgTypeName, '_', 8);
    RdsProtocol.ProgTypeName[9] = 0x00;
    return true;
}

static bool rds_proc_basic_tuning_message(RdsProtocol_t* instance) {
    bool res = false;
    LOG_DEBUG(RDS, "BasicTuning");
    if(instance){
    	res = true;
        char text[20] = "";
        uint8_t text_segment = 0;
        text_segment = instance->Message.BasicTuning0A.segment;
        uint8_t text_offset = text_segment * 2;
        char prog_name[3] = "";
        prog_name[0] = instance->Message.BasicTuning0A.ch1;
        prog_name[1] = instance->Message.BasicTuning0A.ch2;
        prog_name[2] = 0x00;

        instance->ProgServiceName[9] = 0x00;
        memcpy(&instance->ProgServiceName[text_offset], prog_name, 2);
        //print_mem((uint8_t*)instance->ProgServiceName, 8, true, true, true, true);
        snprintf(text, sizeof(text), "Seg: %u [%s]", text_segment, instance->ProgServiceName);
        LOG_DEBUG(RDS, "[%s]", text);
        res = fat_fs_write("BasicTuning.txt", text);
    }

    return res;
}

static bool rds_proc_prog_type_name_message(RdsProtocol_t* instance) {
    bool res = true;
    LOG_DEBUG(RDS, "ProgTypeName");

    uint8_t text_offset = 0;
    char ProgNameSeg[5] = "";
    char text[20] = "";
    //uint8_t text_segment1 = 0x0001 & instance->Message.BlockB.word;
    uint8_t text_segment = instance->Message.ProgTyteNameA.segment;
    text_offset = text_segment * 4;
    switch(instance->Message.ProgTyteNameA.b0) {
    case 0: {
        ProgNameSeg[0] = instance->Message.ProgTyteNameA.ch1;
        ProgNameSeg[1] = instance->Message.ProgTyteNameA.ch2;
        ProgNameSeg[2] = instance->Message.ProgTyteNameA.ch3;
        ProgNameSeg[3] = instance->Message.ProgTyteNameA.ch4;
        instance->ProgTypeName[9] = 0x00;
        memcpy(&instance->ProgTypeName[text_offset], ProgNameSeg, 4);
        //print_mem((uint8_t*)instance->ProgTypeName, 8, true, true, true, true);
        snprintf(text, sizeof(text), "Seg: %u [%s]", text_segment, instance->ProgTypeName);
        LOG_DEBUG(RDS, "[%s]", text);
        res = fat_fs_write("rds.txt", text);
    } break;
    case 1: {

    } break;
    }
    return res;
}

static bool rds_proc_text_message(RdsProtocol_t* instance) {
    bool res = true;
    uint8_t text_size = 0;
    instance->text_cnt++;
    char rds_text[10] = "";
    char text[20] = "";
    LOG_DEBUG(RDS, "RadioText");

    uint8_t text_segment = 0;
    text_segment = instance->Message.RadioTextFrame2A.segment;
    uint8_t text_offset = 0;
    switch(instance->Message.BlockB.b0) {
    case GROUP_TYPE_A:
        text_size = 4;
        text_offset = text_size * text_segment;
        LOG_DEBUG(RDS, "A OffSet:%u Seg:%u", text_offset, text_segment);
        rds_text[0] = instance->Message.RadioTextFrame2A.ch1;
        rds_text[1] = instance->Message.RadioTextFrame2A.ch2;
        rds_text[2] = instance->Message.RadioTextFrame2A.ch3;
        rds_text[3] = instance->Message.RadioTextFrame2A.ch4;
        rds_text[4] = 0x00;
#if 0
    	instance->RadioText[0+text_offset]=instance->Message.RadioTextFrame2A.ch1;
    	instance->RadioText[1+text_offset]=instance->Message.RadioTextFrame2A.ch2;
    	instance->RadioText[2+text_offset]=instance->Message.RadioTextFrame2A.ch3;
    	instance->RadioText[3+text_offset]=instance->Message.RadioTextFrame2A.ch4;
#endif
        break;
    case GROUP_TYPE_B:
        text_size = 2;
        text_offset = text_size * text_segment;
        LOG_DEBUG(RDS, "B Offset:%u Seg:%u", text_offset, text_segment);
        if(instance->Message.RadioTextFrame2B.pi_code != instance->Message.RadioTextFrame2B.pi_code1) {
            LOG_DEBUG(RDS, "PicodeErr %x %x", instance->Message.RadioTextFrame2B.pi_code,
                        instance->Message.RadioTextFrame2B.pi_code1);
        }
#if 0
    	instance->RadioText[0+text_offset]=instance->Message.RadioTextFrame2B.ch1;
    	instance->RadioText[1+text_offset]=instance->Message.RadioTextFrame2B.ch2;
#endif
        rds_text[0] = instance->Message.RadioTextFrame2B.ch1;
        rds_text[1] = instance->Message.RadioTextFrame2B.ch2;
        rds_text[2] = 0x00;
        break;
    }
    instance->RadioText[64] = 0x00;
    memcpy(&instance->RadioText[text_offset], rds_text, text_size);
   // print_mem((uint8_t*)instance->RadioText, 64, true, true, true, true);
    snprintf(text, sizeof(text), "Seg: %u [%s]", text_segment, rds_text);
    LOG_DEBUG(RDS, "[%s]", text);
    LOG_DEBUG(RDS, "[%s]", instance->RadioText);
#ifdef HAS_FAT_FS
    res = fat_fs_write("RadioText.txt", text);
    res = fat_fs_write("RadioText.txt", instance->RadioText);
    if(res) {
        LOG_DEBUG(FAT_FS, "LogOk");
    } else {
        LOG_ERROR(FAT_FS, "LogErr");
    }
#endif
    return res;
}
/**/
int8_t RdsLocTimeOffSet2Num(uint8_t loctimeoffset) {
    int8_t loc_time_off_set_val = 0;
    uint8_t loc_time_off_set_abs_val = MASK_5BIT & loctimeoffset;
    double loc_time_off_set_h = ((double)loc_time_off_set_abs_val) * 0.5;
    if(BIT_5 == (loctimeoffset & BIT_5)) {
        loc_time_off_set_val = ((int8_t)(-1.0 * loc_time_off_set_h));
    } else {
        loc_time_off_set_val = ((int8_t)loc_time_off_set_h);
    }
    return loc_time_off_set_val;
}

/*CT Clock Time and date at the start of every minute*/
static bool rds_proc_time_date_message(RdsProtocol_t* instance) {
    bool res = false;
    instance->time_cnt++;

    switch((uint8_t)instance->Message.BlockB.b0){
    case GROUP_TYPE_B:{
    	LOG_WARNING(RDS, "4BTimeDateFrame!");
        res = true;
    } break;
    case GROUP_TYPE_A:{
        LOG_WARNING(RDS, "4A TimeDateFrame!");
        char text[80] = "";
        ClockTimeDate_t LocMessage={0};
        memcpy(&LocMessage, &instance->Message, sizeof(ClockTimeDate_t));
#if 0
        snprintf(text, sizeof(text), "LocTimeOffSet: %d Time: %u:%u",
        		RdsLocTimeOffSet2Num(LocMessage.ClockTimeDate.loc_time_offset),
    			LocMessage.ClockTimeDate.hour,
    			LocMessage.ClockTimeDate.min);
        LOG_WARNING(RDS, "%s", text);
        LocMessage.BlockA.word=reverse_byte_order_uint16 (LocMessage.BlockA.word);
        LocMessage.BlockB.word=reverse_byte_order_uint16 (LocMessage.BlockB.word);
        LocMessage.BlockC.word=reverse_byte_order_uint16 (LocMessage.BlockC.word);
        LocMessage.BlockD.word=reverse_byte_order_uint16 (LocMessage.BlockD.word);
#endif

        snprintf(text, sizeof(text), "%s",ClockTimeDate2Str(&LocMessage));
        LOG_WARNING(RDS, "%s", text);
#ifdef HAS_FAT_FS
        res = fat_fs_write("RdsTime.txt", text);
        if(res) {
            LOG_DEBUG(FAT_FS, "LogOk");
        } else {
            LOG_ERROR(FAT_FS, "LogErr");
        }
#endif

        snprintf(text, sizeof(text), "RawTime:0x%04x,0x%04x,0x%04x,0x%04x", LocMessage.BlockA.word, LocMessage.BlockB.word,
                 LocMessage.BlockC.word, LocMessage.BlockD.word);
        LOG_WARNING(RDS, "%s", text);
#ifdef HAS_FAT_FS
        res = fat_fs_write("RdsTimeRaw.txt", text);
        if(res) {
            LOG_DEBUG(FAT_FS, "LogOk");
        } else {
            LOG_ERROR(FAT_FS, "LogErr");
        }
#endif
        res = true;
    } break;

    }


    return res;
}

bool rds_proc_message(uint16_t* words) {
    bool res = false;
    cli_printf(CRLF CRLF);
    RdsProtocol.Message.BlockA.word = words[0];
    RdsProtocol.Message.BlockB.word = words[1];
    RdsProtocol.Message.BlockC.word = words[2];
    RdsProtocol.Message.BlockD.word = words[3];
#if 0
    char text[100];
    snprintf(text, sizeof(text), "RawFrame: %04x %04x %04x %04x",
    		RdsProtocol.Message.BlockA.word,RdsProtocol.Message.BlockB.word,
			RdsProtocol.Message.BlockC.word,RdsProtocol.Message.BlockD.word);
    LOG_NOTICE(RDS, "%s", text);
#endif
    log_level_t log_level = log_level_get(RDS);
    if(LOG_LEVEL_DEBUG == log_level) {
        print_mem((uint8_t*)RdsProtocol.Message.byte, 8, true, true, true, true);
        res = rds_print_message(&RdsProtocol.Message);
    }
    RdsProtocol.rx_pkt_cnt++;

    RdsDiagNode(&RdsProtocol);


    switch(RdsProtocol.Message.BlockB.group_type) {
    case GR_TYPE_CLOCK_TIME_DATE:
        res = rds_proc_time_date_message(&RdsProtocol);
        break;
    case GR_TYPE_PROG_TYPE_NAME:
        res = rds_proc_prog_type_name_message(&RdsProtocol);
        break;
    case GR_TYPE_BASIC:
        res = rds_proc_basic_tuning_message(&RdsProtocol);
        break;
    case GR_TYPE_RADIO_TEXT:
        res = rds_proc_text_message(&RdsProtocol);
        break;
    case GR_TYPE_PROG_NUM:
    	res = true;
    	break;
    case GR_TYPE_ENH_OTHER_NET_INF:
    	res = true;
    	break;
    case GR_TYPE_TRAFFIC_MES:
    	res = true;
    	break;
    case GR_TYPE_IN_HOUSE_APP:
    	res = true;
    	break;

    case GR_TYPE_EMERGENCY:
    	res = true;
    	break;
    case GR_TYPE_OPEN_DATA_APP:
    	res = true;
    	break;

    default:
        LOG_ERROR(RDS, "UnProcGroupType %u=[%s]", RdsProtocol.Message.BlockB.group_type,
                  GroupType2Str(RdsProtocol.Message.BlockB.group_type));
        res = rds_print_message(&RdsProtocol.Message);
        break;
    }
    return res;
}

bool rds_mirror_words(uint16_t* word) {
    bool res = false;
    if(word) {
        word[0] = reverse_byte_order_uint16(word[0]);
        word[1] = reverse_byte_order_uint16(word[1]);
        word[2] = reverse_byte_order_uint16(word[2]);
        word[3] = reverse_byte_order_uint16(word[3]);
        res = true;
    }
    return res;
}

bool rds_reverse_words(uint16_t* word) {
    bool res = false;
    if(word) {
        res = swap_16(&word[0], &word[3]);
        if(res) {
            res = swap_16(&word[1], &word[2]);
        }
    }
    return res;
}
