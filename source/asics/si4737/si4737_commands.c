#include "si4737_commands.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "convert.h"
#include "log.h"
#include "data_utils.h"
#include "common_diag.h"
#include "si4737_diag.h"
#include "si4737_drv.h"
#ifdef HAS_RDS
#include "si4737_rds_drv.h"
#endif
#include "si4737_config.h"
#include "table_utils.h"
#include "writer_config.h"
#include "str_utils.h"
#include "radio_stations_rus.h"

static bool si4737_read_property_map(char* key_word1, char* key_word2) {
    bool res = false;
    uint8_t i = 0;
    static const table_col_t cols[] = {{5, "No"}, {8, "id"}, {8, "val"}, {23, "val"},  {20, "name"}};
    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    uint32_t cnt = si4737_get_prop_cnt();
    uint16_t num = 0;
    char log_line[120];
    for (i=0; i<cnt; i++) {
        res = si4737_get_property(Si4737Property[i].id, &Si4737Property[i].val);
        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s 0x%04x " TSEP, log_line, Si4737Property[i].id);
        snprintf(log_line, sizeof(log_line), "%s 0x%04x " TSEP, log_line, Si4737Property[i].val);
        snprintf(log_line, sizeof(log_line), "%s 0b%19s " TSEP, log_line, utoa_bin16(Si4737Property[i].val));
        snprintf(log_line, sizeof(log_line), "%s %18s  " TSEP, log_line, SiPropertyToStr(Si4737Property[i].id));
        if(is_contain(log_line, key_word1, key_word2)) {
            cli_printf(TSEP " %3u ", num);
            cli_printf("%s" CRLF, log_line);
            num++;
        }
    }
    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    return res;
}

bool si4737_property_map_command(int32_t argc, char* argv[]) {
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

    if(res) {
        res = si4737_read_property_map(keyWord1, keyWord2);
    }else {
        LOG_ERROR(SI4737, "Usage: sim keyWord");
    }
    return res;
}

bool si4737_reg_read_command(int32_t argc, char* argv[]){
    bool res = false;
  
    return res;
}

bool si4737_reg_write_command(int32_t argc, char* argv[]){
    bool res = false;
  
    return res;
}

bool si4737_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
  
    return res;
}



bool si4737_diag_low_level_command(int32_t argc, char* argv[]){
    bool res= false;

    return res;
}


bool si4737_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0==argc){
        res = si4737_is_connected();
        if(res){
            LOG_INFO(SI4737,"Connected");
        }else{
            LOG_ERROR(SI4737,"UnMounted");
        }
        Si4737FullRevResp_t FullRevResp;
        res =  si4737_get_rev(&FullRevResp);
        if(res){
            LOG_INFO(SI4737,"ChipRev 0x%02x %c",FullRevResp.RevResp.chiprev,FullRevResp.RevResp.chiprev);
            LOG_INFO(SI4737,"cmp 0x%02x:0x%02x",FullRevResp.RevResp.cmpmajor,FullRevResp.RevResp.cmpminor);
            LOG_INFO(SI4737,"FW 0x%02x:0x%02x",FullRevResp.RevResp.fwmajor ,FullRevResp.RevResp.fwminor);
            LOG_INFO(SI4737,"Patch  0x%04x",FullRevResp.RevResp.patch );
            LOG_INFO(SI4737,"PN: 0x%02x",FullRevResp.RevResp.pn );

            LOG_INFO(SI4737,"cmp %c:%c",FullRevResp.RevResp.cmpmajor,FullRevResp.RevResp.cmpminor);
            LOG_INFO(SI4737,"FW %c:%c",FullRevResp.RevResp.fwmajor ,FullRevResp.RevResp.fwminor);
        }

        Si4737Handler.fm_freq_mhz=0.0;
        Si4737Handler.rssi=0;
        Si4737Handler.snr=0;
        res= si4737_get_fm_tune_freq(&Si4737Handler,SEEK_KEEP  , STC_INT_KEEP  );
        if(res){
            LOG_INFO(SI4737,"FmFreq %f MHz",Si4737Handler.fm_freq_mhz );
            LOG_INFO(SI4737,"RSSI: %u dBuV",Si4737Handler.rssi );
            LOG_INFO(SI4737,"SNR:  %u dB",Si4737Handler.snr );
        }

        res= si4737_get_rsq_status(&Si4737Handler);
        if(res){
            LOG_INFO(SI4737,"FreqOffSet %f Hz",Si4737Handler.freq_offset );
            LOG_INFO(SI4737,"RSSI: %u dBuV",Si4737Handler.rssi );
            LOG_INFO(SI4737,"SNR:  %u dB",Si4737Handler.snr );
        }

        res= si4737_get_rx_volume( &Si4737Handler.rx_volume);
        if(res){
        	LOG_INFO(SI4737,"RxVol: %u",Si4737Handler.rx_volume );
        }
#ifdef HAS_RDS
        res=si4737_get_fm_rds_int_fifo_cnt(&Si4737Handler.rds_fifo_cnt);
        if(res){
            LOG_INFO(SI4737,"RdsFifoCnt: %u",Si4737Handler.rds_fifo_cnt );
        }
#endif
        res = si4737_get_digital_output_format(&Si4737Handler);
        if(res){
        	 LOG_INFO(SI4737,"Digital Output Audio Sample Precision: %u bit",Si4737Handler.out_size_bit );
        	 LOG_INFO(SI4737,"OutFall %s",OutFallToStr(Si4737Handler.out_fall) );
        	 LOG_INFO(SI4737,"OutMono: %s",OutMonoToStr(Si4737Handler.out_mono) );
        	 LOG_INFO(SI4737,"OutMode: %s",OutModeToStr(Si4737Handler.out_mode) );
        }

    }
    return res;
}

