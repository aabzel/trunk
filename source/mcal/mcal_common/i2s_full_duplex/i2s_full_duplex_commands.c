#include "i2s_commands.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "common_diag.h"
#ifdef HAS_ARRAY
#include "array.h"
#include "array_diag.h"
#endif
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#ifdef HAS_I2S_DIAG
#include "i2s_diag.h"
#endif
#include "i2s_drv.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_TEST_I2S
#include "test_i2s.h"
#endif

#ifdef HAS_BSP_NRF5340
#include "hal_nrfx_diag.h"
#endif

#ifndef HAS_I2S
#error "+HAS_I2S"
#endif /*HAS_I2S*/

#ifndef HAS_I2S_COMMANDS
#error "+HAS_I2S_COMMANDS"
#endif /*HAS_I2S_COMMANDS*/

bool i2s_read_sample_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint16_t size = 2;
    if(1 == argc) {
        res = try_str2uint8(argv[0], &num);
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
        res = i2s_read_sample(num, size);
        if(false == res) {
            LOG_ERROR(I2S, "ReadSampleErr %u", num);
        }
    } else {
        LOG_ERROR(I2S, "Usage: I2SNum SampleSize");
    }
    return res;
}

bool i2s_read_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t tx_sample = 0x5555AAAA;
    uint8_t num = 2;
    if(2 == argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2SNum [1-%u]", I2S_COUNT);
        }
        res = try_str2uint32(argv[1], &tx_sample);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr tx_sample");
        }
    }

    if(res) {
        res = i2s_read_write(num, tx_sample);
        if(res) {
            LOG_INFO(I2S, LOG_OK);
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2srw instance txsample");
    }
    return res;
}

bool i2s_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 2;
    uint16_t words = 0;
    if(3 == argc) {
        res = true;
        static uint8_t array[256];
        memset(array, 0, sizeof(array));
        size_t array_len = 0;
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2SNum [0-%u]", I2S_COUNT);
        }
        if(res) {
            res = try_str2array(argv[1], array, sizeof(array), &array_len);
            if(false == res) {
                LOG_ERROR(I2S, "ParseErr array %s", argv[1]);
            } else {
                LOG_INFO(I2S, "spot %u bytes", array_len);
            }
        }

        res = try_str2uint16(argv[2], &words);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr words %s", argv[2]);
        }

        if(res) {
            res = i2s_api_write(num, (SampleType_t*)array, words);
            if(false == res) {
                LOG_ERROR(I2S, "%u WriteErr %u words", num, words);
            } else {
                LOG_INFO(I2S, "%u WrOk! %u words", num, words);
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


static bool i2s_diag_sample(void) {
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
    uint16_t cnt = 0;
    table_cap(&(curWriterPtr->stream), cols0, ARRAY_SIZE(cols0));
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t num = 0;
    // HAL_I2S_StateTypeDef state;
    char temp_str[120];
    for(num = 1; num <= I2S_COUNT; num++) {
        I2sHandle_t* Node = I2sGetNode(num);
        if(Node) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %u " TSEP, temp_str, Node->num);
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(Node->rx_sample.u32[0]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(Node->tx_sample.u32[0]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(Node->rx_sample_fixed.u32[0]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(Node->tx_sample_fixed.u32[0]));

            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(Node->rx_sample.u32[1]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(Node->tx_sample.u32[1]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(Node->rx_sample_fixed.u32[1]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(Node->tx_sample_fixed.u32[1]));
            const I2sConfig_t* I2sConfNode = I2sGetConfig(num);
            if(I2sConfNode) {
                snprintf(temp_str, sizeof(temp_str), "%s %6s " TSEP, temp_str, I2sConfNode->name);
            }

            cli_printf(TSEP " %3u ", cnt);
            cli_printf("%s" CRLF, temp_str);
            cnt++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}


static bool i2s_diag_errors(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"},
        {5, "num"},
        {6, "Err"},
        {6, "WrireErr"},
        {6, "ReadErr"},
        {6, "StartErr"},
        {6, "TxNextErr"},
        {6, "RxNextErr"},
        {6, "stop"},
        {8, "name"},
    };
    uint16_t cnt = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t num = 0;
    char temp_str[120];
    for(num = 0; num <= I2S_COUNT; num++) {

        I2sHandle_t* Node = I2sGetNode(num);
        if(Node) {
            uint32_t err = i2s_err_total(&(Node->Err));
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %1u   " TSEP, temp_str, Node->num);
            snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int) err);
            snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int) Node->Err.write);
            snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int) Node->Err.read);
            snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int) Node->Err.start);
            snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int) Node->Err.tx_next);
            snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int) Node->Err.rx_next);
            snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int) Node->total_stop_cnt);
            const I2sConfig_t* I2sConfNode = I2sGetConfig(num);
            if(I2sConfNode) {
                snprintf(temp_str, sizeof(temp_str), "%s %6s " TSEP, temp_str, I2sConfNode->name);
            }
            cli_printf(TSEP " %3u ", cnt);
            cli_printf("%s" CRLF, temp_str);
            cnt++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}


