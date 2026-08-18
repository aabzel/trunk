#include "bt1026_commands.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "bt1026_config.h"
#include "bt1026_dep.h"
#include "bt1026_diag.h"
#include "bt1026_drv.h"
#include "bt1026_types.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"

#ifdef HAS_BT1026
#include "bt1026_drv.h"
#endif

#ifdef HAS_I2S
#include "i2s_drv.h"
#endif

#ifdef HAS_I2S_DIAG
#include "i2s_diag.h"
#endif

#include "i2s_drv.h"
#include "log.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

bool bt1026_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = bt1026_hw_reset();
    } else {
        LOG_ERROR(BT1026, "Usage: btt");
    }
    return res;
}

bool bt1026_i2s_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }
    if(res) {
#ifdef HAS_I2S_NRFX
        I2sHandle_t* I2sNode = I2sGetNode(BT1026_I2S_NUM);
        if(I2sNode) {
            I2sNode->cur_rx_track = 0;
            I2sNode->i2s_buffers[0].p_rx_buffer = (uint32_t*)&I2sNode->RxBuffer[0][0];
            I2sNode->i2s_buffers[0].p_tx_buffer = (uint32_t*)NULL;
            I2sNode->i2s_buffers[1].p_rx_buffer = (uint32_t*)&I2sNode->RxBuffer[1][0];
            I2sNode->i2s_buffers[1].p_tx_buffer = (uint32_t*)NULL;
            res = i2s_api_start(BT1026_I2S_NUM, 2);
            if(res) {
                LOG_INFO(BT1026, "StartOk");
            } else {
                LOG_ERROR(BT1026, "StartErr");
            }
        }
#endif
    } else {
        LOG_ERROR(BT1026, "Usage: btr");
    }
    return res;
}

bool bt1026_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        LOG_INFO(BT1026, "Version: %u", BT1026_DRIVER_VERSION);
        LOG_INFO(BT1026, "If: UART%u", Bt1026Config.uart_num);
        LOG_INFO(BT1026, "init: %s", OnOffToStr(Bt1026Item.init));
        LOG_INFO(BT1026, "RebootDone: %u", Bt1026Item.reboot_done);
        LOG_INFO(BT1026, "Spin: %u", Bt1026Item.spin);
        LOG_INFO(BT1026, "Rx: %u Byte %u line", Bt1026Item.rx_cnt, Bt1026Item.line_cnt);
        LOG_INFO(BT1026, "Write: %u", Bt1026Item.write_cnt);
        LOG_INFO(BT1026, "Ok: %u", Bt1026Item.ok_cnt);
        LOG_INFO(BT1026, "Cfg: %u", Bt1026Item.cfg_cnt);
        LOG_INFO(BT1026, "Ack: %u", Bt1026Item.ack_cnt);
        LOG_INFO(BT1026, "I2S: %s", OnOffToStr(Bt1026Item.i2s_on));
        LOG_INFO(BT1026, "SampleRate: %s", I2sAudioFreqToStr(Bt1026Item.real_audio_freq));
        LOG_INFO(BT1026, "Resolution: %s", I2sResolutionToStr(Bt1026Item.real_digital_format));
        LOG_INFO(BT1026, "Role: %s", I2sBusRoleToStr(Bt1026Item.real_i2s_role));

        res = true;
    } else {
        LOG_ERROR(BT1026, "Usage: btd");
    }
    return res;
}

bool bt1026_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = bt1026_init();
        if(false == res) {
            LOG_ERROR(BT1026, "Init" LOG_ER);
        } else {
            LOG_INFO(BT1026, "Init" LOG_OK);
        }
    }
    return res;
}

bool bt1026_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    LOG_WARNING(BT1026, "Send argc:%u", argc);
    uint8_t array[256] = "";
    memset(array, 0, sizeof(array));
    strcpy((char*)array, "");
    uint32_t array_len = 0;
    uint32_t i = 0;
    for(i = 0; i < argc; i++) {
        if(0 == i) {
            snprintf((char*)array, sizeof(array), "%s", argv[i]);
            array_len += strlen(argv[i]);
        } else {
            snprintf((char*)array, sizeof(array), "%s %s", array, argv[i]);
            array_len += 1 + strlen(argv[i]);
        }
        res = true;
    }

    if(res) {
        LOG_INFO(BT1026, "Send:[%s] %u byte", array, array_len);
        res = bt1026_send(array, array_len);
        if(false == res) {
            LOG_ERROR(BT1026, "Send" LOG_ER);
        } else {
            LOG_INFO(BT1026, "Send:%u byte" LOG_OK, array_len);
        }
    } else {
        LOG_ERROR(BT1026, "Usage: bts cmd_arg1_arg2");
    }
    return res;
}

bool bt1026_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t array[256] = "";
    memset(array, 0, sizeof(array));
    strcpy((char*)array, "");
    uint32_t array_len = 0;

    if(1 == argc) {
        snprintf((char*)array, sizeof(array), "%s", argv[0]);
        array_len = strlen(argv[0]);
        res = true;
    }

    if(res) {
        array_len++;
        res = bt1026_send_get(array, array_len);
        if(false == res) {
            LOG_ERROR(BT1026, "Send" LOG_ER);
        } else {
            LOG_INFO(BT1026, "Send:%u byte" LOG_OK, array_len);
        }
    } else {
        LOG_ERROR(BT1026, "Usage: btg param");
    }
    return res;
}

