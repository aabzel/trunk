#include "gfsk_drv.h"

#include <string.h>

#include "debug_info.h"
#include "byte_utils.h"
#include "log.h"
#include "common_diag.h"
#include "gfsk_diag.h"
#include "log.h"
#include "lora_constants.h"
#include "sx1262_drv.h"
#include "param_drv.h"
#include "gfsk_constants.h"
#include "gfsk_config.h"

#ifdef HAS_PARAM
#include "param_drv.h"
#endif

#ifndef HAS_GFSK
#error "HAS_GFSK must be added"
#endif

static bool gfsk_is_valid_rate(uint32_t bitrate){
    bool res = false;
    if((600<=bitrate) && (bitrate<=300000)){
        res = true;
    }
    return res;
}

static bool gfsk_is_valid_freq_dev(uint32_t freq_dev){
    bool res = false;
    if((600<=freq_dev) && (freq_dev<=200000)){
        res = true;
    }
    return res;
}

static bool  gfsk_is_valid_modulation(uint32_t freq_dev,
                                      uint32_t bitrate){
    bool res = false;
    if((freq_dev+(bitrate/2))<=250000){
        res = true;
    }
    return res;
}

/*SetModulationParams*/
bool sx1262_set_gfsk_modulation_params(GfskModulationParams_t* modParams) {
    bool res = false;
    if(modParams) {
        res=gfsk_is_valid_rate(modParams->bit_rate);
        if(false==res){
            LOG_ERROR(GFSK, "InvalidBitRate: %u Bit/s",modParams->bit_rate);
        }
        if(res){
            res = gfsk_is_valid_freq_dev(modParams->frequency_deviation);
            if(false==res){
                LOG_ERROR(GFSK, "InvalidFreqDev: %u Hz",modParams->frequency_deviation);
            }
        }
        if(res){
            res = gfsk_is_valid_modulation(modParams->frequency_deviation,
                                           modParams->bit_rate);
            if(false==res) {
                LOG_ERROR(GFSK, "InvalidModulation");
            }
        }
    }

    if(res){
        LOG_INFO(GFSK,"SetModParam  %s %s %s %s",
                 GfskBandwithToStr(modParams->bandwidth),
                 BitRateToStr ((double)modParams->bit_rate),
                 RfFreqToStr(modParams->frequency_deviation),
                 PulseShapeToStr(modParams->pulse_shape));
        uint8_t tx_array[8];
        memset(tx_array, 0x00, sizeof(tx_array));

        uint32_t bit_rate_reg =(uint32_t) ( (32.0 * ((double)XTAL_FREQ_HZ)) / ((double) modParams->bit_rate));
        LOG_DEBUG(GFSK,"bit_rate 0x%08x %u Hz", bit_rate_reg, bit_rate_reg);
#if 1
        tx_array[0] =( bit_rate_reg >> 16 ) & 0xFF;;
        tx_array[1] =( bit_rate_reg >> 8 ) & 0xFF;;
        tx_array[2] =bit_rate_reg & 0xFF;;
#endif

#if 0
        uint32_t bit_rate_be = 0;
        bit_rate_be = reverse_byte_order_uint24( bit_rate_reg);
        LOG_DEBUG(GFSK,"bit_rate_be 0x%08x %u", bit_rate_be, bit_rate_be);
        memcpy(tx_array, &bit_rate_be, 3);
#endif

        //memcpy(tx_array, &bit_rate, 3);
        tx_array[3] = modParams->pulse_shape;
        tx_array[4] = modParams->bandwidth;
        uint32_t fdev = (uint32_t)  (((double)modParams->frequency_deviation ) / ((double)FREQ_STEP));
        LOG_DEBUG(GFSK,"fdev reg 0x%08x %u", fdev, fdev);
#if 1
        tx_array[5] = ( fdev >> 16 ) & 0xFF;
        tx_array[6] = ( fdev >> 8 ) & 0xFF;
        tx_array[7] = ( fdev& 0xFF );
#endif

#if 0
        uint32_t fdev_be = 0;
        fdev_be = reverse_byte_order_uint24(fdev);
        LOG_DEBUG(GFSK,"fdev 0x%08x bit_rate_be 0x%08x", fdev, fdev_be);
        memcpy(&tx_array[5], &fdev_be, 3);
#endif
        uint32_t bandwith_hz= GfskBandWith2Hz(modParams->bandwidth);
        if((modParams->bit_rate+2*modParams->frequency_deviation)<=bandwith_hz){
            LOG_INFO(GFSK,"ModParamOk");
        }else{
            LOG_ERROR(GFSK,"ParamError bandwith:%u Hz", bandwith_hz);
            res = false;
        }
        print_mem(tx_array,sizeof(tx_array),true, false, true, false);
        res = sx1262_send_opcode(OPCODE_SET_MODULATION_PARAMS, tx_array, 8, NULL, 0);
    }

    return res;
}

