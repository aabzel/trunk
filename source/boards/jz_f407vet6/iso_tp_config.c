#include "iso_tp_config.h"

#include "time_mcal.h"
#include "data_utils.h"
#include "iso_tp_custom.h"
#include "log.h"
#include "iqueue_config.h"

static uint8_t iso_tp_res_to_ret(const bool res) {
    uint8_t ret = 1;
    if(res) {
        ret = 0;
    }
    return ret;
}


void iso_tp1_first_frame_indication(n_ff_indn_t* pFirstFrameInd) {
    LOG_DEBUG(ISO_TP,"ISO_TP1,FirstFrame:%s",IsoTpFirstFrameInfoToStr(pFirstFrameInd));
}

void iso_tp1_error(n_rslt err) {
    LOG_ERROR(ISO_TP,"ISO_TP1,Err:%s",Iso15765retToStr(err));
}

void iso_tp1_rx_done(n_indn_t* in_done){
    LOG_INFO(ISO_TP,"ISO_TP1,%s",Iso15765_n_indn_ToStr(in_done));
}

static uint8_t iso_tp1_send_frame_to_can1(cbus_id_type id_type,
                                uint32_t id,
                                cbus_fr_format fr_format,
                                uint8_t size,
                                uint8_t* data) {

    bool res = iso_tp_can_send_frame(1, id_type, id, fr_format, size,data) ;
    uint8_t ret = iso_tp_res_to_ret(res);
    return ret;
}







/* Callback to assing the Network Layer. This callback
   will be fired when a transmission of a canbus frame is ready.
   Callback to assing the Network Layer. This callback
   will be fired when a transmission of a canbus frame is ready.
   - CANBus Frame ID Type [Standard or Extended]
   - Frame ID
   - Frame Type: [CLASSIC or FD]
   - Frame Data Length
   - Frame Data Array
 */
static uint8_t iso_tp2_send_frame_to_can2(cbus_id_type id_type,
                                uint32_t id,
                                cbus_fr_format fr_format,
                                uint8_t size,
                                uint8_t* data) {

    bool res=iso_tp_can_send_frame(2, id_type, id, fr_format, size,data) ;
    uint8_t ret = iso_tp_res_to_ret(res);
    return ret;
}

void iso_tp2_first_frame_indication(n_ff_indn_t* pFirstFrameInd) {
    LOG_DEBUG(ISO_TP,"ISO_TP1,FirstFrame:%s",IsoTpFirstFrameInfoToStr(pFirstFrameInd));
}

void iso_tp2_rx_done(n_indn_t* in_done){
    LOG_INFO(ISO_TP,"ISO_TP2,%s",Iso15765_n_indn_ToStr(in_done));
}

void iso_tp2_error(n_rslt err) {
    LOG_ERROR(ISO_TP,"ISO_TP2,Err:%s",Iso15765retToStr(err));
}


const IsoTpConfig_t IsoTpConfig[] = {
    { .num = 1,
    .uds_num = 1,
    .addressing = ISO_TP_ADDRESSING_FIXED,
    .valid = true,
    .interface_if = {.interface_name = INTERFACE_NAME_CAN, .num = 1,},
    .my_id = 0xA,
    .name = "ISO_TP1",
    .iqueue_num = IQUEUE_NUN_CAN1,
    .call_back_send_frame = iso_tp1_send_frame_to_can1,
    .call_back_rx_done = iso_tp1_rx_done,
    .call_back_error = iso_tp1_error,
    .call_back_first_frame_indication = iso_tp1_first_frame_indication,
    .block_size = 3,
    .separation_time_s = MSEC_2_SEC( 100),
    },

    { .num = 2,
    .uds_num = 2,
    .addressing = ISO_TP_ADDRESSING_FIXED,
    .valid = true,
    .interface_if = {.interface_name = INTERFACE_NAME_CAN, .num = 2,},
    .my_id = 0xB,
    .name = "ISO_TP2",
    .block_size = 3,
    .separation_time_s = MSEC_2_SEC( 100),
    .iqueue_num = IQUEUE_NUN_CAN2,
    .call_back_send_frame = iso_tp2_send_frame_to_can2,
    .call_back_rx_done = iso_tp2_rx_done,
    .call_back_error = iso_tp2_error,
    .call_back_first_frame_indication = iso_tp2_first_frame_indication,
    },
};

IsoTpHandle_t IsoTpInstance[] = {
    {.num = 1, .valid = true, },
    {.num = 2, .valid = true, },
};


COMPONENT_GET_CNT(IsoTp, iso_tp)



