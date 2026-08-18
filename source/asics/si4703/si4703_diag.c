#include "si4703_diag.h"

#include "common_diag.h"
#include "num_to_str.h"
#include "si4703_mcal.h"
#include "diag_inc.h"
#include "gpio_diag.h"
#include "interfaces_diag.h"
#include "log.h"

const char* Si4703SeekDirToStr(Si4703SeekDir_t seek_dir) {
    char *name = "?";
    switch (seek_dir) {
        case SEEK_DIR_DOWN: name = "Down";  break;
        case SEEK_DIR_UP: name = "Up";    break;
        default:  name = "?";     break;
    }
    return name;
}

const char* Si4703SeekModeToStr(Si4703SeekEnd_t seek_end) {
    char *name = "?";
    switch (seek_end) {
        case SEEK_END_WRAP:  name = "Wrap";            break;
        case SEEK_END_HALT:  name = "Halt";            break;
        default:  name = "?";            break;
    }
    return name;
}

const Si4703RegInfo_t Si4703RegInfo[SI4703_REG_CNT] = {
        { .access = ACCESS_READ_ONLY,  .reg_index=6, .valid = true, .reg_addr = SI4703_REG_DEVICE_ID,    .name = "DeviceID", },
        { .access = ACCESS_READ_ONLY,  .reg_index=7, .valid = true, .reg_addr = SI4703_REG_CHIPID,      .name = "ChipID", },
        { .access = ACCESS_READ_WRITE, .reg_index=8, .valid = true, .reg_addr = SI4703_REG_POWERCFG,    .name = "PowerCFG", },
        { .access = ACCESS_READ_WRITE, .reg_index=9, .valid = true, .reg_addr = SI4703_REG_CHANNEL,     .name = "Channel", },
        { .access = ACCESS_READ_WRITE, .reg_index=10, .valid = true, .reg_addr = SI4703_REG_SYSCONFIG1,  .name = "SysConfig1", },
        { .access = ACCESS_READ_WRITE, .reg_index=11, .valid = true, .reg_addr = SI4703_REG_SYSCONFIG2,  .name = "SYSCONFIG2", },
        { .access = ACCESS_READ_WRITE, .reg_index=12, .valid = true, .reg_addr = SI4703_REG_SYSCONFIG3,  .name = "SYSCONFIG3", },
        { .access = ACCESS_READ_WRITE, .reg_index=13, .valid = true, .reg_addr = SI4703_REG_TEST1,       .name = "TEST1", },
        { .access = ACCESS_READ_WRITE, .reg_index=14, .valid = true, .reg_addr = SI4703_REG_TEST2,       .name = "TEST2", },
        { .access = ACCESS_READ_WRITE, .reg_index=15, .valid = true, .reg_addr = SI4703_REG_BOOTCONFIG,  .name = "BOOTCONFIG", },
        { .access = ACCESS_READ_ONLY,  .reg_index=0, .valid = true, .reg_addr = SI4703_REG_STATUS_RSSI, .name = "StatusRssi", },
        { .access = ACCESS_READ_ONLY,  .reg_index=1, .valid = true, .reg_addr = SI4703_REG_READ_CHAN,   .name = "ReadChan", },
        { .access = ACCESS_READ_ONLY,  .reg_index=2, .valid = true, .reg_addr = SI4703_REG_RDSA,        .name = "RDSA", },
        { .access = ACCESS_READ_ONLY,  .reg_index=3, .valid = true, .reg_addr = SI4703_REG_RDSB,        .name = "RDSB", },
        { .access = ACCESS_READ_ONLY,  .reg_index=4, .valid = true, .reg_addr = SI4703_REG_RDSC,        .name = "RDSC", },
        { .access = ACCESS_READ_ONLY,  .reg_index=5, .valid = true, .reg_addr = SI4703_REG_RDSD,        .name = "RDSD", },
};


uint32_t si4703_reg_cnt(void) {
    uint32_t reg_cnt = ARRAY_SIZE(Si4703RegInfo);
    return reg_cnt;
}


const Si4703RegInfo_t* Si4703GetRegInfo(const Si4703RegAddr_t addr) {
    uint32_t i = 0;
    Si4703RegInfo_t* Info = NULL;
    uint32_t reg_cnt = si4703_reg_cnt();
    for (i = 0; i < reg_cnt; i++) {
        if (addr == Si4703RegInfo[i].reg_addr ) {
            if ( Si4703RegInfo[i].valid ) {
                Info = &Si4703RegInfo[i];
            }
            break;
        }
    }
    return Info;
}


