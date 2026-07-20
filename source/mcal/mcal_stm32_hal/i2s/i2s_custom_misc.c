#include "i2s_custom_misc.h"

#include "stm32fx_hal.h"
#include "connectivity_const.h"
#include "i2s_custom_drv.h"

SPI_TypeDef* I2sGetBaseAddr(uint8_t num) {
    SPI_TypeDef *I2Sx = NULL;
    const I2sInfo_t* Info = I2sGetInfo(num);
    if(Info){
        I2Sx = Info->I2Sx;
    }
    return I2Sx;
}

uint32_t I2sBus2Code(const ClockBus_t CurBus) {
    uint32_t periph_clk_code = 0;
#if defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) ||\
    defined(STM32F413xx) || defined(STM32F423xx)
    switch (CurBus) {
    case CLOCK_BUS_APB1:
        periph_clk_code = RCC_PERIPHCLK_I2S_APB1;
        break;
    case CLOCK_BUS_APB2:
        periph_clk_code = RCC_PERIPHCLK_I2S_APB2;
        break;
    default:
        break;
    }
#endif
    return periph_clk_code;
}

int8_t get_i2s_index(SPI_TypeDef* I2Sx) {
    int8_t num = -1;
    uint32_t i = 0;
    uint32_t cnt = i2s_info_get_cnt( );
    for(i=0;i<cnt;i++) {
        if(I2Sx==I2sInfo[i].I2Sx) {
            num = I2sInfo[i].num;
        }
    }

#if 0
#ifdef SPI1
    if(SPI1 == I2Sx) {
        num = 1;
    }
#endif /*SPI1*/

#ifdef SPI2
    if(SPI2 == I2Sx) {
        num = 2;
    }
#endif /*SPI2*/

#ifdef SPI3
    if(SPI3 == I2Sx) {
        num = 3;
    }
#endif /*SPI2*/

#ifdef I2S2ext
    if(I2S2ext == I2Sx) {
        num = 4;
    }
#endif /*SPI4*/

#ifdef I2S2ext
    if(I2S3ext == I2Sx) {
        num = 5;
    }
#endif /*SPI5*/

#ifdef SPI6
    if(SPI6 == I2Sx) {
        num = 6;
    }
#endif /*SPI6*/
#endif

    return num;
}

uint32_t I2sParseFullDuplexMode(const I2sFullDuplex_t full_duplex) {
    uint32_t code = 0xFFFFFFFF;
    switch (full_duplex) {
    case FULL_DUPLEX_OFF:
        code = I2S_FULLDUPLEXMODE_DISABLE;
        break;
    case FULL_DUPLEX_ON:
        code = I2S_FULLDUPLEXMODE_ENABLE;
        break;
    default:
        break;
    }
    return code;
}

uint32_t I2sParseMCLKOutput(const I2sMclkOut_t mclk_out) {
    uint32_t code = I2S_MCLKOUTPUT_DISABLE;
    switch (mclk_out) {
        case I2S_MCLKOUT_ON:        code = I2S_MCLKOUTPUT_ENABLE;        break;
        case I2S_MCLKOUT_OFF:        code = I2S_MCLKOUTPUT_DISABLE;        break;
        default:        break;
    }
    return code;
}

uint32_t I2sParseDataFormat(I2sDataFormat_t data_format) {
    uint32_t code = 0xFFFFFFFF;
    switch (data_format) {
    case I2S_DATA_FORMAT_16B:
        code = I2S_DATAFORMAT_16B;
        break;
    case I2S_DATA_FORMAT_16B_EXTENDED:
        code = I2S_DATAFORMAT_16B_EXTENDED;
        break;
    case I2S_DATA_FORMAT_24B:
        code = I2S_DATAFORMAT_24B;
        break;
    case I2S_DATA_FORMAT_32B:
        code = I2S_DATAFORMAT_32B;
        break;
    default:
        break;
    }
    return code;
}

uint32_t I2sParseCPol(I2sCpol_t cpol) {
    uint32_t code = I2S_CPOL_LOW;
    switch (cpol) {
    case I2S_CLOCK_POL_LOW:
        code = I2S_CPOL_LOW;
        break;
    case I2S_CLOCK_POL_HIGH:
        code = I2S_CPOL_HIGH;
        break;
    default:
        code = 0xFFFFFFFF;
        break;
    }
    return code;
}

uint32_t I2sParseClockSource(I2sClockSource_t clock_source) {
    uint32_t code = I2S_CLK_UNDEF;
    switch (clock_source) {
    case I2S_CLK_PLL:
        code = I2S_CLOCK_PLL;
        break;
    case I2S_CLK_EXT:
        code = I2S_CLOCK_EXTERNAL;
        break;
    default:
        code = I2S_CLK_UNDEF;
        break;
    }
    return code;
}

uint32_t I2sParseAudioFreq(AudioFreq_t audio_freq) {
    uint32_t code = I2S_AUDIOFREQ_32K;
    switch (audio_freq) {
    case AUDIO_FREQ_192K:
        code = I2S_AUDIOFREQ_192K;
        break;
    case AUDIO_FREQ_96K:
        code = I2S_AUDIOFREQ_96K;
        break;
    case AUDIO_FREQ_48K:
        code = I2S_AUDIOFREQ_48K;
        break;
    case AUDIO_FREQ_44K:
        code = I2S_AUDIOFREQ_44K;
        break;
    case AUDIO_FREQ_32K:
        code = I2S_AUDIOFREQ_32K;
        break;
    case AUDIO_FREQ_22K:
        code = I2S_AUDIOFREQ_22K;
        break;
    case AUDIO_FREQ_16K:
        code = I2S_AUDIOFREQ_16K;
        break;
    case AUDIO_FREQ_11K:
        code = I2S_AUDIOFREQ_11K;
        break;
    case AUDIO_FREQ_8K:
        code = I2S_AUDIOFREQ_8K;
        break;
    default:
        code = I2S_AUDIOFREQ_32K;
        break;
    }
    return code;
}


