#include "nvram_diagnostic.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "data_utils.h"
#include "system_diag.h"
#include "table_utils.h"
#include "general_macros.h"
#include "writer_config.h"
#include "storage_diagnostic.h"
#include "storage_diag.h"
#include "str_utils.h"
#ifdef HAS_DIAG
#include "common_diag.h"
#endif

#include "log.h"
#include "nvram_configuration.h"
#include "nvram_drv.h"
#include "nvram_types.h"

#ifdef HAS_TIME_DIAG
#include "time_diag.h"
#endif

#ifdef HAS_ACCELEROMETER_EHAL_DIAG
#include "accelerometer_diagnostic.h"
#endif

#ifdef HAS_ACCELEROMETER_DIAG
#include "accelerometer_diag.h"
#endif

#ifdef HAS_GNSS_DIAG
#include "gnss_diag.h"
#endif

#ifdef HAS_BOOT_DIAG
#include "boot_diag.h"
#endif

#ifdef HAS_NUM_DIAG
#include "num_to_str.h"
#endif

const char* NVRAM_VariableInfoToStr(const NVRAM_INFO* const  Info){
    static char text[120] = { 0 };
	if(Info){
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sID:%u,", text, Info->id);
        snprintf(text, sizeof(text), "%sLen:%u,", text, Info->len);
        snprintf(text, sizeof(text), "%sEEPROMaddr:0x%08x,", text, Info->eepromAddress);
        snprintf(text, sizeof(text), "%sType:%s,", text, STORAGE_TypeToStr(Info->type));
        snprintf(text, sizeof(text), "%sDflt:%s,", text, Info->defaultValue);
        snprintf(text, sizeof(text), "%sName:%s,", text, Info->name);

	}
    return text;
}

const char* NVRAM_IdToStr(NVRAM_DATA_ID nvramId) {
    char* text = "?";
	const NVRAM_INFO* Info = NVRAM_GetVariableInfo(nvramId);
	if(Info) {
		text = NVRAM_VariableInfoToStr(Info);
	}
    return text;
}


