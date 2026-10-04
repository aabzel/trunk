#include "iso_tp_config.h"

#include "time_mcal.h"
#include "data_utils.h"
#include "iso_tp_mcal.h"
#include "log.h"
#include "iqueue_config.h"

#ifdef HAS_ISO_TP_CUSTOM
#include "iso_tp_custom.h"
#include "iso_tp_diagnostic.h"
#include "iso15765_misc.h"
#endif

#ifdef HAS_CLI
#include "cli_drv.h"
#endif

#define ISO_TP_TX_FIFO_SIZE 1024
static uint8_t IsoTp1TxFifo[ISO_TP_TX_FIFO_SIZE]={0};
static uint8_t IsoTp2TxFifo[ISO_TP_TX_FIFO_SIZE]={0};


/* First Frame Indication Callback: Will be fired when a FF is received, giving back some useful information */
static bool iso_tpx_first_frame_indication(uint8_t num, n_ff_indn_t* pFirstFrameInd) {
    bool res = false ;
    LOG_NOTICE(ISO_TP,"ISO_TP_%u,RxFirstFrame %s",num, IsoTpFirstFrameInfoToStr(pFirstFrameInd));
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
                    Node->target_id = in_done->n_ai.n_sa;
                    LOG_INFO(ISO_TP, "IsoTP%u,MyEnvelopRx:%s", iso_num, Iso15765_n_indn_ToStr(in_done));
                    Node->rx_done = true;
#ifdef HAS_CLI
                    cli_process_data(Node->cli_num, in_done->msg, in_done->msg_sz);
#endif
                }
            }
        } else {
            LOG_ERROR(ISO_TP, "MoveErr,Ret,%u=%s", in_done->rslt, Iso15765retToStr(in_done->rslt));
        }
    }
    return res;
}

#ifdef HAS_ISO_TP_CUSTOM
static void iso_tp1_first_frame_indication(n_ff_indn_t* pFirstFrameInd) {
    iso_tpx_first_frame_indication(1, pFirstFrameInd);
}

static void iso_tp1_error(n_rslt err) {
    iso_tp_x_error(1, err);
}

static uint8_t iso_tp1_can1_send_frame(cbus_id_type id_type,
                                       uint32_t id,
                                       cbus_fr_format fr_format,
                                       uint8_t size,
                                       uint8_t* data) {
    bool res = iso_tp_can_send_frame(1, id_type, id, fr_format, size, data);
    uint8_t ret = IsoTpResToRet(res);
    return ret;
}

static void iso_tp1_rx_done(n_indn_t* in_done) {
    iso_tp_rx_done(1, in_done);
}
#endif






#ifdef HAS_ISO_TP_CUSTOM
static void iso_tp2_first_frame_indication(n_ff_indn_t* pFirstFrameInd) {
    iso_tpx_first_frame_indication(2, pFirstFrameInd) ;
}

/* Will be fired in any occured error. */
static void iso_tp2_error(n_rslt err) {
    iso_tp_x_error(2,err);
}

static uint8_t iso_tp2_can2_send_frame(cbus_id_type id_type,
                                       uint32_t id,
                                       cbus_fr_format fr_format,
                                       uint8_t size,
                                       uint8_t* data) {
    bool res = iso_tp_can_send_frame(2, id_type, id, fr_format, size, data);
    uint8_t ret = IsoTpResToRet(res);
    return ret;
}

/* Indication Callback: Will be fired when a reception is available or an error occured during the reception. */
static void iso_tp2_rx_done(n_indn_t* in_done) {
    iso_tp_rx_done(2, in_done);
}
#endif


const IsoTpConfig_t SECTION_CFG_DATA IsoTpConfig[] = {
    {
        .TxFiFoMem = IsoTp1TxFifo,
        .addressing = ISO_TP_ADDRESSING_FIXED,
        .block_size = 3,
        .call_back_error = iso_tp1_error,
        .call_back_first_frame_indication = iso_tp1_first_frame_indication,
        .call_back_rx_done = iso_tp1_rx_done,
        .call_back_send_frame = iso_tp1_can1_send_frame,
        .cli_num = 1,
        .interface_if = {.interface_name = INTERFACE_NAME_CAN, .num = 1,},
        .iqueue_num = IQUEUE_NUN_CAN1,
        .my_id = 0xA,
        .name = "ISO_TP1",
        .num = 1,
        .separation_time_s = MSEC_2_SEC( 100),
        .tx_fifo_size = sizeof(IsoTp1TxFifo),
        .uds_num = 1,
        .valid = true,
#ifdef HAS_ISO_TP_CUSTOM
#endif
    },

    {
        .TxFiFoMem = IsoTp2TxFifo,
        .addressing = ISO_TP_ADDRESSING_FIXED,
        .block_size = 3,
        .cli_num = 1,
        .call_back_error = iso_tp2_error,
        .call_back_first_frame_indication = iso_tp2_first_frame_indication,
        .call_back_rx_done = iso_tp2_rx_done,
        .call_back_send_frame = iso_tp2_can2_send_frame,
        .interface_if = {.interface_name = INTERFACE_NAME_CAN, .num = 2,},
        .iqueue_num = IQUEUE_NUN_CAN2,
        .my_id = 0xB,
        .name = "ISO_TP2",
        .num = 2,
        .separation_time_s = MSEC_2_SEC( 100),
        .tx_fifo_size = sizeof(IsoTp2TxFifo),
        .uds_num = 2,
        .valid = true,
#ifdef HAS_ISO_TP_CUSTOM
#endif
    },
};

IsoTpHandle_t IsoTpInstance[] = {
    {.num = 1, .valid = true, },
    {.num = 2, .valid = true, },
};

COMPONENT_GET_CNT(IsoTp, iso_tp)