/*
possible return values:
    I2S_MODE_MASTER_TX
    I2S_MODE_MASTER_RX
 */
uint32_t I2sMasterDirToMode(const ConnectivitDir_t direction) {
    uint32_t master_code = I2S_MODE_MASTER_RX;
    switch (direction) {
        case CONNECT_DIR_TRANSMIT:   master_code = I2S_MODE_MASTER_TX; break;
        case CONNECT_DIR_RECEIVER:   master_code = I2S_MODE_MASTER_RX; break;
        case CONNECT_DIR_RX_TX:      master_code = I2S_MODE_MASTER_RX; break;
        default: { master_code = I2S_MODE_MASTER_RX;}  break;
    }
    return master_code;
}

/*
possible return values:
    I2S_MODE_SLAVE_TX
    I2S_MODE_SLAVE_RX
 */
uint32_t I2sSlaveDirToMode(const ConnectivitDir_t direction) {
    uint32_t slave_code = I2S_MODE_SLAVE_RX;
    switch (direction) {
        case CONNECT_DIR_TRANSMIT:   slave_code = I2S_MODE_SLAVE_TX; break;
        case CONNECT_DIR_RECEIVER:   slave_code = I2S_MODE_SLAVE_RX; break;
        case CONNECT_DIR_RX_TX:      slave_code = I2S_MODE_SLAVE_RX; break;
        default: { slave_code = I2S_MODE_SLAVE_RX;}  break;
    }
    return slave_code;
}

/*
possible return values:
    I2S_MODE_SLAVE_TX
    I2S_MODE_SLAVE_RX
    I2S_MODE_MASTER_TX
    I2S_MODE_MASTER_RX
 */
uint32_t I2sDirRoleToMode( const IfBusRole_t bus_role,
                           const ConnectivitDir_t direction ) {
    uint32_t slave_code = I2S_MODE_SLAVE_RX;
    switch (bus_role) {
        case IF_BUS_ROLE_MASTER:
            slave_code = I2sMasterDirToMode(direction);
            break;
        case IF_BUS_ROLE_SLAVE:
            slave_code = I2sSlaveDirToMode(direction);
            break;
        default: { slave_code = I2S_MODE_SLAVE_RX;}  break;
    }
    return slave_code;
}


uint32_t I2sParseStandard(I2sStandard_t standard) {
    uint32_t code = I2S_STANDARD_LSB;
    switch (standard) {
    case I2S_STD_PHILIPS:
        code = I2S_STANDARD_PHILIPS;
        break;
    case I2S_STD_MSB:
        code = I2S_STANDARD_MSB;
        break;
    case I2S_STD_LSB:
        code = I2S_STANDARD_LSB;
        break;
    case I2S_STD_PCM_SHORT:
        code = I2S_STANDARD_PCM_SHORT;
        break;
    case I2S_STD_PCM_LONG:
        code = I2S_STANDARD_PCM_LONG;
        break;
    default:
        break;
    }
    return code;
}

uint8_t I2sSampleBitness2bytes(Stm32I2sDatLen_t code) {
    uint8_t num_bytes = 0;
    switch ( code) {
    case I2S_DAT_LEN16_BIT:
        num_bytes = 2;
        break;
    case I2S_DAT_LEN24_BIT:
        num_bytes = 4;
        break;
    case I2S_DAT_LEN32_BIT:
        num_bytes = 4;
        break;
    case I2S_DAT_NOT_ALLOWED:
        num_bytes = 0;
        break;

    default:
        num_bytes = 0;
        break;
    }
    return num_bytes;
}

#if 0
uint32_t I2sSampleRate2Hz(AudioFreq_t code) {
    uint32_t sample_rate = 0;
   switch ( code) {
    case AUDIO_FREQ_192K:
        sample_rate = 192000;
        break; // DVD-Audio (MLP 2.0);
    case AUDIO_FREQ_96K:
        sample_rate = 96000;
        break; // DVD-Audio (MLP 5.1);
    case AUDIO_FREQ_48K:
        sample_rate = 48000;
        break; // DVD, DAT;
    case AUDIO_FREQ_44K:
        sample_rate = 44100;
        break; //
    case AUDIO_FREQ_32K:
        sample_rate = 32000;
        break;
    case AUDIO_FREQ_22K:
        sample_rate = 22050;
        break;
    case AUDIO_FREQ_16K:
        sample_rate = 16000;
        break;
    case AUDIO_FREQ_11K:
        sample_rate = 11025;
        break;
    case AUDIO_FREQ_8K:
        sample_rate = 8000;
        break;
    default:
        break;
    }
    return sample_rate;
}
#endif

ConnectivitDir_t I2SOperationToDirection(const IfOperation_t operation) {
    ConnectivitDir_t dir = CONNECT_DIR_UNDEF;
    switch ( operation) {
        case INTERFACE_OPERATION_RECEPTION:         dir = CONNECT_DIR_RECEIVER;         break;
        case INTERFACE_OPERATION_SEND:         dir = CONNECT_DIR_TRANSMIT;         break;
        case INTERFACE_OPERATION_RECEPTION_AND_TRANSMISSION:         dir = CONNECT_DIR_RX_TX;        break;
        default:        dir = CONNECT_DIR_UNDEF;        break;
    }
    return dir;
}