const char* NVRAM_ValToStr(NVRAM_DATA_ID id, U8* const rawData, uint32_t size) {
    const char* name = "?";
    /*TODO: Look first on the facility.*/
    if(rawData && (0 < size)) {
        static char temp_name[100] = "??";
        memset(temp_name, 0, sizeof(temp_name));
        switch(id) {

#ifdef HAS_ACCELEROMETER_EHAL_DIAG
        case NVRAM_ID_ACCEL_CALIB1:
        case NVRAM_ID_ACCEL_CALIB2:
        {
            name = ACCEL_CalibDataToStr((ACCEL_CALIB_DATA*)rawData);
        }break;
#endif

#ifdef HAS_DECAWAVE
        case NVRAM_ID_DECAWAVE_ID: {
            U16 word = 0;
            memcpy(&word, rawData, 2);
            name = HexWord2Str(word);
        } break;
#endif /*HAS_DECAWAVE*/

#ifdef HAS_KEEPASS
        case NVRAM_ID_KEEPPASS_FILE_NAME: {
            snprintf(temp_name, sizeof(temp_name), "%s", rawData);
            name = temp_name;
        } break;

        case NVRAM_ID_KEEPPASS_PASS_WORD: {
            uint32_t len = strlen((char*)rawData);
            memset(temp_name, '*', len);
            temp_name[len] = 0x00;
            name = temp_name;
        } break;
#endif /*HAS_KEEPASS*/

#ifdef HAS_WDT
        case NVRAM_ID_WDT_MUTE: {
            name = OnOffToStr((U8)*rawData);
        } break;
#endif /*HAS_WDT*/

#ifdef HAS_GFSK
        case NVRAM_ID_CRC_INIT: {
            U16 word = 0;
            memcpy(&word, rawData, 2);
            name = HexWord2Str(word);
        } break;
        case NVRAM_ID_CRC_POLY: {
            U16 word = 0;
            memcpy(&word, rawData, 2);
            name = HexWord2Str(word);
        } break;
        case NVRAM_ID_GFSK_BITRATE: {
            uint32_t bit_rate = 0;
            memcpy(&bit_rate, rawData, 4);
            name = BitRate2Str((double)bit_rate);
        } break;
        case NVRAM_ID_SYNC_WORD: {
            uint64_t sync_word = 0;
            memcpy(&sync_word, rawData, 8);
            name = SyncWord2Str(sync_word);
        } break;
        case NVRAM_ID_GFSK_PULSE_SHAPE: {
            name = PulseShape2Str(*rawData);
        } break;
        case NVRAM_ID_SYNC_WORD_LEN: {
            name = SyncWordLen2Str(*rawData);
        } break;
        case NVRAM_ID_GFSK_PACKET_TYPE: {
            name = GfskPacetType2Str(*rawData);
        } break;
        case NVRAM_ID_GFSK_PAYLOAD_LEN: {
            name = PayloadLen2Str((U8)*rawData);
        } break;
        case NVRAM_ID_GFSK_FREQ_DEV: {
            uint32_t freq_dev = 0;
            memcpy(&freq_dev, rawData, 4);
            name = RfFreq2Str(freq_dev);
        } break;

        case NVRAM_ID_GFSK_PRE_LEN: {
            U16 word = 0;
            memcpy(&word, rawData, 2);
            name = PreambleLen2Str(word);
        } break;

        case NVRAM_ID_PRE_DET_LEN: {
            name = PreDetLen2Str((U8)*rawData);
        } break;
        case NVRAM_ID_ADDR_COMP: {
            name = Byte2Str((U8)*rawData);
        } break;
        case NVRAM_ID_GFSK_BANDWIDTH: {
            name = GfskBandwith2Str((U8)*rawData);
        } break;
        case NVRAM_ID_NODE_ADDR: {
            name = Byte2Str((U8)*rawData);
        } break;
        case NVRAM_ID_GFSK_CRC_TYPE: {
            name = Crc2Str((U8)*rawData);
        } break;
        case NVRAM_ID_BROADCAST_ADDR: {
            name = Byte2Str((U8)*rawData);
        } break;
        case NVRAM_ID_WHITENING: {
            name = OnOffToStr((U8)*rawData);
        } break;
        case NVRAM_ID_WHITENING_INIT_VALUE: {
            U16 word = 0;
            memcpy(&word, rawData, 2);
            name = HexWord2Str(word);
        } break;
#endif /*HAS_GFSK*/

#ifdef HAS_LORA
        case NVRAM_ID_LORA_SF: {
            name = spreading_factor2str((U8)*rawData);
        } break;
        case NVRAM_ID_LORA_CR: {
            name = coding_rate2str((U8)*rawData);
        } break;
        case NVRAM_ID_LORA_BW: {
            name = bandwidth2str((U8)*rawData);
        } break;
        case NVRAM_ID_LORA_SYNC_WORD: {
            U16 word = 0;
            memcpy(&word, rawData, 2);
            name = HexWord2Str(word);
        } break;
        case NVRAM_ID_PAYLOAD_LENGTH: {
            name = PayloadLen2Str((U8)*rawData);
        } break;

        case NVRAM_ID_PREAMBLE_LENGTH: {
            name = PreambleLen2Str((U16)*rawData);
        } break;
        case NVRAM_ID_LORA_HEADER_TYPE: {
            name = LoraHeaderType2Str((U8)*rawData);
        } break;
        case NVRAM_ID_CRC_TYPE: {
            name = LoraCrcType2Str((U8)*rawData);
        } break;
#endif

#ifdef HAS_SX1262
        case NVRAM_ID_RETX: {
            name = OnOffToStr((U8)*rawData);
        } break;
        case NVRAM_ID_RX_GAIN: {
            name = RxGain2Str((U8)*rawData);
        } break;
        case NVRAM_ID_OUT_POWER: {
            float watts = dbm2watts((uint32_t)*rawData);
            snprintf(temp_name, sizeof(temp_name), "%7.3f W", watts);
            name = temp_name;
        } break;
        case NVRAM_ID_FREQ: {
            uint32_t freq = 0;
            memcpy(&freq, rawData, 4);
            name = RfFreq2Str(freq);
        } break;

        case NVRAM_ID_TX_MUTE: {
            name = OnOffToStr((U8)*rawData);
        } break;
        case NVRAM_ID_WIRELESS_INTERFACE: {
            name = WireLessIf2Str((U8)*rawData);
        } break;

        case NVRAM_ID_IQ_SETUP: {
            name = IqSetUp2Str((U8)*rawData);
        } break;

        case NVRAM_ID_MAX_LINK_DIST: {
            name = LinkDist2str((double)*rawData);
        } break;

        case NVRAM_ID_MAX_BIT_RATE: {
            Type64Union_t un64;
            memcpy(&un64, rawData, sizeof(Type64Union_t));
            name = BitRate2Str((double)un64.d64);
        } break;

#endif /*HAS_SX1262*/

#ifdef HAS_BOOT
        case NVRAM_ID_BOOT_CMD: {
            name = boot_cmd2str((U8)*rawData);
        } break;
#endif

#ifdef HAS_I2S1
        case NVRAM_ID_I2S1_BUS_ROLE: {
            name = I2sRole2Str((U8)*rawData);
        } break;
#endif /*HAS_I2S1*/

#ifdef HAS_I2S2
        case NVRAM_ID_I2S2_BUS_ROLE: {
            // name = I2sRole2Str((U8)*rawData);
        } break;
#endif /*HAS_I2S2*/

#ifdef HAS_I2S3
        case NVRAM_ID_I2S3_BUS_ROLE: {
            name = I2sRole2Str((U8)*rawData);
        } break;
#endif /*HAS_I2S3*/

#ifdef HAS_I2S4
        case NVRAM_ID_I2S4_BUS_ROLE: {
            name = I2sRole2Str((U8)*rawData);
        } break;
#endif /*HAS_I2S4*/

#ifdef HAS_I2S5
        // case NVRAM_ID_I2S5_BUS_ROLE: {
        //    name = I2sRole2Str((U8)*rawData);
        //} break;
#endif /*HAS_I2S5*/

#ifdef HAS_BC127
        case NVRAM_ID_BC127_I2S_BUS_ROLE: {
            name = Bc127I2sBusRole2Str((U8)*rawData);
        } break;
#endif /*HAS_BC127*/

#ifdef HAS_WM8731
        case NVRAM_ID_WM8731_I2S_BUS_ROLE: {
            name = Wm8731I2sBusRole2Str((U8)*rawData);
        } break;
#endif /*HAS_WM8731*/

#ifdef HAS_AES
        case NVRAM_ID_AES_256BIT_KEY_ID: {
            name = Array2Str(rawData, 32);
        } break;
#endif

#ifdef HAS_CAN
        case NVRAM_ID_CAN_NODE_ID: {
            uint32_t can_id = 0;
            memcpy(&can_id, rawData, 4);
            name = QWord2Str(can_id);
        } break;
#endif

        case NVRAM_ID_MAX_UP_TIME: {
#ifdef HAS_TIME_DIAG
            uint32_t time_ms = 0;
            memcpy(&time_ms, rawData, 4);
            name = Ms2Str(time_ms);
#endif
        } break;
#ifdef HAS_BOOTLOADER
        case NVRAM_ID_BOOT_CNT: {
            name = Byte2Str((U8)*rawData);
        } break;
        case NVRAM_ID_APP_START:
        case NVRAM_ID_APP_CRC32: {
#ifdef HAS_NUM_DIAG
            uint32_t app_crc = 0;
            memcpy(&app_crc, rawData, 4);
            name = HexQWord2Str(app_crc);
#endif
        } break;
        case NVRAM_ID_APP_LEN: {
            uint32_t app_len = 0;
            memcpy(&app_len, rawData, 4);
            name = AppSize2str(app_len);
        } break;
#endif /*HAS_BOOTLOADER*/
#ifdef HAS_PWR_MUX
        case NVRAM_ID_PWR_SRC: {
            name = pwr_source2str((U8)*rawData);
        } break;
#endif /*HAS_PWR_MUX*/

#ifdef HAS_GNSS_RTK
        case NVRAM_ID_GPS:
        case NVRAM_ID_GLONASS:
        case NVRAM_ID_GALILEO:
        case NVRAM_ID_BEI_DOU: {
            name = OnOffToStr((bool)*rawData);
        } break;

        case NVRAM_ID_GNSS_MODE: {
            name = rtk_mode2str((U8)*rawData);
        } break;
        case NVRAM_ID_RTK_FIX_LONG: {
            uint32_t time_ms = 0;
            memcpy(&time_ms, rawData, 4);
            name = Ms2Str(time_ms);
        } break;
        case NVRAM_ID_RTK_CHANNEL: {
            name = interface2str((Interfaces_t)*rawData);
        } break;
        case NVRAM_ID_BASE_LOCATION: {
            name = coordinate2str((void*)rawData);
        } break;
#endif /*HAS_ZED_F9P*/

#ifdef HAS_GNSS_DIAG
        case NVRAM_ID_TRUE_LOCATION: {
            name = coordinate2str((void*)rawData);
        } break;
#endif

#ifdef HAS_DS_TWR
        case NVRAM_ID_PHASE1_OFFSET:
        case NVRAM_ID_PHASE2_OFFSET:
        case NVRAM_ID_FINAL_OFFSET: {
            double offset_m = 0.0;
            if(sizeof(double) == size) {
                memcpy(&offset_m, rawData, sizeof(double));
                snprintf(temp_name, sizeof(temp_name), "%7.3f m", offset_m);
                name = temp_name;
            }
        } break;
#endif

        default:
            name = "UndefID";
            break;
        } // switch
    }
    return name;
}

