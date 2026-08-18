#include "bt1026_drv.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bit_const.h"
#include "bt1026_config.h"
#include "bt1026_const.h"
#include "bt1026_diag.h"
#include "core_driver.h"
#include "i2s_diag.h"
#include "limiter.h"
#include "log_utils.h"

#ifdef HAS_TIMER
#include "timer_drv.h"
#endif

#include "clocks.h"
#include "common_functions.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "time_mcal.h"
#ifdef HAS_UART
#include "uart_drv.h"
#endif
#ifdef HAS_PARAM
#include "param_drv.h"
#endif

static uint8_t Role2Bt1026Role(I2sMode_t bus_mode) {
    uint8_t mode = 0;
    switch((uint16_t)bus_mode) {
    case I2SMODE_SLAVE_RX:
    case I2SMODE_SLAVE_TX:
    case I2SMODE_SLAVE:
        mode = BT1026_I2SMODE_SLAVE;
        break;

    case I2SMODE_MASTER_RX:
    case I2SMODE_MASTER_TX:
    case I2SMODE_MASTER:
        mode = BT1026_I2SMODE_MASTER;
        break;
    }
    return mode;
}

static uint8_t SampleRate2Bt1026SampleRate(AudioFreq_t audio_freq) {
    uint8_t sample_rate = 0;
    switch((uint16_t)audio_freq) {
    case I2S_AUDIO_FREQ_48K:
        sample_rate = BT_SAMPLE_RATE_48000_HZ;
        break;
    case I2S_AUDIO_FREQ_41K:
        sample_rate = BT_SAMPLE_RATE_44100_HZ;
        break;
    default:
        sample_rate = BT_SAMPLE_RATE_44100_HZ;
        break;
    }
    return sample_rate;
}

static uint8_t Relolution2Bt1026Resolution(I2sDataFormat_t resolution) {
    uint8_t resol = 0;
    switch((uint16_t)resolution) {
    case I2S_DATA_FORMAT_8B:
        resol = RES_16_BIT;
        break;
    case I2S_DATA_FORMAT_16B:
        resol = RES_16_BIT;
        break;
    case I2S_DATA_FORMAT_16B_EXTENDED:
        resol = RES_16_BIT;
        break;
    case I2S_DATA_FORMAT_24B:
        resol = RES_24_BIT;
        break;
    case I2S_DATA_FORMAT_32B:
        resol = RES_32_BIT;
        break;
    default:
        resol = RES_32_BIT;
        break;
    }
    return resol;
}

/*array must be in RAM*/
bool bt1026_send(uint8_t* array, uint32_t len) {
    bool res = false;
    LOG_DEBUG(BT1026, "Send: [%s] %u byte", array, len);
    if(array && len) {
        res = is_ram_addr((uint32_t)array);
        if(res) {
            array[len] = CARRIAGE_RETURN;
            array[len + 1] = LINE_FEED;
            Bt1026Item.ack = false;
            res = uart_send(UART_NUM_BT1026, array, (uint16_t)len + 2);
            if(false == res) {
                LOG_ERROR(BT1026, "Send: Uart:%u %u byte", UART_NUM_BT1026, len);
            } else {
                Bt1026Item.write_cnt++;
            }
        } else {
            LOG_ERROR(BT1026, "Command [%s] Not In RAM", array);
        }
    } else {
        LOG_ERROR(BT1026, "SendDatErr");
    }
    return res;
}

I2sDataFormat_t Bt1026ResolutionToI2sResolution(uint8_t resolution) {
    I2sDataFormat_t data_format = I2S_DATA_FORMAT_UNDEF;
    switch(resolution) {
    case RES_16_BIT:
        data_format = I2S_DATA_FORMAT_16B;
        break;
    case RES_24_BIT:
        data_format = I2S_DATA_FORMAT_24B;
        break;
    case RES_32_BIT:
        data_format = I2S_DATA_FORMAT_32B;
        break;
    }
    return data_format;
}

