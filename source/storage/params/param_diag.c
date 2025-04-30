#include "param_diag.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "data_utils.h"
#include "system_diag.h"
#include "table_utils.h"
#include "writer_config.h"
//#include "flash_fs.h"
#include "storage_diag.h"
#include "str_utils.h"
#ifdef HAS_DIAG
#include "common_diag.h"
#endif

#include "log.h"
#include "param_config.h"
#include "param_drv.h"
#include "param_types.h"

#ifdef HAS_TIME_DIAG
#include "time_diag.h"
#endif

#ifdef HAS_GNSS_DIAG
#include "gnss_diag.h"
#endif

#ifdef HAS_I2S_DIAG
#include "i2s_diag.h"
#endif

#ifdef HAS_SX1262_DIAG
#include "sx1262_diag.h"
#endif

#ifdef HAS_ZED_F9P_DIAG
#include "zed_f9p_diag.h"
#endif

#ifdef HAS_BOOT_DIAG
#include "boot_diag.h"
#endif

#ifdef HAS_WM8731_DIAG
#include "wm8731_diag.h"
#endif

#ifdef HAS_BC127_DIAG
#include "bc127_diag.h"
#endif

#ifdef HAS_GFSK_DIAG
#include "gfsk_diag.h"
#endif

#ifdef HAS_PWR_MUX_DIAG
#include "pwr_mux_diag.h"
#endif

#ifdef HAS_NUM_DIAG
#include "num_to_str.h"
#endif

char* ParamId2Str(Id_t id) {
    char* name = "?";
    uint16_t i = 0;
    uint32_t cnt = param_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(id == ParamArray[i].id) {
            name = ParamArray[i].name;
            break;
        }
    }
    return name;
}

