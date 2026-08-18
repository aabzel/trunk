#include "si4737_drv.h"

#include <gpio_stm32_diag.h>
#include <stdbool.h>
#include <string.h>

#include "bit_const.h"
#include "byte_utils.h"
#include "clocks.h"
#include "data_types.h"
#include "gpio_mcal.h"
#include "i2c_config.h"
#include "i2c_mcal.h"
#include "log.h"
#include "si4737_config.h"
#include "si4737_diag.h"
#include "si4737_rds_drv.h"
#include "timer_utils.h"

Si4737Property_t Si4737Property[] = {
    {
        .id = SI4737_FM_DEEMPHASIS,
        .val = 0x0000,
    },
    {
        .id = SI4737_FM_BLEND_STEREO_THRESHOLD,
        .val = 0x0000,
    },
    {
        .id = SI4737_FM_BLEND_MONO_THRESHOLD,
        .val = 0x0000,
    },
    {
        .id = SI4737_FM_RSQ_INT_SOURCE,
        .val = 0x0000,
    },
    {
        .id = SI4737_FM_SOFT_MUTE_RATE,
        .val = 0x0000,
    },
    {
        .id = SI4737_FM_SOFT_MUTE_MAX_ATTENUATION,
        .val = 0x0000,
    },
    {
        .id = SI4737_FM_SOFT_MUTE_SNR_THRESHOLD,
        .val = 0x0000,
    },
    {
        .id = SI4737_FM_SEEK_BAND_BOTTOM,
        .val = 0x0000,
    },
    {
        .id = SI4737_FM_SEEK_BAND_TOP,
        .val = 0x0000,
    },
    {
        .id = SI4737_FM_SEEK_FREQ_SPACING,
        .val = 0x0000,
    },
    {
        .id = SI4737_FM_SEEK_TUNE_SNR_THRESHOLD,
        .val = 0x0000,
    },
    {
        .id = SI4737_FM_SEEK_TUNE_RSSI_THRESHOLD,
        .val = 0x0000,
    },
    {
        .id = SI4737_FM_RDS_INT_SOURCE,
        .val = 0x0000,
    },
    {
        .id = SI4737_FM_RDS_INT_FIFO_COUNT,
        .val = 0x0000,
    },
    {
        .id = SI4737_FM_RDS_CONFIG,
        .val = 0x0000,
    },
    {
        .id = SI4737_AM_DEENOHASIS,
        .val = 0x0000,
    },
    {
        .id = SI4737_AM_CHANNEL_FILTER,
        .val = 0x0000,
    },
    {
        .id = SI4737_AM_AUTO_VOLUME_CTRL_MAX_GAIN,
        .val = 0x0000,
    },
    {
        .id = SI4737_AM_RSQ_INTERRUPTS,
        .val = 0x0000,
    },
    {
        .id = SI4737_AM_SOFT_MUTE_RATE,
        .val = 0x0000,
    },
    {
        .id = SI4737_AM_SOFT_MUTE_MAX_ATTENUATION,
        .val = 0x0000,
    },
    {
        .id = SI4737_AM_SOFT_MUTE_SNR_THRESHOLD,
        .val = 0x0000,
    },
    {
        .id = SI4737_AM_SEEK_BAND_BOTTOM,
        .val = 0x0000,
    },
    {
        .id = SI4737_AM_SEEK_BAND_TOP,
        .val = 0x0000,
    },
    {
        .id = SI4737_AM_SEEK_FREQ_SPACING,
        .val = 0x0000,
    },
    {
        .id = SI4737_AM_SEEK_SNR_THRESHOLD,
        .val = 0x0000,
    },
    {
        .id = SI4737_AM_SEEK_RSSI_THRESHOLD,
        .val = 0x0000,
    },
    {
        .id = SI4737_RX_VOLUME,
        .val = 0x0000,
    },
    {
        .id = SI4737_RX_HARD_MUTE,
        .val = 0x0000,
    },
    {
        .id = SI4737_WB_MAX_TUNE_ERROR,
        .val = 0x0000,
    },
    {
        .id = SI4737_WB_RSQ_INT_SOURCE,
        .val = 0x0000,
    },
    {
        .id = SI4737_WB_ASQ_INT_SOURCE,
        .val = 0x0000,
    },
};

