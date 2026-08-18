#include "si4703_mcal.h"

#include <string.h>

#include "std_includes.h"
#include "bit_const.h"
#include "byte_utils.h"
#include "data_types.h"
#include "fm_tuner_rus.h"
#include "code_generator.h"
#include "gpio_mcal.h"
#include "log.h"
#include "compiler_const.h"

#ifdef HAS_I2C
#include "si4703_i2c.h"
#endif

#ifdef HAS_SPI
#include "si4703_spi.h"
#endif
//#include "rds_protocol.h"

COMPONENT_GET_NODE(Si4703, si4703)
COMPONENT_GET_CONFIG(Si4703, si4703)

bool si4703_is_reg_writable(const Si4703RegAddr_t reg_addr) {
    bool res = false;
    Si4703RegInfo_t *Info = Si4703GetRegInfo(reg_addr);
    if (Info) {
        if (ACCESS_READ_WRITE == Info->access) {
            res = true;
        }
    }
    return res;
}

/*ISO-26262 require verify configuration*/
bool Si4703IsValidConfig(const Si4703Config_t* const Config) {
    bool res = false;
    if (Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(SI4703, "SI4703_%u,Name,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool si4703_init_custom(void) {
    bool res = false;
    LOG_INFO(SI4703, "Version:%s", SI4703_VERSION);
    return res;
}

bool si4703_init_common(const Si4703Config_t* const Config, Si4703Handle_t* const Node) {
    bool res = false;
    if (Config) {
        if (Node) {
            Node->if_code = Config->if_code;
            Node->i2c_addr = Config->i2c_addr;
            Node->PadReset = Config->PadReset;
            Node->PadSen = Config->PadSen;
            Node->PadGpio1 = Config->PadGpio1;
            Node->PadGpio2 = Config->PadGpio2;
            Node->PadSdio = Config->PadSdio;
            Node->PadSclk = Config->PadSclk;
            Node->fm_freq_mhz = Config->fm_freq_mhz;
            Node->name = Config->name;
            Node->num = Config->num;
            res = true;
        }
    }
    return res;
}


bool si4703_reset(uint8_t num) {
    bool res = true;
    Si4703Handle_t *Node = Si4703GetNode(num);
    if (Node) {
        res = gpio_logic_level_set(Node->PadReset, GPIO_LVL_LOW);
        wait_ms(10);
        LOG_INFO(SI4703, "Reset,1->0,%s", GpioPadToStr(Node->PadReset));
    }
    return res;
}

static bool si4703_out_of_reset_ll(const Si4703Handle_t * const Node) {
    bool res = false;
    if (Node) {
        res = gpio_logic_level_set(Node->PadReset, GPIO_LVL_HI);
        wait_ms(10);
        LOG_INFO(SI4703, "Reset,0->1,%s,FetchIf", GpioPadToStr(Node->PadReset));
        res = true;
    }
    return res;
}


bool si4703_is_valid_device_id(const Si4703RegDeviceID_t DeviceID ){
    bool res = false;
    if(SI4703_DEVICEID_MANUFACTURER_ID==DeviceID.mfgid){
        if(SI4703_DEVICEID_PART_NUMBER_SI4703==DeviceID.pn){
            res = true;
        }
    }
    return res;
}

bool si4703_is_connected(uint8_t num) {
    bool res = false;
    Si4703RegDeviceID_t DeviceID = { 0 };
    res = si4703_read_reg(num, SI4703_REG_DEVICE_ID, &DeviceID.word);
    if (res) {
        LOG_DEBUG(SI4703, "DeviceID:%s", Si4703DeviceIDToStr(&DeviceID));
        res = si4703_is_valid_device_id(DeviceID);
        if (res) {
        } else {
            LOG_ERROR(SI4703, "DeviceID:%s", Si4703DeviceIDToStr(&DeviceID));
            res = false;
        }
    } else {
        LOG_ERROR(SI4703, "ReadErr");
    }
    return res;
}

bool si4703_is_power_up(uint8_t num) {
    bool res = false;
    Si4703Handle_t *Node = Si4703GetNode(num);
    if (Node) {
        Si4703RegChipID_t ChipID = { 0 };
        ChipID.word = 0;
        res = si4703_read_reg(num, SI4703_REG_CHIPID, &ChipID.word);
        if (res) {
            switch (ChipID.dev) {
                case SI4703_DEV_CODE_AFTER_PUP:
                    LOG_DEBUG(SI4703, "PowerUp");
                    Node->power = POWER_UP;
                    res = true;
                    break;
                case SI4703_DEV_CODE_BEFORE_PUP:
                    LOG_WARNING(SI4703, "PowerDown");
                    Node->power = POWER_DOWN;
                    res = false;
                    break;
                default:
                    LOG_ERROR(SI4703, "Undef Dev 0x%x", ChipID.dev);
                    break;
            }

            if (ChipID.firmware) {
                LOG_DEBUG(SI4703, "PowerUp,FW:0x%x", ChipID.firmware);
                Node->power = POWER_UP;
            } else {
                LOG_WARNING(SI4703, "PowerDown");
                Node->power = POWER_DOWN;
            }
        } else {
            LOG_DEBUG(SI4703, "ChipId ReadErr");
        }
    }
    return res;
}

#if 0
/* Hide silly, wrapped and continuous register reading and make interface
 * appear sane and normal. This also makes the driver compatible with
 * using the 3-wire interface. */
uint16_t si4700_read_reg_v2(uint8_t num, uint8_t reg_addr) {
    uint16_t val = 0xFFFF;
    Si4703Handle_t *Node = Si4703GetNode(num);
    bool res = si4700_read(num, ((reg_addr - SI4703_REG_STATUS_RSSI) & 0xF) + 1);
    if (res) {
        val = Node->cache[reg_addr];
    } else {
        LOG_ERROR(SI4703, "ReadRegErr");
    }
    return val;
}
#endif

bool si4703_read_reg(const uint8_t num, const Si4703RegAddr_t reg_addr, uint16_t* const reg_val) {
    bool res = false;
    if (reg_val) {
        Si4703Handle_t *Node = Si4703GetNode(num);
        if (Node) {
            switch (Node->if_code.interface_name) {

                case INTERFACE_NAME_SPI: {
#ifdef HAS_SPI
                    res = si4703_spi_read_reg(num, reg_addr, reg_val);
#endif
                }
                    break;

                case INTERFACE_NAME_I2C: {
#ifdef HAS_I2C
                    res = si4703_i2c_read_reg(num, reg_addr, reg_val);
#endif
                }
                    break;

                default: {
                    res = false;
                }
                    break;
            }
        }
    }
#if 0
#ifdef HAS_I2C
        res = i2c_mcal_write(Node->if_code.num, Node->i2c_addr, &reg_addr, 1);
        if(res) {
            res = i2c_mcal_read(Node->if_code.num, Node->i2c_addr, (uint8_t* ) reg_val, 2);
            if(false == res) {
                LOG_ERROR(I2C, "%u ReadRegErr Reg:0x%04X", Node->if_code.num, *reg_val);
            } else {
                LOG_DEBUG(I2C, "%u ReadRegOk Reg:0x%02X RegVal:0x%04X", Node->if_code.num, reg_addr, *reg_val);
            }
        } else {
            LOG_ERROR(I2C, "%u SetRegAddrErr ChipAddr:0x%02x Reg:0x%04X=%s", Node->if_code.num,
                      Node->i2c_addr,
                      reg_addr,si4703_get_reg_name(reg_addr));
        }
#endif /*HAS_I2C*/
#endif
    return res;
}

#if 0
/* writes <len> registers from cache to radio at offset 0x02 */
static bool si4700_write(uint8_t num, int len) {
    bool res = false;
    Si4703Handle_t *Node = Si4703GetNode(num);
    if (Node) {

    }
#ifdef HAS_I2C
    if (Node) {
        int i;
        unsigned char buf[32];
        unsigned char *ptr = buf;
        uint16_t data;

        for (i = 0; i < len; i++) {
            data = Node->cache[(i + SI4703_REG_POWERCFG) & 0xF];
            *ptr++ = (data >> 8) & 0xFF;
            *ptr++ = data & 0xFF;
        }
        res = i2c_mcal_write(Node->if_code.num, SI4703_I2C_ADDR, buf, len * 2);
    }
#endif
    return res;
}
#endif

#if 0
static bool si4700_write_reg_v2(uint8_t num, uint8_t reg_addr, uint16_t value) {
    bool res = true;
    Si4703Handle_t* Node=Si4703GetNode(num);
    if(Node) {
        Node->cache[reg_addr] = value;
        si4700_write(num,((reg_addr - SI4703_REG_POWERCFG) & 0xF) + 1);
    }
    return res;
}
#endif


bool si4703_write_reg(uint8_t num, Si4703RegAddr_t regis_addr, uint16_t reg_val) {
    bool res = false;
    LOG_DEBUG(SI4703, "Write Reg:0x%02x,Val:0x%04x", regis_addr, reg_val);
    Si4703Handle_t* Node = Si4703GetNode(num);
    if (Node) {
        res = si4703_is_reg_writable(regis_addr);
        if (res) {
            switch (Node->if_code.interface_name) {
                case INTERFACE_NAME_I2C: {
#ifdef HAS_I2C
                res = si4703_i2c_write_reg(num, regis_addr, reg_val);
#endif
                } break;
                case INTERFACE_NAME_SPI: {
#ifdef HAS_SPI
                res = si4703_spi_write_reg(num,  regis_addr, reg_val);
#endif
                } break;
                default: break;
            }
        }
    }

    return res;
}

bool si4703_write_lazy_reg(uint8_t num, uint8_t reg_addr, uint16_t reg_val) {
    bool res = false;
    Si4703Handle_t *Node = Si4703GetNode(num);
    uint16_t cur_reg_val = 0xFFFF;
    res = si4703_read_reg(num, reg_addr, &cur_reg_val);
    if (res) {
        if (cur_reg_val != reg_val) {
            res = si4703_write_reg(num, reg_addr, reg_val);
            Node->reg_val_disaccord++;
        }
    } else {
        LOG_ERROR(SI4703, "ReadErr");
    }

    return res;
}

static bool si4703_tune_stop(uint8_t num) {
    bool res = false;
    Si4703Handle_t *Node = Si4703GetNode(num);
    Si4703RegChannel_t RegChannel;
    RegChannel.word = 0;
    res = si4703_read_reg(num, SI4703_REG_CHANNEL, &RegChannel.word);
    RegChannel.tune = 0;
    res = si4703_write_reg(num, SI4703_REG_CHANNEL, RegChannel.word);
    Node->tune_start = false;
    return res;
}

bool si4703_seek_clr(uint8_t num) {
    bool res = false;
    Si4703Handle_t *Node = Si4703GetNode(num);
    Si4703RegPwrCfg_t RegPwrCfg;
    RegPwrCfg.word = 0;
    res = si4703_read_reg(num, SI4703_REG_POWERCFG, &RegPwrCfg.word);
    RegPwrCfg.seek = 0;
    res = si4703_write_reg(num, SI4703_REG_POWERCFG, RegPwrCfg.word);
    Node->clear_seek = false;
    return res;
}

bool si4703_xtall_ctrl(uint8_t num, bool on, uint16_t preserv) {
    bool res = true;
    LOG_INFO(SI4703, "SetStall");
    //Si4703Handle_t* Node=Si4703GetNode(num);
    Si4703RegTest1_t RegTest1;
    RegTest1.word = 0;
    res = si4703_read_reg(num, SI4703_REG_TEST1, &RegTest1.word);
    if (res) {
        RegTest1.xoscen = 1; /*  Crystal Oscillator Enable.  */
        RegTest1.ahizen = 0; /*  Audio High-Z DisEnable  */
        RegTest1.res = preserv;
        res = si4703_write_reg(num, SI4703_REG_TEST1, RegTest1.word);
        LOG_INFO(SI4703, "SetStallDone");
        wait_ms(1000);
    }
    return res;
}

bool si4703_power_up(uint8_t num) {
    bool res = true;
    Si4703Handle_t *Node = Si4703GetNode(num);
    if (Node) {
        LOG_INFO(SI4703, "PowerUp...");
        res = si4703_out_of_reset_ll(Node);
        res = si4703_xtall_ctrl(num, true, 0x0100);

        Si4703RegPwrCfg_t PwrCfg;
        PwrCfg.word = 0;

        PwrCfg.dmute = 1; //Mute Disable
        PwrCfg.dsmute = 1; //Softmute Disable.
        PwrCfg.seek = 1; /**/
        PwrCfg.skmode = 0; //Seek Mode.
        PwrCfg.seekup = 1; // Seek Direction
        PwrCfg.rdsm = RDS_MODE_VERBOSE; // RDS Mode.
        PwrCfg.mono = 0; //Mono Select.
#if 0
        When proper voltages are applied to the Si4702/03-C19, the ENABLE and DISABLE bits in
        Register 02h can be used to select between powerup and powerdown modes.
        When voltage is first applied to the device, ENABLE = 0 and DISABLE = 0.
        Setting ENABLE = 1 and DISABLE = 0 puts the device in powerup mode.
#endif

        PwrCfg.enable = 1; /*Powerup Enable.*/
        PwrCfg.disable = 0; /* Powerup Disable*/
        // res = si4703_write_reg(num,SI4703_REG_POWERCFG, 0x4001);
        res = si4703_write_reg(num, SI4703_REG_POWERCFG, PwrCfg.word);
        LOG_INFO(SI4703, "PowerUpDone");
        wait_ms(1000);
    }
    return res;
}

int32_t Volume2dfbs(uint8_t volume_code) {
    int32_t volume = 0;
    switch (volume_code) {
        case 1:
            volume = -28;
            break;
        case 14:
            volume = -2;
            break;
        case 15:
            volume = 0;
            break;
    }
    return volume;
}

static double Band2BandStart(Si4703BandSel_t band) {
    double band_start_mhz = 0.0;
    switch ((uint8_t) band) {
        case BAND_SEL_87_5_108_MHz:
            band_start_mhz = 87.5;
            break;
        case BAND_SEL_76_108_MHz:
            band_start_mhz = 76.0;
            break;
        case BAND_SEL_76_90_MHz:
            band_start_mhz = 76.0;
            break;
    }
    return band_start_mhz;
}

static double ChannelSpacing2Val(Si4703Channel_Spacing_t space) {
    double channel_spacing_mhz = 0.0;
    switch ((uint8_t) space) {
        case CHAN_SPACE_200_KHZ:
            channel_spacing_mhz = 0.2;
            break;
        case CHAN_SPACE_100_KHZ:
            channel_spacing_mhz = 0.1;
            break;
        case CHAN_SPACE_50_KHZ:
            channel_spacing_mhz = 0.05;
            break;
    }
    return channel_spacing_mhz;
}

bool si4703_proc_reg_chip_id(uint8_t num, uint16_t reg_val){
    bool res = false;
    Si4703RegChipID_t ChipID;
    ChipID.word = reg_val;
    LOG_DEBUG(SI4703, "ChipID:%s",Si4703ChipIdToStr(&ChipID));
    return res;
}

bool si4703_proc_read_chan_reg(uint8_t num, uint16_t reg_val) {
    bool res = false;
    Si4703Handle_t *Node = Si4703GetNode(num);

    LOG_DEBUG(SI4703, "ReadChannel 0x0B");
    Si4703RegReadChan_t ReadChan;
    ReadChan.word = reg_val;
//    RdsBlockErrorsToStr(ReadChan.blerb, 'B');
    //   RdsBlockErrorsToStr(ReadChan.blerc, 'C');
    //  RdsBlockErrorsToStr(ReadChan.blerd, 'D');
    LOG_DEBUG(SI4703, "Channel %u", ReadChan.readchan);
    Node->fm_freq_read_mhz = Node->band_start_mhz + Node->channel_spacing_mhz * ((double) ReadChan.readchan);
    LOG_DEBUG(SI4703, "FmFreqRead: %f MHz", Node->fm_freq_read_mhz);
    if (Node->fetch_freq) {
        LOG_INFO(SI4703, "FmFreq %5.2f MHz", Node->fm_freq_read_mhz);
        Node->fetch_freq = false;
    }
    return res;
}

bool si4703_read_rds(uint8_t num, uint16_t* words) {
    bool res = false;
    res = si4703_read_reg(num, SI4703_REG_RDSA, &words[0]);
    res = si4703_read_reg(num, SI4703_REG_RDSB, &words[1]);
    res = si4703_read_reg(num, SI4703_REG_RDSC, &words[2]);
    res = si4703_read_reg(num, SI4703_REG_RDSD, &words[3]);
    return res;
}


bool si4703_proc_status_rssi_reg(uint8_t num, uint16_t reg_val) {
    bool res = false;

    Si4703Handle_t *Node = Si4703GetNode(num);
    LOG_DEBUG(SI4703, "Reg 0x0A StatusRssi");
    Si4703RegStatusRssi_t StatusRssi;
    StatusRssi.word = reg_val;
    LOG_DEBUG(SI4703, "StatusRssi:%s",Si4703StatusRssiToStr(&StatusRssi));

    if (StatusRssi.rdss) {
        LOG_DEBUG(SI4703, "RdsDecoderSynchronized");
        Node->rds_sync_cnt++;
    }

    if (StatusRssi.rdsr) {
        Node->rds_recv_cnt++;
        LOG_DEBUG(SI4703,"RDSReady");
        uint16_t word[4] = { 0 };
        si4703_read_rds(num, word);
#ifdef HAS_RDS
        res = rds_proc_message(word);
#endif
    }

    if (StatusRssi.st) {
        Node->stereo = true;
        LOG_DEBUG(SI4703, "Stereo");
    } else {
        Node->stereo = false;
    }

    if(StatusRssi.sf_bl){
        LOG_INFO(SI4703,"Seek failure/Band limit reached.");
    }

    if (StatusRssi.stc) {
        LOG_WARNING(SI4703, "SeekTuneDone!");
        Node->clear_seek = true;
        si4703_seek_clr(num);
        if (Node->tune_start) {
            LOG_WARNING(SI4703, "TuneDone!");
            si4703_tune_stop(num);
        }
        Node->fetch_freq = true;
    }

    RdsBlockErrorsToStr(StatusRssi.blera, 'A');
    if(StatusRssi.blera){
        LOG_DEBUG(SI4703,"RDS Block A Errors.");
    }

    LOG_DEBUG(SI4703, "RSSI %u", StatusRssi.rssi);
    return res;
}

bool si4703_proc_sys_config2_reg(uint8_t num, uint16_t reg_val) {
    bool res = false;
    Si4703Handle_t *Node = Si4703GetNode(num);
    LOG_DEBUG(SI4703, "ProcCfg2");
    Si4703RegSysCfg2_t SysCfg2;
    SysCfg2.word = reg_val;
    Node->band_sel = SysCfg2.band;
    Node->band_start_mhz = Band2BandStart(SysCfg2.band);
    Node->channel_spacing_mhz = ChannelSpacing2Val(SysCfg2.space);
    Node->volume = Volume2dfbs(SysCfg2.volume);
    Node->seekth = SysCfg2.seekth;
    return res;
}


static bool si4703_proc_reg(uint8_t num, uint8_t reg, uint16_t reg_val) {
    bool res = false;
    switch (reg) {
        case SI4703_REG_STATUS_RSSI:
            res = si4703_proc_status_rssi_reg(num, reg_val);
            break;
        case SI4703_REG_SYSCONFIG2:
            res = si4703_proc_sys_config2_reg(num, reg_val);
            break;
        case SI4703_REG_READ_CHAN:
            res = si4703_proc_read_chan_reg(num, reg_val);
            break;
        case SI4703_REG_CHIPID:
            res = si4703_proc_reg_chip_id(num, reg_val);
                    break;

    }
    return res;
}

bool si4703_set_channel(uint8_t num, uint16_t channel, Si4703Tune_t tune) {
    bool res = true;
    Si4703Handle_t *Node = Si4703GetNode(num);
    LOG_INFO(SI4703, "SetChan %u", channel);
    Si4703RegChannel_t RegChannel;
    RegChannel.word = 0;
    RegChannel.tune = tune;
    RegChannel.channel = channel;
    Node->tune_start = true;
    res = si4703_write_reg(num, SI4703_REG_CHANNEL, RegChannel.word);
    return res;
}

uint16_t si4700_freq2Chan(uint8_t num, double des_freq) {
    uint16_t channel;
    Si4703Handle_t *Node = Si4703GetNode(num);
    if(Node) {
        LOG_INFO(SI4703, "BandStart: %f MHz", Node->band_start_mhz);
        LOG_INFO(SI4703, "ChannelSpacing: %f MHz", Node->channel_spacing_mhz);
        double dynamic_range = des_freq - Node->band_start_mhz;
        LOG_INFO(SI4703, "DynamicRange: %f MHz", dynamic_range);
        channel = (uint16_t) (dynamic_range / Node->channel_spacing_mhz);
        LOG_INFO(SI4703, "Channel:%u ", channel);
    }
    return channel;
}

bool si4700_set_frequency(uint8_t num, double des_freq) {
    bool res = true;
    LOG_INFO(SI4703, "SetFreq:%f MHz", des_freq);
    uint16_t  channel = si4700_freq2Chan(num, des_freq);
    res = si4703_set_channel(num, channel, TUNE_ENABLE);
    return res;
}

bool si4703_fm_seek_start(uint8_t num, Si4703SeekDir_t seek_dir, Si4703SeekEnd_t seek_end) {
    bool res = false;
    LOG_INFO(SI4703, "SeekStart:Dir:%s,Mode:%s", Si4703SeekDirToStr(seek_dir), Si4703SeekModeToStr(seek_end));
    Si4703RegPwrCfg_t RegPwrCfg;
    RegPwrCfg.word = 0;
    res = si4703_read_reg(num, SI4703_REG_POWERCFG, &RegPwrCfg.word);
    if(res) {
        RegPwrCfg.seek = 1;
        RegPwrCfg.seekup = seek_dir;
        RegPwrCfg.skmode = seek_end;
        res = si4703_write_reg(num, SI4703_REG_POWERCFG, RegPwrCfg.word);
    }
    return res;
}


bool si4703_select_if(const uint8_t num, const InterfaceName_t if_name) {
    bool res = false;
    Si4703Handle_t* Node = Si4703GetNode(num);
    if (Node) {
        switch (if_name) {
            case INTERFACE_NAME_I2C: {
#ifdef HAS_I2C
                res = si4703_i2c_select_if(Node->num);
#endif
            } break;
            case INTERFACE_NAME_SPI: {
#ifdef HAS_SPI
                res = si4703_spi_select_if(Node->num);
#endif
            } break;
            default: {
#ifdef HAS_SPI
                res = si4703_spi_select_if(Node->num);
#endif
            }
        }
        res = si4703_out_of_reset_ll(Node);
    }
    return res;
}



bool si4703_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SI4703, "SI4703_%u", num);
    const Si4703Config_t *Config = Si4703GetConfig(num);
    if (Config) {
        res = Si4703IsValidConfig(Config);
        if (res) {
#ifdef HAS_SI4703_DIAG
            LOG_WARNING(SI4703, "%s", Si4703ConfigToStr(Config));
#endif
            Si4703Handle_t *Node = Si4703GetNode(num);
            if (Node) {
                res = si4703_init_common(Config, Node);
                res = si4703_select_if(num, Config->if_code.interface_name);
                if (res) {
                    res=si4703_xtall_ctrl(num, true, 0x0100) ;
                    res = si4703_power_up(num);
                    res=si4703_xtall_ctrl(num, true, 0x3C04) ;
                    res = si4703_write_reg(num, SI4703_REG_SYSCONFIG1, Config->SysCfg1.word);
                    res = si4703_write_reg(num, SI4703_REG_SYSCONFIG2, Config->SysCfg2.word);
                    res = si4703_write_reg(num, SI4703_REG_SYSCONFIG3, Config->SysCfg3.word);
                    res = si4703_proc_one(num);
                    res = si4703_fm_seek_start(num, SEEK_DIR_UP, SEEK_END_WRAP);
                    // res = si4703_reset();
                    res = si4700_set_frequency(num, RADIO_CHILD);
                    Node->valid = true;
                    Node->init = true;
                    res = true;
                }
            } else {
                LOG_ERROR(SI4703, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(SI4703, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(SI4703, "ConfigErr %u", num);
    }
    return res;
}

bool si4703_volume_set(uint8_t num ,uint8_t volume){
    bool res;
    LOG_INFO(SI4703, "SI4703_%u,volume:%u", num,volume);
    Si4703RegSysCfg2_t SysCfg2;
    res = si4703_read_reg(num,  SI4703_REG_SYSCONFIG2  , &SysCfg2.word);
    if(res) {
        SysCfg2.volume = volume;
        res = si4703_write_reg(num, SI4703_REG_SYSCONFIG2, SysCfg2.word);
    }
    return res;
}

bool si4703_volume_get(uint8_t num ,uint8_t * const volume) {
    bool res;
    Si4703RegSysCfg2_t SysCfg2;
    res = si4703_read_reg(num,  SI4703_REG_SYSCONFIG2  , &SysCfg2.word);
    if(res) {
        *volume = SysCfg2.volume ;
        LOG_INFO(SI4703, "SI4703_%u,Set,Volume:%u", num,SysCfg2.volume);
    }
    return res;
}

bool si4703_volume_down(uint8_t num){
    bool res;
    uint8_t  volume = 0 ;
    res=si4703_volume_get(num ,&volume)   ;
    if(res){
        volume=(uint8_t)int32_range_limiter(volume-1,0,15);
        res=si4703_volume_set(num , volume);
    }
    return res;
}

bool si4703_volume_up(uint8_t num){
    bool res;
    uint8_t volume = 0 ;
    res = si4703_volume_get(num ,&volume)   ;
    if(res){
        volume=(uint8_t)int32_range_limiter(volume+1,0,15);
        res=si4703_volume_set(num , volume);
    }
    return res;
}



bool si4703_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(SI4703, "SI4703_%u,Proc", num);
    Si4703Handle_t *Node = Si4703GetNode(num);
    if (Node) {
        res = si4703_is_connected(num);
        if (res) {
            LOG_DEBUG(SI4703, "Connected");
            uint32_t reg_addr = 0;
            for (reg_addr = 0; reg_addr < SI4703_REG_CNT; reg_addr++) {
                res = si4703_read_reg(num, reg_addr, &Node->RegRead[reg_addr]);
                if (res) {
                    res = si4703_proc_reg(num, reg_addr, Node->RegRead[reg_addr]);
                }
            }
            res = si4703_is_power_up(num);
            if(!res){
                res = si4703_power_up(num);
            }
        } else {
            LOG_DEBUG(SI4703, "Disconect");
        }
        LOG_DEBUG(SI4703, "%s", Si4703NodeToStr(Node));
        Node->spin++;
    }
    return res;
}

COMPONENT_INIT_PATTERT(SI4703, SI4703, si4703)
COMPONENT_PROC_PATTERT(SI4703, SI4703, si4703)
