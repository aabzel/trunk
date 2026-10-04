#include "iso_tp_config.h"

#include "data_utils.h"
#include "time_mcal.h"
#include "iso_tp_mcal.h"
#include "array_diag.h"
#include "log.h"
#include "iso_tp_diagnostic.h"
#include "iqueue_config.h"
#include "iso15765_misc.h"

#ifdef HAS_ISO_TP_CUSTOM
#include "iso_tp_custom.h"
#endif

#ifdef HAS_CRC32
#include "crc32.h"
#endif

#ifdef HAS_CAN_SHELL
#include "can_shell_mcal.h"
#endif

static uint8_t IsoTpFiFoMem1[1024]={0};

/* First Frame Indication Callback: Will be fired when a FF is received, giving back some useful information */
static bool iso_tpx_first_frame_indication(uint8_t num, n_ff_indn_t* pFirstFrameInd) {
    bool res = false ;
    LOG_DEBUG(ISO_TP,"IsoTp%u,RxFirstFrame:%s",num, IsoTpFirstFrameInfoToStr(pFirstFrameInd));
    IsoTpHandle_t *Node = IsoTpGetNode(num);
    if(Node) {
        Node->target_id = pFirstFrameInd->n_ai.n_sa;
        Node->expected_size = pFirstFrameInd->msg_sz ;
        Node->rx_msg_size = 0 ;
        Node->in_progress = true;
        Node->rx_done = false;
        res = true;
    }
    return res;
}

static bool iso_tp_x_error(uint8_t num, n_rslt err) {
    bool res = false;
    LOG_ERROR(ISO_TP, "ISO_TP_%u,Err:0x%04x=%s", num, err, Iso15765retToStr(err));
    IsoTpHandle_t *Node = IsoTpGetNode(num);
    if (Node) {
        Node->in_progress = false;
        Node->error_done = true;
        Node->error_cnt++;
        res = true;
    }
    return res;
}

