#include "si4737_diag.h"

#include <stdio.h>

#include "data_utils.h"

static Si4737PropertyDiag_t Si4737PropertyLut[] = {
    {
        .id = SI4737_FM_DEEMPHASIS,
        .name = "FmDeemphasis",
    },
    {
        .id = SI4737_FM_BLEND_STEREO_THRESHOLD,
        .name = "FmBlendStereoThrshld",
    },
    {
        .id = SI4737_FM_BLEND_MONO_THRESHOLD,
        .name = "FmBlendMonoThrshld",
    },
    {
        .id = SI4737_FM_RSQ_INT_SOURCE,
        .name = "FmRsqIntSrc",
    },
    {
        .id = SI4737_FM_SOFT_MUTE_RATE,
        .name = "FmSoftMuteRate",
    },
    {
        .id = SI4737_FM_SOFT_MUTE_MAX_ATTENUATION,
        .name = "FmSoftMuteMaxAtten",
    },
    {
        .id = SI4737_FM_SOFT_MUTE_SNR_THRESHOLD,
        .name = "FmSoftMuteSnrThrshld",
    },
    {
        .id = SI4737_FM_SEEK_BAND_BOTTOM,
        .name = "FmSeekBandBottom",
    },
    {
        .id = SI4737_FM_SEEK_BAND_TOP,
        .name = "FmSeekBandTop",
    },
    {
        .id = SI4737_FM_SEEK_FREQ_SPACING,
        .name = "FmSeekFreqSpacing",
    },
    {
        .id = SI4737_FM_SEEK_TUNE_SNR_THRESHOLD,
        .name = "FmSeekTuneSnrThrshld",
    },
    {
        .id = SI4737_FM_SEEK_TUNE_RSSI_THRESHOLD,
        .name = "FmSeekTuneRssiThrshld",
    },
    {
        .id = SI4737_FM_RDS_INT_SOURCE,
        .name = "FmRdsIntSrc",
    },
    {
        .id = SI4737_FM_RDS_INT_FIFO_COUNT,
        .name = "FmRdsIntFifoCnt",
    },
    {
        .id = SI4737_FM_RDS_CONFIG,
        .name = "FmRdsConfig",
    },
    {
        .id = SI4737_AM_DEENOHASIS,
        .name = "AmDeenohasis",
    },
    {
        .id = SI4737_AM_CHANNEL_FILTER,
        .name = "AmChannelFilter",
    },
    {
        .id = SI4737_AM_AUTO_VOLUME_CTRL_MAX_GAIN,
        .name = "AmAutoVolumeCtrlMaxGain",
    },
    {
        .id = SI4737_AM_RSQ_INTERRUPTS,
        .name = "AmRsqInterrupts",
    },
    {
        .id = SI4737_AM_SOFT_MUTE_RATE,
        .name = "AmSoftMuteRate",
    },
    {
        .id = SI4737_AM_SOFT_MUTE_MAX_ATTENUATION,
        .name = "AmSoftMuteMaxAtten",
    },
    {
        .id = SI4737_AM_SOFT_MUTE_SNR_THRESHOLD,
        .name = "AmSoftMuteSnrThrshld",
    },
    {
        .id = SI4737_AM_SEEK_BAND_BOTTOM,
        .name = "AmSeekBandBottom",
    },
    {
        .id = SI4737_AM_SEEK_BAND_TOP,
        .name = "AmSeekBandTop",
    },
    {
        .id = SI4737_AM_SEEK_FREQ_SPACING,
        .name = "AmSeekFreqSpacing",
    },
    {
        .id = SI4737_AM_SEEK_SNR_THRESHOLD,
        .name = "AmSeekSnrThrshld",
    },
    {
        .id = SI4737_AM_SEEK_RSSI_THRESHOLD,
        .name = "AmSeekRssiThrshld",
    },
    {
        .id = SI4737_RX_VOLUME,
        .name = "RxVolume",
    },
    {
        .id = SI4737_RX_HARD_MUTE,
        .name = "RxHardMute",
    },
    {
        .id = SI4737_WB_MAX_TUNE_ERROR,
        .name = "WbMaxTuneError",
    },
    {
        .id = SI4737_WB_RSQ_INT_SOURCE,
        .name = "WbRsqIntSrc",
    },
    {
        .id = SI4737_WB_ASQ_INT_SOURCE,
        .name = "WbASQIntSrc",
    },
};

