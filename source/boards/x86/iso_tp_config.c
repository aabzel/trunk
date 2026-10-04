#include "iso_tp_config.h"

#include "crc32.h"
#include "data_utils.h"
#include "time_mcal.h"
#include "iso_tp_mcal.h"
#include "array_diag.h"
#include "log.h"

#ifdef HAS_IQUEUE
#include "iqueue_config.h"
#endif

#ifdef HAS_ISO_TP_CUSTOM
#include "iso_tp_diagnostic.h"
#include "iso_tp_custom.h"
#endif

#ifdef HAS_ISO_TP_CUSTOM
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
#endif

#ifdef HAS_ISO_TP_CUSTOM
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

#ifdef HAS_ISO_TP_CUSTOM
static uint8_t iso_tp2_send_frame_to_iso_tp3(cbus_id_type id_type,
                                             uint32_t id,
                                             cbus_fr_format fr_format,
                                             uint8_t size,
                                             uint8_t* data) {
    uint8_t ret = iso_tp_send_frame_to_iso_tpX(3, id_type,id,fr_format,size,data);
    return ret;
}
#endif


#ifdef HAS_ISO_TP_CUSTOM
static uint8_t iso_tp3_send_frame_to_iso_tp2(cbus_id_type id_type,
                                             uint32_t id,
                                             cbus_fr_format fr_format,
                                             uint8_t size,
                                             uint8_t* data) {
    uint8_t ret = iso_tp_send_frame_to_iso_tpX(2, id_type, id, fr_format, size, data);
    return ret;
}
#endif


#ifdef HAS_ISO_TP_CUSTOM
/*Rx Done call backs*/
static bool iso_tp_rx_done(uint8_t num, n_indn_t* in_done) {
    bool res = false ;
    if(in_done) {
        LOG_INFO(ISO_TP, "ISO_TP_%u,ReceptionAvailable:%s",num, Iso15765_n_indn_ToStr(in_done));
        IsoTpHandle_t *Node = IsoTpGetNode(num);
        if(Node) {
            Node->rx_done = true;
            uint32_t rx_crc32 = crc32_calc(in_done->msg, in_done->msg_sz);
            LOG_INFO(ISO_TP, "RxCRC32,0x%08X", rx_crc32);
            Node->rx_msg_size = in_done->msg_sz;
            if(in_done->msg_sz <= sizeof(Node->RxData)) {
                LOG_INFO(ISO_TP, "CopyRxData,Max:%u",sizeof(Node->RxData));
                memcpy(Node->RxData, in_done->msg, (size_t) in_done->msg_sz);
                res = true;
            }
            Node->in_progress = false;
        }
    }
    return res;
}
#endif

#ifdef HAS_ISO_TP_CUSTOM
/* Indication Callback: Will be fired when a reception is available or an error occured during the reception. */
static void iso_tp1_rx_done(n_indn_t* in_done) {
    iso_tp_rx_done(1, in_done);
}

static void iso_tp2_rx_done(n_indn_t* in_done) {
    iso_tp_rx_done(2, in_done);
}

static void iso_tp3_rx_done(n_indn_t* in_done) {
    iso_tp_rx_done(3, in_done);
}
#endif

#ifdef HAS_ISO_TP_CUSTOM
/**/
static bool iso_tp_x_error(uint8_t num,n_rslt err) {
    bool res = false ;
    LOG_ERROR(ISO_TP,"ISO_TP_%u,Err:0x%04x=%s", num, err, Iso15765retToStr(err));
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        Node->in_progress = false;
        Node->error_done = true;
        Node->error_cnt++;
        res = true;
    }
    return res;
}
#endif

#ifdef HAS_ISO_TP_CUSTOM
/* Will be fired in any occured error. */
static void iso_tp1_error(n_rslt err){
    iso_tp_x_error(1,err);
}

static void iso_tp2_error(n_rslt err){
    iso_tp_x_error(2,err);
}

static void iso_tp3_error(n_rslt err){
    iso_tp_x_error(3,err);
}
#endif

