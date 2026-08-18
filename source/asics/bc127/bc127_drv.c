#include "bc127_drv.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bc127_config.h"
#include "bc127_const.h"
#include "bc127_diag.h"
#include "bit_const.h"
#include "cli_utils.h"
//#include "core_utils.h"

#ifdef HAS_TIMER
#include "timer_drv.h"
#endif

#include "clocks.h"
#include "common_functions.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "time_mcal.h"
#ifdef HAS_UART
#include "uart_drv.h"
#endif
#ifdef HAS_PARAM
#include "param_drv.h"
#endif

static bool bc127_parse_error(char* line, uint32_t size) {
    bool res = false;
    if(line && 6 == size) {
        res = try_strl2uint16(line, 6, (uint16_t*)&Bc127Item.err_code);
        if(res) {
            LOG_ERROR(BC127, "Errror 0x%04x %s", Bc127Item.err_code, ErrorCodeToStr(Bc127Item.err_code));
        }
    }
    return res;
}

// 000000000011111111112
// 012345678901234567890
// 0 44100 64 100A00 OFF
static bool bc127_parse_audio_digital(char* line, uint32_t size) {
    bool res = false;
    if(line && size) {
        LOG_DEBUG(BC127, "ParseAudioigital[%s] Len:%u", line, size);
        res = try_strl2uint8(line, 1, (uint8_t*)&Bc127Item.digital_format);
        if(false == res) {
            LOG_ERROR(BC127, "ParseErr[%s]", line);
        }
        res = try_strl2uint32(&line[2], 5, (uint32_t*)&Bc127Item.digital_rate);
        if(false == res) {
            LOG_ERROR(BC127, "ParseErr[%s]", &line[2]);
        }
        res = try_strl2uint32(&line[8], 2, &Bc127Item.param_1);
        if(false == res) {
            LOG_ERROR(BC127, "ParseErr[%s]", &line[8]);
        }
        res = try_strl2uint32_hex(&line[11], 6, &Bc127Item.Param2.reg_val);
        if(false == res) {
            LOG_ERROR(BC127, "ParseErr[%s]", &line[11]);
        }
    }
    return res;
}

bool bc127_extract_volume(uint8_t link_id, uint8_t* volume) {
    bool res = false;
    uint32_t i;
    uint32_t cnt = ARRAY_SIZE(Bc127Item.LinkVolume);
    for(i = 0; i < cnt; i++) {
        if(Bc127Item.LinkVolume[i].link_id == link_id) {
            (*volume) = Bc127Item.LinkVolume[i].volume;
            res = true;
        }
    }
    return res;
}

static bool bc127_update_volume(Bc127Handle_t* Bc127Handle, LinkVolume_t* LinkVolume) {
    bool res = false;
    bool insert = false;
    LOG_DEBUG(BC127, "UpdateVolume");
    uint32_t i;
    uint32_t cnt = ARRAY_SIZE(Bc127Handle->LinkVolume);
    for(i = 0; i < cnt; i++) {
        if(Bc127Handle->LinkVolume[i].link_id == LinkVolume->link_id) {
            LOG_DEBUG(BC127, "UpdateVolume");
            memcpy(&Bc127Handle->LinkVolume[i], LinkVolume, sizeof(LinkVolume_t));
            Bc127Handle->LinkVolume[i].busy = true;
            insert = true;
            break;
        }
    }

    if(false == insert) {
        for(i = 0; i < cnt; i++) {
            if(false == Bc127Handle->LinkVolume[i].busy) {
                LOG_DEBUG(BC127, "InsertVolume");
                memcpy(&Bc127Handle->LinkVolume[i], LinkVolume, sizeof(LinkVolume_t));
                Bc127Handle->LinkVolume[i].busy = true;
                insert = true;
                break;
            }
        }
    }

    return res;
}

bool bc127_parse_volume(char* line, uint32_t size, Bc127Handle_t* Bc127Handle) {
    bool res = false;
    LOG_DEBUG(BC127, "ParseVolume");
    if(line && size && Bc127Handle) {
        LinkVolume_t LinkVolume;
        LinkVolume.busy = false;
        int ret = sscanf(line, "%u %s %x", (unsigned int*)&LinkVolume.link_id, LinkVolume.name,
                         (unsigned int*)&LinkVolume.volume);
        if(3 == ret) {
            LOG_DEBUG(BC127, "SpotChanVolume %u [%s] %x", LinkVolume.link_id, LinkVolume.name, LinkVolume.volume);
            LinkVolume.busy = true;
            res = bc127_update_volume(Bc127Handle, &LinkVolume);
        }
    }
    return res;
}

