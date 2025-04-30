#include "i2s_commands.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef HAS_ARRAY
#include "array.h"
#endif
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "i2s_mcal.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_TEST_I2S
#include "test_i2s.h"
#endif

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

bool i2s_listen_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 2;
    uint32_t duration_ms = 3000;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2SNum [1-%u]", I2S_COUNT);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &duration_ms);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr DurationMs %s", argv[1]);
        }
    }

    if(res) {
        res = i2s_listen(num, duration_ms);
    } else {
        LOG_ERROR(I2S, "Usage: i2sl Num DurationMs");
    }

    return res;
}

bool i2s_calc_dft_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 2;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2SNum [1-%u]", I2S_COUNT);
        }
    }

    if(res) {
        res = false;
#ifdef HAS_DFT
        res = i2s_calc_dft(num);
#endif
    } else {
        LOG_ERROR(I2S, "Usage: i2sdf Num");
    }

    return res;
}

bool i2s_rec_show_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 2;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2SNum [1-%u]", I2S_COUNT);
        }
    }

    if(res) {
        res = i2s_print_rx(num);
        if(res) {
            LOG_INFO(I2S, LOG_OK);
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2srs Num");
    }
    return res;
}

bool i2s_rec_reverse_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 2;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2SNum [1-%u]", I2S_COUNT);
        }
    }

    if(res) {
        res = i2s_rec_reverse_byte_order(num);
        if(res) {
            LOG_INFO(I2S, LOG_OK);
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2srr Num");
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

bool i2s_diag_sample_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = i2s_diag_sample();
    } else {
        LOG_ERROR(I2S, "Usage: i2sa");
    }
    return res;
}

bool i2s_diag_configs_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = i2s_diag_config();
    } else {
        LOG_ERROR(I2S, "Usage: I2sNum");
        LOG_INFO(I2S, "I2sNum [0..%u]", I2S_COUNT);
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
        LOG_INFO(I2S, "i2sNum [0..%u]", I2S_COUNT);
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
        uint8_t num = 0;                                                                                               \
        bool status = false;                                                                                           \
        if(1 <= argc) {                                                                                                \
            res = try_str2uint8(argv[0], &num);                                                                        \
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
            I2sHandle_t* Node = I2sGetNode(num);                                                                       \
            if(Node) {                                                                                                 \
                Node->FLAG = status;                                                                                   \
                LOG_INFO(I2S, "%u SetOk!", num);                                                                       \
            } else {                                                                                                   \
                LOG_ERROR(I2S, "NodeGetErr");                                                                          \
            }                                                                                                          \
        } else {                                                                                                       \
            LOG_ERROR(I2S, CMD_SHORT " num status");                                                                   \
        }                                                                                                              \
        return res;                                                                                                    \
    }

SET_COMMAND(iir, "i2sii")
SET_COMMAND(echo, "i2se")
SET_COMMAND(dac, "i2sdac")
// SET_COMMAND(play, "i2sp")

#ifdef HAS_DDS
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
    } else {
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
                if(Node->RxBuffer) {
                    // Node->rx_buff_size = array_len * 2;
                    res = i2s_api_read(num, (SampleType_t*)Node->RxBuffer, Node->samples_cnt);
                    if(false == res) {
                        LOG_ERROR(I2S, "ReadErr");
                    } else {
#ifdef HAS_ARRAY_DIAG
                        double sample_period = 1.0 / ((double)Node->audio_freq_hz);
                        res = array_i32_print((int32_t*)&Node->RxBuffer[0], Node->samples_cnt, sample_period);
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

/*i2spt 2 1 1*/
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
            LOG_INFO(I2S, "I2S%u PlayStatic DAC%u %s Ok", num, dac_num, OnOffToStr(status));
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
            LOG_INFO(I2S, "%u Dac %u %s Ok", num, dac_num, OnOffToStr(status));
        } else {
            LOG_ERROR(I2S, "PlayErr");
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2spl I2sNum DacNum On");
    }
    return res;
}

bool i2s_dma_pause_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum[%s]", argv[0]);
        }
    }
    res = i2s_dma_stop(num);
    return res;
}