const char* param_val2str(Id_t id, uint8_t* const value, uint32_t size) {
    const char* name = "?";
    /*TODO: Look first on the falility.*/
    if(value && (0 < size)) {
        static char temp_name[100] = "??";
        memset(temp_name, 0, sizeof(temp_name));
        switch(id) {
#ifdef HAS_DECAWAVE
        case PAR_ID_DECAWAVE_ID: {
            uint16_t word = 0;
            memcpy(&word, value, 2);
            name = HexWord2Str(word);
        } break;
#endif /*HAS_DECAWAVE*/

#ifdef HAS_KEEPASS
        case PAR_ID_KEEPPASS_FILE_NAME: {
            snprintf(temp_name, sizeof(temp_name), "%s", value);
            name = temp_name;
        } break;

        case PAR_ID_KEEPPASS_PASS_WORD: {
            uint32_t len = strlen((char*)value);
            memset(temp_name, '*', len);
            temp_name[len] = 0x00;
            name = temp_name;
        } break;
#endif /*HAS_KEEPASS*/

#ifdef HAS_WDT
        case PAR_ID_WDT_MUTE: {
            name = OnOff2Str((uint8_t)*value);
        } break;
#endif /*HAS_WDT*/

#ifdef HAS_GFSK
        case PAR_ID_CRC_INIT: {
            uint16_t word = 0;
            memcpy(&word, value, 2);
            name = HexWord2Str(word);
        } break;
        case PAR_ID_CRC_POLY: {
            uint16_t word = 0;
            memcpy(&word, value, 2);
            name = HexWord2Str(word);
        } break;
        case PAR_ID_GFSK_BITRATE: {
            uint32_t bit_rate = 0;
            memcpy(&bit_rate, value, 4);
            name = BitRate2Str((double)bit_rate);
        } break;
        case PAR_ID_SYNC_WORD: {
            uint64_t sync_word = 0;
            memcpy(&sync_word, value, 8);
            name = SyncWord2Str(sync_word);
        } break;
        case PAR_ID_GFSK_PULSE_SHAPE: {
            name = PulseShape2Str(*value);
        } break;
        case PAR_ID_SYNC_WORD_LEN: {
            name = SyncWordLen2Str(*value);
        } break;
        case PAR_ID_GFSK_PACKET_TYPE: {
            name = GfskPacetType2Str(*value);
        } break;
        case PAR_ID_GFSK_PAYLOAD_LEN: {
            name = PayloadLen2Str((uint8_t)*value);
        } break;
        case PAR_ID_GFSK_FREQ_DEV: {
            uint32_t freq_dev = 0;
            memcpy(&freq_dev, value, 4);
            name = RfFreq2Str(freq_dev);
        } break;

        case PAR_ID_GFSK_PRE_LEN: {
            uint16_t word = 0;
            memcpy(&word, value, 2);
            name = PreambleLen2Str(word);
        } break;

        case PAR_ID_PRE_DET_LEN: {
            name = PreDetLen2Str((uint8_t)*value);
        } break;
        case PAR_ID_ADDR_COMP: {
            name = Byte2Str((uint8_t)*value);
        } break;
        case PAR_ID_GFSK_BANDWIDTH: {
            name = GfskBandwith2Str((uint8_t)*value);
        } break;
        case PAR_ID_NODE_ADDR: {
            name = Byte2Str((uint8_t)*value);
        } break;
        case PAR_ID_GFSK_CRC_TYPE: {
            name = Crc2Str((uint8_t)*value);
        } break;
        case PAR_ID_BROADCAST_ADDR: {
            name = Byte2Str((uint8_t)*value);
        } break;
        case PAR_ID_WHITENING: {
            name = OnOff2Str((uint8_t)*value);
        } break;
        case PAR_ID_WHITENING_INIT_VALUE: {
            uint16_t word = 0;
            memcpy(&word, value, 2);
            name = HexWord2Str(word);
        } break;
#endif /*HAS_GFSK*/

#ifdef HAS_LORA
        case PAR_ID_LORA_SF: {
            name = spreading_factor2str((uint8_t)*value);
        } break;
        case PAR_ID_LORA_CR: {
            name = coding_rate2str((uint8_t)*value);
        } break;
        case PAR_ID_LORA_BW: {
            name = bandwidth2str((uint8_t)*value);
        } break;
        case PAR_ID_LORA_SYNC_WORD: {
            uint16_t word = 0;
            memcpy(&word, value, 2);
            name = HexWord2Str(word);
        } break;
        case PAR_ID_PAYLOAD_LENGTH: {
            name = PayloadLen2Str((uint8_t)*value);
        } break;

        case PAR_ID_PREAMBLE_LENGTH: {
            name = PreambleLen2Str((uint16_t)*value);
        } break;
        case PAR_ID_LORA_HEADER_TYPE: {
            name = LoraHeaderType2Str((uint8_t)*value);
        } break;
        case PAR_ID_CRC_TYPE: {
            name = LoraCrcType2Str((uint8_t)*value);
        } break;
#endif

#ifdef HAS_SX1262
        case PAR_ID_RETX: {
            name = OnOff2Str((uint8_t)*value);
        } break;
        case PAR_ID_RX_GAIN: {
            name = RxGain2Str((uint8_t)*value);
        } break;
        case PAR_ID_OUT_POWER: {
            float watts = dbm2watts((uint32_t)*value);
            snprintf(temp_name, sizeof(temp_name), "%7.3f W", watts);
            name = temp_name;
        } break;
        case PAR_ID_FREQ: {
            uint32_t freq = 0;
            memcpy(&freq, value, 4);
            name = RfFreq2Str(freq);
        } break;

        case PAR_ID_TX_MUTE: {
            name = OnOff2Str((uint8_t)*value);
        } break;
        case PAR_ID_WIRELESS_INTERFACE: {
            name = WireLessIf2Str((uint8_t)*value);
        } break;

        case PAR_ID_IQ_SETUP: {
            name = IqSetUp2Str((uint8_t)*value);
        } break;

        case PAR_ID_MAX_LINK_DIST: {
            name = LinkDist2str((double)*value);
        } break;

        case PAR_ID_MAX_BIT_RATE: {
            Type64Union_t un64;
            memcpy(&un64, value, sizeof(Type64Union_t));
            name = BitRate2Str((double)un64.d64);
        } break;

#endif /*HAS_SX1262*/

#ifdef HAS_BOOT
        case PAR_ID_BOOT_CMD: {
            uint8_t cmd = *value;
            name = BootCmdToStr(cmd);
        } break;
#endif

#ifdef HAS_I2S1
        case PAR_ID_I2S1_BUS_ROLE: {
            name = I2sRole2Str((uint8_t)*value);
        } break;
#endif /*HAS_I2S1*/

#ifdef HAS_I2S2
        case PAR_ID_I2S2_BUS_ROLE: {
            // name = I2sRole2Str((uint8_t)*value);
        } break;
#endif /*HAS_I2S2*/

#ifdef HAS_I2S3
        case PAR_ID_I2S3_BUS_ROLE: {
            name = I2sRole2Str((uint8_t)*value);
        } break;
#endif /*HAS_I2S3*/

#ifdef HAS_I2S4
        case PAR_ID_I2S4_BUS_ROLE: {
            name = I2sRole2Str((uint8_t)*value);
        } break;
#endif /*HAS_I2S4*/

#ifdef HAS_I2S5
        case PAR_ID_I2S5_BUS_ROLE: {
            name = I2sRole2Str((uint8_t)*value);
        } break;
#endif /*HAS_I2S5*/

#ifdef HAS_BC127
        case PAR_ID_BC127_I2S_BUS_ROLE: {
            name = Bc127I2sBusRole2Str((uint8_t)*value);
        } break;
#endif /*HAS_BC127*/

#ifdef HAS_WM8731
        case PAR_ID_WM8731_I2S_BUS_ROLE: {
            name = Wm8731I2sBusRole2Str((uint8_t)*value);
        } break;
#endif /*HAS_WM8731*/

#ifdef HAS_AES
        case PAR_ID_AES_256BIT_KEY_ID: {
            name = Array2Str(value, 32);
        } break;
#endif

#ifdef HAS_CAN
        case PAR_ID_CAN_NODE_ID: {
            uint32_t can_id = 0;
            memcpy(&can_id, value, 4);
            name = QWord2Str(can_id);
        } break;
#endif

        case PAR_ID_MAX_UP_TIME: {
#ifdef HAS_TIME_DIAG
            uint32_t time_ms = 0;
            memcpy(&time_ms, value, 4);
            name = Ms2Str(time_ms);
#endif
        } break;
#ifdef HAS_BOOTLOADER
        case PAR_ID_BOOT_CNT: {
            name = Byte2Str((uint8_t)*value);
        } break;
        case PAR_ID_APP_START:
        case PAR_ID_APP_CRC32: {
#ifdef HAS_NUM_DIAG
            uint32_t app_crc = 0;
            memcpy(&app_crc, value, 4);
            name = HexQWord2Str(app_crc);
#endif
        } break;
        case PAR_ID_APP_LEN: {
            uint32_t app_len = 0;
            memcpy(&app_len, value, 4);
            name = AppSize2str(app_len);
        } break;
#endif /*HAS_BOOTLOADER*/
#ifdef HAS_PWR_MUX
        case PAR_ID_PWR_SRC: {
            name = pwr_source2str((uint8_t)*value);
        } break;
#endif /*HAS_PWR_MUX*/

#ifdef HAS_GNSS_RTK
        case PAR_ID_GPS:
        case PAR_ID_GLONASS:
        case PAR_ID_GALILEO:
        case PAR_ID_BEI_DOU: {
            name = OnOff2Str((bool)*value);
        } break;

        case PAR_ID_GNSS_MODE: {
            name = rtk_mode2str((uint8_t)*value);
        } break;
        case PAR_ID_RTK_FIX_LONG: {
            uint32_t time_ms = 0;
            memcpy(&time_ms, value, 4);
            name = Ms2Str(time_ms);
        } break;
        case PAR_ID_RTK_CHANNEL: {
            name = interface2str((Interfaces_t)*value);
        } break;
        case PAR_ID_BASE_LOCATION: {
            name = coordinate2str((void*)value);
        } break;
#endif /*HAS_ZED_F9P*/

#ifdef HAS_GNSS_DIAG
        case PAR_ID_TRUE_LOCATION: {
            name = coordinate2str((void*)value);
        } break;
#endif

#ifdef HAS_DS_TWR
        case PAR_ID_PHASE1_OFFSET:
        case PAR_ID_PHASE2_OFFSET:
        case PAR_ID_FINAL_OFFSET: {
            double offset_m = 0.0;
            if(sizeof(double) == size) {
                memcpy(&offset_m, value, sizeof(double));
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

bool param_default(char* keyWord1, char* keyWord2) {
    bool res = false;
    uint16_t i = 0, num = 1;
    static const table_col_t cols[] = {{5, "No"},  {6, "ID"},      {12, "group"}, {9, "type"}, {23, "VariableName"},
                                       {5, "len"}, {13, "default"}};
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    char line_str[250] = "";
    for(i = 0; i < param_get_cnt(); i++) {
        strcpy(line_str, TSEP);
        snprintf(line_str, sizeof(line_str), "%s %4u " TSEP, line_str, ParamArray[i].id);
#ifdef HAS_SYSTEM_DIAG
        snprintf(line_str, sizeof(line_str), "%s %10s " TSEP, line_str, Facility2Str(ParamArray[i].facility));
#endif
        snprintf(line_str, sizeof(line_str), "%s %7s " TSEP, line_str, StorageTypeToStr(ParamArray[i].type));
        snprintf(line_str, sizeof(line_str), "%s %21s " TSEP, line_str, ParamArray[i].name);
        snprintf(line_str, sizeof(line_str), "%s %3u " TSEP, line_str, ParamArray[i].len);
        snprintf(line_str, sizeof(line_str), "%s %11s " TSEP, line_str, ParamArray[i].default_value);

        res = is_contain(line_str, keyWord1, keyWord2);
        if(res) {
            cli_printf(TSEP " %3u %s" CRLF, num, line_str);
            num++;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool param_diag(char* keyWord1, char* keyWord2) {
    bool res = false;
    char valStr[80] = "";
    memset(valStr, 0x00, sizeof(valStr));
    strncpy(valStr, "", sizeof(valStr));
    uint16_t i = 0, num = 1;
    static const table_col_t cols[] = {{5, "No"},     {6, "id"},
#ifdef HAS_SYSTEM_DIAG
                                       {12, "group"},
#endif
                                       {9, "type"},   {23, "VariableName"},
                                       {5, "len"},    {12, "val"},
                                       {17, "name"}};
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    char line_str[250] = "";
    char suffix_str[80] = "";
    for(i = 0; i < param_get_cnt(); i++) {
        memset(valStr, 0x00, sizeof(valStr));
        memset(line_str, 0x00, sizeof(line_str));
        strcpy(line_str, TSEP);

        snprintf(suffix_str, sizeof(suffix_str), " %4u " TSEP, ParamArray[i].id);
        strcat(line_str, suffix_str);

#ifdef HAS_SYSTEM_DIAG
        snprintf(suffix_str, sizeof(suffix_str), " %10s " TSEP, Facility2Str(ParamArray[i].facility));
        strcat(line_str, suffix_str);
#endif

        snprintf(suffix_str, sizeof(suffix_str), " %7s " TSEP, StorageTypeToStr(ParamArray[i].type));
        strcat(line_str, suffix_str);

        snprintf(suffix_str, sizeof(suffix_str), " %21s " TSEP, ParamArray[i].name);
        strcat(line_str, suffix_str);

        uint8_t value[100] = {0};
        res = param_get(ParamArray[i].id, value);
        if(res) {
            snprintf(line_str, sizeof(line_str), "%s %3u " TSEP, line_str, ParamArray[i].len);
            if(ParamArray[i].hide) {
                snprintf(line_str, sizeof(line_str), "%s %10s " TSEP, line_str, "secret");
            } else {
                res = DataToValStrBuff(value, ParamArray[i].len, ParamArray[i].type, valStr, sizeof(valStr));
                snprintf(line_str, sizeof(line_str), "%s %10s " TSEP, line_str, str_limit(valStr, 8));
            }
        } else {
            snprintf(line_str, sizeof(line_str), "%s --- " TSEP, line_str);
            snprintf(line_str, sizeof(line_str), "%s %10s " TSEP, line_str, "lack");
        }

        snprintf(suffix_str, sizeof(suffix_str), " %15s", param_val2str(ParamArray[i].id, value, sizeof(value)));
        strcat(line_str, suffix_str);

        res = is_contain(line_str, keyWord1, keyWord2);
        if(res) {
            cli_printf(TSEP " %3u ", num);
            cli_printf("%s", line_str);
            cli_printf(CRLF);
            num++;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
