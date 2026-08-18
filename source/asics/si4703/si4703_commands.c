#include "si4703_commands.h"

#include <string.h>
#include <stdio.h>

#include "std_includes.h"
#include "convert.h"
#include "log.h"
#include "data_utils.h"
#include "common_diag.h"
#include "si4703_mcal.h"
#include "table_utils.h"
#include "writer_config.h"
#include "str_utils.h"

bool si4703_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if (0 <= argc) {
        res = true;
    }

    if (1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SI4703, res, "Num");
    }

    if (res) {
        res = si4703_diag_one(num);
        log_info_res(SI4703, res, "Diag");

        res = si4703_diag();
        log_info_res(SI4703, res, "Diag");
    } else {
        LOG_ERROR(SI4703, "Usage: fdat");
    }

    return res;
}

bool si4703_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if (1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SI4703, res, "Num");
    }

    if (0 == argc) {
        res = si4703_mcal_init();
        log_info_res(SI4703, res, "Init");
    }
    return res;
}

static bool si4703_read_reg_map(char* key_word1, char* key_word2) {
    bool res = false;
    LOG_INFO(SI4703, "key1:[%s] key2:[%s]", key_word1, key_word2);
    static const table_col_t cols[] = { { 5, "No" }, { 6, "Addr" }, { 11, "BinAddr" }, { 8, "Val" }, { 19, "BinVal" }, {
            20, "name" } };
    uint16_t reg_cnt = 0;
    reg_cnt = si4703_reg_cnt();
    LOG_INFO(SI4703, "RegCnt:%u", reg_cnt);

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint16_t num = 1;
    uint8_t i = 0;
    for (i = 0; i < reg_cnt; i++) {
        uint16_t reg_val = 0;
        res = si4703_read_reg(1, Si4703RegInfo[i].reg_addr, &reg_val);

        char temp_str[120] = { 0 };
        strncpy(temp_str, TSEP, sizeof(temp_str));
        snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, num);
        snprintf(temp_str, sizeof(temp_str), "%s 0x%02x " TSEP, temp_str, Si4703RegInfo[i].reg_addr);
        snprintf(temp_str, sizeof(temp_str), "%s %9s " TSEP, temp_str, utoa_bin8(Si4703RegInfo[i].reg_addr));
        snprintf(temp_str, sizeof(temp_str), "%s 0x%04x " TSEP, temp_str, reg_val);
        snprintf(temp_str, sizeof(temp_str), "%s %9s " TSEP, temp_str, utoa_bin16(reg_val));
        snprintf(temp_str, sizeof(temp_str), "%s %18s " TSEP, temp_str, Si4703RegInfo[i].name);
        res = is_contain(temp_str, key_word1, key_word2);
        if (res) {
            cli_printf("%s" CRLF, temp_str);
            num++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool si4703_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";

    if (0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }

    if (1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }

    if (2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if (2 < argc) {
        LOG_ERROR(GPIO, "Usage: gl keyWord");
    }

    if (res) {
        res = si4703_read_reg_map(keyWord1, keyWord2);
    } else {
        LOG_ERROR(SI4703, "Usage: sim");
    }
    return res;
}

// sir 0x08
bool si4703_reg_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t reg_addr = 0;
    uint16_t reg_val = 0;
    if (1 == argc) {
        res = try_str2uint8(argv[0], &reg_addr);
        if (false == res) {
            LOG_ERROR(SI4703, "ParseErr RegAddr %s", argv[0]);
        }
    }
    if (res) {
        res = si4703_read_reg(1, reg_addr, &reg_val);
        if (false == res) {
            LOG_ERROR(SI4703, "ReadErr [0x%02x]", reg_addr);
        } else {
            LOG_INFO(SI4703, "ReadOk [0x%02x]=0x%04x", reg_addr, reg_val);
        }
    } else {
        LOG_ERROR(SI4703, "Usage: sir RegAddr");
    }
    return res;
}
// sir 0x08; siw 0x08   0x5555 ;sir 0x08
bool si4703_reg_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t reg_addr = 0;
    uint16_t reg_val = 0;
    char bit_mask[30] = "****_****_****_****";
    if (2 == argc) {
        res = try_str2uint8(argv[0], &reg_addr);
        if (false == res) {
            LOG_ERROR(SI4703, "ParseErr RegAddr %s", argv[0]);
        }
        res = try_str2uint16(argv[1], &reg_val);
        if (false == res) {
            LOG_ERROR(SI4703, "ParseErr RegVal %s", argv[1]);
            strcpy(bit_mask, argv[1]);
            //res = is_valid_bit_mask_u16(bit_mask);
        }
    }
    if (res) {
        res = false;
        //res = is_valid_bit_mask_u16(bit_mask);
        if (res) {
            LOG_INFO(SI4703, "StopBitMask [%s]", bit_mask);
            //res = si4703_write_reg_by_bitmask(reg_addr, bit_mask);
        } else {
            res = si4703_write_reg(1, reg_addr, reg_val);
            if (false == res) {
                LOG_ERROR(SI4703, "WriteErr [0x%02x]=0x%04x", reg_addr, reg_val);
            } else {
                LOG_INFO(SI4703, "WriteOk [0x%02x]=0x%04x", reg_addr, reg_val);
            }
        }
    } else {
        LOG_ERROR(SI4703, "Usage1: siw RegAddr RegVal");
        LOG_ERROR(SI4703, "Usage2: siw RegAddr BitMask");
    }
    return res;
}

bool si4703_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    if (0 == argc) {
        res = si4703_reset(1);
        log_info_res(SI4703, res, "Reset");
    } else {
        LOG_ERROR(SI4703, "Usage: sit");
    }
    return res;
}