static const Si4737CommandInfo_t Si4737CommandInfo[] = {{
                                                            .cmd = SI4737_CMD_GET_REV,
                                                            .arg_cnt = 0,
                                                            .resp_size = 15,
                                                        },
                                                        {
                                                            .cmd = SI4737_CMD_POWER_UP,
                                                            .arg_cnt = 2,
                                                            .resp_size = 1,
                                                        },
                                                        {
                                                            .cmd = SI4737_CMD_POWER_DOWN,
                                                            .arg_cnt = 0,
                                                            .resp_size = 1,
                                                        },
                                                        {
                                                            .cmd = SI4737_CMD_SET_PROPERTY,
                                                            .arg_cnt = 5,
                                                            .resp_size = 1,
                                                        },
                                                        {
                                                            .cmd = SI4737_CMD_GET_PROPERTY,
                                                            .arg_cnt = 3,
                                                            .resp_size = 4,
                                                        },
                                                        {
                                                            .cmd = SI4737_CMD_FM_TUNE_FREQ,
                                                            .arg_cnt = 4,
                                                            .resp_size = 1,
                                                        },
                                                        {
                                                            .cmd = SI4737_CMD_FM_SEEK_START,
                                                            .arg_cnt = 1,
                                                            .resp_size = 1,
                                                        },
                                                        {
                                                            .cmd = SI4737_CMD_FM_RSQ_STATUS,
                                                            .arg_cnt = 1,
                                                            .resp_size = 8,
                                                        },
                                                        {
                                                            .cmd = SI4737_CMD_FM_RDS_STATUS,
                                                            .arg_cnt = 1,
                                                            .resp_size = 13,
                                                        },
                                                        {
                                                            .cmd = SI4737_CMD_AM_TUNE_FREQ,
                                                            .arg_cnt = 5,
                                                            .resp_size = 1,
                                                        },
                                                        {
                                                            .cmd = SI4737_CMD_AM_SEEK_START,
                                                            .arg_cnt = 5,
                                                            .resp_size = 1,
                                                        },
                                                        {
                                                            .cmd = SI4737_CMD_AM_RSQ_STATUS,
                                                            .arg_cnt = 1,
                                                            .resp_size = 6,
                                                        },
                                                        {
                                                            .cmd = SI4737_CMD_WB_TUNE_FREQ,
                                                            .arg_cnt = 3,
                                                            .resp_size = 0,
                                                        },
                                                        {
                                                            .cmd = SI4737_CMD_WB_RSQ_STATUS,
                                                            .arg_cnt = 1,
                                                            .resp_size = 8,
                                                        },
                                                        {
                                                            .cmd = SI4737_GET_INT_STATUS,
                                                            .arg_cnt = 0,
                                                            .resp_size = 1,
                                                        }

};

bool si4737_get_resp(uint8_t* resp, uint8_t len) {
    bool res = true;
    res = i2c_read(I2C_NUM_SI4737, SI4737_I2C_ADDR, resp, len);
    return res;
}

bool si4737_set_command(uint8_t cmd, uint8_t* arg, uint8_t arg_cnt) {
    bool res = true;
    uint8_t TxArray[100] = {0};
    TxArray[0] = cmd;
    if(arg) {
        memcpy(&TxArray[1], arg, arg_cnt);
    }
    res = i2c_write(I2C_NUM_SI4737, SI4737_I2C_ADDR, TxArray, arg_cnt + 1);
    return res;
}

/*Command 0x12 SET_PROPERTY*/
bool si4737_set_property(uint16_t property, uint16_t val) {
    bool res = false;
    LOG_DEBUG(SI4737, "Set Prop:0x%04x Val:0x%04x", property, val);
    SetPropArg_t SetPropArg;
    SetPropArg.buff[0] = 0;
    SetPropArg.property = reverse_byte_order_uint16(property);
    SetPropArg.value = reverse_byte_order_uint16(val);
    res = si4737_set_command(SI4737_CMD_SET_PROPERTY, SetPropArg.buff, sizeof(SetPropArg_t));
    return res;
}

