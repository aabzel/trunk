#include "i2s_custom_commands.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "i2s_custom_types.h"
#include "i2s_mcal.h"
#include "i2s_custom_drv.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "hal_diag.h"
#include "array_diag.h"
#include "i2s_diag.h"
#include "i2s_mcal.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "table_utils.h"
#include "writer_config.h"

#ifndef HAS_I2S
#error "+HAS_I2S"
#endif /**/

#ifndef HAS_I2S_COMMANDS
#error "+HAS_I2S_COMMANDS"
#endif /**/

bool i2s_custom_read_sample_command(int32_t argc, char* argv[]) {
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

bool i2s_custom_read_write_command(int32_t argc, char* argv[]) {
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
       // res = i2s_read_write(num, tx_sample);
        if(res) {
            LOG_INFO(I2S, LOG_OK);
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2srw instance txsample");
    }
    return res;
}

bool i2s_custom_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 2;
    uint16_t words = 0;
    if(3 == argc) {
        res = true;
        static uint8_t array[256];
        memset(array, 0xFF, sizeof(array));
        uint32_t array_len = 0;
        res = try_str2uint8(argv[0], &num);
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
            res = i2s_mcal_write(num, (uint16_t*)array, words);
            if(false == res) {
                LOG_ERROR(I2S, "%u Unable to send I2S %u", num, words);
            } else {
                LOG_INFO(I2S, "%u WrOk!%d words", num, words);
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


bool i2s_custom_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = i2s_custom_diag();
    } else {
        LOG_ERROR(I2S, "Usage: i2sd");
    }
    return res;
}

bool i2s_custom_diag_ll_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 2 ;

    if(0 <= argc) {
        num = 2 ;
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }


    if(res) {
        res = i2s_diag_low_level(num);
    } else {
        LOG_ERROR(I2S, "Usage: i2sdl Num");
    }
    return res;
}

#if 0
bool i2s_custom_echo_command(int32_t argc, char* argv[]){
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
bool i2s_custom_loopback_command(int32_t argc, char* argv[]){
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
    bool i2s_custom_set_##FLAG##_command(int32_t argc, char* argv[]) {                                                        \
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
                LOG_INFO(I2S, "Ok!");                                                                                  \
            } else {                                                                                                   \
                LOG_ERROR(I2S, "NodeGetErr");                                                                          \
            }                                                                                                          \
        } else {                                                                                                       \
            LOG_ERROR(I2S, CMD_SHORT " num status");                                                               \
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

bool i2s_custom_read_command(int32_t argc, char* argv[]) {
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
                LOG_ERROR(I2S, "Unable to extract array_len %s", argv[2]);
            }
        }

        if(res) {
            I2sHandle_t* Node = I2sGetNode(num);
            if(Node) {
                if(Node->RxArray) {
                    res = i2s_mcal_read(num, (uint16_t*)Node->RxArray, Node->samples_cnt);
                    if(false == res) {
                        LOG_ERROR(I2S, "ReadErr");
                    } else {
                        res = print_mem((uint8_t*)Node->RxArray, Node->samples_cnt * 2, true, false, true, false);
                        cli_printf(CRLF);
                    }
                } else {
                    LOG_ERROR(I2S, "MallocErr");
                }
            }
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2sr num size");
        LOG_INFO(I2S, "num");
        LOG_INFO(I2S, "size");
    }
    return res;
}

bool i2s_custom_init_command(int32_t argc, char* argv[]) {
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


bool i2s_prescaler_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num =2;

    uint32_t I2SDIV ;  /*Bits 7:0 I2SDIV: I2S Linear prescaler   */
    uint32_t ODD;      /*Bit 8 ODD: Odd factor for the prescaler */
    uint32_t MCKOE ;   /*Bit 9 MCKOE: Master clock output enable*/

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &I2SDIV);
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &ODD);
    }

    if(4 <= argc) {
        res = try_str2uint32(argv[3],&MCKOE);
    }

    I2sReg_SPI_I2SPR_t I2SPR;
    I2SPR.dword = 0;
    I2SPR.I2SDIV = I2SDIV;
    I2SPR.ODD = ODD;
    I2SPR.MCKOE = MCKOE;

    if(res) {
        switch(argc) {
            case 0:{
                res = i2s_prescaler_get(  2 , &I2SPR);
                I2sDiagReg_I2SPR(   I2SPR.dword);
            } break;

            case 1: {
                I2sDiagReg_I2SPR(   I2SPR.dword);
                res = i2s_prescaler_get(  num , &I2SPR);
                I2sDiagReg_I2SPR(   I2SPR.dword);
            }break;

            case 2:{
                I2sDiagReg_I2SPR(   I2SPR.dword);
                res = i2s_prescaler_set(  num ,    I2SPR.I2SDIV,   0,   0);
            } break;

            case 3:{
                I2sDiagReg_I2SPR(   I2SPR.dword);
                res = i2s_prescaler_set(  num ,    I2SPR.I2SDIV,   I2SPR.ODD,   0);
            } break;

            case 4:{
                I2sDiagReg_I2SPR(   I2SPR.dword);
                res = i2s_prescaler_set(  num ,   I2SPR.I2SDIV,   I2SPR.ODD,   I2SPR.MCKOE);
            } break;

            default: res = false; break;
        }

    } else {
        LOG_ERROR(I2S, "Usage: i2p num Div Odd MCLKo");
    }
    return res;
}


bool i2s_custom_play_command(int32_t argc, char* argv[]) {
    bool res = false;
#if 0
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
            LOG_INFO(I2S, "Ok!");
        } else {
            LOG_ERROR(I2S, "PlayErr");
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2spl I2sNum DacNum On");
    }
#endif
    return res;
}

#define SET_DMA_COMMAND(FLAG_S, FLAG_C, CMD_SHORT)                                                                     \
    bool i2s_custom_dma_##FLAG_S##_command(int32_t argc, char* argv[]) {                                                      \
        bool res = false;                                                                                              \
        uint8_t num = 0;                                                                                           \
        if(1 <= argc) {                                                                                                \
            res = try_str2uint8(argv[0], &num);                                                                    \
            if(false == res) {                                                                                         \
                LOG_ERROR(I2S, "ParseErr I2Snum [1....5]");                                                            \
            }                                                                                                          \
        }                                                                                                              \
        if(res) {                                                                                                      \
            I2sHandle_t* Node = I2sGetNode(num);                                                                \
            if(Node) {                                                                                              \
                HAL_StatusTypeDef ret;                                                                                 \
                ret = HAL_I2S_DMA##FLAG_C(Node->pHandle);                                                            \
                if(HAL_OK == ret) {                                                                                    \
                    LOG_INFO(I2S, #FLAG_C LOG_OK);                                                                     \
                } else {                                                                                               \
                    LOG_ERROR(I2S, "Dma" #FLAG_C " %s", HalStatusToStr(ret));                                           \
                }                                                                                                      \
            } else {                                                                                                   \
                LOG_ERROR(I2S, "NodeGetErr");                                                                          \
            }                                                                                                          \
        } else {                                                                                                       \
            LOG_ERROR(I2S, CMD_SHORT " num");                                                                      \
        }                                                                                                              \
        return res;                                                                                                    \
    }

SET_DMA_COMMAND(pause, Pause, "i2sdp")
SET_DMA_COMMAND(resume, Resume, "i2sdr")
SET_DMA_COMMAND(stop, Stop, "i2sds")