#define SI4703_PARSE_REG(REG_NAME,PARSER_NAME)       \
  do{                                                \
      uint16_t reg_val = 0;                          \
      LOG_DEBUG(SI4703, "ReadReg 0x%x",REG_NAME);    \
      bool loc_res = si4703_read_reg(1,REG_NAME, &reg_val);   \
      if(loc_res) {                                     \
          LOG_DEBUG(SI4703, "ReadRegOk 0x%x Val:0x%04x",REG_NAME,reg_val);    \
          res = PARSER_NAME( reg_val, keyWord1);   \
      }else{                                     \
          LOG_ERROR(SI4703, "ReadRegErr 0x%x",REG_NAME);    \
          out_res = false;                       \
      }                                          \
  }while(0);

bool si4703_diag_low_level_command(int32_t argc, char* argv[]) {
    bool out_res = true;
    bool res = false;
    char keyWord1[20] = "";
    if (0 == argc) {
        res = true;
    }
    if (1 == argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }

    if (res) {
        const Si4703Config_t *Config = Si4703GetConfig(1);
        if (Config) {
            LOG_INFO(SI4703, "ChipAddr:0x%02x", Config->i2c_addr);

            SI4703_PARSE_REG(0, si4703_parse_deviceid);
            SI4703_PARSE_REG(1, si4703_parse_chipid);
            SI4703_PARSE_REG(2, si4703_parse_power_configuration);
            SI4703_PARSE_REG(3, si4703_parse_channel);
            SI4703_PARSE_REG(4, si4703_parse_system_configuration_1);
            SI4703_PARSE_REG(5, si4703_parse_system_configuration_2);
            SI4703_PARSE_REG(6, si4703_parse_system_configuration_3);
            SI4703_PARSE_REG(7, si4703_parse_test_1);
            SI4703_PARSE_REG(8, si4703_parse_test_2);
            SI4703_PARSE_REG(9, si4703_parse_boot_configuration);
            SI4703_PARSE_REG(10, si4703_parse_status_rssi);
            SI4703_PARSE_REG(11, si4703_parse_read_channel);
            SI4703_PARSE_REG(12, si4703_parse_rdsa);
            SI4703_PARSE_REG(13, si4703_parse_rdsb);
            SI4703_PARSE_REG(14, si4703_parse_rdsc);
            SI4703_PARSE_REG(15, si4703_parse_rdsd);

        }

    } else {
        LOG_ERROR(SI4703, "Usage: sid keyWord");
    }
    return out_res;
}

bool si4703_set_fm_freq_command(int32_t argc, char* argv[]) {
    bool res = false;
    double fm_freq = 0.0;
    if (1 == argc) {
        res = try_str2double(argv[0], &fm_freq);
        if (false == res) {
            LOG_ERROR(SI4703, "ParseErr FmFreq %s", argv[0]);
        }
    }

    if (res) {
        res = si4700_set_frequency(1, fm_freq);
        log_info_res(SI4703, res, "FreqSet");
    } else {
        LOG_ERROR(SI4703, "sif FmFreq");
    }

    return res;
}

bool si4703_power_up_command(int32_t argc, char* argv[]) {
    bool res = false;
    if (0 == argc) {
        res = true;
    }
    if (res) {
        res = si4703_power_up(1);
        log_info_res(SI4703, res, "PowerUp");
    }
    return res;
}

bool si4703_xtall_en_command(int32_t argc, char* argv[]) {
    bool on_off = true;
    bool res = false;
    uint16_t seed = 0x0100;
    if (1 == argc) {
        res = try_str2bool(argv[0], &on_off);
        if (false == res) {
            LOG_ERROR(SI4703, "ParseErr on_off %s", argv[0]);
        }
    }
    if (2 == argc) {
        res = try_str2uint16(argv[1], &seed);
        if (false == res) {
            LOG_ERROR(SI4703, "ParseErr reserved %s", argv[1]);
        }
    }
    if (res) {
        res = si4703_xtall_ctrl(1, on_off, seed);
        log_info_res(SI4703, res, "xTallCtrl");

    }
    return res;
}

bool si4703_rf_seek_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t seek_dir = SEEK_DIR_UP;
    uint8_t seek_end = SEEK_END_WRAP;
    if (0 <= argc) {
        res = true;
    }

    if (1 <= argc) {
        res = try_str2uint8(argv[0], &seek_dir);
        if (false == res) {
            LOG_ERROR(SI4703, "ParseErr SeekDir %s", argv[0]);
        }
    }

    if (2 <= argc) {
        res = try_str2uint8(argv[1], &seek_end);
        if (false == res) {
            LOG_ERROR(SI4703, "ParseErr SeekEnd %s", argv[1]);
        }
    }

    if (res) {
        LOG_INFO(SI4703, "Seek:Dir:%u,End:%u", seek_dir, seek_end);
        res = si4703_fm_seek_start(1, (Si4703SeekDir_t) seek_dir, (Si4703SeekEnd_t) seek_end);
        log_info_res(SI4703, res, "Seek");

    } else {
        LOG_ERROR(SI4703, "Usage: sis Dir End");
    }
    return res;
}

bool si4703_volume_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t volume = 2;
    if (1 <= argc) {
        res = try_str2uint8(argv[0], &volume);
        log_info_res(SI4703, res, "volume");
    }

    if (res) {
        uint8_t old_volume = 0;
        res = si4703_volume_get(1, &old_volume);
        if (res) {
            LOG_INFO(SI4703, "Get,Volume:%u", old_volume);
        }

        res = si4703_volume_set(1, volume);
        log_info_res(SI4703, res, "SetVolume");
    }
    return res;
}