/*Command 0x12. SET_PROPERTY*/
bool si4737_get_property(uint16_t property, uint16_t* val) {
    bool res = false;
    LOG_DEBUG(SI4737, "Get Prop:0x%04x", property);
    uint8_t arg[3];
    arg[0] = 0;
    uint16_t property_be = reverse_byte_order_uint16(property);
    memcpy(&arg[1], &property_be, 2);
    res = si4737_set_command(SI4737_CMD_GET_PROPERTY, arg, sizeof(arg));
    if(res) {
        Type32Union_t un32;
        un32.u32 = 0;
        res = si4737_get_resp(&un32.u8[0], 4);
        if(res) {
            (*val) = reverse_byte_order_uint16(un32.u16[1]);
        }
    }

    return res;
}

bool si4737_get_fm_rsq_status(uint8_t* resp) {
    bool res = false;
    uint8_t arg1 = 0;
    res = si4737_set_command(SI4737_CMD_FM_RSQ_STATUS, &arg1, 1);
    if(res) {
        res = si4737_get_resp(resp, 8);
    }
    return res;
}

bool si4737_proc_status(uint8_t status, Si4737Handler_t* instance) {
    bool res = true;
    Si4737Status_t Status;
    Status.byte = status;
    if(Status.cts) {
        LOG_DEBUG(SI4737, "ClearToSend");
        instance->cts_cnt++;
    } else {
        LOG_DEBUG(SI4737, "WaitBeforeSendingNextCmd");
    }
    if(Status.rsq_int) {
        LOG_DEBUG(SI4737, "RxSigQaInt");
        instance->rsq_int_cnt++;
        instance->rsq_int = true;
    }
    if(Status.err) {
        LOG_ERROR(SI4737, "Err");
        instance->err_cnt++;
        res = false;
    }
    if(Status.rds_int) {
        LOG_WARNING(SI4737, "RdsInt");
        instance->rds_int_cnt++;
        instance->rds_int = true;
    }
    if(Status.asq_int) {
        LOG_DEBUG(SI4737, "SigQaDone");
        instance->asq_cnt++;
    }
    if(Status.stc_int) {
        LOG_WARNING(SI4737, "TuneDone");
        instance->stc_int_cnt++;
        instance->stc_int = true;
    }
    return res;
}

bool si4737_set_fm_rsq_int(void) {
    bool res = false;
    FmRsqIntSource_t FmRsqIntSource;
    FmRsqIntSource.mult_hien = 0;
    FmRsqIntSource.rssi_lien = 0;
    FmRsqIntSource.rssi_hien = 0;
    FmRsqIntSource.snr_lien = 0;
    FmRsqIntSource.snr_hien = 0;
    FmRsqIntSource.mult_lien = 0;
    FmRsqIntSource.mult_hien = 0;
    FmRsqIntSource.blend_ien = 0;
    res = si4737_set_property(SI4737_FM_RSQ_INT_SOURCE, FmRsqIntSource.word);
    return res;
}

bool si4737_set_gpo_ien(void) {
    bool res = false;
    GpoIen_t GpoIen;
    GpoIen.word = 0;
    GpoIen.asqien = 1;
    GpoIen.asqrep = 1;
    GpoIen.ctsien = 1;
    GpoIen.rdsien = 1;
    GpoIen.rdsrep = 1;
    GpoIen.stcien = 1;
    GpoIen.stcrep = 1;
    GpoIen.errien = 1;
    res = si4737_set_property(SI4737_GPO_IEN, GpoIen.word);
    return res;
}

bool si4737_set_fm_tune_freq(double freq_mhz) {
    bool res = false;
    FmTuneFreqArg_t FmTuneFreqArg;
    FmTuneFreqArg.antcap = 0;
    uint16_t freq_code = freq_mhz * 100.0;
    LOG_INFO(SI4737, "FreqCode %u", freq_code);
    FmTuneFreqArg.freq_10mhz = reverse_byte_order_uint16(freq_code);
    res = si4737_set_command(SI4737_CMD_FM_TUNE_FREQ, FmTuneFreqArg.buff, 4);
    if(res) {
        Si4737FmTuneFreqResp_t Si4737FmTuneFreqResp;
        Si4737FmTuneFreqResp.byte = 0;
        res = si4737_get_resp(&Si4737FmTuneFreqResp.byte, sizeof(Si4737FmTuneFreqResp_t));
        if(res) {
            if(ERROR_SPOT == Si4737FmTuneFreqResp.status.err) {
                LOG_ERROR(SI4737, "Err");
                res = false;
            }
        }
    }
    return res;
}

