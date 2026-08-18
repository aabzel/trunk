#include "lora_drv.h"

#include <string.h>
#include <math.h>

#include "float_utils.h"
#include "param_drv.h"
#include "lora_config.h"
#include "sx1262_drv.h"
#include "sx1262_types.h"
#include "sx1262_op_codes.h"
#include "sx1262_config.h"
#include "common_diag.h"
#include "sx1262_registers.h"

bool is_valid_spreading_factor(SpreadingFactor_t Spreading_factor) {
    bool res = false;
    switch(Spreading_factor) {
    case SF5:
        res = true;
        break;
    case SF6:
        res = true;
        break;
    case SF7:
        res = true;
        break;
    case SF8:
        res = true;
        break;
    case SF9:
        res = true;
        break;
    case SF10:
        res = true;
        break;
    case SF11:
        res = true;
        break;
    case SF12:
        res = true;
        break;
    default:
        res = false;
        break;
    }
    return res;
}

bool is_valid_coding_rate(LoRaCodingRate_t coding_rate) {
    bool res = false;
    switch(coding_rate) {
    case LORA_CR_4_5:
        res = true;
        break;
    case LORA_CR_4_6:
        res = true;
        break;
    case LORA_CR_4_7:
        res = true;
        break;
    case LORA_CR_4_8:
        res = true;
        break;
    default:
        res = false;
        break;
    }
    return res;
}

bool is_valid_bandwidth(BandWidth_t bandwidth) {
    bool res = false;
    switch(bandwidth) {
    case LORA_BW_7:
        res = true;
        break;
    case LORA_BW_10:
        res = true;
        break;
    case LORA_BW_20:
        res = true;
        break;
    case LORA_BW_41:
        res = true;
        break;
    case LORA_BW_15:
        res = true;
        break;
    case LORA_BW_31:
        res = true;
        break;
    case LORA_BW_62:
        res = true;
        break;
    case LORA_BW_125:
        res = true;
        break;
    case LORA_BW_250:
        res = true;
        break;
    case LORA_BW_500:
        res = true;
        break;
    default:
        res = false;
        break;
    }
    return res;
}

bool sx1262_set_modulation_quality_workaround(BandWidth_t band_width) {
    bool res = false;
    uint8_t tx_modulation = 0;
    res = sx1262_get_tx_modulation(&tx_modulation);
    if(res) {
        if(LORA_BW_500 == band_width) {
            RESET_BIT_NUM(tx_modulation, 2);
        } else {
            SET_BIT_NUM(tx_modulation, 2);
        }
        res = sx1262_set_tx_modulation(tx_modulation);
    }
    return res;
}

bool sx1262_set_lora_modulation_params(LoRaModulationParams_t* modParams) {
    bool res = false, res1 = false, res2 = false, res3 = false;
    res1 = is_valid_bandwidth(modParams->band_width);
    if(false == res1) {
#ifdef HAS_LOG
        LOG_ERROR(LORA, "BandWidthError %u", modParams->band_width);
#endif
    } else {
        res = sx1262_set_modulation_quality_workaround(modParams->band_width);
    }
    res2 = is_valid_coding_rate(modParams->coding_rate);
    if(false == res2) {
#ifdef HAS_LOG
        LOG_ERROR(LORA, "CodingRateError %u", modParams->coding_rate);
#endif
    }
    res3 = is_valid_spreading_factor(modParams->spreading_factor);
    if(false == res3) {
#ifdef HAS_LOG
        LOG_ERROR(LORA, "SpreadingFactorError %u", modParams->spreading_factor);
#endif
    }
    if(res1 && res2 && res3) {

        uint8_t tx_array[8]; /**/
        memset(tx_array, 0x00, sizeof(tx_array));
        tx_array[0] = modParams->spreading_factor;
        tx_array[1] = modParams->band_width;
        tx_array[2] = modParams->coding_rate;
        tx_array[3] = modParams->low_data_rate_optimization; // Low Data Rate Optimization (LDRO) LDRO
                                                             // LowDataRateOptimize 0:OFF; 1:ON; TODO
        res = sx1262_send_opcode(OPCODE_SET_MODULATION_PARAMS, tx_array, sizeof(tx_array), NULL, 0);
    }
    return res;
}