AudioFreq_t Bt1026SampleRateToI2sSampleRate(uint8_t sample_rate) {
    AudioFreq_t audio_freq = I2S_AUDIO_FREQ_UNDEF;
    switch(sample_rate) {
    case BT_SAMPLE_RATE_44100_HZ:
        audio_freq = I2S_AUDIO_FREQ_44K;
        break;
    case BT_SAMPLE_RATE_48000_HZ:
        audio_freq = I2S_AUDIO_FREQ_48K;
        break;
    }
    return audio_freq;
}

I2sMode_t Bt1026BusRoleToI2sBusRole(uint8_t role) {
    I2sMode_t bus_role = I2SMODE_UNDEF;
    switch(role) {
    case BT1026_I2SMODE_SLAVE:
        bus_role = I2SMODE_SLAVE;
        break;
    case BT1026_I2SMODE_MASTER:
        bus_role = I2SMODE_MASTER;
        break;
    }
    return bus_role;
}

bool bt1026_parse_i2scfg(uint8_t i2scfg_val) {
    LOG_DEBUG(BT1026, "Parse CFG %u 0x%x", i2scfg_val, i2scfg_val);
    Bt1026I2sConfig_t Bt1026I2sConfig;
    Bt1026I2sConfig.byte = i2scfg_val;
    Bt1026Item.i2s_on = Bt1026I2sConfig.status;
    Bt1026Item.real_i2s_role = Bt1026BusRoleToI2sBusRole(Bt1026I2sConfig.role);
    Bt1026Item.real_audio_freq = Bt1026SampleRateToI2sSampleRate(Bt1026I2sConfig.sample_rate);
    Bt1026Item.real_digital_format = Bt1026ResolutionToI2sResolution(Bt1026I2sConfig.resolution);
    return true;
}

bool bt1026_parse_line(char* line, uint32_t size) {
    bool res = false;
    if(line && size) {
        LOG_DEBUG(BT1026, "ParseStr[%s] Len:%u", line, size);
        if(!strncmp(line, "OK", 2)) {
            Bt1026Item.ok_cnt++;
            if(Bt1026Item.wait_ack) {
                Bt1026Item.ack_cnt++;
                Bt1026Item.wait_ack = false;
            }
        } else if(!strncmp(line, "ERROR", 5)) {
            Bt1026Item.err_cnt++;
        } else if(!strncmp(line, "+I2SCFG=", 8)) {
            Bt1026Item.cfg_cnt++;
            Bt1026Item.i2scfg_val = 0;
            res = try_str2uint8(&line[8], &Bt1026Item.i2scfg_val);
            if(res) {
                res = bt1026_parse_i2scfg(Bt1026Item.i2scfg_val);
            } else {
                LOG_ERROR(BT1026, "ParseI2S cfg err");
            }
        } else {
            LOG_NOTICE(BT1026, "UndefReply [%s] Len:%u", line, size);
        }
    }
    return res;
}
bool bt1026_set_i2s_config(bool status, I2sDataFormat_t resolution, I2sMode_t bus_role, AudioFreq_t audio_freq) {
    bool res = false;
    Bt1026I2sConfig_t Bt1026I2sConfig;
    Bt1026I2sConfig.byte = 0;

    Bt1026I2sConfig.status = status;
    Bt1026I2sConfig.role = (Bt1026I2sBusRole_t)Role2Bt1026Role(bus_role);
    Bt1026I2sConfig.format = 0;
    Bt1026I2sConfig.sample_rate = (BT1026SampleRate_t)SampleRate2Bt1026SampleRate(audio_freq);
    Bt1026I2sConfig.resolution = (BT1026Resolution_t)Relolution2Bt1026Resolution(resolution);
    LOG_INFO(BT1026, "Set I2S config %u", Bt1026I2sConfig.byte);
    res = parse_i2s_config(Bt1026I2sConfig.byte);
    static char text[40] = "";
    snprintf(text, sizeof(text), "AT+I2SCFG=%u", Bt1026I2sConfig.byte);
    uint32_t tx_len = strlen(text);
    res = bt1026_send((uint8_t*)text, tx_len);
    /*TODO wait*/
    return res;
}