static bool bc127_parse_line(char* line, uint32_t size) {
    bool res = false;
    if(line && size) {
        LOG_DEBUG(BC127, "ParseStr[%s] Len:%u", line, size);
        if(!strncmp(line, "ERROR ", 6)) {
            res = bc127_parse_error(&line[6], size - 6);
        }
        if(!strncmp(line, "AUDIO_DIGITAL=", 14)) {
            res = bc127_parse_audio_digital(&line[14], size - 14);
        }
        if(!strncmp(line, BC127_ACK, strlen(BC127_ACK))) {
            Bc127Item.ack = true;
            Bc127Item.ack_cnt++;
        } else {
            res = bc127_parse_volume(line, size, &Bc127Item);
        }
    }
    return res;
}

static bool bc127_proc_byte(char in_byte) {
    bool res = false;
    if(0x0D != in_byte) {
        if(Bc127Item.pos < sizeof(Bc127Item.cur_line)) {
            Bc127Item.cur_line[Bc127Item.pos] = in_byte;
            Bc127Item.pos++;
            res = true;
        } else {
            res = false;
        }
    } else {
        memset(Bc127Item.fix_line, 0, sizeof(Bc127Item.cur_line));
        memcpy(Bc127Item.fix_line, Bc127Item.cur_line, sizeof(Bc127Item.cur_line));
        memset(Bc127Item.cur_line, 0, sizeof(Bc127Item.cur_line));
        res = bc127_parse_line(Bc127Item.fix_line, Bc127Item.pos);
        Bc127Item.pos = 0;
        Bc127Item.line_cnt++;
    }
    return res;
}

bool bc127_proc(void) {
    bool res = false;
    Log.time_stamp = false;
    Log.facility_name = false;
    UartHandle_t* UartNode = UartGetNode(UART_NUM_BC127);
    if(UartNode) {
        uint32_t print_cnt = 0;
        char out_char = 0x00;
        FifoIndex_t cnt = fifo_get_count(&UartNode->RxFifo);
        if(cnt) {
            cli_printf(CRLF);
        }
        while(cnt) {
            res = fifo_pull(&UartNode->RxFifo, &out_char);
            if(res) {
                res = bc127_proc_byte(out_char);
                if(0x0D != out_char) {
                    Log.new_line = false;
                    LOG_NOTICE(BC127, "%c", out_char);
                    Log.new_line = true;
                } else {
                    cli_printf(CRLF);
                }
                print_cnt++;
            }
            cnt = fifo_get_count(&UartNode->RxFifo);
        }
        if(print_cnt) {
            res = true;
            cli_printf(CRLF);
        }
    }
    Log.time_stamp = true;
    Log.facility_name = true;
    return res;
}

bool bc127_check(void) {
    bool res = true;
    return res;
}

static bool bc127_wait_ack(uint32_t wait_pause_ms) {
    bool res = false, loop = true;
    LOG_DEBUG(BC127, "WaitAck");
    uint32_t start_ms = 0U, curr_ms = 0U, diff_ms = 0;
    start_ms = time_get_ms32();
    uint64_t loop_start_time_us = 0;
    while(loop) {
        if(Bc127Item.ack) {
            res = true;
            loop = false;
            LOG_DEBUG(BC127, "Ack!");
        }
        if(false == res) {
            loop_start_time_us = timer_get_us();
            super_loop(loop_start_time_us);

            curr_ms = time_get_ms32();
            diff_ms = curr_ms - start_ms;
            if(wait_pause_ms < diff_ms) {
                res = false;
                LOG_ERROR(BC127, "WaitAckTimeOut");
                loop = false;
            }
        }
    }
    return res;
}

static bool bc127_flush(void) {
    bool res = false;
    LOG_DEBUG(BC127, "Flush");
    uint8_t enter = CARRIAGE_RETURN;
    Bc127Item.ack = false;
    res = uart_send_api(UART_NUM_BC127, &enter, 1);
    if(res) {
        bc127_wait_ack(1000);
        res = true;
    }
    return res;
}

