#include "i2s_custom_commands.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "i2s_custom_types.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "hal_diag.h"
#include "i2s_diag.h"
#include "i2s_drv.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "table_utils.h"
#include "writer_config.h"

#ifndef HAS_I2S
#error "+HAS_I2S"
#endif /*HAS_I2S*/

#ifndef HAS_I2S_COMMANDS
#error "+HAS_I2S_COMMANDS"
#endif /*HAS_I2S_COMMANDS*/

bool i2s_stm_read_sample_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t i2s_num = 0;
    uint16_t size = 2;
    if(1 == argc) {
        res = try_str2uint8(argv[0], &i2s_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2SNum [1-%u]", I2S_COUNT);
        }
    }
    if(2 <= argc) {
        res = try_str2uint16(argv[2], &size);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2SNum [1-%u]", I2S_COUNT);
        }
    }
    if(res) {
        res = i2s_read_sample(i2s_num, size);
        if(false == res) {
            LOG_ERROR(I2S, "ReadSampleErr %u", i2s_num);
        }
    } else {
        LOG_ERROR(I2S, "Usage: I2SNum SampleSize");
    }
    return res;
}

bool i2s_stm_read_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t tx_sample = 0x5555AAAA;
    uint8_t i2s_num = 2;
    if(2 == argc) {
        res = try_str2uint8(argv[0], &i2s_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2SNum [1-%u]", I2S_COUNT);
        }
        res = try_str2uint32(argv[1], &tx_sample);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr tx_sample");
        }
    }

    if(res) {
        res = i2s_read_write(i2s_num, tx_sample);
        if(res) {
            LOG_INFO(I2S, LOG_OK);
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2srw instance txsample");
    }
    return res;
}

bool i2s_stm_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t i2s_num = 2;
    uint16_t words = 0;
    if(3 == argc) {
        res = true;
        static uint8_t array[256];
        memset(array, 0xFF, sizeof(array));
        uint32_t array_len = 0;
        res = try_str2uint8(argv[0], &i2s_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2SNum [1-%u]", I2S_COUNT);
        }
        if(res) {
            res = try_str2array(argv[1], array, sizeof(array), &array_len);
            if(false == res) {
                LOG_ERROR(I2S, "Unable to extract array %s", argv[1]);
            } else {
                LOG_INFO(I2S, "spot %u bytes", array_len);
            }
        }

        res = try_str2uint16(argv[2], &words);
        if(false == res) {
            LOG_ERROR(I2S, "Unable to extract words %s", argv[2]);
        }

        if(res) {
            res = i2s_write(i2s_num, (uint16_t*)array, words);
            if(false == res) {
                LOG_ERROR(I2S, "%u Unable to send I2S %u", i2s_num, words);
            } else {
                LOG_INFO(I2S, "%u WrOk!%d words", i2s_num, words);
            }
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2sw instance hex_string words");
        LOG_INFO(I2S, "instance");
        LOG_INFO(I2S, "hex_string 0x[0...F]+");
        LOG_INFO(I2S, "words");
    }
    return res;
}

static bool i2s_stm_diag_low_level(void) {
    bool res = false;
    static const table_col_t cols[] = {{5, "No"},  {12, "Base"}, {5, "mode"}, {5, "i2s"},    {4, "bit"}, {10, "Role"},
                                       {5, "Std"}, {6, "chlen"}, {5, "Psr"},  {6, "ClkOut"}, {12, "Odd"}};
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i2s_num = 0;
    char temp_str[120];
    char suffix[50];
    for(i2s_num = 1; i2s_num <= I2S_COUNT; i2s_num++) {
        SPI_TypeDef* I2sBaseAddr = I2sGetBaseAddr(i2s_num);
        strcpy(temp_str, TSEP);
        RegI2sConfig_t Reg;
        RegI2sPsc_t RegPscPre;
        if(I2sBaseAddr) {
            Reg.reg_val = I2sBaseAddr->I2SCFGR;
            RegPscPre.reg_val = I2sBaseAddr->I2SPR;
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, i2s_num);

            snprintf(suffix, sizeof(suffix), " 0x%08x " TSEP, (unsigned int)I2sBaseAddr);
            strcat(temp_str, suffix);

            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, SerialMode2Str(Reg.i2smod));
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, OnOff2Str(Reg.i2se));
            snprintf(temp_str, sizeof(temp_str), "%s %2s " TSEP, temp_str, I2sBit2Str(Reg.datlen));
            snprintf(temp_str, sizeof(temp_str), "%s %8s " TSEP, temp_str, I2sRole2Str(Reg.i2scfg));
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, I2sStd2Str(Reg.i2sstd));
            snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, I2sChlen2Str(Reg.chlen));
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, RegPscPre.i2sdiv);
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, OnOff2Str(RegPscPre.mckoe));
            snprintf(temp_str, sizeof(temp_str), "%s %10s " TSEP, temp_str, I2sOdd2Str(RegPscPre.odd));
        }
        cli_printf("%s" CRLF, temp_str);
        num++;
        res = true;
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

