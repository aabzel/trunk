#include "iso_tp_config.h"

#include "time_mcal.h"
#include "data_utils.h"
#include "iso_tp_custom.h"
#include "iso_tp_mcal.h"
#include "log.h"
#include "iso_tp_diagnostic.h"
#include "iqueue_config.h"
#include "iso15765_misc.h"

#ifdef HAS_CRC32
#include "crc32.h"
#endif

#ifdef HAS_CAN_SHELL
#include "can_shell_mcal.h"
#endif

static uint8_t IsoTpFiFoMem1[400]={0};
static uint8_t IsoTpFiFoMem2[400]={0};

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
static uint8_t iso_tp1_can1_send_frame(cbus_id_type id_type,
                                      uint32_t id,
                                      cbus_fr_format fr_format,
                                      uint8_t size,
                                      uint8_t* data) {
    bool res = iso_tp_can_send_frame(1, id_type, id, fr_format, size, data);
    n_rslt ret = IsoTpResToRet(res);
    return ret;
}

static uint8_t iso_tp2_can2_send_frame(cbus_id_type id_type,
                                      uint32_t id,
                                      cbus_fr_format fr_format,
                                      uint8_t size,
                                      uint8_t* data) {
    bool res = iso_tp_can_send_frame(2, id_type, id, fr_format, size, data);
    n_rslt ret = IsoTpResToRet(res);
    return ret;
}

/*Rx Done call backs*/
static bool iso_tp_rx_done(uint8_t iso_num, n_indn_t* in_done) {
    bool res = false;
    if(in_done) {
        LOG_DEBUG(ISO_TP, "IsoTP%u,MoveDone:%s", iso_num, Iso15765_n_indn_ToStr(in_done));
        res = iso15765_ret_to_res(in_done->rslt);
        if(res) {
            IsoTpHandle_t *Node = IsoTpGetNode(iso_num);
            if(Node) {
                if(Node->my_id == in_done->n_ai.n_ta) {
                    LOG_INFO(ISO_TP, "IsoTP%u,MyEnvelopRx:%s", iso_num, Iso15765_n_indn_ToStr(in_done));
                    Node->rx_done = true;
#ifdef HAS_CAN_SHELL
                    res = can_shell_iso_tp_rx_data(1, iso_num, in_done->msg, in_done->msg_sz);
#endif

#ifdef HAS_CRC32
                    uint32_t rx_crc32 = crc32_calc(in_done->msg, in_done->msg_sz);
                    LOG_INFO(ISO_TP, "RxCRC32,0x%08X", rx_crc32);
#endif
                    Node->rx_msg_size = in_done->msg_sz;
                    if(in_done->msg_sz <= sizeof(Node->RxData)) {
                        LOG_INFO(ISO_TP, "CopyRxData,Max:%u", sizeof(Node->RxData));
                        memcpy(Node->RxData, in_done->msg, (size_t) in_done->msg_sz);
                        res = true;
                    }
                    Node->in_progress = false;
                }
            }
        } else {
            LOG_ERROR(ISO_TP, "MoveErr,Ret,%u=%s", in_done->rslt, Iso15765retToStr(in_done->rslt));
        }
    }
    return res;
}

/* Indication Callback: Will be fired when a reception is available or an error occured during the reception. */
static void iso_tp1_rx_done(n_indn_t* in_done) {
    iso_tp_rx_done(1, in_done);
}

/* Indication Callback: Will be fired when a reception is available or an error occured during the reception. */
static void iso_tp2_rx_done(n_indn_t* in_done) {
    iso_tp_rx_done(2, in_done);
}


/**/
static bool iso_tp_x_error(uint8_t num, n_rslt err) {
    bool res = false;
    LOG_ERROR(ISO_TP,"IsoTp%u,Err:0x%04x=%s", num, err, Iso15765retToStr(err));
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        Node->in_progress = false;
        Node->error_done = true;
        Node->error_cnt++;
        res = true;
    }
    return res;
}

/* Will be fired in any occured error. */
static void iso_tp1_error(n_rslt err){
    iso_tp_x_error(1,err);
}

/* Will be fired in any occured error. */
static void iso_tp2_error(n_rslt err){
    iso_tp_x_error(2,err);
}

/* First Frame Indication Callback: Will be fired when a FF is received, giving back some useful information */
static bool iso_tpx_first_frame_indication(uint8_t num, n_ff_indn_t* pFirstFrameInd) {
    bool res = false ;
    LOG_NOTICE(ISO_TP,"ISO_TP_%u,RxFirstFrame %s",num, IsoTpFirstFrameInfoToStr(pFirstFrameInd));
    IsoTpHandle_t *Node = IsoTpGetNode(num);
    if(Node) {
        Node->expected_size = pFirstFrameInd->msg_sz ;
        Node->rx_msg_size = 0 ;
        Node->in_progress = true;
        Node->rx_done = false;
        res = true;
    }
    return res;
}

static void iso_tp1_first_frame_indication(n_ff_indn_t* pFirstFrameInd) {
    iso_tpx_first_frame_indication(1, pFirstFrameInd) ;
}

static void iso_tp2_first_frame_indication(n_ff_indn_t* pFirstFrameInd) {
    iso_tpx_first_frame_indication(2, pFirstFrameInd) ;
}

const IsoTpConfig_t SECTION_CFG_DATA IsoTpConfig[] = {
    {
        .addressing = ISO_TP_ADDRESSING_FIXED,
        .block_size = 3,
        .name = "IsoTp1",
        .TxFiFoMem = IsoTpFiFoMem1,
        .tx_fifo_size = sizeof(IsoTpFiFoMem1),
        .num = 1,
        .uds_num = 1,
        .valid = true,
        .my_id = 0xA,
        .call_back_send_frame = iso_tp1_can1_send_frame,
        .call_back_rx_done = iso_tp1_rx_done,
        .call_back_error = iso_tp1_error,
        .call_back_first_frame_indication = iso_tp1_first_frame_indication,
        .interface_if = {.interface_name = INTERFACE_NAME_CAN, .num = 1,},
        .iqueue_num = IQUEUE_NUN_CAN1,
        .separation_time_s = MSEC_2_SEC( 100),
    },

    {
        .addressing = ISO_TP_ADDRESSING_FIXED,
        .block_size = 3,
        .name = "IsoTp2",
        .TxFiFoMem = IsoTpFiFoMem2,
        .tx_fifo_size = sizeof(IsoTpFiFoMem2),
        .num = 2,
        .uds_num = 2,
        .valid = true,
        .my_id = 0xB,
        .call_back_send_frame = iso_tp2_can2_send_frame,
        .call_back_rx_done = iso_tp2_rx_done,
        .call_back_error = iso_tp2_error,
        .call_back_first_frame_indication = iso_tp2_first_frame_indication,
        .interface_if = {.interface_name = INTERFACE_NAME_CAN, .num = 2,},
        .iqueue_num = IQUEUE_NUN_CAN2,
        .separation_time_s = MSEC_2_SEC( 100),
    },
};

IsoTpHandle_t IsoTpInstance[] = {
    {.num = 1, .valid = true, },
    {.num = 2, .valid = true, },
};

COMPONENT_GET_CNT(IsoTp, iso_tp)