static bool i2s_diag_all(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"},
        {5, "num"},
        {9, "TxSampleCnt"},
        {9, "ToggleCnt"},
        {9, "ItCnt"},
        {9, "StopCnt"},
        {9, "StatusStopCnt"},
#ifdef HAS_SW_DAC
        {5, "Dac"},
#endif
        {6, "echo"},
        {6, "loop"},
        {6, "iir"},
        {6, "Err"},
        {9, "rxHalfCnt"},
        {9, "txHalfCnt"},
        {9, "rxCnt"},
        {9, "txCnt"},
        {8, "name"},
    };
    uint16_t cnt = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t num = 0;
    char temp_str[200];
    for(num = 0; num <= I2S_COUNT; num++) {

        I2sHandle_t* Node = I2sGetNode(num);
        //#define __HAL_I2S_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)
        // __HAL_I2S_GET_FLAG(__HANDLE__, __FLAG__)
        // TODO: get bittness
        if(Node) {
            uint32_t err = i2s_err_total(&(Node->Err));
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %1u   " TSEP, temp_str, Node->num);
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, u32val2Str(Node->tx_sample_cnt));
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, u32val2Str(Node->toggle_cnt));
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, u32val2Str(Node->it_cnt));
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, u32val2Str(Node->total_stop_cnt));
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, u32val2Str(Node->status_stop_cnt));
#ifdef HAS_SW_DAC
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, Node->dac_num);
#endif
            snprintf(temp_str, sizeof(temp_str), "%s %3s  " TSEP, temp_str, OnOff2Str(Node->echo));
            snprintf(temp_str, sizeof(temp_str), "%s %3s  " TSEP, temp_str, OnOff2Str(Node->loopback));
            snprintf(temp_str, sizeof(temp_str), "%s %3s  " TSEP, temp_str, OnOff2Str(Node->iir));
            snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int) err);
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, u32val2Str(Node->rx_half_cnt));
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, u32val2Str(Node->tx_half_cnt));
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, u32val2Str(Node->rx_cnt));
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, u32val2Str(Node->tx_cnt));
            const I2sConfig_t* I2sConfNode = I2sGetConfig(num);
            if(I2sConfNode) {
                snprintf(temp_str, sizeof(temp_str), "%s %6s " TSEP, temp_str, I2sConfNode->name);
            }
            cli_printf(TSEP " %3u ", cnt);
            cli_printf("%s" CRLF, temp_str);
            cnt++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool i2s_diag_sample_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = i2s_diag_sample();
    } else {
        LOG_ERROR(I2S, "Usage: i2sa");
    }
    return res;
}

bool i2s_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(0 <= argc) {
        res = true;
        num = 0;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2SNum [0-%u]", I2S_COUNT);
        }
    }

    if(res) {
        res = i2s_diag_one(num);
        res = i2s_diag_all();
    } else {
        LOG_ERROR(I2S, "Usage: i2sd i2sNum");
        LOG_INFO(I2S, "i2sNum [0..%u]",I2S_COUNT);
    }
    return res;
}

bool i2s_diag_errors_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = i2s_diag_errors();
    } else {
        LOG_ERROR(I2S, "Usage: i2ser");
    }
    return res;
}


#if 0
bool i2s_echo_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    bool status = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
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
        I2sHandle_t* Node = I2sGetNode(  num) ;
        if(Node){
            Node->echo = status;
        }else{
            LOG_ERROR(I2S, "NodeGetErr");
        }
    }else{
        LOG_ERROR(I2S, "i2se num status");
    }
    return res;
}
#endif

#if 0
bool i2s_loopback_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    bool status = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
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
        I2sHandle_t* Node = I2sGetNode(  num) ;
        if(Node){
            Node->loopback = status;
        }else{
            LOG_ERROR(I2S, "NodeGetErr");
        }
    }else{
        LOG_ERROR(I2S, "i2sl num status");
    }
    return res;
}
#endif