static bool i2s_stm_diag_sample(void) {
    bool res = false;
    static const table_col_t cols0[] = {
        {9, ""},
        {35, "left"},
        {35, "right"},
        {8, ""},
    };

    static const table_col_t cols[] = {
        {5, "No"}, {3, "#"},  {8, "Rx"},    {8, "Tx"},    {8, "RxFix"}, {8, "TxFix"},
        {8, "Rx"}, {8, "Tx"}, {8, "RxFix"}, {8, "TxFix"}, {8, "name"},
    };
    uint16_t num = 0;
    table_cap(&(curWriterPtr->stream), cols0, ARRAY_SIZE(cols0));
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i2s_num = 0;
    // HAL_I2S_StateTypeDef state;
    char temp_str[120];
    for(i2s_num = 1; i2s_num <= I2S_COUNT; i2s_num++) {
        I2sHandle_t* I2sNode = I2sGetNode(i2s_num);
        if(I2sNode) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %u " TSEP, temp_str, I2sNode->num);
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(I2sNode->rx_sample.u32[0]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(I2sNode->tx_sample.u32[0]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(I2sNode->rx_sample_fixed.u32[0]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(I2sNode->tx_sample_fixed.u32[0]));

            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(I2sNode->rx_sample.u32[1]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(I2sNode->tx_sample.u32[1]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(I2sNode->rx_sample_fixed.u32[1]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(I2sNode->tx_sample_fixed.u32[1]));
            I2sConfig_t* I2sConfNode = I2sGetConfNode(i2s_num);
            if(I2sConfNode) {
                snprintf(temp_str, sizeof(temp_str), "%s %6s " TSEP, temp_str, I2sConfNode->name);
            }

            cli_printf(TSEP " %3u ", num);
            cli_printf("%s" CRLF, temp_str);
            num++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

static bool i2s_stm_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"},        {5, "num"},       {6, "echo"},  {6, "loop"},  {6, "iir"},    {6, "Err"},
        {9, "rxHalfCnt"}, {9, "txHalfCnt"}, {9, "rxCnt"}, {9, "txCnt"}, {10, "state"}, {8, "name"},
    };
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i2s_num = 0;
    HAL_I2S_StateTypeDef state;
    char temp_str[120];
    for(i2s_num = 1; i2s_num <= I2S_COUNT; i2s_num++) {

        I2sHandle_t* I2sNode = I2sGetNode(i2s_num);
        //#define __HAL_I2S_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)
        // __HAL_I2S_GET_FLAG(__HANDLE__, __FLAG__)
        // TODO: get bittness
        if(I2sNode) {
            strcpy(temp_str, TSEP);
            state = HAL_I2S_GetState(&I2sNode->i2s_h);
            snprintf(temp_str, sizeof(temp_str), "%s %1u   " TSEP, temp_str, I2sNode->num);
            snprintf(temp_str, sizeof(temp_str), "%s %3s  " TSEP, temp_str, OnOff2Str(I2sNode->echo));
            snprintf(temp_str, sizeof(temp_str), "%s %3s  " TSEP, temp_str, OnOff2Str(I2sNode->loopback));
            snprintf(temp_str, sizeof(temp_str), "%s %3s  " TSEP, temp_str, OnOff2Str(I2sNode->iir));
            snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int)I2sNode->error_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, u32val2Str(I2sNode->rx_half_cnt));
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, u32val2Str(I2sNode->tx_half_cnt));
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, u32val2Str(I2sNode->rx_cnt));
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, u32val2Str(I2sNode->tx_cnt));
            snprintf(temp_str, sizeof(temp_str), "%s %8s " TSEP, temp_str, HalI2sState2Str(state));
            I2sConfig_t* I2sConfNode = I2sGetConfNode(i2s_num);
            if(I2sConfNode) {
                snprintf(temp_str, sizeof(temp_str), "%s %6s " TSEP, temp_str, I2sConfNode->name);
            }

            cli_printf(TSEP " %3u ", num);
            cli_printf("%s" CRLF, temp_str);
            num++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool i2s_stm_diag_sample_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = i2s_diag_sample();
    } else {
        LOG_ERROR(I2S, "Usage: i2sa");
    }
    return res;
}