const char* Si4703ConfigToStr(const Si4703Config_t* const Config) {
    if (Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sIF:%s,", text, IfCodeToStr(Config->if_code));
        snprintf(text, sizeof(text), "%sFreq:%f Hz,", text, Config->fm_freq_mhz);
        snprintf(text, sizeof(text), "%sI2CAddr:0x%x,", text, Config->i2c_addr);
        snprintf(text, sizeof(text), "%sRst:%s,", text, GpioPadToStr(Config->PadReset));
        snprintf(text, sizeof(text), "%sRst:%s,", text, GpioPadToStr(Config->PadReset));
        snprintf(text, sizeof(text), "%sSEN:%s,", text, GpioPadToStr(Config->PadSen));
        snprintf(text, sizeof(text), "%sGpio1:%s,", text, GpioPadToStr(Config->PadGpio1));
        snprintf(text, sizeof(text), "%sGpio2:%s,", text, GpioPadToStr(Config->PadGpio2));
        snprintf(text, sizeof(text), "%sSdio:%s,", text, GpioPadToStr(Config->PadSdio));
        snprintf(text, sizeof(text), "%sSclk:%s,", text, GpioPadToStr(Config->PadSclk));
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sRDS:%u,", text, Config->rds_en);
    }
    return text;
}




const char* Si4703NodeToStr(const Si4703Handle_t* const Node) {
    if (Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sPower:%u,", text, Node->power);
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sreg_val_disaccord:%u,", text, Node->reg_val_disaccord);
        snprintf(text, sizeof(text), "%sInCon:%u,", text, Node->connected);
        snprintf(text, sizeof(text), "%sseekth:%u,", text, Node->seekth);
        snprintf(text, sizeof(text), "%sfreq_offset:%f,", text, Node->freq_offset);
        snprintf(text, sizeof(text), "%sBandSel:%u,", text, Node->band_sel);
        snprintf(text, sizeof(text), "%sFMfreqSetReal:%f,", text, Node->fm_freq_set_real);
        snprintf(text, sizeof(text), "%sBandStartMHz:%f,", text, Node->band_start_mhz);
        snprintf(text, sizeof(text), "%schannel_spacing_mhz:%f,", text, Node->channel_spacing_mhz);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}


const char*  Si4703DeviceIDToStr(const  Si4703RegDeviceID_t * const Value){
    if (Value) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sRegVal:0x%04X,", text, Value->word);
        snprintf(text, sizeof(text), "%sRegVal:0b%s,", text, utoa_bin16(Value->word));
        snprintf(text, sizeof(text), "%smfgid:0x%X,", text, Value->mfgid);
        snprintf(text, sizeof(text), "%sPartNum:%u,", text, Value->pn);
    }
    return text;
}

const char* Si4703ChipIdToStr(const Si4703RegChipID_t *const Value){
    if (Value) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sRegVal:0x%04X,", text, Value->word);
        snprintf(text, sizeof(text), "%sRegVal:0b%s,", text, utoa_bin16(Value->word));
        snprintf(text, sizeof(text), "%sFirmware:0x%X,", text, Value->firmware);
        snprintf(text, sizeof(text), "%sDevice:%u,", text, Value->dev);
        snprintf(text, sizeof(text), "%sChipVersion:%u,", text, Value->rev);
    }
    return text;
}

const char* Si4703StatusRssiToStr(const Si4703RegStatusRssi_t* const Value) {
    if (Value) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sRegVal:0x%04X,", text, Value->word);
        snprintf(text, sizeof(text), "%sRegVal:0b%s,", text, utoa_bin16(Value->word));
        snprintf(text, sizeof(text), "%srssi:%u,", text, Value->rssi);
        snprintf(text, sizeof(text), "%sStereo:%u,", text, Value->st);
        snprintf(text, sizeof(text), "%sblera:%u,", text, Value->blera);
        snprintf(text, sizeof(text), "%srdss:%u,", text, Value->rdss);
        snprintf(text, sizeof(text), "%safcrl:%u,", text, Value->afcrl);
        snprintf(text, sizeof(text), "%ssf_bl:%u,", text, Value->sf_bl);
        snprintf(text, sizeof(text), "%sstc:%u,", text, Value->stc);
        snprintf(text, sizeof(text), "%srdsr:%u,", text, Value->rdsr);
    }
    return text;
}