#define SET_COMMAND(FLAG, CMD_SHORT)                                                                                   \
    bool i2s_set_##FLAG##_command(int32_t argc, char* argv[]) {                                                        \
        bool res = false;                                                                                              \
        uint8_t num = 0;                                                                                           \
        bool status = false;                                                                                           \
        if(1 <= argc) {                                                                                                \
            res = try_str2uint8(argv[0], &num);                                                                    \
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
            I2sHandle_t* Node = I2sGetNode(num);                                                                \
            if(Node) {                                                                                              \
                Node->FLAG = status;                                                                                \
                LOG_INFO(I2S, "%u SetOk!",num);                                                                                  \
            } else {                                                                                                   \
                LOG_ERROR(I2S, "NodeGetErr");                                                                          \
            }                                                                                                          \
        } else {                                                                                                       \
            LOG_ERROR(I2S, CMD_SHORT " num status");                                                               \
        }                                                                                                              \
        return res;                                                                                                    \
    }

SET_COMMAND(iir, "i2sii")
SET_COMMAND(echo, "i2se")
SET_COMMAND(dac, "i2sdac")
//SET_COMMAND(play, "i2sp")

#ifdef HAS_SW_DAC
bool i2s_set_dac_num_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t dac_num = 0;
    if(2 == argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum [1-%u]", I2S_COUNT);
        }
        res = try_str2uint8(argv[0], &dac_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr DacNum");
        }
    }

    if(res) {
        I2sHandle_t* Node = I2sGetNode(num);
        if(Node) {
            Node->dac_num = dac_num;
            LOG_INFO(I2S, "%u Set DacNum %u", num, dac_num);
        } else {
            LOG_ERROR(I2S, "NodeErr");
        }
    }else{
        LOG_ERROR(I2S, "Usage: i2sdn I2sNum DacNum");
    }
    return res;
}
#endif

// i2r 0 0xef 1  -- hang on
// i2r 0 0xef 2  -- hang on

bool i2s_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(2 == argc) {
        res = true;
        uint8_t num = 0;
        uint16_t array_len = 0;
        if(res) {
            res = try_str2uint8(argv[0], &num);
            if(false == res) {
                LOG_ERROR(I2S, "ParseErr I2S Number [1....5]");
            }
        }

        if(res) {
            res = try_str2uint16(argv[1], &array_len);
            if(false == res) {
                LOG_ERROR(I2S, "ParseErr array_len %s", argv[2]);
            }
        }

        if(res) {
            I2sHandle_t* Node = I2sGetNode(num);
            if(Node) {
#if 0
                if(Node->rx_buffer) {
                    free((void*)Node->rx_buffer);
                    Node->rx_buffer = NULL;
                    LOG_WARNING(I2S, "FreeRx");
                }
                Node->rx_buffer = (SampleType_t*)malloc(array_len * 2);
#endif
                if(&Node->RxBuffer[0]) {
                    //Node->rx_buff_size = array_len * 2;
                    res = i2s_api_read(num, (SampleType_t*) &Node->RxBuffer[0], Node->samples_cnt);
                    if(false == res) {
                        LOG_ERROR(I2S, "ReadErr");
                    } else {
#ifdef HAS_ARRAY_DIAG
                    	double sample_period = 1.0/((double)Node->audio_freq);
                        res = array_i32_print((int32_t*)&Node->RxBuffer[0], Node->samples_cnt, sample_period );
#endif
                        cli_printf(CRLF);
                    }
                } else {
                    LOG_ERROR(I2S, "MallocErr");
                }
            }
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2sr I2sNum Size");
    }
    return res;
}

bool i2s_init_command(int32_t argc, char* argv[]) {
    uint8_t num = 0;
    bool res = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum");
        }
    }
    if(res) {
        res = i2s_init_one(num);
        if(false == res) {
            LOG_ERROR(I2S, "I2sInitErr %u", num);
        }
    }
    return res;
}



bool i2s_play_tone_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t dac_num = 0;
    bool status = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
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
        res = i2s_play_static_tx(num, dac_num, status);
        if(res) {
            LOG_INFO(I2S, "I2S%u PlayStatic DAC%u %s Ok",num,dac_num,OnOff2Str(status));
        } else {
            LOG_ERROR(I2S, "PlayErr");
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2spt I2sNum DacNum On");
    }
    return res;
}


