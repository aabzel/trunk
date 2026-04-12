#include "can_call_backs.h"

#include "can_isr.h"
#include "hal_mcal.h"

#ifdef HAS_ISO_TP
#include "iso15765_misc.h"
#include "iso_tp_mcal.h"
#endif

static bool CanRxHeaderTypeToMessage(const uint8_t num, const CAN_RxHeaderTypeDef* const Header,
                                     CanMessage_t* const RxMessage) {
    bool res = true;
    RxMessage->mesg_buff_idx = Header->FilterMatchIndex;
    RxMessage->can_bus_num = num;
    RxMessage->frame_type = CanRTRtoFrameType(Header->RTR);
    RxMessage->id_type = CanIDEtoIdentifierType(Header->IDE);
    RxMessage->size = Header->DLC;
    RxMessage->is_fd = false;
    // RxMessage->time_stamp = Header->Timestamp;
    RxMessage->time_stamp = time_get_ms32();

    switch(Header->IDE) {
    case CAN_ID_STD:
        RxMessage->identifier.standard = Header->StdId;
        break;
    case CAN_ID_EXT:
        RxMessage->identifier.extended = Header->ExtId;
        break;
    default:
        break;
    }

    return res;
}

static bool iso_tp_proc_can_frame(const CanMessage_t* const pRxMessage) {
    bool res = false;
    InterfaceType_t interface_if = {0};
    interface_if.interface_name = INTERFACE_NAME_CAN;
    interface_if.num = pRxMessage->can_bus_num;
    IsoTpHandle_t* IsoTp = IsoTpIfToNode(interface_if);
    if(IsoTp) {
        canbus_frame_t isoTpFrame = {0};
        res = IsoTpCanMessageToBusFrame(pRxMessage, &isoTpFrame);
        if(res) {
            n_rslt rslt = iso15765_enqueue(&IsoTp->instance, &isoTpFrame);
            res = iso15765_ret_to_res(rslt);
        }
    }
    return res;
}

static bool can_rx_frame(CAN_HandleTypeDef* pHcan, uint32_t RxFifo) {
    bool res = false;
    CanHandle_t* Node = CanHandleToNode(pHcan);
    if(Node) {
        CAN_RxHeaderTypeDef msgHeader;
        HAL_StatusTypeDef ret = HAL_CAN_GetRxMessage(pHcan, RxFifo, &msgHeader, Node->RxMessage.data);
        res = HAL_retToRes(ret);
        if(res) {
            can_isr_rx_done_ll(Node);
            Node->RxMessage.can_bus_num = Node->num;
            Node->RxMessage.time_stamp = time_get_ms32();
            res = CanRxHeaderTypeToMessage(Node->num, &msgHeader, &Node->RxMessage);
            Node->unproc_rx_message = true;
#ifdef HAS_ISO_TP
            res = iso_tp_proc_can_frame(&Node->RxMessage);
#endif
        }
    }
    return res;
}

void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef* hcan) {
    can_rx_frame(hcan, CAN_RX_FIFO0);
    CanHandle_t* Node = CanHandleToNode(hcan);
    if(Node) {
        Node->rx_fifo_full_cnt++;
        Node->rx_fifo_full_done = true;
        can_isr_error_ll(Node);
    }
}

void HAL_CAN_RxFifo1FullCallback(CAN_HandleTypeDef* hcan) {
    can_rx_frame(hcan, CAN_RX_FIFO1);
    CanHandle_t* Node = CanHandleToNode(hcan);
    if(Node) {
        Node->rx_fifo_full_cnt++;
        Node->rx_fifo_full_done = true;
        can_isr_error_ll(Node);
    }
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan) { can_rx_frame(hcan, CAN_RX_FIFO0); }

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef* hcan) { can_rx_frame(hcan, CAN_RX_FIFO1); }

void HAL_CAN_ErrorCallback(CAN_HandleTypeDef* hcan) {
    CanHandle_t* Node = CanHandleToNode(hcan);
    if(Node) {
        can_isr_error_ll(Node);
        uint32_t err = HAL_CAN_GetError(hcan);

        if(HAL_CAN_ERROR_TX_TERR0 == (err & HAL_CAN_ERROR_TX_TERR0)) {
            Node->tx_error_cnt++;
        }

        if(HAL_CAN_ERROR_TX_TERR1 == (err & HAL_CAN_ERROR_TX_TERR1)) {
            Node->tx_error_cnt++;
        }

        if(HAL_CAN_ERROR_TX_TERR2 == (err & HAL_CAN_ERROR_TX_TERR2)) {
            Node->tx_error_cnt++;
        }
    }

    HAL_CAN_ResetError(hcan);
}

/* CAN HAL subsystem callbacks */
void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef* hcan) {
    CanHandle_t* Node = CanHandleToNode(hcan);
    if(Node) {
        can_isr_tx_done_ll(Node);
        can_tx_indication(Node);
    }
}

void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef* hcan) {
    CanHandle_t* Node = CanHandleToNode(hcan);
    if(Node) {
        can_isr_tx_done_ll(Node);
        can_tx_indication(Node);
    }
}
void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef* hcan) {
    CanHandle_t* Node = CanHandleToNode(hcan);
    if(Node) {
        can_isr_tx_done_ll(Node);
        can_tx_indication(Node);
    }
}

void HAL_CAN_TxMailbox0AbortCallback(CAN_HandleTypeDef* hcan) {
    CanHandle_t* Node = CanHandleToNode(hcan);
    if(Node) {
        can_isr_error_ll(Node);
    }
}

void HAL_CAN_TxMailbox1AbortCallback(CAN_HandleTypeDef* hcan) {
    CanHandle_t* Node = CanHandleToNode(hcan);
    if(Node) {
        can_isr_error_ll(Node);
    }
}
void HAL_CAN_TxMailbox2AbortCallback(CAN_HandleTypeDef* hcan) {
    CanHandle_t* Node = CanHandleToNode(hcan);
    if(Node) {
        can_isr_error_ll(Node);
    }
}

void HAL_CAN_SleepCallback(CAN_HandleTypeDef* hcan) {
    CanHandle_t* Node = CanHandleToNode(hcan);
    if(Node) {
    }
}
void HAL_CAN_WakeUpFromRxMsgCallback(CAN_HandleTypeDef* hcan) {
    CanHandle_t* Node = CanHandleToNode(hcan);
    if(Node) {
    }
}