static bool bt1026_proc_byte(char in_byte) {
    bool res = false;
    if((0x0D != in_byte) && (0x0A != in_byte)) {
        if(Bt1026Item.pos < sizeof(Bt1026Item.cur_line)) {
            Bt1026Item.cur_line[Bt1026Item.pos] = in_byte;
            Bt1026Item.pos++;
            res = true;
        } else {
            res = false;
        }
    } else {
        memset(Bt1026Item.fix_line, 0, sizeof(Bt1026Item.cur_line));
        memcpy(Bt1026Item.fix_line, Bt1026Item.cur_line, sizeof(Bt1026Item.cur_line));
        memset(Bt1026Item.cur_line, 0, sizeof(Bt1026Item.cur_line));

        res = bt1026_parse_line(Bt1026Item.fix_line, Bt1026Item.pos);
        Bt1026Item.pos = 0;
        Bt1026Item.line_cnt++;
    }
    return res;
}

bool bt1026_init(void) {
    bool res = false;
    LOG_INFO(BT1026, "Init");

    res = limiter_init(&Bt1026Item.LinkLimiter);
    res = limiter_init(&Bt1026Item.DiagLimiter);

    set_log_level(BT1026, LOG_LEVEL_INFO);

    res = bt1026_set_i2s_config(true, Bt1026ConfigLut.digital_format, Bt1026ConfigLut.i2s_role,
                                Bt1026ConfigLut.audio_freq);
    return res;
}

static bool bt1026_check_cfg(void) {
    bool res = true;

    if(Bt1026Item.real_i2s_role != Bt1026ConfigLut.i2s_role) {
        res = false;
        LOG_ERROR(BT1026, "I2S Role UnMatch R:%s S:%s", I2sBusRole2Str(Bt1026Item.real_i2s_role),
                  I2sBusRole2Str(Bt1026ConfigLut.i2s_role));
    }
    if(Bt1026Item.real_digital_format != Bt1026ConfigLut.digital_format) {
        res = false;
        LOG_ERROR(BT1026, "I2S Resolution UnMatch R:%u S:%u Bit", Bt1026Item.real_digital_format,
                  Bt1026ConfigLut.digital_format);
    }
    if(Bt1026Item.real_audio_freq != Bt1026ConfigLut.audio_freq) {
        res = false;
        LOG_ERROR(BT1026, "I2S audio_freq UnMatch R:%u S:%u Hz", Bt1026Item.real_audio_freq,
                  Bt1026ConfigLut.audio_freq);
    }
    if(false == res) {
        // bt1026_init( );
    }

    return res;
}

bool bt1026_check_link(void) {
    bool res = true;
    if(Bt1026Item.wait_ack) {
        uint32_t diff = time_get_ms32() - Bt1026Item.ping_start_ms;
        if(BT1026_LINK_TIMEOUT_MS < diff) {
            Bt1026Item.wait_ack = false;
            LOG_ERROR(BT1026, "LackOfLink %u ms %u ms", diff, BT1026_LINK_TIMEOUT_MS);
        } else {
            res = bt1026_check_cfg();
        }
    } else {
        static char text[40] = "";
        strcpy(text, "AT");
        uint32_t tx_len = strlen(text);
        Bt1026Item.wait_ack = true;
        Bt1026Item.ping_start_ms = time_get_ms32();
        res = bt1026_send((uint8_t*)text, tx_len);
    }
    return res;
}

bool bt1026_diag(void) {
    bool res = true;
    Bt1026Item.real_digital_format = I2S_DATA_FORMAT_UNDEF;
    Bt1026Item.real_audio_freq = I2S_AUDIO_FREQ_UNDEF;
    Bt1026Item.real_i2s_role = I2SMODE_UNDEF;
    static char text[40] = "";
    snprintf(text, sizeof(text), "AT+I2SCFG");
    uint32_t tx_len = strlen(text);
    res = bt1026_send((uint8_t*)text, tx_len);
    return res;
}