bool si4737_rf_seek_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t seek_dir=SEEK_DIR_UP;
    uint8_t seek_end=SEEK_END_WRAP;
    if(0==argc){
        res = true;
    }
    if(2==argc){
        res = try_str2uint8(argv[0], &seek_dir);
        if(false==res){
            LOG_ERROR(SI4737,"ParseErr SeekDir %s",argv[0]);
        }
        res = try_str2uint8(argv[1], &seek_end);
        if(false==res){
            LOG_ERROR(SI4737,"ParseErr SeekEnd %s",argv[1]);
        }
    }
    if(res) {
        res = si4737_fm_seek_start( (SeekDir_t) seek_dir, (SeekEnd_t)  seek_end);
        if(res){
            LOG_INFO(SI4737, "SeekOk");
        }else{
            LOG_ERROR(SI4737, "SeekErr");
        }

    }else {
        LOG_ERROR(SI4737, "Usage: sis Dir End");
    }
    return res;
}

bool si4737_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0==argc){
        res = true;
    }
    if(res){
        res= si4737_init();
        if(res){
            LOG_INFO(SI4737,"InitOk" );
        }else{
            LOG_ERROR(SI4737,"InitErr" );
        }
    }else{
        LOG_ERROR(SI4737, "Usage: sii");
    }
    return res;
}


bool si4737_play_command(int32_t argc, char* argv[]){
    bool res = false;

    return res;
}

bool si4737_property_get_command(int32_t argc, char* argv[]){
    bool res = false;
    uint16_t property = 0;
    uint16_t val = 0;
    if(1 == argc) {
        res = try_str2uint16(argv[0], &property);
        if(false == res) {
            LOG_ERROR(SI4737, "ParseErr property %s", argv[0]);
        }
    }
    if(res) {
        res = si4737_get_property(property, &val);
        if(res) {
            LOG_INFO(SI4737, "GetPropOk 0x%08x=0x%08x",property,val);
        }else {
            LOG_ERROR(SI4737, "GetPropErr 0x%08x",property);
        }
    }else{
        LOG_ERROR(SI4737, "sir prop");
    }
    return res;
}

bool si4737_property_set_command(int32_t argc, char* argv[]){
    bool res = false;
    uint16_t property = 0;
    uint16_t val = 0;
    if(2 == argc) {
        res = try_str2uint16(argv[0], &property);
        if(false == res) {
            LOG_ERROR(SI4737, "ParseErr property %s", argv[0]);
        }

        res = try_str2uint16(argv[1], &val);
        if(false == res) {
            LOG_ERROR(SI4737, "ParseErr Val %s", argv[1]);
        }
    }
    if(res) {
        res = si4737_set_property(property, val);
        if(res) {
            LOG_INFO(SI4737, "SetPropOk 0x%08x=0x%08x",property,val);
        }else {
            LOG_ERROR(SI4737, "SetPropErr 0x%08x=0x%08x",property,val);
        }
    }else{
        LOG_ERROR(SI4737, "sps prop");
    }
    return res;
}

bool si4737_set_rf_freq_command(int32_t argc, char* argv[]){
    bool res = false;
    double fm_freq = 0.0;
    if(1 == argc) {
        res = try_str2double(argv[0], &fm_freq);
        if(false == res) {
            LOG_ERROR(SI4737, "ParseErr FmFreq %s", argv[0]);
        }
    }

    if(res) {
        res= si4737_set_fm_tune_freq(  fm_freq);
        if(res){
            LOG_INFO(SI4737, "SetOk %f MHz", fm_freq);
        }else{
            LOG_ERROR(SI4737, "SetErr %f MHz", fm_freq);
        }
    }else{
        LOG_ERROR(SI4737, "sirf FmFreq");
    }

    return res;
}

bool si4737_set_rx_volume_command(int32_t argc, char* argv[]){
    bool res = false;
    uint16_t rx_volume = 0;
    if(1==argc){
        res = try_str2uint16(argv[0], &rx_volume);
        if(false == res) {
            LOG_ERROR(SI4737, "ParseErr RxVolume %s", argv[0]);
        }
    }
    if(res){
    	res= si4737_set_rx_volume( rx_volume);
        if(res){
        	LOG_INFO(SI4737, "SetVolOk %u", rx_volume);
        }else{
        	LOG_ERROR(SI4737, "SetVolOk %u", rx_volume);
        }
    }else{
    	LOG_ERROR(SI4737, "Usage: siv Vol");
    	LOG_INFO(SI4737, "Vol [0...63]");
    }
    return res;
}