bool sx1262_load_params(Sx1262_t* sx1262Instance) {
    bool out_res = true;
    sx1262Instance->lora_sync_word_set = DFLT_LORA_SYNC_WORD;
    sx1262Instance->crc_init = 0x1D0F;
    sx1262Instance->crc_poly = 0x1021;
    sx1262Instance->ReTxFsm.retx_cnt_max = RETX_TRY_CNT_DFLT;
#ifdef HAS_LORA
    sx1262Instance->lora_mod_params.band_width = DFLT_LORA_BW;
    sx1262Instance->lora_mod_params.coding_rate = DFLT_LORA_CR;
    sx1262Instance->lora_mod_params.spreading_factor = DFLT_SF;
    sx1262Instance->lora_mod_params.low_data_rate_optimization = LDRO_OFF;
#endif
    sx1262Instance->packet_param.packet_type = PACKET_TYPE_LORA;
    sx1262Instance->packet_param.proto.lora.header_type = LORA_VAR_LEN_PACT;
    sx1262Instance->packet_param.proto.lora.crc_type = LORA_CRC_ON;
    sx1262Instance->packet_param.proto.lora.invert_iq = IQ_SETUP_STANDARD;
    sx1262Instance->packet_param.proto.lora.preamble_length = DFLT_PREAMBLE_LEN;
    sx1262Instance->packet_param.proto.lora.payload_length = 255;
    sx1262Instance->output_power = DFLT_OUT_POWER;
    sx1262Instance->rf_frequency_hz = DFLT_FREQ_MHZ;
    sx1262Instance->tx_mute = false;
    sx1262Instance->retx = RETX_NO_NEED;
#ifdef HAS_SX1262_BIT_RATE
    sx1262Instance->tx_max_bit_rate = 0.0;
#endif

#ifdef HAS_PARAM
    bool res = true;

#ifdef HAS_GFSK
    res = sx1262_load_params_gfsk(sx1262Instance);
#endif

#ifdef HAS_LORA
    res = sx1262_load_params_lora(sx1262Instance);
#endif
    LOAD_PARAM(SX1262, PAR_ID_RETX_CNT, sx1262Instance->ReTxFsm.retx_cnt_max, RETX_TRY_CNT_DFLT);
    LOAD_PARAM(SX1262, PAR_ID_WIRELESS_INTERFACE, sx1262Instance->packet_param.packet_type, PACKET_TYPE_LORA);
    LOAD_PARAM(SX1262, PAR_ID_RETX, sx1262Instance->retx, RETX_NO_NEED);
    LOAD_PARAM(SX1262, PAR_ID_TX_MUTE, sx1262Instance->tx_mute, false);
    LOAD_PARAM(SX1262, PAR_ID_RX_GAIN, sx1262Instance->rx_gain, RXGAIN_POWER_SAVING);
    LOAD_PARAM(SX1262, PAR_ID_IQ_SETUP, sx1262Instance->packet_param.proto.lora.invert_iq, IQ_SETUP_STANDARD);
    LOAD_PARAM(SX1262, PAR_ID_FREQ, sx1262Instance->rf_frequency_hz, DFLT_FREQ_MHZ);
    LOAD_PARAM(SX1262, PAR_ID_OUT_POWER, sx1262Instance->output_power, DFLT_OUT_POWER);

#ifdef HAS_SX1262_BIT_RATE
    // LOAD_PARAM(PAR_ID_MAX_BIT_RATE, sx1262Instance->tx_max_bit_rate, 8, "BitRate" ,0.0, BitRateToStr);

    res = param_get(PAR_ID_MAX_BIT_RATE, (uint8_t*)&sx1262Instance->tx_max_bit_rate);
    if(res) {
#ifdef HAS_LOG
        LOG_INFO(SX1262, "Load BitRate FromParams [%s]", BitRateToStr(sx1262Instance->tx_max_bit_rate));
#endif
    } else {
#ifdef HAS_LOG
        LOG_WARNING(SX1262, "Set DfltBitRate [%s]", BitRateToStr(0.0));
#endif
        sx1262Instance->tx_max_bit_rate = 0.0;
        out_res = false;
    }
#endif /*HAS_SX1262_BIT_RATE*/
#endif /*HAS_PARAM*/
    return out_res;
}