STD_RESULT NVRAM_Default(char* keyWord1, char* keyWord2) {
    bool ret = false;
    U16 i = 0, num = 1;
    static const table_col_t cols[] = {{5, "No"},  {6, "ID"},   {9, "type"}, {23, "VariableName"},
                                       {5, "len"}, {13, "default"}};
    table_header(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));
    char text_line[250] = "";
    for(i = 0; i < NVRAM_GetCnt(); i++) {
        strcpy(text_line, TSEP);
        snprintf(text_line, sizeof(text_line), "%s %4u " TSEP, text_line, NvramArray[i].id);

        snprintf(text_line, sizeof(text_line), "%s %7s " TSEP, text_line, STORAGE_TypeToStr(NvramArray[i].type));
        snprintf(text_line, sizeof(text_line), "%s %21s " TSEP, text_line, NvramArray[i].name);
        snprintf(text_line, sizeof(text_line), "%s %3u " TSEP, text_line, NvramArray[i].len);
        snprintf(text_line, sizeof(text_line), "%s %11s " TSEP, text_line, NvramArray[i].defaultValue);

        ret = is_contain(text_line, keyWord1, keyWord2);
        if(ret) {
            cli_printf(TSEP " %3u %s" CRLF, num, text_line);
            num++;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));

    return ret;
}