bool sx1262_load_params_gfsk(Sx1262_t* sx1262Instance){
   bool out_res = true;
   bool res = true;
#ifdef HAS_PARAM
   res = param_get(PAR_ID_SYNC_WORD, (uint8_t*)&sx1262Instance->GfskParam.set_sync_word);
   if(res) {
#ifdef HAS_LOG
       LOG_INFO(LORA, "Load SyncWordFrom Params %llu [%s]", sx1262Instance->GfskParam.set_sync_word,
                SyncWordToStr(sx1262Instance->GfskParam.set_sync_word));
#endif
   } else {
#ifdef HAS_LOG
       LOG_WARNING(LORA, "Set DfltSyncWord %llu [%s]", sx1262Instance->GfskParam.set_sync_word,
                   SyncWordToStr(DFLT_SYNC_WORD));
#endif
       sx1262Instance->GfskParam.set_sync_word = DFLT_SYNC_WORD;
       res = false;
       out_res = false;
   }

   LOAD_PARAM(GFSK, PAR_ID_CRC_POLY, sx1262Instance->crc_poly, 0x1021);
   LOAD_PARAM(GFSK, PAR_ID_CRC_INIT, sx1262Instance->crc_init, 0x1D0F);
   LOAD_PARAM(GFSK, PAR_ID_SYNC_WORD_LEN, sx1262Instance->packet_param.proto.gfsk.syncword_length,  DFLT_SYNC_WORD_BITS_LEN);
   LOAD_PARAM(GFSK, PAR_ID_WHITENING, sx1262Instance->GfskParam.whitening,   Whitening_ENABLE);
   LOAD_PARAM(GFSK, PAR_ID_GFSK_FREQ_DEV, sx1262Instance->gfsk_mod_params.frequency_deviation,   1000);
   LOAD_PARAM(GFSK, PAR_ID_GFSK_BANDWIDTH, sx1262Instance->gfsk_mod_params.bandwidth,   GFSK_BW_11700              );
   LOAD_PARAM(GFSK, PAR_ID_GFSK_PULSE_SHAPE, sx1262Instance->gfsk_mod_params.pulse_shape,                PSH_Gaussian_BT_1_0);
   LOAD_PARAM(GFSK, PAR_ID_GFSK_CRC_TYPE, sx1262Instance->packet_param.proto.gfsk.crc_type,   CRC_OFF           );
   LOAD_PARAM(GFSK, PAR_ID_GFSK_PAYLOAD_LEN, sx1262Instance->packet_param.proto.gfsk.payload_length, DFLT_PAYLOAD_LEN);
   LOAD_PARAM(GFSK, PAR_ID_PRE_DET_LEN, sx1262Instance->packet_param.proto.gfsk.preamble_detector_length,                PLE_DET_OFF);
   LOAD_PARAM(GFSK, PAR_ID_GFSK_PRE_LEN, sx1262Instance->packet_param.proto.gfsk.preamble_length,   8         );
   LOAD_PARAM(GFSK, PAR_ID_ADDR_COMP, sx1262Instance->packet_param.proto.gfsk.addr_comp, ADDR_FILT_NODE_BROADCAST_ADDR);
   LOAD_PARAM(GFSK, PAR_ID_BROADCAST_ADDR, sx1262Instance->GfskParam.broadcast_addr, DFLT_BROADCAST_ADDR);
   LOAD_PARAM(GFSK, PAR_ID_NODE_ADDR, sx1262Instance->GfskParam.node_addr,  DFLT_NODE_ADDR);
   LOAD_PARAM(GFSK, PAR_ID_GFSK_BITRATE, sx1262Instance->gfsk_mod_params.bit_rate, 1500 * 8);
   LOAD_PARAM(GFSK, PAR_ID_GFSK_PACKET_TYPE, sx1262Instance->packet_param.proto.gfsk.packet_type,               GFSK_PACKET_FIXED);
   LOAD_PARAM(GFSK, PAR_ID_WHITENING_INIT_VALUE, sx1262Instance->GfskParam.whitening_init,   DFLT_WHITENING_INIT);
#else
   res = false;
#endif
   return out_res;
}


