#include "i2s_diag.h"

#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "i2s_types.h"
#include "log.h"

static char name[80];

const char* I2sAudioFreq2Str(AudioFreq_t freq) {
    snprintf(name, sizeof(name), "%u Hz",freq);
    return name;
}

const char* I2sResolution2Str(I2sDataFormat_t code){
    const char* name="?";
    switch((uint8_t)code){
        case I2S_DATA_FORMAT_8B:     name="8"; break;
        case I2S_DATA_FORMAT_16B:     name="16"; break;
        case I2S_DATA_FORMAT_16B_EXTENDED:  name="16"; break;
        case I2S_DATA_FORMAT_24B:   name="24"; break;
        case I2S_DATA_FORMAT_32B:   name="32"; break;

        default : name="??"; break;
    }
    return name;
}

const char* I2sBusRole2Str(I2sRole_t code){
    const char* name="?";
    switch((uint8_t)code){
        case I2SMODE_SLAVE:     name="Slave"; break;
        case I2SMODE_SLAVE_RX:  name="SlaveRx"; break;
        case I2SMODE_SLAVE_TX:  name="SlaveTx"; break;
        case I2SMODE_MASTER:    name="Master"; break;
        case I2SMODE_MASTER_TX: name="MasterTx"; break;
        case I2SMODE_MASTER_RX: name="MasterRx"; break;
        default : name="??"; break;
    }
    return name;
}

const char* I2sSampleMode2Str(SampleMode_t sample_mode) {
    const char* name="?";
    switch((uint8_t)sample_mode){
        case SAMPLE_MODE_MONO:    name="Mono"; break;
        case SAMPLE_MODE_STEREO:  name="Stereo"; break;

        default : name="??"; break;
    }
    return name;
}

const char* I2sStandard2Str(Standard_t standard) {
    const char* name="?";
    switch((uint8_t)standard) {
        case I2S_STD_PHILIPS:     name="Philips"; break;
        case I2S_STD_MSB:  name="MSB"; break;
        case I2S_STD_LSB:  name="LSB"; break;
        case I2S_STD_PCM_SHORT:  name="PCM_SHORT"; break;
        case I2S_STD_PCM_LONG:  name="PCM_LONG"; break;


        default : name="??"; break;
    }
    return name;
}

const char* I2sClockSource2Str(  I2sClockSource_t clock_source){
    const char* name="?";
    switch((uint8_t)clock_source){
        case I2S_CLK_PLL:     name="PLL"; break;
        case I2S_CLK_EXT:  name="Exp"; break;

        default : name="??"; break;
    }
    return name;
}

const char* I2sFullDuplex2Str(FullDuplex_t full_duplex){
    const char* name="?";
    switch((uint8_t)full_duplex){
        case FULL_DUPLEX_OFF: name="Simplex"; break;
        case FULL_DUPLEX_ON:  name="FullDuplex"; break;

        default : name="??"; break;
    }
    return name;
}

const char* I2sState2Str(I2sState_t state){
    const char* name="?";
    switch((uint8_t)state){
        case I2S_STATE_OFF: name="Off"; break;
        case I2S_STATE_AMP: name="Amp"; break;
        case I2S_STATE_RUN: name="Run"; break;
        case I2S_STATE_DEC:  name="Dec"; break;

        default : name="??"; break;
    }
    return name;
}


bool I2sDiagConfig(const I2sConfig_t* const Config) {
    bool res = false;
    if(Config){
        char line[120]="";
        strncpy(line,"",sizeof(line)-1);
        snprintf(line,sizeof(line),"%s SampleRate:%u Hz,", line,Config->audio_freq);
        snprintf(line,sizeof(line),"%s RxBuff:%u Sample,", line,Config->samples_cnt);
        snprintf(line,sizeof(line),"%s BusRole %s,",line, I2sBusRole2Str(Config->mode));

        snprintf(line,sizeof(line),"%s DataFormat %u bit,", line, Config->data_format);
        snprintf(line,sizeof(line),"%s SckFreq %u Hz,", line, Config->sck_freq_hz);
        snprintf(line,sizeof(line),"%s FullDuplex %s,", line, I2sFullDuplex2Str(Config->full_duplex));
        snprintf(line,sizeof(line),"%s SampleMode %s,", line, I2sSampleMode2Str(Config->sample_mode));
        snprintf(line,sizeof(line),"%s MclkOut %s,", line, OnOff2Str(Config->mclk_out));
        snprintf(line,sizeof(line),"%s Std %s,", line, I2sStandard2Str(Config->standard));
        snprintf(line,sizeof(line),"%s Clock %s", line, I2sClockSource2Str(Config->clock_source));

        LOG_INFO(I2S, "%s", line);
        res = true;
    }

    return res;
}

#ifdef HAS_I2S_VOLUME
const char* I2sFsmDiag2Str(const I2sHandle_t* const Node ){
    static char line[120]="";
    if(Node){
        strncpy(line,"",sizeof(line)-1);
        snprintf(line,sizeof(line),"%s State %s,", line, I2sState2Str(Node->state));
        snprintf(line,sizeof(line),"%s PCMmaxSet %d,", line, Node->pcm_max_set);
        snprintf(line,sizeof(line),"%s PCMmaxGet %d,", line, Node->pcm_max_get);
    }

    return line;
}
#endif