bool i2s_stm_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = i2s_diag();
    } else {
        LOG_ERROR(I2S, "Usage: i2sd");
    }
    return res;
}

bool i2s_stm_diag_ll_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = i2s_diag_low_level();
    } else {
        LOG_ERROR(I2S, "Usage: i2sdl");
    }
    return res;
}

#if 0
bool i2s_stm_echo_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t i2s_num = 0;
    bool status = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &i2s_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2Snum [1....5]");
        }
    }
    if(2 <= argc) {
        res = try_str2bool(argv[1], &status);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr status");
        }
    }
    if(res){
        I2sHandle_t* I2sNode = I2sGetNode(  i2s_num) ;
        if(I2sNode){
            I2sNode->echo = status;
        }else{
            LOG_ERROR(I2S, "NodeGetErr");
        }
    }else{
        LOG_ERROR(I2S, "i2se i2s_num status");
    }
    return res;
}
#endif

#if 0
bool i2s_stm_loopback_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t i2s_num = 0;
    bool status = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &i2s_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2Snum [1....5]");
        }
    }
    if(2 <= argc) {
        res = try_str2bool(argv[1], &status);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr status");
        }
    }
    if(res){
        I2sHandle_t* I2sNode = I2sGetNode(  i2s_num) ;
        if(I2sNode){
            I2sNode->loopback = status;
        }else{
            LOG_ERROR(I2S, "NodeGetErr");
        }
    }else{
        LOG_ERROR(I2S, "i2sl i2s_num status");
    }
    return res;
}
#endif

#define SET_COMMAND(FLAG, CMD_SHORT)                                                                                   \
    bool i2s_stm_set_##FLAG##_command(int32_t argc, char* argv[]) {                                                        \
        bool res = false;                                                                                              \
        uint8_t i2s_num = 0;                                                                                           \
        bool status = false;                                                                                           \
        if(1 <= argc) {                                                                                                \
            res = try_str2uint8(argv[0], &i2s_num);                                                                    \
            if(false == res) {                                                                                         \
                LOG_ERROR(I2S, "ParseErr I2Snum [1....5]");                                                            \
            }                                                                                                          \
        }                                                                                                              \
        if(2 <= argc) {                                                                                                \
            res = try_str2bool(argv[1], &status);                                                                      \
            if(false == res) {                                                                                         \
                LOG_ERROR(I2S, "ParseErr status");                                                                     \
            }                                                                                                          \
        }                                                                                                              \
        if(res) {                                                                                                      \
            I2sHandle_t* I2sNode = I2sGetNode(i2s_num);                                                                \
            if(I2sNode) {                                                                                              \
                I2sNode->FLAG = status;                                                                                \
                LOG_INFO(I2S, "Ok!");                                                                                  \
            } else {                                                                                                   \
                LOG_ERROR(I2S, "NodeGetErr");                                                                          \
            }                                                                                                          \
        } else {                                                                                                       \
            LOG_ERROR(I2S, CMD_SHORT " i2s_num status");                                                               \
        }                                                                                                              \
        return res;                                                                                                    \
    }

SET_COMMAND(iir, "i2sii")
SET_COMMAND(loopback, "i2sl")
SET_COMMAND(echo, "i2se")
SET_COMMAND(dac, "i2sda")
SET_COMMAND(play, "i2sp")

// i2r 0 0xef 1  -- hang on
// i2r 0 0xef 2  -- hang on