#ifdef HAS_ISO_TP_CUSTOM
/* First Frame Indication Callback: Will be fired when a FF is received, giving back some useful information */
static bool iso_tpx_first_frame_indication(uint8_t num, n_ff_indn_t* pFirstFrameInd) {
    bool res = false ;
    LOG_INFO(ISO_TP,"ISO_TP_%u,RxFirstFrame %s",num, IsoTpFirstFrameInfoToStr(pFirstFrameInd));
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
#endif

#ifdef HAS_ISO_TP_CUSTOM
static void iso_tp1_first_frame_indication(n_ff_indn_t* pFirstFrameInd) {
    iso_tpx_first_frame_indication(1, pFirstFrameInd) ;
}

static void iso_tp2_first_frame_indication(n_ff_indn_t* pFirstFrameInd) {
    iso_tpx_first_frame_indication(2, pFirstFrameInd) ;
}

static void iso_tp3_first_frame_indication(n_ff_indn_t* pFirstFrameInd) {
    iso_tpx_first_frame_indication(3, pFirstFrameInd) ;
}
#endif

const IsoTpConfig_t IsoTpConfig[] = {
    {
    .addressing = ISO_TP_ADDRESSING_FIXED,
    .block_size = 3,
    .name = "IsoTp1",
    .num = 1,
    .valid = true,
    .my_id = 0xA,
#ifdef HAS_ISO_TP_CUSTOM
    .call_back_send_frame = iso_tp1_can0_send_frame,
    .call_back_rx_done = iso_tp1_rx_done,
    .call_back_error = iso_tp1_error,
    .call_back_first_frame_indication = iso_tp1_first_frame_indication,
#endif
    .separation_time_s = MSEC_2_SEC(10),
#ifdef HAS_CAN0
    .interface_if = {.interface_name=INTERFACE_NAME_CAN, .num=0,}  ,
#endif

#ifdef HAS_IQUEUE
    .iqueue_num = IQUEUE_NUN_CAN_FRAME_1,
#endif
    .uds_num = 1,
    },

    {
    .addressing = ISO_TP_ADDRESSING_FIXED,
    .block_size = 3,
    .num = 2,
    .valid = true,
    .my_id = 0xB,
#ifdef HAS_ISO_TP_CUSTOM
    .call_back_send_frame = iso_tp2_send_frame_to_iso_tp3,
    .call_back_rx_done = iso_tp2_rx_done,
    .call_back_error = iso_tp2_error,
    .call_back_first_frame_indication = iso_tp2_first_frame_indication,
#endif
    .separation_time_s = MSEC_2_SEC(10),
    .interface_if = {.interface_name = INTERFACE_NAME_ISO_TP, .num = 3,}  ,
#ifdef HAS_IQUEUE
    .iqueue_num = IQUEUE_NUN_CAN_FRAME_2,
#endif
    .name = "IsoTp2",
    .uds_num = 2,
    },

    {
    .addressing = ISO_TP_ADDRESSING_FIXED,
    .num = 3,
    .valid = true,
    .my_id = 0xC,
    .block_size = 3,
#ifdef HAS_ISO_TP_CUSTOM
    .call_back_send_frame = iso_tp3_send_frame_to_iso_tp2,
    .call_back_rx_done = iso_tp3_rx_done,
    .call_back_error = iso_tp3_error,
    .call_back_first_frame_indication = iso_tp3_first_frame_indication,
#endif
    .separation_time_s = MSEC_2_SEC(10),
    .interface_if = { .interface_name = INTERFACE_NAME_ISO_TP, .num=2, }  ,
#ifdef HAS_IQUEUE
    .iqueue_num = IQUEUE_NUN_CAN_FRAME_3,
#endif
    .name = "IsoTp3",
    .uds_num = 3,
    },
};

IsoTpHandle_t IsoTpInstance[]={
#ifdef HAS_CAN0
    {.num = 1, .valid = true, },
#endif
    {.num = 2, .valid = true, },
    {.num = 3, .valid = true, },
};

COMPONENT_GET_CNT(IsoTp, iso_tp)