/* SetPacketParams
 * This command is used to set the parameters of the packet handling block.
 * */
bool sx1262_set_gfsk_packet_params(GfskPacketParam_t *gfsk) {
#ifdef HAS_LOG
    LOG_PARN(GFSK, "SetGfskPacketParams");
#endif
    bool res = false;
    if(gfsk){
        LOG_INFO(GFSK,"SetPackParam PL:%u PDL:%u SWL:%u AC:%u PT:%u PL:%u CT:%u W:%u",
                  gfsk->preamble_length,
                  gfsk->preamble_detector_length,
                  gfsk->syncword_length,
                  gfsk->addr_comp,
                  gfsk->packet_type,
                  gfsk->payload_length ,
                  gfsk->crc_type,
                  gfsk->whitening
                  );
        uint8_t tx_array[9];
        memset(tx_array, 0xFF, sizeof(tx_array));
        uint16_t preamble_length_be = 0;

        preamble_length_be = reverse_byte_order_uint16( gfsk->preamble_length);
        memcpy(tx_array, &preamble_length_be, 2);
        tx_array[2] = gfsk->preamble_detector_length;
        tx_array[3] = gfsk->syncword_length;
        tx_array[4] = gfsk->addr_comp;
        tx_array[5] = gfsk->packet_type;
        tx_array[6] = gfsk->payload_length;
        tx_array[7] = gfsk->crc_type;
        tx_array[8] = gfsk->whitening;
        res = sx1262_send_opcode(OPCODE_SET_PACKET_PARAMS, tx_array, 9, NULL, 0);
    }

    return res;
}

double gfsk_calc_max_frame_tx_time(uint32_t bitrate,
                                   uint16_t n_preamble,
                                   uint8_t sync_word_len,
                                   uint8_t crc_len
                                   ) {
    float t_frame = 0.0f;
    double t_bit = 0.0;
    t_bit = 1.0/((double) bitrate);
    uint16_t frame_len = n_preamble + sync_word_len  + 1 + FIFO_SIZE + crc_len;
    t_frame = ((double)frame_len)*t_bit*8.0;
    return t_frame;
}

uint8_t GfskCrcType2Len(uint8_t code){
    uint8_t len = 0;
    switch (code)    {
    case CRC_OFF:    {
        len = 0;
    }        break;
    case CRC_1BYTE:    {
        len = 1;
    }        break;
    case CRC_2BYTE:    {
        len = 2;
    }        break;
    case CRC_1BYTE_INV:    {
        len = 1;
    }        break;
    case CRC_2BYTE_INV:    {
        len = 2;
    }        break;
    default:    {
        len = 0;
    }        break;
    }
    return len;
}

uint8_t SyncWordLenCode2Len(uint8_t bit_cnt){
    uint8_t len = 0;
    len = Bits2Bytes(bit_cnt);
    return len;
}

bool gfsk_proc_rx_status(GfskRxStatus_t RxStatus){
    bool res = true;
    if(RxStatus.preamble_err){
        LOG_ERROR(GFSK, "PreErr");
        res = false;
    }

    if(RxStatus.sync_err){
        LOG_ERROR(GFSK, "SyncErr");
        res = false;
    }

    if(RxStatus.adrs_err){
        LOG_ERROR(GFSK, "AddrErr");
        res = false;
    }

    if(RxStatus.length_err){
        LOG_ERROR(GFSK, "LenErr");
        res = false;
    }

    if(RxStatus.abort_err){
        LOG_ERROR(GFSK, "AbortErr");
        res = false;
    }

    if(RxStatus.pkt_sent){
        LOG_INFO(GFSK, "PktSent");
    }
    if(RxStatus.pkt_received){
        LOG_INFO(GFSK, "PktRx");
    }
    return res;

}