bool si4703_diag_one(uint8_t num) {
    bool res = false;
    return res;
}

const char* si4703_get_reg_name(uint8_t addr) {
    uint32_t i = 0;
    const char *name = "?";
    uint32_t reg_cnt = si4703_reg_cnt();
    for (i = 0; i < reg_cnt; i++) {
        if (Si4703RegInfo[i].reg_addr == addr) {
            if (Si4703RegInfo[i].valid) {
                name = Si4703RegInfo[i].name;
            }
            break;
        }
    }
    return name;
}

bool RdsBlockErrorsToStr(uint8_t bler, char block) {
    bool res = false;
    LOG_DEBUG(SI4703, "Block %c Errors", block);
    switch (bler) {
        case 0:
            LOG_DEBUG(SI4703, "0 ErrorsRequiringCorrection");
            break;
        case 1:
            LOG_DEBUG(SI4703, "1–2 ErrorsRequiringCorrection");
            break;
        case 2:
            LOG_DEBUG(SI4703, "3–5 ErrorsRequiringCorrection");
            break;
        case 3:
            LOG_DEBUG(SI4703, "6+ ErrorsOrErrorInCheckwordCorrectionNotPossible.");
            break;
    }
    return res;
}

bool si4703_parse_deviceid(uint16_t reg_val, char* keyWord1) {
    bool res = true;
    LOG_INFO(SI4703, CRLF CRLF"%s()", __FUNCTION__);
    Si4703RegDeviceID_t DeviceID;
    DeviceID.word = reg_val;
    LOG_INFO(SI4703, "Part Number 0x%x", DeviceID.pn);
    LOG_INFO(SI4703, "Manufacturer ID. 0x%x", DeviceID.mfgid);
    return res;
}

bool si4703_parse_chipid(uint16_t reg_val, char* keyWord1) {
    bool res = false;
    LOG_INFO(SI4703, CRLF CRLF"%s()", __FUNCTION__);
    Si4703RegChipID_t ChipID;
    ChipID.word = reg_val;
    LOG_INFO(SI4703, "Dev 0x%x", ChipID.dev);
    LOG_INFO(SI4703, "Rev 0x%x", ChipID.rev);
    LOG_INFO(SI4703, "Fw 0x%x", ChipID.firmware);
    return res;
}

bool si4703_parse_power_configuration(uint16_t reg_val, char* keyWord1) {
    bool res = false;
    Si4703RegPwrCfg_t PwrCfg;
    PwrCfg.word = reg_val;
    LOG_INFO(SI4703, CRLF CRLF"%s()", __FUNCTION__);
    LOG_INFO(SI4703, "enable %u", PwrCfg.enable);
    LOG_INFO(SI4703, "disable %u", PwrCfg.disable);
    LOG_INFO(SI4703, "seek %u", PwrCfg.seek);
    LOG_INFO(SI4703, "SeekDir %u", PwrCfg.seekup);
    LOG_INFO(SI4703, "SeekMode %u", PwrCfg.skmode);
    LOG_INFO(SI4703, "RdsMode %u", PwrCfg.rdsm);
    LOG_INFO(SI4703, "mono %u", PwrCfg.mono);
    LOG_INFO(SI4703, "MuteDisable %u", PwrCfg.dmute);
    LOG_INFO(SI4703, "SoftmuteDisable %u", PwrCfg.dsmute);
    return res;
}

//Register 03h. Channel
bool si4703_parse_channel(uint16_t reg_val, char* keyWord1) {
    bool res = false;
    Si4703Handle_t* Node = Si4703GetNode(1);
    if (Node) {
        LOG_INFO(SI4703, CRLF CRLF"%s()", __FUNCTION__);
        Si4703RegChannel_t RegChannel;
        RegChannel.word = reg_val;
        LOG_INFO(SI4703, "channel %u", RegChannel.channel);
        LOG_INFO(SI4703, "tune %u", RegChannel.tune);
        Node->fm_freq_set_real = Node->channel_spacing_mhz * ((double) RegChannel.channel) + Node->band_start_mhz;
        LOG_INFO(SI4703, "FmSreqSetReal %f MHz", Node->fm_freq_set_real);
    }
    return res;
}