/*array must be in RAM*/
bool bc127_send(uint8_t* array, uint32_t len) {
    bool res = false;
    LOG_DEBUG(BC127, "Send: [%s] %u byte", array, len);
    if(array && len) {
        res = is_ram_addr((uint32_t)array);
        if(res) {
            array[len] = CARRIAGE_RETURN;
            Bc127Item.ack = false;
            res = uart_send_api(UART_NUM_BC127, array, (uint16_t)len + 1);
            if(false == res) {
                LOG_ERROR(BC127, "Send: Uart:%u %u byte", UART_NUM_BC127, len);
            }
        } else {
            LOG_ERROR(BC127, "Command [%s] Not In RAM", array);
        }
    } else {
        LOG_ERROR(BC127, "SendDatErr");
    }
    return res;
}

bool bc127_send_get(uint8_t* param, uint32_t len) {
    bool res = false;
    LOG_DEBUG(BC127, "Get");
    if(param && len) {
        static char getArr[40] = "";
        snprintf(getArr, sizeof(getArr), "GET %s", param);
        uint32_t tx_len = strlen(getArr);
        res = bc127_send((uint8_t*)getArr, tx_len);
        if(false == res) {
            LOG_ERROR(BC127, "SendErr: [%s] %u byte", param, tx_len);
        } else {
            bc127_wait_ack(1000);
        }
    }
    return res;
}

bool bc127_send_set(uint8_t* param, uint32_t param_len, uint8_t* value, uint32_t val_len) {
    bool res = false;
    LOG_DEBUG(BC127, "Set");
    if(param && param_len && value && val_len) {
        static char setArr[40] = "";
        snprintf(setArr, sizeof(setArr), "SET %s=%s", param, value);
        uint32_t tx_len = strlen(setArr);
        res = bc127_send((uint8_t*)setArr, tx_len);
        if(false == res) {
            LOG_ERROR(BC127, "SendErr: [%s] %u byte", param, tx_len);
        } else {
            bc127_wait_ack(1000);
        }
    }
    return res;
}

bool bc127_save(void) {
    bool res = false;
    LOG_DEBUG(BC127, "Save");
    char command[30] = {0};
    strcpy(command, BC127_WRITE);
    uint32_t command_len = strlen(BC127_WRITE);
    res = bc127_send((uint8_t*)command, command_len);
    return res;
}

bool bc127_reset(void) {
    bool res = false;
    LOG_DEBUG(BC127, "Reset");
    char command[30] = {0};
    strcpy(command, BC127_RESET);
    uint32_t command_len = strlen(BC127_RESET);
    res = bc127_send((uint8_t*)command, command_len);
    return res;
}

bool bc127_config_audio(void) {
    bool res = false;
    LOG_DEBUG(BC127, "ConfAudio");
    uint32_t param_len = strlen(BC127_AUDIO);
    char value[30] = {0};
    memset(value, 0, sizeof(value));

    strcpy((char*)value, "0 1");
    uint32_t val_len = strlen(value);
    res = bc127_send_set((uint8_t*)BC127_AUDIO, param_len, (uint8_t*)value, val_len);
    return res;
}

bool bc127_config_audio_digital(void) {
    bool res = false;
    LOG_DEBUG(BC127, "ConfAudioDigital");
    uint32_t param_len = strlen(BC127_AUDIO_DIGITAL);
    char value[30] = {0};
    memset(value, 0, sizeof(value));
    Bc127Param2_t Param2;
    Param2.reg_val = 0;

    Param2.start_rx_sampling = Bc127Config.i2s_param.start_rx_sampling;           // :1;/*Bit0*/
    Param2.start_tx_sampling = Bc127Config.i2s_param.start_tx_sampling;           // :1;/*Bit1*/
    Param2.crop_enable = Bc127Config.i2s_param.crop_enable;                       // :1;/*Bit2*/
    Param2.justify_resolution = Bc127Config.i2s_param.justify_resolution;         // :2;/*Bit3-4*/
    Param2.res1 = 0;                                                              // :2;/*Bit5-6*/
    Param2.audio_attenuation_enable = Bc127Config.i2s_param.audio_attenuation_en; // :1;/*Bit7*/
    Param2.channel_polarity = Bc127Config.i2s_param.channel_polarity;             // :1;/*Bit8*/
    Param2.left_justify_delay = Bc127Config.i2s_param.left_justify_delay;         // :1;/*Bit9*/
    Param2.justify_format = Bc127Config.i2s_param.justify_format;                 // :1;/*Bit10*/
    Param2.mode = Bc127Config.i2s_param.bus_mode;                                 // :1;/*Bit11*/
    Param2.audio_attenuation = Bc127Config.i2s_param.audio_attenuation;           // :4;/*Bit12-15*/
    Param2.bits_per_sample = Bc127Config.i2s_param.bits_per_sample;               // :8;/*Bit16-23*/
    Param2.res2 = 0;                                                              // :8;/*Bit24-31*/

    snprintf((char*)value, sizeof(value), "%u %u %u %06x ON", (unsigned int)Bc127Config.digital_format,
             (unsigned int)Bc127Config.digital_rate, (unsigned int)Bc127Config.i2s_param.scaling_factor,
             (unsigned int)Param2.reg_val);
    uint32_t val_len = strlen(value);
    res = bc127_send_set((uint8_t*)BC127_AUDIO_DIGITAL, param_len, (uint8_t*)value, val_len);
    return res;
}