bool si4737_get_interrupts_command(int32_t argc, char* argv[]){
    bool res = false;
    if(0==argc){
        res = true;
        LOG_INFO(SI4737, "ErrCnt: %u",Si4737Handler.err_cnt);
        LOG_INFO(SI4737, "ValidCnt: %u",Si4737Handler.valid_cnt);
        LOG_INFO(SI4737, "ClearToSendCnt: %u",Si4737Handler.cts_cnt);
#ifdef HAS_RDS
        LOG_INFO(SI4737, "RdsIntCnt: %u",Si4737Handler.rds_int_cnt);
        LOG_WARNING(SI4737, "RdsRecvCnt: %u",Si4737Handler.rds_recv_cnt);
#endif
        LOG_INFO(SI4737, "RsqIntCnt: %u",Si4737Handler.rsq_int_cnt);
        LOG_INFO(SI4737, "AudioSigQaCnt: %u",Si4737Handler.asq_cnt);
        LOG_INFO(SI4737, "Seek/TuneCmptCnt: %u",Si4737Handler.stc_int_cnt);
    }
    return res;
}

#ifdef HAS_RDS
bool si4737_get_rds_command(int32_t argc, char* argv[]){
	bool res = false;
	uint8_t fifo_cnt = 1;
	if(0==argc) {
		res = true;
	}
	if(res) {
	    res = si4737_get_fm_rds_status(&Si4737Handler, &fifo_cnt);
	    if(res) {
	    	LOG_INFO(SI4737, "GetRdsOk");
	    }else {
	    	LOG_ERROR(SI4737, "GetRdsErr");
	    }
	}else {
		LOG_ERROR(SI4737, "Usage: sgr");
	}
	return res;
}
#endif

static bool si4737_get_stations_diag(char* key_word1, char* key_word2){
    bool res = false;
    uint16_t s =0;
    static const table_col_t cols[] = {{4, "#"}, {4, "id"}, {7, "Freq"}, {15, "name"}};
    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    char log_line[120];
    uint16_t num = 1;
    uint16_t cnt= fm_statinos_cnt( );
    for(s=0;s<cnt;s++){
        strcpy(log_line, TSEP);
              snprintf(log_line, sizeof(log_line), "%s %2u " TSEP, log_line, FmStationInfoLut[s].id);
              snprintf(log_line, sizeof(log_line), "%s %5.1f " TSEP, log_line, FmStationInfoLut[s].fm_freq_mhz);
              snprintf(log_line, sizeof(log_line), "%s %13s " TSEP, log_line, FmStationInfoLut[s].name);
              if(is_contain(log_line, key_word1, key_word2)) {
                  cli_printf(TSEP " %2u ", num);
                  cli_printf("%s" CRLF, log_line);
                  num++;
              }
    }
    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    return res;
}

bool si4737_get_stations_command(int32_t argc, char* argv[]) {
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
        LOG_ERROR(GPIO, "Usage: sst keyWord");
    }
    if(res) {
        res = si4737_get_stations_diag(keyWord1, keyWord2);
    }
    return res;
}

bool si4737_set_stations_command(int32_t argc, char* argv[]){
    bool res = false;
    char station_name[20]="??";
    if(0==argc){
        res = true;
    }
    if(1==argc){
        strcpy(station_name,argv[0]);
        res = true;
    }
    if(res){
        res=fm_stations_set(station_name);
        if(res) {
            LOG_INFO(SI4737, "SetFmStationOk");
        }else {
            LOG_ERROR(SI4737, "SetFmStationErr");
        }
    }else{
        LOG_ERROR(SI4737, "Usage: sss name");
    }

    return res;
}


bool si4737_set_hard_mute_command(int32_t argc, char* argv[]){
    bool res = false;
    bool right=false;
    bool left=false;
    if(2==argc){
        res = try_str2bool(argv[0], &left);
        if(false == res) {
            LOG_ERROR(SI4737, "ParseErr left %s", argv[0]);
        }
        res = try_str2bool(argv[1], &right);
        if(false == res) {
            LOG_ERROR(SI4737, "ParseErr right %s", argv[1]);
        }
    }
    if(res) {
        res = si4737_set_mute(left,right);
        if(res){
            LOG_INFO(SI4737, "SetHwMuteOk");
        }
    }else{
        LOG_ERROR(SI4737, "Usage: shm L R");
    }
    return res;
}

bool si4737_power_down_command(int32_t argc, char* argv[]){
    bool res = false;
    if(1==argc){
        res = true;
    }
    if(res){
        res = si4737_power_down();
        if(res){
            LOG_INFO(SI4737, "PowerDownOk");
        }
    }else{
        LOG_ERROR(SI4737, "Usage: spd");
    }
    return res;
}