const char* SiPropertyToStr(uint16_t id) {
    const char* name = "?";
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(Si4737PropertyLut); i++) {
        if(Si4737PropertyLut[i].id == id) {
            name = Si4737PropertyLut[i].name;
            break;
        }
    }
    return name;
}

const char* RdsBlockToStr(uint8_t rds_block) {
    const char* sub_name = "?";
    switch(rds_block) {
    case RDS_BLOCK_A:
        sub_name = "A";
        break;
    case RDS_BLOCK_B:
        sub_name = "B";
        break;
    case RDS_BLOCK_C:
        sub_name = "C";
        break;
    case RDS_BLOCK_D:
        sub_name = "B";
        break;
    default:
        break;
    }
    return sub_name;
}

const char* parse_rds_block_corr_err(uint8_t byte, RdsBlock_t rds_block) {
    const char* sub_name = "?";
    static char name[10];
    switch(byte) {
    case RDS_BLOCK_CORR_NO_ERR:
        sub_name = "NoErr";
        break;
    case RDS_BLOCK_CORR_1_2_BIT:
        sub_name = "1,2 BitsErrDetCor";
        break;
    case RDS_BLOCK_CORR_3_5_BIT:
        sub_name = "3,5 BitsErrDetCor";
        break;
    case RDS_BLOCK_CORR_UNCORR:
        sub_name = "UnCorrectable";
        break;
    default:
        break;
    }

    snprintf(name, sizeof(name), "%s %s", RdsBlockToStr(rds_block), sub_name);
    return name;
}

const char* SeekDirToStr(uint8_t SeekDir) {
    const char* name = "?";
    switch(SeekDir) {
    case SEEK_DIR_DOWN:
        name = "Down";
        break;
    case SEEK_DIR_UP:
        name = "Up";
        break;
    }
    return name;
}

const char* SeekEndToStr(uint8_t SeekEnd) {
    const char* name = "?";
    switch(SeekEnd) {
    case SEEK_END_HALT:
        name = "Halt";
        break;
    case SEEK_END_WRAP:
        name = "Wrap";
        break;
    }
    return name;
}

const char* OutFallToStr(uint8_t out_fall) {
    const char* name = "?";
    switch(out_fall) {
    case DIGITAL_OUT_CLK_EDGE_RISING:
        name = "Rising";
        break;
    case DIGITAL_OUT_CLK_EDGE_FALING:
        name = "Faling";
        break;
    }
    return name;
}

const char* OutMonoToStr(uint8_t code) {
    const char* name = "?";
    switch(code) {
    case DIGITAL_OUT_MODE_STEREO:
        name = "Stereo";
        break;
    case DIGITAL_OUT_MODE_MONO:
        name = "Mono";
        break;
    }
    return name;
}

const char* OutModeToStr(uint8_t code) {
    const char* name = "?";
    switch(code) {
    case DIGITAL_OUT_MODE_I2S:
        name = "I2S";
        break;
    case DIGITAL_OUT_MODE_LEFT_JUSTIFIED:
        name = "LeftJust";
        break;
    case DIGITAL_OUT_MODE_MSB_AT_2ND_DCLK_AFTER_DFS_PULSE:
        name = "Msb2nd";
        break;
    case DIGITAL_OUT_MODE_MSB_AT_1ST_DCLK_AFTER_DFS_PULSE:
        name = "Msb1st";
        break;
    }
    return name;
}