bool i2s_play_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t dac_num = 0;
    bool status = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
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
        res = i2s_play_tx(num, dac_num, status);
        if(res) {
            LOG_INFO(I2S, "%u Dac %u %s Ok",num,dac_num,OnOff2Str(status));
        } else {
            LOG_ERROR(I2S, "PlayErr");
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2spl I2sNum DacNum On");
    }
    return res;
}

bool i2s_dma_pause_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num=1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum[%s]", argv[0]);
        }
    }
    res=i2s_dma_stop(num);
    return res;
}

bool i2s_dma_resume_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num=0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum[%s]", argv[0]);
        }
    }
    return res;
}

bool i2s_dma_stop_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num=0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum[%s]", argv[0]);
        }
    }
    res=i2s_dma_stop(num);
    return res;
}

bool i2s_test_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum[%s]", argv[0]);
        }
    }
    if(res){
    	res = false;
#ifdef HAS_TEST_I2S
        res = test_i2s_write_one_qword(num);
#endif
        if(res){
        	LOG_INFO(I2S, "%u Test Ok", num);
        }else{
        	LOG_INFO(I2S, "%u Test Err", num);
        }
    }else {
    	LOG_ERROR(I2S, "Usage: i2st I2sNum");
    }
    return res;
}

bool i2s_config_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t word_size=0;
	uint8_t channels =0;
	uint32_t audio_freq=I2S_AUDIO_FREQ_41K;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum[%s]", argv[0]);
        }
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &word_size);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr WordSize[%s]", argv[1]);
        }
    }
    if(3 <= argc) {
        res = try_str2uint8(argv[2], &channels);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr channels[%s]", argv[2]);
        }
    }

    if(4 <= argc) {
        res = try_str2uint32(argv[3], &audio_freq);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr AudioFreq [%s]", argv[3]);
        }
    }
    if(res && (4==argc)) {
        res = i2s_config_tx(num, word_size, channels, audio_freq);
        if(res) {
        	LOG_INFO(I2S, "%u ConfigOk",num);
        }else {
        	LOG_ERROR(I2S, "%u ConfigErr",num);
        }
    }else {
    	LOG_ERROR(I2S, "Usage: i2sc I2sNum word_size channels audio_freq");
    }
    return res;
}


bool i2s_ctrl_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    bool status = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum[%s]", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2bool(argv[1], &status);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr status[%s]", argv[1]);
        }
    }

    if(res) {
        res = i2s_send(num, status);
        if(res) {
            LOG_INFO(I2S, "%u Send %s Ok",num,OnOff2Str(status));
        } else {
            LOG_ERROR(I2S, "PlayErr");
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2sct I2sNum OnOff");
    }
    return res;
}

bool i2s_set_loopback_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    uint8_t loop_back_mode = LOOPBACK_SHARED_MEM;
    uint32_t words_num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum [1-%u]", I2S_COUNT);
        }
    }
    if(2 <= argc && res) {
        res = try_str2uint32(argv[1], &words_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr Words");
        }
    }
    if(3 <= argc && res) {
        res = try_str2uint8(argv[2], &loop_back_mode);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr Mode");
        }
    }

    if(res) {
    	switch(loop_back_mode){
    	case LOOPBACK_SHARED_MEM:
            res= i2s_loopback_shared_memory(num, words_num);
    		break;
    	case LOOPBACK_SWITCH_MEM:
            res= i2s_loopback(num, words_num);
    		break;
    	default : res = false; break;
    	}
        if(res) {
        	LOG_INFO(I2S, "LoopBackOk");
        }else {
        	LOG_ERROR(I2S, "LoopBackErr");
        }
    }else{
    	LOG_ERROR(I2S, "i2sl I2sNum Words mode");
    }

    return res;
}

bool i2s_set_tone_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    double freq = 0.0;
    uint32_t amp=300;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum [1-%u]", I2S_COUNT);
        }
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &freq);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr Freq[%s]", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &amp);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr Amp[%s]", argv[2]);
        }
    }

    if(res) {
    	res = false;
#ifdef HAS_TEST_I2S
        res = test_i2s_play_freq_com(num, freq, amp);
#endif
        if(res) {
        	LOG_INFO(I2S, "ToneOk");
        }else {
        	LOG_ERROR(I2S, "ToneErr");
        }
    }else {
        LOG_ERROR(I2S, "Usage: i2sn I2sNum Freq Amp");
    }
    return res;
}