bool i2s_dma_resume_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum[%s]", argv[0]);
        }
    }
    return res;
}

bool i2s_dma_stop_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum[%s]", argv[0]);
        }
    }
    res = i2s_dma_stop(num);
    return res;
}

bool i2s_test_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum[%s]", argv[0]);
        }
    }
    if(res) {
        res = false;
#ifdef HAS_TEST_I2S
        res = test_i2s_write_one_qword(num);
#endif
        if(res) {
            LOG_INFO(I2S, "%u Test Ok", num);
        } else {
            LOG_INFO(I2S, "%u Test Err", num);
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2st I2sNum");
    }
    return res;
}

bool i2s_config_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t word_size = 0;
    uint8_t channels = 0;
    uint32_t audio_freq_hz = I2S_AUDIO_FREQ_41K;
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
        res = try_str2uint32(argv[3], &audio_freq_hz);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr AudioFreq [%s]", argv[3]);
        }
    }
    if(res && (4 == argc)) {
        res = i2s_config_tx(num, word_size, channels, audio_freq_hz);
        if(res) {
            LOG_INFO(I2S, "%u ConfigOk", num);
        } else {
            LOG_ERROR(I2S, "%u ConfigErr", num);
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2sc I2sNum word_size channels audio_freq_hz");
    }
    return res;
}

bool i2s_ctrl_command(int32_t argc, char* argv[]) {
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
            LOG_INFO(I2S, "%u Send %s Ok", num, OnOffToStr(status));
        } else {
            LOG_ERROR(I2S, "PlayErr");
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2sct I2sNum OnOff");
    }
    return res;
}

bool i2s_set_loopback_command(int32_t argc, char* argv[]) {
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
        switch(loop_back_mode) {
        case LOOPBACK_SHARED_MEM:
            res = i2s_loopback_shared_memory(num, words_num);
            break;
        case LOOPBACK_SWITCH_MEM:
            res = i2s_loopback(num, words_num);
            break;
        default:
            res = false;
            break;
        }
        if(res) {
            LOG_INFO(I2S, "LoopBackOk");
        } else {
            LOG_ERROR(I2S, "LoopBackErr");
        }
    } else {
        LOG_ERROR(I2S, "i2sl I2sNum Words mode");
    }

    return res;
}

bool i2s_set_tone_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    double freq = 0.0;
    uint32_t amp = 300;
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
        } else {
            LOG_ERROR(I2S, "ToneErr");
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2sn I2sNum Freq Amp");
    }
    return res;
}

bool i2s_stream_diag_command(int32_t argc, char* argv[]) {
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
        res = i2s_stream_diag(num);
    } else {
        LOG_ERROR(I2S, "Usage: i2ssd Num");
        LOG_INFO(I2S, "i2sNum [0..%u]", I2S_COUNT);
    }
    return res;
}

bool i2s_bus_role_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t bus_role = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2SNum [0-%u]", I2S_COUNT);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &bus_role);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr BusRole");
        }
    }

    if(res) {
        switch(argc) {
        case 1: {
            I2sRole_t bus_role = I2SMODE_UNDEF;
            res = i2s_bus_role_get(num, &bus_role);
            LOG_INFO(I2S, "Get,I2S_%u,Role:%s", num, I2sBusRole2Str(bus_role));
        } break;
        case 2: {
            LOG_INFO(I2S, "Set,I2S_%u,Role:%s", num, I2sBusRole2Str((I2sRole_t)bus_role));
            res = i2s_bus_role_set(num, (I2sRole_t)bus_role);

        } break;
        }
    } else {
        LOG_ERROR(I2S, "Usage: i2sbr I2sNum BusRole");
        LOG_INFO(I2S, "I2sNum [0..%u]", I2S_COUNT);
    }
    return res;
}
