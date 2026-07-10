#include "sound_recorder_diag.h"

#include "sound_recorder_mcal.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "table_utils.h"
#include "fat_fs_diag.h"
#include "writer_config.h"
#include "log.h"

const char* SoundRecorderConfigToStr(const SoundRecorderConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* SoundRecorderNodeToStr(const SoundRecorderHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sFile:%s,", text, Node->file_name);
        snprintf(text, sizeof(text), "%sSamFreq:%u Hz,", text, Node->sample_freq_hz);
        snprintf(text, sizeof(text), "%sstate:%u,", text, Node->wr_ok_cnt);
        snprintf(text, sizeof(text), "%sstate:%u,", text, Node->state);
        snprintf(text, sizeof(text), "%si2s_error_cnt:%u,", text, Node->i2s_error_cnt);
        snprintf(text, sizeof(text), "%srec_cnt:%u,", text, Node->rec_cnt);
        snprintf(text, sizeof(text), "%ssample_cnt:%u,", text, Node->sample_cnt);
        snprintf(text, sizeof(text), "%sErrCnt:%u,", text, Node->error_cnt);
        snprintf(text, sizeof(text), "%stotal_file_size:%u,", text, Node->total_file_size);
        snprintf(text, sizeof(text), "%sstart_rec_ms:%u,", text, Node->start_rec_ms);
        snprintf(text, sizeof(text), "%sstop_rec_ms:%u,", text, Node->stop_rec_ms);
        snprintf(text, sizeof(text), "%sdata_size:%u,", text, Node->data_size);
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%scur_save_size:%u,", text, Node->cur_save_size);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool SoundRecorderPrintfMem(const SoundRecorderHandle_t* const Node) {
    bool res = false ;
    if(Node) {
        uint32_t i = 0 ;
        uint32_t s = 0 ;
        for(s=0,i=0;i<Node->sample_cnt;s++,i+=2){
            char temp[150] = {0};
            strcpy(temp, "");
            snprintf(temp, sizeof(temp), "%s %u ", temp, s);
            snprintf(temp, sizeof(temp), "%s %u ", temp, i);
            snprintf(temp, sizeof(temp), "%s 0x%04x ", temp, Node->RxSampleArray[i]);
            snprintf(temp, sizeof(temp), "%s 0x%04x ", temp, Node->RxSampleArray[i+1]);

            snprintf(temp, sizeof(temp), "%s %d ", temp, Node->RxSampleArray[i]);
            snprintf(temp, sizeof(temp), "%s %d ", temp, Node->RxSampleArray[i+1]);
            cli_printf("%s",temp);
        }
    }
    return res;
}

bool sound_recorder_diag_one(uint8_t num) {
    bool res = false;
    const SoundRecorderConfig_t *Config = SoundRecorderGetConfig(num);
    if(Config) {
        LOG_INFO(SOUND_RECORDER, "%s", SoundRecorderConfigToStr(Config));
        SoundRecorderHandle_t *Node = SoundRecorderGetNode(num);
        if(Node) {
            LOG_INFO(SOUND_RECORDER, "%s", SoundRecorderNodeToStr(Node));
            res = true;
        }
    }

    return res;
}

bool sound_recorder_diag(void) {
    bool res = false;
    res = sound_recorder_diag_one(1);
    return res;
}


bool sound_recorder_raw_reg_diag(uint8_t num) {
    bool res = false;
    SoundRecorderHandle_t *Node = SoundRecorderGetNode(num);
    if(Node){
        res = true;
    }
    return res;
}

bool sound_recorder_stop_report(const SoundRecorderHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(SOUND_RECORDER, "RecDuration:%u ms", Node->duration_ms);
        LOG_INFO(SOUND_RECORDER, "WrOkCnt:%u", Node->wr_ok_cnt);

        if(FR_OK!=Node->fat_fs_err_code){
            LOG_ERROR(SOUND_RECORDER, "FatErrCode:%u=%s", Node->fat_fs_err_code, FatFsResToStr(Node->fat_fs_err_code));
        }

        if(Node->error_cnt){
            LOG_ERROR(SOUND_RECORDER, "WrErrorCnt:%u", Node->error_cnt);
        }

        if(Node->long_write_error_cnt){
            LOG_WARNING(SOUND_RECORDER, "longWriteErrorCnt:%u", Node->long_write_error_cnt);
        }

        if(Node->error_size_cnt){
            LOG_ERROR(SOUND_RECORDER, "WrSzErrorCnt:%u", Node->error_size_cnt);
        }

        LOG_INFO(SOUND_RECORDER, "total_file_size:%u", Node->total_file_size);

        if(Node->error_size_cnt){
            LOG_ERROR(SOUND_RECORDER, "I2SerrCnt:%u", Node->i2s_error_cnt);
        }

        LOG_INFO(SOUND_RECORDER, "rec_cnt:%u", Node->rec_cnt);
        LOG_INFO(SOUND_RECORDER, "FileNAme:%s", Node->file_name);
        res = true;
    }
    return res;
}