bool si4703_parse_system_configuration_1(uint16_t reg_val, char* keyWord1) {
    bool res = false;
    LOG_INFO(SI4703, CRLF CRLF"%s()", __FUNCTION__);
    Si4703RegSysCfg1_t SysCfg1;
    SysCfg1.word = reg_val;
    LOG_INFO(SI4703, "gpio1 %u", SysCfg1.gpio1);
    LOG_INFO(SI4703, "gpio2 %u", SysCfg1.gpio2);
    LOG_INFO(SI4703, "gpio3 %u", SysCfg1.gpio3);
    LOG_INFO(SI4703, "Stereo/Mono Blend Level Adjustment %u", SysCfg1.blndadj);
    LOG_INFO(SI4703, "AGC Disable %u", SysCfg1.agcd);
    LOG_INFO(SI4703, "De-emphasis %u", SysCfg1.de);
    LOG_INFO(SI4703, "RDS Enable %u", SysCfg1.rds);
    LOG_INFO(SI4703, "Seek/Tune Complete Interrupt Enable. %u", SysCfg1.stcien);
    LOG_INFO(SI4703, "RDS Interrupt Enable %u", SysCfg1.rdsien);
    return res;
}

bool si4703_parse_system_configuration_2(uint16_t reg_val, char* keyWord1) {
    bool res = false;
    LOG_INFO(SI4703, CRLF CRLF"%s()", __FUNCTION__);
    Si4703RegSysCfg2_t SysCfg2;
    SysCfg2.word = reg_val;

    LOG_INFO(SI4703, "Volume %u", SysCfg2.volume);
    LOG_INFO(SI4703, "ChannelSpacing %u", SysCfg2.space);
    LOG_INFO(SI4703, "BandSel %u", SysCfg2.band);
    LOG_INFO(SI4703, "RSSISeekThreshold %u", SysCfg2.seekth);
    return res;
}

bool si4703_parse_system_configuration_3(uint16_t reg_val, char* keyWord1) {
    bool res = false;
    LOG_INFO(SI4703, CRLF CRLF"%s()", __FUNCTION__);
    Si4703RegSysCfg3_t SysCfg3;
    SysCfg3.word = reg_val;

    LOG_INFO(SI4703, "SeekFMImpulseDetectionThreshold %u", SysCfg3.skcnt);
    LOG_INFO(SI4703, "SeekSNRThreshold %u", SysCfg3.sksnr);
    LOG_INFO(SI4703, "ExtendedVolumeRange %u", SysCfg3.volext);
    LOG_INFO(SI4703, "SoftmuteAttenuation %u", SysCfg3.smutea);
    LOG_INFO(SI4703, "SoftmuteAttackRecoverRate %u", SysCfg3.smuter);
    return res;
}

bool si4703_parse_test_1(uint16_t reg_val, char* keyWord1) {
    bool res = false;
    LOG_INFO(SI4703, CRLF CRLF"%s()", __FUNCTION__);
    Si4703RegTest1_t RegTest1;
    RegTest1.word = reg_val;
    LOG_INFO(SI4703, "Crystal Oscillator Enable %u", RegTest1.xoscen);
    LOG_INFO(SI4703, "Audio High-Z Enable %u", RegTest1.ahizen);
    return res;
}

bool si4703_parse_test_2(uint16_t reg_val, char* keyWord1) {
    bool res = false;
    LOG_INFO(SI4703, CRLF CRLF"%s()", __FUNCTION__);
    //Si4703RegTest2_t RegTest2;
    //RegTest2.word = reg_val;
    return res;
}

bool si4703_parse_boot_configuration(uint16_t reg_val, char* keyWord1) {
    bool res = false;
    LOG_INFO(SI4703, CRLF CRLF"%s()", __FUNCTION__);
    return res;
}

bool si4703_parse_status_rssi(uint16_t reg_val, char* keyWord1) {
    bool res = false;
    LOG_INFO(SI4703, CRLF CRLF"%s()", __FUNCTION__);
    Si4703RegStatusRssi_t RegStatusRssi;
    RegStatusRssi.word = reg_val;
    LOG_INFO(SI4703, "RSSI %u", RegStatusRssi.rssi);
    LOG_INFO(SI4703, "Stereo Indicator %u", RegStatusRssi.st);
    LOG_INFO(SI4703, "RDS Block A Errors %u", RegStatusRssi.blera);
    LOG_INFO(SI4703, "RDS Synchronized %u", RegStatusRssi.rdss);
    LOG_INFO(SI4703, "AFC Rail %u", RegStatusRssi.afcrl);
    LOG_INFO(SI4703, "Seek Fail/Band Limit. %u", RegStatusRssi.sf_bl);
    LOG_INFO(SI4703, "Seek/Tune Complete %u", RegStatusRssi.stc);
    LOG_INFO(SI4703, "RDS Ready %u", RegStatusRssi.rdsr);
    return res;
}