bool si4737_fm_seek_start(SeekDir_t SeekDir, SeekEnd_t SeekEnd, Si4737Handler_t* instance) {
    bool res = false;
    res = si4737_get_fm_tune_freq(&Si4737Handler, SEEK_ABBORT, STC_INT_CLEAR);
    if(res) {
        res = false;
        LOG_INFO(SI4737, "FmSeek %f %s %s", Si4737Handler.fm_freq_mhz, SeekDirToStr(SeekDir), SeekEndToStr(SeekEnd));
        FmSeekStartArg1_t arg;
        arg.byte = 0;
        arg.seekup = SeekDir;
        arg.wrap = SeekEnd;
        res = si4737_set_command(SI4737_CMD_FM_SEEK_START, &arg.byte, 1);
        if(res) {
            FmSeekStartResp_t Resp;
            res = si4737_get_resp(&Resp.byte, 1);
            if(res) {
                si4737_proc_status(Resp.byte, instance);
            }
        }
    }
    return res;
}

bool si4737_power_up(uint8_t opmode, Si4737Handler_t* instance) {
    bool res = false;
    PowerUpArg_t Arg;
    Arg.Arg1 = Si4737Config.PwgUpArg1;
    Arg.op_mode = opmode;
    res = si4737_set_command(SI4737_CMD_POWER_UP, Arg.buff, sizeof(PowerUpArg_t));
    if(res) {
        PowerUpResp_t Resp;
        res = si4737_get_resp(&Resp.byte, 1);
        if(res) {
            si4737_proc_status(Resp.status.byte, instance);
        }
    }
    return res;
}

bool si4737_reset(void) {
    bool res = true;
    LOG_INFO(SI4737, "Reset 0->1 %s", GpioPadToStr(PAD_SI4737_RST));
    res = gpio_set_state(PAD_SI4737_RST, 0);
    delay_us(100);
    res = gpio_set_state(PAD_SI4737_RST, 1);
    delay_us(100);
    return res;
}

bool si4737_init(void) {
    bool res = true;
    LOG_INFO(SI4737, "Init");
    res = si4737_reset();
    res = si4737_power_up((uint8_t)Si4737Config.OpMode, &Si4737Handler);
    if(res) {
        delay_ms(300);
        res = si4737_set_gpo_ien();
        // res = si4737_set_fm_rsq_int( );
        res = si4737_set_fm_tune_freq(Si4737Config.fm_freq_mhz);
#ifdef HAS_RDS
        res = si4737_init_rds();
#endif
    }

    return res;
}

uint32_t si4737_get_prop_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(Si4737Property);
    return cnt;
}

bool si4737_get_rev(Si4737FullRevResp_t* FullRevResp) {
    bool res = false;
    res = si4737_set_command(SI4737_CMD_GET_REV, NULL, 0);
    if(res) {
        res = false;
        if(FullRevResp) {
            memset(FullRevResp->buff, 0, sizeof(Si4737FullRevResp_t));
            res = si4737_get_resp(FullRevResp->buff, sizeof(Si4737FullRevResp_t));
        }
    }
    return res;
}