STD_RESULT NVRAM_Diag(char* keyWord1, char* keyWord2) {
	STD_RESULT ret = RESULT_NOT_OK;
    char valStr[80] = "";
    memset(valStr, 0x00, sizeof(valStr));
    strncpy(valStr, "", sizeof(valStr));
    U16 i = 0, num = 1;
    static const table_col_t cols[] = {{5, "No"},     {6, "id"},
    		{12, "eepromStart"},
    		{12, "eepromEnd"},
                                       {9, "type"},   {23, "VariableName"},
                                       {5, "len"},    {12, "val"},
                                       {17, "name"}};
    table_header(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));

    char text_line[250] = "";
    for(i = 0; i < NVRAM_GetCnt(); i++) {
        memset(valStr, 0x00, sizeof(valStr));
        memset(text_line, 0x00, sizeof(text_line));
        strcpy(text_line, TSEP);

        snprintf(text_line, sizeof(text_line), "%s %4u " TSEP,text_line, NvramArray[i].id);
        snprintf(text_line, sizeof(text_line), "%s 0x%08x " TSEP,text_line, NvramArray[i].eepromAddress);
        U32 eepromAddressEnd = NvramArray[i].eepromAddress + NvramArray[i].len;
        snprintf(text_line, sizeof(text_line), "%s 0x%08x " TSEP,text_line, eepromAddressEnd);
        snprintf(text_line, sizeof(text_line), "%s %7s " TSEP,text_line, STORAGE_TypeToStr(NvramArray[i].type));
        snprintf(text_line, sizeof(text_line), "%s %21s " TSEP,text_line, NvramArray[i].name);


        U8 binData[100] = {0};
        ret = NVRAM_Get(NvramArray[i].id, binData);
        if(RESULT_OK==ret) {
            snprintf(text_line, sizeof(text_line), "%s %3u " TSEP, text_line, NvramArray[i].len);
            ret = STORAGE_DataToStrLine(binData, NvramArray[i].len, NvramArray[i].type, valStr, sizeof(valStr));
            snprintf(text_line, sizeof(text_line), "%s %10s " TSEP, text_line, str_limit(valStr, 8));
        } else {
            snprintf(text_line, sizeof(text_line), "%s --- " TSEP, text_line);
            snprintf(text_line, sizeof(text_line), "%s %10s " TSEP, text_line, "lack");
        }

        snprintf(text_line, sizeof(text_line), "%s %15s",text_line, NVRAM_ValToStr(NvramArray[i].id, binData, sizeof(binData)));

        bool res =  is_contain(text_line, keyWord1, keyWord2);
        if(res) {
            cli_printf(TSEP" %3u %s"CRLF,num, text_line);
            num++;
            ret = RESULT_OK;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));

    return ret;
}