bool bt1026_proc(void) {
    bool res = false;
    log_level_t log_level = log_level_get(BT1026);
    uint64_t up_time_us = time_get_us();
    res = limiter_ll(&Bt1026Item.LinkLimiter, BT1026_LINK_CHECK_PERIOD_US, up_time_us, bt1026_check_link);
    res = limiter_ll(&Bt1026Item.DiagLimiter, BT1026_DIAG_PERIOD_US, up_time_us, bt1026_diag);

    Log.time_stamp = false;
    Log.facility_name = false;
    UartHandle_t* UartNode = UartGetNode(UART_NUM_BT1026);
    if(UartNode) {
        uint32_t print_cnt = 0;
        char out_char = 0x00;
        FifoIndex_t cnt = fifo_get_count(&UartNode->RxFifo);
        if(cnt) {
            if(log_level <= LOG_LEVEL_NOTICE) {
                cli_printf(CRLF);
            }
        }
        while(cnt) {
            res = fifo_pull(&UartNode->RxFifo, &out_char);
            if(res) {
                res = bt1026_proc_byte(out_char);
                if((0x0D != out_char) && (0x0A != out_char)) {
                    Log.new_line = false;
                    LOG_NOTICE(BT1026, "%c", out_char);
                    Log.new_line = true;
                } else {
                    if(log_level <= LOG_LEVEL_NOTICE) {
                        cli_printf(CRLF);
                    }
                }
                print_cnt++;
            }
            cnt = fifo_get_count(&UartNode->RxFifo);
        }
        if(print_cnt) {
            res = true;
            if(log_level <= LOG_LEVEL_NOTICE) {
                cli_printf(CRLF);
            }
        }
    }
    Log.time_stamp = true;
    Log.facility_name = true;

    return res;
}

#if 0
static bool bt1026_wait_ack(uint32_t wait_pause_ms) {
    bool res = false, loop = true;
    LOG_DEBUG(BT1026, "WaitAck");
    uint32_t start_ms = 0U, curr_ms = 0U, diff_ms = 0;
    start_ms = time_get_ms32();
    uint64_t loop_start_time_us = 0;
    while(loop) {
        if(Bt1026Item.ack) {
            res = true;
            loop = false;
            LOG_DEBUG(BT1026, "Ack!");
        }
        if(false == res) {
            loop_start_time_us = timer_get_us();
            super_loop(loop_start_time_us);

            curr_ms = time_get_ms32();
            diff_ms = curr_ms - start_ms;
            if(wait_pause_ms < diff_ms) {
                res = false;
                LOG_ERROR(BT1026, "WaitAckTimeOut");
                loop = false;
            }
        }
    }
    return res;
}
#endif

bool bt1026_send_get(uint8_t* param, uint32_t len) {
    bool res = false;
    LOG_DEBUG(BT1026, "Get");

    return res;
}

bool bt1026_send_set(uint8_t* param, uint32_t param_len, uint8_t* value, uint32_t val_len) {
    bool res = false;
    return res;
}

bool bt1026_save(void) {
    bool res = false;
    LOG_DEBUG(BT1026, "Save");

    return res;
}

bool bt1026_hw_reset(void) {
    bool res = false;
    LOG_DEBUG(BT1026, "HwReset");
    res = gpio_set_state(BT1026_PAD_RESET, GPIO_LVL_LOW);
    res = wait_us(10000);
    res = gpio_set_state(BT1026_PAD_RESET, GPIO_LVL_HI);
    return res;
}

bool bt1026_config_audio(void) {
    bool res = false;
    LOG_DEBUG(BT1026, "ConfAudio");
    return res;
}

bool bt1026_config_audio_digital(void) {
    bool res = false;
    LOG_DEBUG(BT1026, "ConfAudioDigital");
    return res;
}

#ifdef HAS_PARAM
static bool bt1026_load_params(Bt1026Config_t* Bt1026ConfigPtr) {
    bool out_res = true;
    if(Bt1026ConfigPtr) {
        LOAD_PARAM_V2(BT1026, PAR_ID_BT1026_I2S_BUS_ROLE, Bt1026ConfigPtr->i2s_param.bus_mode);
        // LOAD_PARAM_V2(BT1026, PAR_ID_BT1026_I2S_SCALING_FACTOR,Bt1026ConfigPtr->i2s_param.scaling_factor);
    }
    return out_res;
}
#endif

bool bt1026_get_volume(uint8_t* volume) {
    bool res = true;
    return res;
}

bool bt1026_set_volume(uint8_t volume) {
    bool res = false;
    return res;
}
// bool status,uint8_t role,uint8_t sample_rate,uint8_t format,uint8_t resolution,