bool si4703_parse_read_channel(uint16_t reg_val, char* keyWord1) {
    bool res = false;
    LOG_INFO(SI4703, CRLF CRLF"%s()", __FUNCTION__);
    Si4703RegReadChan_t RegReadChan;
    RegReadChan.word = reg_val;
    LOG_INFO(SI4703, "Read Channel %u", RegReadChan.readchan);
    LOG_INFO(SI4703, "RDS Block D Errors %u", RegReadChan.blerd);
    LOG_INFO(SI4703, "RDS Block C Errors %u", RegReadChan.blerc);
    LOG_INFO(SI4703, "RDS Block B Errors %u", RegReadChan.blerb);
    return res;
}

bool si4703_parse_rdsa(uint16_t reg_val, char* keyWord1) {
    bool res = false;
    LOG_INFO(SI4703, CRLF CRLF"%s()", __FUNCTION__);
    Si4703RegRdsA_t RegRdsA;
    RegRdsA.word = reg_val;
    LOG_INFO(SI4703, "rdsa 0x%x", RegRdsA.rdsa);
    return res;
}

bool si4703_parse_rdsb(uint16_t reg_val, char* keyWord1) {
    bool res = false;
    LOG_INFO(SI4703, CRLF CRLF"%s()", __FUNCTION__);
    Si4703RegRdsB_t RegRdsB;
    RegRdsB.word = reg_val;
    LOG_INFO(SI4703, "rdsb 0x%x", RegRdsB.rdsb);
    return res;
}

bool si4703_parse_rdsd(uint16_t reg_val, char* keyWord1) {
    bool res = false;
    LOG_INFO(SI4703, CRLF CRLF"%s()", __FUNCTION__);
    Si4703RegRdsD_t RegRdsD;
    RegRdsD.word = reg_val;
    LOG_INFO(SI4703, "rdsd 0x%x", RegRdsD.rdsd);
    return res;
}

bool si4703_parse_rdsc(uint16_t reg_val, char* keyWord1) {
    bool res = false;
    LOG_INFO(SI4703, CRLF CRLF"%s()", __FUNCTION__);
    Si4703RegRdsC_t RegRdsC;
    RegRdsC.word = reg_val;
    LOG_INFO(SI4703, "rdsc 0x%x", RegRdsC.rdsc);
    return res;
}


const char* Si4703ChipIDToStr(const Si4703RegChipID_t* const Reg) {
    if (Reg) {
        snprintf(text, sizeof(text), "Fw:0x%x,Dev:0x%x,Rev:0x%x", Reg->firmware, Reg->dev, Reg->rev);
    }
    return text;
}


bool si4703_diag(void){
    bool res= false;
    Si4703Handle_t* Node=Si4703GetNode(1);
        LOG_INFO(SI4703, "RegWrDisaccord: %u",Node->reg_val_disaccord);
        LOG_INFO(SI4703, "SpinCnt: %u",Node->spin);
        LOG_INFO(SI4703, "BandStart: %f MHz",Node->band_start_mhz);
        LOG_INFO(SI4703, "FmFreqSet: %f MHz",Node->fm_freq_set);
        LOG_INFO(SI4703, "FmFreqSetReal: %f MHz",Node->fm_freq_set_real);
        LOG_INFO(SI4703, "FmFreqRead: %f MHz",Node->fm_freq_read_mhz );
        LOG_INFO(SI4703, "ChannelSpacing: %f MHz",Node->channel_spacing_mhz);
        LOG_INFO(SI4703, "RdsSyncCnt: %u", Node->rds_sync_cnt);
        LOG_INFO(SI4703, "RdsRxCnt: %u", Node->rds_recv_cnt);
        LOG_INFO(SI4703, "Stereo: %s", OnOffToStr(Node->stereo));
        Si4703RegTest1_t RegTest1;
        RegTest1.word = 0;
        res = si4703_read_reg(1,SI4703_REG_TEST1, &RegTest1.word );
        if(res){
            LOG_INFO(SI4703, "CrystalOscillator: %s ",OnOffToStr(RegTest1.xoscen));
        }
        res = true;
    return res;
}