#ifdef HAS_PARAM
static bool bc127_load_params(Bc127Config_t* Bc127ConfigPtr) {
    bool out_res = true;
    if(Bc127ConfigPtr) {
        LOAD_PARAM_V2(BC127, PAR_ID_BC127_I2S_BUS_ROLE, Bc127ConfigPtr->i2s_param.bus_mode);
        // LOAD_PARAM_V2(BC127, PAR_ID_BC127_I2S_SCALING_FACTOR,Bc127ConfigPtr->i2s_param.scaling_factor);
    }
    return out_res;
}
#endif

bool bc127_init(void) {
    bool res = true;
    uint32_t len = 0;
    memset(Bc127Item.LinkVolume, 0, sizeof(Bc127Item.LinkVolume));
    memcpy(&Bc127Config, &Bc127ConfigLut, sizeof(Bc127Config_t));
#ifdef HAS_PARAM
    res = bc127_load_params(&Bc127Config);
#endif
    set_log_level(BC127, LOG_LEVEL_DEBUG);
    LOG_INFO(BC127, "Init");

    bc127_flush();
    res = bc127_config_audio();
    res = bc127_config_audio_digital();

    len = strlen(BC127_AUDIO_DIGITAL);
    /*Auto-connects on Reset*/
    res = bc127_send_set(BC127_AUTOCONN, len, (uint8_t*)"1", 1) && res;

    res = bc127_save();
    res = bc127_reset();

    len = strlen(BC127_AUDIO_DIGITAL);
    res = bc127_send_get(BC127_AUDIO_DIGITAL, len) && res;
    return res;
}

bool bc127_get_volume_id(uint8_t link_id, uint8_t* volume) {
    bool res = true;
    char command[40] = "";
    snprintf(command, sizeof(command), "VOLUME %u", link_id);
    uint32_t len = strlen(command);
    res = bc127_send((uint8_t*)command, len);
    if(res) {
        res = bc127_wait_ack(1000);
    }
    if(res) {
        res = bc127_extract_volume(link_id, volume);
    }
    return res;
}

bool bc127_get_volume(uint8_t* volume) {
    bool res = true;
    char command[40] = "";
    snprintf(command, sizeof(command), "%s", BC127_VOLUME);
    uint32_t len = strlen(command);
    res = bc127_send((uint8_t*)command, len);
    if(res) {
        res = bc127_wait_ack(2000);
    }
    if(res) {
        res = bc127_extract_volume(Bc127Item.LinkVolume[0].link_id, volume);
    }
    return res;
}

bool bc127_set_volume(uint8_t volume) {
    bool res = true;
    char command[40] = "";
    snprintf(command, sizeof(command), "%s", BC127_VOLUME);
    uint32_t len = strlen(command);
    res = bc127_send((uint8_t*)command, len);
    if(res) {
        res = bc127_wait_ack(10000);
    } else {
        LOG_ERROR(BC127, "SendErr");
    }

    if(res) {
        uint32_t i = 0;
        uint32_t cnt = ARRAY_SIZE(Bc127Item.LinkVolume);
        for(i = 0; i < cnt; i++) {
            if(Bc127Item.LinkVolume[i].busy) {
                char command[40] = "";
                snprintf(command, sizeof(command), "VOLUME %u %X", Bc127Item.LinkVolume[i].link_id, volume);
                uint32_t len = strlen(command);
                res = bc127_send((uint8_t*)command, len);
                if(res) {
                    res = bc127_wait_ack(1000);
                }
            }
        }
    }
    return res;
}

bool bc127_set_volume_id(uint8_t link_id, uint8_t volume) {
    bool res = true;
    char command[40] = "";
    snprintf(command, sizeof(command), "VOLUME %u %X", link_id, volume);
    uint32_t len = strlen(command);
    res = bc127_send((uint8_t*)command, len);
    if(res) {
        bc127_wait_ack(1000);
        res = true;
    }
    return res;
}