static bool iso_tp_rx_done(uint8_t iso_num, n_indn_t *in_done) {
    bool res = false;
    if (in_done) {
        LOG_INFO(ISO_TP, "IsoTp%u,MoveDone:[%s]", iso_num, Iso15765_n_indn_ToStr(in_done));
        res = iso15765_ret_to_res(in_done->rslt);
        if (res) {
            IsoTpHandle_t *Node = IsoTpGetNode(iso_num);
            if (Node) {
                Node->target_id = in_done->n_ai.n_sa;
                Node->rx_done = true;
#ifdef HAS_CAN_SHELL
                res = can_shell_iso_tp_rx_data(1, iso_num, in_done->msg, in_done->msg_sz);
#endif
                memset(in_done->msg,0,sizeof(in_done->msg));
            }
        } else {
            LOG_ERROR(ISO_TP, "MoveErr,Ret,%u=%s", in_done->rslt, Iso15765retToStr(in_done->rslt));
        }
    }
    return res;
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
static uint8_t iso_tp1_can0_send_frame(cbus_id_type id_type,
                                      uint32_t id,
                                      cbus_fr_format fr_format,
                                      uint8_t size,
                                      uint8_t* data) {
    bool res = iso_tp_can_send_frame(0, id_type, id, fr_format, size, data);
    n_rslt ret = IsoTpResToRet(res);
    return ret;
}

#if 0
static uint8_t iso_tp_send_frame_to_iso_tpX(uint32_t iso_tp_dist, cbus_id_type id_type,
                                      uint32_t id,
                                      cbus_fr_format fr_format,
                                      uint8_t size,
                                      uint8_t* data) {
    n_rslt ret = N_ERROR;
    LOG_DEBUG(ISO_TP, "ISO_TP_%u,Rx,ID:0x%08x,Data:%s",iso_tp_dist,id,ArrayToStr(data,size));
    IsoTpHandle_t* Node = IsoTpGetNode(iso_tp_dist);
    if(Node) {
        bool res = iso_tp_is_my_id(  id, Node);
        if(res) {
            canbus_frame_t RxFrame = {0};
            RxFrame.id = id;               /* CAN Frame Id */
            RxFrame.id_type = id_type;     /* CAN Frame Id Type `cbus_id_type` */
            RxFrame.fr_format = fr_format; /* CAN Frame Format `cbus_fr_format` */
            RxFrame.dlc = size;            /* Size of data */
            if( size <= sizeof( RxFrame.dt) ) {
                memcpy(RxFrame.dt, data, size); /* Actual data of the frame */
                LOG_DEBUG(ISO_TP, "ISO_TP_%u,RxFrame:%s",iso_tp_dist,Iso15765CanBusFrameToStr(&RxFrame));
                ret = iso15765_enqueue(&Node->instance, &RxFrame);
            }
        }
    }

    return ret;
}
#endif

#if 0
static uint8_t iso_tp2_send_frame_to_iso_tp3(cbus_id_type id_type,
                                             uint32_t id,
                                             cbus_fr_format fr_format,
                                             uint8_t size,
                                             uint8_t* data) {
    uint8_t ret = iso_tp_send_frame_to_iso_tpX(3, id_type,id,fr_format,size,data);
    return ret;
}

static uint8_t iso_tp3_send_frame_to_iso_tp2(cbus_id_type id_type,
                                             uint32_t id,
                                             cbus_fr_format fr_format,
                                             uint8_t size,
                                             uint8_t* data) {
    uint8_t ret = iso_tp_send_frame_to_iso_tpX(2, id_type, id, fr_format, size, data);
    return ret;
}
#endif


/* Indication Callback: Will be fired when a reception is available or an error occured during the reception. */
static void iso_tp1_rx_done(n_indn_t* in_done) {
    iso_tp_rx_done(1, in_done);
}


#if 0
static void iso_tp2_rx_done(n_indn_t* in_done) {
    iso_tp_rx_done(2, in_done);
}

static void iso_tp3_rx_done(n_indn_t* in_done) {
    iso_tp_rx_done(3, in_done);
}
#endif

/* Will be fired in any occured error. */
static void iso_tp1_error(n_rslt err){
    iso_tp_x_error(1,err);
}

#if 0
static void iso_tp2_error(n_rslt err){
    iso_tp_x_error(2,err);
}

static void iso_tp3_error(n_rslt err){
    iso_tp_x_error(3,err);
}
#endif


static void iso_tp1_first_frame_indication(n_ff_indn_t* pFirstFrameInd) {
    iso_tpx_first_frame_indication(1, pFirstFrameInd) ;
}

#if 0
static void iso_tp2_first_frame_indication(n_ff_indn_t* pFirstFrameInd) {
    iso_tpx_first_frame_indication(2, pFirstFrameInd) ;
}

static void iso_tp3_first_frame_indication(n_ff_indn_t* pFirstFrameInd) {
    iso_tpx_first_frame_indication(3, pFirstFrameInd) ;
}
#endif

const IsoTpConfig_t IsoTpConfig[] = {
#ifdef HAS_CAN0
    {
        .addressing = ISO_TP_ADDRESSING_FIXED,
        .block_size = 3,
        .name = "IsoTp1",
        .TxFiFoMem = IsoTpFiFoMem1,
        .tx_fifo_size = sizeof(IsoTpFiFoMem1),
        .num = 1,
        .valid = true,
        .my_id = 0xE,
        .call_back_send_frame = iso_tp1_can0_send_frame,
        .call_back_rx_done = iso_tp1_rx_done,
        .call_back_error = iso_tp1_error,
        .call_back_first_frame_indication = iso_tp1_first_frame_indication,
        .interface_if = { .interface_name = INTERFACE_NAME_CAN, .num = 0, }  ,
        .iqueue_num = IQUEUE_NUN_CAN_FRAME_1,
        .separation_time_s = MSEC_2_SEC(50),
        .uds_num = 1,
    },
#endif

#if 0
    {
        .addressing = ISO_TP_ADDRESSING_FIXED,
        .block_size = 3,
        .name = "IsoTp2",
        .num = 2,
        .TxFiFoMem = IsoTpFiFoMem2,
        .tx_fifo_size = sizeof(IsoTpFiFoMem2),
        .valid = true,
        .my_id = 0xB,
        .call_back_send_frame = iso_tp2_send_frame_to_iso_tp3,
        .call_back_rx_done = iso_tp2_rx_done,
        .call_back_error = iso_tp2_error,
        .call_back_first_frame_indication = iso_tp2_first_frame_indication,
        .interface_if = {.interface_name = INTERFACE_NAME_ISO_TP, .num = 3,}  ,
        .iqueue_num = IQUEUE_NUN_CAN_FRAME_2,
        .separation_time_s = MSEC_2_SEC(10),
        .uds_num = 2,
    },

    {
        .addressing = ISO_TP_ADDRESSING_FIXED,
        .name = "IsoTp3",
        .num = 3,
        .TxFiFoMem = IsoTpFiFoMem3,
        .tx_fifo_size = sizeof(IsoTpFiFoMem3),
        .valid = true,
        .my_id = 0xC,
        .block_size = 3,
        .call_back_send_frame = iso_tp3_send_frame_to_iso_tp2,
        .call_back_rx_done = iso_tp3_rx_done,
        .call_back_error = iso_tp3_error,
        .call_back_first_frame_indication = iso_tp3_first_frame_indication,
        .interface_if = { .interface_name = INTERFACE_NAME_ISO_TP, .num=2, }  ,
        .iqueue_num = IQUEUE_NUN_CAN_FRAME_3,
        .separation_time_s = MSEC_2_SEC(10),
        .uds_num = 3,
    },
#endif
};

IsoTpHandle_t IsoTpInstance[]={
#ifdef HAS_CAN0
    {.num = 1, .valid = true, },
#endif

#if 0
    {.num = 2, .valid = true, },
    {.num = 3, .valid = true, },
#endif
};

COMPONENT_GET_CNT(IsoTp, iso_tp)