/*returns band_width in kHz multiplied by 100 in order to fit in 2 bytes*/
uint32_t bandwidth2num(BandWidth_t bandwidth) {
    uint32_t band_width = 0;
    switch(bandwidth) {
    case LORA_BW_7:
        band_width = 7810;
        break;
    case LORA_BW_10:
        band_width = 10420;
        break;
    case LORA_BW_15:
        band_width = 15630;
        break;
    case LORA_BW_20:
        band_width = 20830;
        break;
    case LORA_BW_31:
        band_width = 31250;
        break;
    case LORA_BW_41:
        band_width = 41670;
        break;
    case LORA_BW_62:
        band_width = 62500;
        break;
    case LORA_BW_125:
        band_width = 125000;
        break;
    case LORA_BW_250:
        band_width = 250000;
        break;
    case LORA_BW_500:
        band_width = 500000;
        break;

    default:
        band_width = 0;
        break;
    }
    return band_width;
}

bool sx1262_load_params_lora(Sx1262_t* sx1262Instance){
   bool out_res = true;
   if(sx1262Instance){
       LOAD_PARAM(LORA, PAR_ID_LORA_CR, sx1262Instance->lora_mod_params.coding_rate, DFLT_LORA_CR);
       LOAD_PARAM(LORA, PAR_ID_LORA_BW, sx1262Instance->lora_mod_params.band_width, DFLT_LORA_BW);
       LOAD_PARAM(LORA, PAR_ID_LORA_SF, sx1262Instance->lora_mod_params.spreading_factor, DFLT_SF);
       LOAD_PARAM(LORA, PAR_ID_LORA_SYNC_WORD, sx1262Instance->lora_sync_word_set, DFLT_LORA_SYNC_WORD);
       LOAD_PARAM(LORA, PAR_ID_LORA_HEADER_TYPE, sx1262Instance->packet_param.proto.lora.header_type, LORA_VAR_LEN_PACT);
       LOAD_PARAM(LORA, PAR_ID_LOW_DATA_RATE, sx1262Instance->lora_mod_params.low_data_rate_optimization, LDRO_OFF);
       LOAD_PARAM(LORA, PAR_ID_PAYLOAD_LENGTH, sx1262Instance->packet_param.proto.lora.payload_length, 255);
       LOAD_PARAM(LORA, PAR_ID_CRC_TYPE, sx1262Instance->packet_param.proto.lora.crc_type, LORA_CRC_ON);
       LOAD_PARAM(LORA, PAR_ID_PREAMBLE_LENGTH, sx1262Instance->packet_param.proto.lora.preamble_length,DFLT_PREAMBLE_LEN);
   }else{
       out_res = false;
   }
   return out_res;
}

double lora_calc_data_rate(uint8_t sf_code, uint8_t bw_code, uint8_t cr_code) {
    double data_rate = 0.0;
    uint32_t bandwidth_hz = bandwidth2num((BandWidth_t)bw_code);
    data_rate = ((double)(bandwidth_hz * sf_code * 4)) / ((powf(2.0f, (double)sf_code)) * ((double)(4 + cr_code)));
    return data_rate;
}


double lora_calc_max_frame_tx_time(uint8_t sf_code, uint8_t bw_code, uint8_t cr_code, uint16_t n_preamble,
                                   uint8_t header, uint8_t low_data_rate_opt, double* out_t_sym,
                                   double* out_t_preamble) {
    double t_frame = 0.0f;
    double t_payload = 0.0f;
    uint16_t pl = 256;
    double Tsym = 0.0;
    double t_preamble = 0.0;
    Tsym = pow(2.0f, (double)sf_code) / ((double)bandwidth2num((BandWidth_t)bw_code));
    t_preamble = (((double)n_preamble) + 4.25) * (Tsym);
    double payloadSymbNb =
        8.0f + double_max(((double)(cr_code + 4)) * ceil(((double)(8 * pl - 4 * sf_code + 44 + 20 * header)) /
                                                         ((double)(4 * (sf_code - 2 * low_data_rate_opt)))),
                          0.0f);
    t_payload = payloadSymbNb * Tsym;
    t_frame = t_preamble + t_payload;

    if(out_t_sym) {
        (*out_t_sym) = Tsym;
    }
    if(out_t_preamble) {
        (*out_t_preamble) = t_preamble;
    }
    return t_frame;
}