bool bt1026_get_volume_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t volume = 0;

    if(res) {
        res = false;
        /*TODO*/
        LOG_INFO(BT1026, "GetVol %u Ok!", volume);
    } else {
        LOG_ERROR(BT1026, "GetVol %u Err", volume);
        LOG_ERROR(BT1026, "Usage: btgv");
    }

    return res;
}

bool bt1026_set_volume_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t volume = 0;
    if(1 == argc) {
        res = try_str2uint8(argv[0], &volume);
        res = bt1026_set_volume(volume);
    }

    if(res) {
        LOG_INFO(BT1026, "SetVol %u Ok!", volume);
    } else {
        LOG_ERROR(BT1026, "SetVol %u Err", volume);
        LOG_ERROR(BT1026, "Usage: bsv Vol");
    }

    return res;
}

bool bt1026_play_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t i2s_num = 0;
    uint32_t words_num = I2S_BUFFER_SIZE;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &i2s_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum [1-%u]", I2S_COUNT);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &words_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr Words");
        }
    }
#ifdef HAS_I2S_NRFX
    I2sHandle_t* I2sNode = I2sGetNode(i2s_num);
    if(I2sNode) {
        I2sNode->cur_tx_track = 0;
        I2sNode->cur_rx_track = 1;

        memset((void*)&I2sNode->RxBuffer[0][0], 0, I2S_BUFFER_SIZE * 2);
        I2sNode->switch_needed = false;
        I2sNode->i2s_buffers[0].p_rx_buffer = (uint32_t*)&I2sNode->RxBuffer[0][0];
        I2sNode->i2s_buffers[0].p_tx_buffer = (uint32_t*)&I2sNode->RxBuffer[0][0];

        I2sNode->i2s_buffers[1].p_rx_buffer = (uint32_t*)&I2sNode->RxBuffer[0][0];
        I2sNode->i2s_buffers[1].p_tx_buffer = (uint32_t*)&I2sNode->RxBuffer[0][0];

        if(words_num <= I2S_BUFFER_SIZE) {
            res = i2s_api_start(i2s_num, words_num);
        } else {
            LOG_ERROR(I2S, "NumOfWordsErr In:%u Max:%u", words_num, I2S_BUFFER_SIZE);
        }
    }
#endif

    return res;
}

bool bt1026_play_swc_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t i2s_num = 0;
    uint32_t words_num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &i2s_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum [1-%u]", I2S_COUNT);
        }
    }
    if(2 <= argc) {
        res = try_str2uint32(argv[1], &words_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr Words");
        }
    }

    if(res) {
#ifdef HAS_I2S_NRFX
        I2sHandle_t* I2sNode = I2sGetNode(i2s_num);
        if(I2sNode) {
            I2sNode->cur_tx_track = 1;
            I2sNode->cur_rx_track = 0;

            I2sNode->switch_needed = true;
            uint8_t i = 0;
            for(i = 0; i < 2; i++) {
                memset((void*)&(I2sNode->TxBuffer[i][0]), 0, I2S_BUFFER_SIZE * 4);
                memset((void*)&(I2sNode->RxBuffer[i][0]), 0, I2S_BUFFER_SIZE * 4);
            }

            I2sNode->i2s_buffers[0].p_rx_buffer = (uint32_t*)&(I2sNode->RxBuffer[0][0]);
            I2sNode->i2s_buffers[1].p_rx_buffer = (uint32_t*)&(I2sNode->RxBuffer[1][0]);

            I2sNode->i2s_buffers[0].p_tx_buffer = (uint32_t*)&(I2sNode->TxBuffer[0][0]);
            I2sNode->i2s_buffers[1].p_tx_buffer = (uint32_t*)(uint32_t const*)&(I2sNode->TxBuffer[1][0]);

            if(words_num <= I2S_BUFFER_SIZE) {
                // nrfx_i2s_next_buffers_set((nrfx_i2s_buffers_t const *)
                // &(I2sNode->i2s_buffers[I2sNode->cur_tx_track]));
                res = i2s_api_start(i2s_num, words_num);
            } else {
                LOG_ERROR(I2S, "NumOfWordsErr In:%u Max:%u", words_num, I2S_BUFFER_SIZE);
            }
        } else {
            LOG_ERROR(I2S, "Node Err");
        }
#endif
    }
    return res;
}

bool bt1026_play_swj_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint32_t words_num = 0;
    uint8_t i2s_num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &i2s_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2sNum [1-%u]", I2S_COUNT);
        }
    }
    if(2 <= argc) {
        res = try_str2uint32(argv[1], &words_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr Words");
        }
    }
    if(res) {
#ifdef HAS_I2S
        res = i2s_loopback(i2s_num, words_num);
        if(res) {
            LOG_INFO(I2S, "LoopBackOk");
        } else {
            LOG_ERROR(I2S, "Node Err");
        }
#endif
    }
    return res;
}

bool bt1026_pairing_command(int32_t argc, char* argv[]) {
    bool res = false;
    bool on_off = 0;
    if(1 == argc) {
        res = try_str2bool(argv[0], &on_off);
    }

    if(res) {
        set_log_level(BT1026, LOG_LEVEL_DEBUG);
        res = bt1026_pairing(on_off);
        set_log_level(BT1026, LOG_LEVEL_INFO);
    }
    return res;
}

bool bt1026_reboot_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        set_log_level(BT1026, LOG_LEVEL_DEBUG);
        res = bt1026_reboot(&Bt1026Item);
        set_log_level(BT1026, LOG_LEVEL_INFO);
    }
    return res;
}

bool bt1026_enable_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = bt1026_enable();
    return res;
}