bool i2s_stm_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(2 == argc) {
        res = true;
        uint8_t i2s_num = 0;
        uint16_t array_len = 0;
        if(res) {
            res = try_str2uint8(argv[0], &i2s_num);
            if(false == res) {
                LOG_ERROR(I2S, "ParseErr I2S Number [1....5]");
            }
        }

        if(res) {
            res = try_str2uint16(argv[1], &array_len);
            if(false == res) {
                LOG_ERROR(I2S, "Unable to extract array_len %s", argv[2]);
            }
        }

        if(res) {
            I2sHandle_t* I2sNode = I2sGetNode(i2s_num);
            if(I2sNode) {
                if(I2sNode->rx_buff) {
                    free((void*)I2sNode->rx_buff);
                    I2sNode->rx_buff = NULL;
                    LOG_WARNING(I2S, "FreeRx");
                }
                I2sNode->rx_buff = (uint8_t*)malloc(array_len * 2);
                if(I2sNode->rx_buff) {
                    I2sNode->rx_buff_size = array_len * 2;
                    res = i2s_read(i2s_num, (uint16_t*)I2sNode->rx_buff, array_len);
                    if(false == res) {
                        LOG_ERROR(I2S, "ReadErr");
                    } else {
                        res = print_mem((uint8_t*)I2sNode->rx_buff, array_len * 2, true, false, true, false);
                        cli_printf(CRLF);
                    }
                } else {
                    LOG_ERROR(I2S, "MallocErr");
                }
            }
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2sr i2s_num size");
        LOG_INFO(I2S, "i2s_num");
        LOG_INFO(I2S, "size");
    }
    return res;
}

bool i2s_stm_init_command(int32_t argc, char* argv[]) {
    uint8_t i2s_num = 0;
    bool res = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &i2s_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum");
        }
    }
    if(res) {
        res = i2s_init_ll(i2s_num);
        if(false == res) {
            LOG_ERROR(I2S, "I2sInitErr %u", i2s_num);
        }
    }
    return res;
}

bool i2s_stm_play_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t i2s_num = 0;
    uint8_t dac_num = 0;
    bool status = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &i2s_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum[%s]", argv[0]);
        }
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &dac_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr DacNum[%s]", argv[1]);
        }
    }
    if(3 <= argc) {
        res = try_str2bool(argv[2], &status);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr status[%s]", argv[2]);
        }
    }
    if(res) {
        res = i2s_play_tx(i2s_num, dac_num, status);
        if(res) {
            LOG_INFO(I2S, "Ok!");
        } else {
            LOG_ERROR(I2S, "PlayErr");
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2spl I2sNum DacNum On");
    }
    return res;
}

#define SET_DMA_COMMAND(FLAG_S, FLAG_C, CMD_SHORT)                                                                     \
    bool i2s_stm_dma_##FLAG_S##_command(int32_t argc, char* argv[]) {                                                      \
        bool res = false;                                                                                              \
        uint8_t i2s_num = 0;                                                                                           \
        if(1 <= argc) {                                                                                                \
            res = try_str2uint8(argv[0], &i2s_num);                                                                    \
            if(false == res) {                                                                                         \
                LOG_ERROR(I2S, "ParseErr I2Snum [1....5]");                                                            \
            }                                                                                                          \
        }                                                                                                              \
        if(res) {                                                                                                      \
            I2sHandle_t* I2sNode = I2sGetNode(i2s_num);                                                                \
            if(I2sNode) {                                                                                              \
                HAL_StatusTypeDef ret;                                                                                 \
                ret = HAL_I2S_DMA##FLAG_C(&I2sNode->i2s_h);                                                            \
                if(HAL_OK == ret) {                                                                                    \
                    LOG_INFO(I2S, #FLAG_C LOG_OK);                                                                     \
                } else {                                                                                               \
                    LOG_ERROR(I2S, "Dma" #FLAG_C " %s", HalStatus2Str(ret));                                           \
                }                                                                                                      \
            } else {                                                                                                   \
                LOG_ERROR(I2S, "NodeGetErr");                                                                          \
            }                                                                                                          \
        } else {                                                                                                       \
            LOG_ERROR(I2S, CMD_SHORT " i2s_num");                                                                      \
        }                                                                                                              \
        return res;                                                                                                    \
    }

SET_DMA_COMMAND(pause, Pause, "i2sdp")
SET_DMA_COMMAND(resume, Resume, "i2sdr")
SET_DMA_COMMAND(stop, Stop, "i2sds")
