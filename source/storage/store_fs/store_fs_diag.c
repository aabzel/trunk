#include "store_fs_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"
#include "storage.h"
#include "storage_config.h"
#include "storage_diag.h"
#include "store_fs.h"
#include "store_fs_config.h"
#include "str_utils.h"
#include "system_diag.h"

const char* StoreFsConfigToStr(const StoreFsConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* StoreFsNodeToStr(const StoreFsHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

#if 0
const char* StoreFsValToStr(StorageId_t id, uint8_t* const value, uint32_t size) {
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
            name = HexWordToStr(word);
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
            name = OnOffToStr((uint8_t)*value);
        } break;
#endif /*HAS_WDT*/

#ifdef HAS_GFSK
        case PAR_ID_CRC_INIT: {
            uint16_t word = 0;
            memcpy(&word, value, 2);
            name = HexWordToStr(word);
        } break;
        case PAR_ID_CRC_POLY: {
            uint16_t word = 0;
            memcpy(&word, value, 2);
            name = HexWordToStr(word);
        } break;
        case PAR_ID_GFSK_BITRATE: {
            uint32_t bit_rate = 0;
            memcpy(&bit_rate, value, 4);
            name = BitRateToStr((double)bit_rate);
        } break;
        case PAR_ID_SYNC_WORD: {
            uint64_t sync_word = 0;
            memcpy(&sync_word, value, 8);
            name = SyncWordToStr(sync_word);
        } break;
        case PAR_ID_GFSK_PULSE_SHAPE: {
            name = PulseShapeToStr(*value);
        } break;
        case PAR_ID_SYNC_WORD_LEN: {
            name = SyncWordLenToStr(*value);
        } break;
        case PAR_ID_GFSK_PACKET_TYPE: {
            name = GfskPacetTypeToStr(*value);
        } break;
        case PAR_ID_GFSK_PAYLOAD_LEN: {
            name = PayloadLenToStr((uint8_t)*value);
        } break;
        case PAR_ID_GFSK_FREQ_DEV: {
            uint32_t freq_dev = 0;
            memcpy(&freq_dev, value, 4);
            name = RfFreqToStr(freq_dev);
        } break;

        case PAR_ID_GFSK_PRE_LEN: {
            uint16_t word = 0;
            memcpy(&word, value, 2);
            name = PreambleLenToStr(word);
        } break;

        case PAR_ID_PRE_DET_LEN: {
            name = PreDetLenToStr((uint8_t)*value);
        } break;
        case PAR_ID_ADDR_COMP: {
            name = ByteToStr((uint8_t)*value);
        } break;
        case PAR_ID_GFSK_BANDWIDTH: {
            name = GfskBandwithToStr((uint8_t)*value);
        } break;
        case PAR_ID_NODE_ADDR: {
            name = ByteToStr((uint8_t)*value);
        } break;
        case PAR_ID_GFSK_CRC_TYPE: {
            name = CrcToStr((uint8_t)*value);
        } break;
        case PAR_ID_BROADCAST_ADDR: {
            name = ByteToStr((uint8_t)*value);
        } break;
        case PAR_ID_WHITENING: {
            name = OnOffToStr((uint8_t)*value);
        } break;
        case PAR_ID_WHITENING_INIT_VALUE: {
            uint16_t word = 0;
            memcpy(&word, value, 2);
            name = HexWordToStr(word);
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
            name = HexWordToStr(word);
        } break;
        case PAR_ID_PAYLOAD_LENGTH: {
            name = PayloadLenToStr((uint8_t)*value);
        } break;

        case PAR_ID_PREAMBLE_LENGTH: {
            name = PreambleLenToStr((uint16_t)*value);
        } break;
        case PAR_ID_LORA_HEADER_TYPE: {
            name = LoraHeaderTypeToStr((uint8_t)*value);
        } break;
        case PAR_ID_CRC_TYPE: {
            name = LoraCrcTypeToStr((uint8_t)*value);
        } break;
#endif

#ifdef HAS_SX1262
        case PAR_ID_RETX: {
            name = OnOffToStr((uint8_t)*value);
        } break;
        case PAR_ID_RX_GAIN: {
            name = RxGainToStr((uint8_t)*value);
        } break;
        case PAR_ID_OUT_POWER: {
            float watts = dbm2watts((uint32_t)*value);
            snprintf(temp_name, sizeof(temp_name), "%7.3f W", watts);
            name = temp_name;
        } break;
        case PAR_ID_FREQ: {
            uint32_t freq = 0;
            memcpy(&freq, value, 4);
            name = RfFreqToStr(freq);
        } break;

        case PAR_ID_TX_MUTE: {
            name = OnOffToStr((uint8_t)*value);
        } break;
        case PAR_ID_WIRELESS_INTERFACE: {
            name = WireLessIfToStr((uint8_t)*value);
        } break;

        case PAR_ID_IQ_SETUP: {
            name = IqSetUpToStr((uint8_t)*value);
        } break;

        case PAR_ID_MAX_LINK_DIST: {
            name = LinkDist2str((double)*value);
        } break;

        case PAR_ID_MAX_BIT_RATE: {
            Type64Union_t un64;
            memcpy(&un64, value, sizeof(Type64Union_t));
            name = BitRateToStr((double)un64.d64);
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
            name = I2sRoleToStr((uint8_t)*value);
        } break;
#endif /*HAS_I2S1*/

#ifdef HAS_I2S2
        case PAR_ID_I2S2_BUS_ROLE: {
            // name = I2sRoleToStr((uint8_t)*value);
        } break;
#endif /*HAS_I2S2*/

#ifdef HAS_I2S3
        case PAR_ID_I2S3_BUS_ROLE: {
            name = I2sRoleToStr((uint8_t)*value);
        } break;
#endif /*HAS_I2S3*/

#ifdef HAS_I2S4
        case PAR_ID_I2S4_BUS_ROLE: {
            name = I2sRoleToStr((uint8_t)*value);
        } break;
#endif /*HAS_I2S4*/

#ifdef HAS_I2S5
        case PAR_ID_I2S5_BUS_ROLE: {
            name = I2sRoleToStr((uint8_t)*value);
        } break;
#endif /*HAS_I2S5*/

#ifdef HAS_BC127
        case PAR_ID_BC127_I2S_BUS_ROLE: {
            name = Bc127I2sBusRoleToStr((uint8_t)*value);
        } break;
#endif /*HAS_BC127*/

#ifdef HAS_WM8731
        case PAR_ID_WM8731_I2S_BUS_ROLE: {
            name = Wm8731I2sBusRoleToStr((uint8_t)*value);
        } break;
#endif /*HAS_WM8731*/

#ifdef HAS_AES
        case PAR_ID_AES_256BIT_KEY_ID: {
            name = ArrayToStr(value, 32);
        } break;
#endif

#ifdef HAS_CAN
        case PAR_ID_CAN_NODE_ID: {
            uint32_t can_id = 0;
            memcpy(&can_id, value, 4);
            name = QWordToStr(can_id);
        } break;
#endif

        case PAR_ID_MAX_UP_TIME: {
#ifdef HAS_TIME_DIAG
            uint32_t time_ms = 0;
            memcpy(&time_ms, value, 4);
            name = MsToStr(time_ms);
#endif
        } break;
#ifdef HAS_BOOTLOADER
        case PAR_ID_BOOT_CNT: {
            name = ByteToStr((uint8_t)*value);
        } break;
        case PAR_ID_APP_START:
        case PAR_ID_APP_CRC32: {
#ifdef HAS_NUM_DIAG
            uint32_t app_crc = 0;
            memcpy(&app_crc, value, 4);
            name = HexQWordToStr(app_crc);
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
            name = OnOffToStr((bool)*value);
        } break;

        case PAR_ID_GNSS_MODE: {
            name = rtk_mode2str((uint8_t)*value);
        } break;
        case PAR_ID_RTK_FIX_LONG: {
            uint32_t time_ms = 0;
            memcpy(&time_ms, value, 4);
            name = MsToStr(time_ms);
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
#endif

const char* StoreFsDataToStr(const StorageId_t id, const void* const data) {
    char* name = "?";
    if(data) {
        StorageItem_t* Item = StorageGetNode(id);
        if(Item) {
            if(Item->parser) {
                name = (char*)Item->parser(data);
            }
        }
    }
    return name;
}

bool store_fs_diag(uint8_t num, char* keyWord1, char* keyWord2) {
    bool res = false;
    cli_printf(CRLF);
    static const table_col_t cols[] = {
        {5, "No"},     {6, "id"},
#ifdef HAS_SYSTEM_DIAG
        {12, "group"},
#endif
        {9, "type"},   {23, "VariableName"},
        {5, "len"},    {17, "Value"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint16_t cnt = 1;
    uint16_t i = 0;
    for(i = 0; i < storage_get_cnt(); i++) {
        uint8_t value[100] = {0};
        res = store_fs_get(num, StorageArray[i].id, value);

        char temp[200] = {0};
        strcpy(temp, TSEP);

        snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, cnt);
        snprintf(temp, sizeof(temp), "%s %4u " TSEP, temp, StorageArray[i].id);
#ifdef HAS_SYSTEM_DIAG
        snprintf(temp, sizeof(temp), "%s %10s " TSEP, temp, FacilityToStr(StorageArray[i].facility));
#endif
        snprintf(temp, sizeof(temp), "%s %7s " TSEP, temp, StorageTypeToStr(StorageArray[i].type));
        snprintf(temp, sizeof(temp), "%s %21s " TSEP, temp, StorageArray[i].name);
        snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, StorageArray[i].len);
        snprintf(temp, sizeof(temp), "%s %15s " TSEP, temp, StoreFsDataToStr(StorageArray[i].id, value));

        res = is_contain(temp, keyWord1, keyWord2);
        if(res) {
            cli_printf("%s" CRLF, temp);
            cnt++;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