bool si4737_is_connected(void) {
    bool res = false;
    Si4737FullRevResp_t FullRevResp;
    res = si4737_get_rev(&FullRevResp);
    if(res) {
        if(SI4737_CHIP_REV == FullRevResp.RevResp.chiprev) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

bool si4737_get_fm_tune_freq(Si4737Handler_t* instance, SeekCancel_t Seek, SeekTuneIntClear_t SeekTuneInt) {
    bool res = false;
    FmTuneFreq_t Arg1;
    Arg1.cancel = Seek;
    Arg1.intack = SeekTuneInt;
    res = si4737_set_command(SI4737_FM_TUNE_STATUS, &Arg1.byte, 1);
    if(res) {
        FmTuneStatusResp_t Resp;
        memset(Resp.buff, 0, sizeof(FmTuneStatusResp_t));
        res = si4737_get_resp(Resp.buff, sizeof(FmTuneStatusResp_t));
        if(res) {
            si4737_proc_status(Resp.status.byte, instance);
            if(Resp.Resp1.bltf) {
                LOG_WARNING(SI4737, "HitBand");
            }
            if(instance) {
                uint16_t read_freq_code = reverse_byte_order_uint16(Resp.read_freq);
                instance->fm_freq_mhz = ((double)read_freq_code) / 100.0;
                LOG_INFO(SI4737, "CurFreq %f Mhz", instance->fm_freq_mhz);
                instance->rssi = Resp.rssi;
                instance->snr = Resp.snr;
            }
            if(Resp.Resp1.valid) {
                instance->valid_cnt++;
                LOG_DEBUG(SI4737, "ValidChannel %f Mhz", instance->fm_freq_mhz);
            }
        }
    }
    return res;
}

bool si4737_get_rsq_status(Si4737Handler_t* instance) {
    bool res = false;
    FmRsqStatusArg1_t Arg1;
    Arg1.intack = INT_STATUS_CLEAR;
    res = si4737_set_command(SI4737_CMD_FM_RSQ_STATUS, &Arg1.byte, 1);
    if(res) {
        FmRsqStatusResp_t Resp;
        res = si4737_get_resp(Resp.buff, sizeof(FmRsqStatusResp_t));
        if(res) {
            si4737_proc_status(Resp.status.byte, instance);
            if(Resp.Resp2.valid) {
                instance->valid_cnt++;
                LOG_DEBUG(SI4737, "ValidChannel SNR:%u RSSI:%u Mult:%u", Resp.snr, Resp.rssi, Resp.mult);
            }
            if(Resp.Resp3.pilot) {
                instance->pilot_cnt++;
                LOG_DEBUG(SI4737, "StereoPilot");
            }
            instance->rssi = Resp.rssi;
            instance->snr = Resp.snr;
            instance->mult = Resp.mult;
            instance->freq_offset = ((double)Resp.freqoff_khz) * 1000.0;
        }
    }
    return res;
}

bool si4737_get_rx_volume(uint16_t* rx_volume) {
    bool res = false;
    res = si4737_get_property(SI4737_RX_VOLUME, rx_volume);
    return res;
}

bool si4737_set_rx_volume(uint16_t rx_volume) {
    bool res = false;
    if(rx_volume <= 63) {
        res = true;
        res = si4737_set_property(SI4737_RX_VOLUME, rx_volume);
        if(res) {
            LOG_INFO(SI4737, "SetVolOk %u", rx_volume);
        } else {
            LOG_ERROR(SI4737, "SetVolOk %u", rx_volume);
        }
    } else {
        LOG_ERROR(SI4737, "VolErr %u", rx_volume);
        res = false;
    }

    return res;
}

bool si4737_get_int_status(Si4737Handler_t* instance) {
    bool res = false;
    res = si4737_set_command(SI4737_GET_INT_STATUS, NULL, 0);
    if(res) {
        Si4737Status_t status;
        status.byte = 0;
        res = si4737_get_resp(&status.byte, sizeof(Si4737Status_t));
        if(res) {
            si4737_proc_status(status.byte, instance);
        }
    } else {
        LOG_ERROR(SI4737, "SendGetIntStatErr");
    }
    return res;
}

bool si4737_proc(void) {
    bool res = false;
    res = si4737_is_connected();
    if(false == res) {
        LOG_ERROR(SI4737, "I2cLinkErr");
        i2c_init_ll(I2C_NUM_SI4737);
    } else {
        res = si4737_get_int_status(&Si4737Handler);
        if(Si4737Handler.rds_int) {
            Si4737Handler.rds_int = false;
#ifdef HAS_RDS
            uint8_t fifo_cnt = 1;
            res = si4737_get_fm_rds_status(&Si4737Handler, &fifo_cnt);
#endif
        }
        if(Si4737Handler.stc_int) {
            Si4737Handler.stc_int = false;
            res = si4737_get_fm_tune_freq(&Si4737Handler, SEEK_ABBORT, STC_INT_CLEAR);
        }
        res = si4737_get_rsq_status(&Si4737Handler);
    }
    return res;
}

bool si4737_set_mute(bool left, bool right) {
    bool res = false;
    RxHardMute_t RxHardMute;
    RxHardMute.l_mute = left;
    RxHardMute.r_mute = right;
    res = si4737_set_property(SI4737_RX_HARD_MUTE, RxHardMute.word);
    return res;
}

bool si4737_power_down(void) {
    bool res = false;
    res = si4737_set_command(SI4737_CMD_POWER_DOWN, NULL, 0);
    if(res) {
        Si4737Status_t Resp;
        Resp.byte = 0;
        res = si4737_get_resp(&Resp.byte, 1);
        if(res) {
            res = si4737_proc_status(Resp.byte, &Si4737Handler);
        }
    }
    return res;
}

static uint8_t DigitalOutputFormat2Num(uint8_t code) {
    uint8_t precision = 0;
    switch(code) {
    case DIG_OUT_AUDIO_PREC_16_BIT:
        precision = 16;
        break;
    case DIG_OUT_AUDIO_PREC_20_BIT:
        precision = 20;
        break;
    case DIG_OUT_AUDIO_PREC_24_BIT:
        precision = 24;
        break;
    case DIG_OUT_AUDIO_PREC_8_BIT:
        precision = 8;
        break;
    default:
        break;
    }
    return precision;
}

static uint8_t DigitalOutputFormat2Code(uint8_t precision) {
    uint8_t code = 0;
    switch(precision) {
    case 16:
        code = DIG_OUT_AUDIO_PREC_16_BIT;
        break;
    case 20:
        code = DIG_OUT_AUDIO_PREC_20_BIT;
        break;
    case 24:
        code = DIG_OUT_AUDIO_PREC_24_BIT;
        break;
    case 8:
        code = DIG_OUT_AUDIO_PREC_8_BIT;
        break;
    default:
        break;
    }
    return code;
}

bool si4737_get_digital_output_format(Si4737Handler_t* instance) {
    bool res = false;
    DigitalOutputFormat_t DigitalOutputFormat;
    DigitalOutputFormat.word = 0;
    res = si4737_get_property(SI4737_DIGITAL_OUTPUT_FORMAT, &DigitalOutputFormat.word);
    if(res) {
        instance->out_size_bit = DigitalOutputFormat2Num(DigitalOutputFormat.osize);
        instance->out_mono = DigitalOutputFormat.omono;
        instance->out_mode = DigitalOutputFormat.omode;
        instance->out_fall = DigitalOutputFormat.ofall;
    }
    return res;
}

bool si4737_set_digital_ouput_format(Si4737Handler_t* instance) {
    bool res = false;
    if(instance) {
        DigitalOutputFormat_t DigitalOutputFormat;
        DigitalOutputFormat.word = 0;
        DigitalOutputFormat.osize = DigitalOutputFormat2Code(instance->out_size_bit);
        DigitalOutputFormat.omono = instance->out_mono;
        DigitalOutputFormat.omode = instance->out_mode;
        DigitalOutputFormat.ofall = instance->out_fall;
        res = si4737_set_property(SI4737_DIGITAL_OUTPUT_FORMAT, DigitalOutputFormat.word);
    }
    return res;
}

bool fm_stations_set(char* station_name) {
    bool res = false;
    const FmStationInfo_t* FmStationInfo = fm_stations_get_node(station_name);
    if(NULL == FmStationInfo) {
        LOG_INFO(SYS, "Set %u", station_num);
        uint16_t cnt = fm_statinos_cnt();
        if(station_num < cnt) {
            FmStationInfo = &FmStationInfoLut[station_num];
            station_num++;
        } else {
            station_num = 0;
        }
    }

    if(FmStationInfo) {
        LOG_INFO(SYS, "Set %s", FmStationInfo->name);
        res = si4737_set_fm_tune_freq(FmStationInfo->fm_freq_mhz);
        if(res) {
            LOG_INFO(SYS, "Set %f MHz", FmStationInfo->fm_freq_mhz);
        } else {
            LOG_ERROR(SYS, "Set %f MHz Err", FmStationInfo->fm_freq_mhz);
        }
    }
    return res;
}
