#include "can_custom_isr.h"

#include <string.h>

#include "can_isr.h"
#include "can_mcal.h"

#ifdef HAS_IQUEUE
#include "iqueue.h"
#endif

int32_t canCustomRxHandler(canNode_t* const pNode, FLEXCAN_RxMsgType const* const pRxMsg) {
    int32_t ret = 1;
    if(pNode) {
        pNode->rx_done = true;
        if(pRxMsg) {
            memcpy(&pNode->rxMsg, pRxMsg, sizeof(FLEXCAN_RxMsgType));
            ret = -1;
        }
    }
    return ret;
}

static bool can_is_hand_on(const CanHandle_t* const Node) {
    bool res = false;
    if(0 == Node->CANx->IFLAG1) {
        CanRegERFSR_t ERFSR;
        ERFSR.dword = Node->CANx->ERFSR;
        if(0 == ERFSR.ERFWMI) {
            if(0 == ERFSR.ERFOVF) {
                if(0 == ERFSR.ERFF) {
                    if(0 == ERFSR.ERFDA) {
                        res = true;
                        if(0 == ERFSR.ERFEL) {
                            /*
                             Nothing happened, but an interruption occurred.
                             */
                            res = true;
                        }
                    }
                }
            }
        }
    }

    return res;
}

static bool can_proc_errors(CanHandle_t* const Node) {
    bool res = false;
    Node->ESR1.dword = FLEXCAN_HWA_GetErrorInfo(Node->CANx);

    if(Node->ESR1.BOFFINT) {
        Node->error_bus_off = true;
        Node->error_bus_off_cnt++;
        Node->error = true;
        res = true;
    }

    if(Node->ESR1.ERROVR) {
        Node->error_overrun = true;
        Node->error_overrun_cnt++;
        Node->error = true;
        res = true;
    }

    if(Node->ESR1.ERRINT_FAST) {
        Node->error_data_phase = true;
        Node->error_data_phase_cnt++;
        Node->error = true;
        res = true;
    }

    if(Node->ESR1.BOFFDONEINT) {
        Node->error_bus_off_done = true;
        Node->error_bus_off_done_cnt++;
        Node->error = true;
        res = true;
    }

    if(Node->ESR1.TWRNINT) {
        Node->warning_tx = true;
        Node->warning_tx_cnt++;
        Node->error = true;
        res = true;
    }

    if(Node->ESR1.RWRNINT) {
        Node->warning_rx = true;
        Node->warning_rx_cnt++;
        Node->error = true;
        res = true;
    }

    if(Node->ESR1.ERRINT) {
        Node->error = true;
        Node->error_cnt++;
        res = true;
    }

    if(res) {
        FLEXCAN_HWA_ClrErrorInfo(Node->CANx, Node->ESR1.dword);
    }
    return res;
}

#ifdef HAS_IQUEUE
static bool can_fifo_push_rx_message(const CanHandle_t* const Node) {
    bool res = false;
    InterfaceType_t Interface = {
        .interface_name = INTERFACE_NAME_CAN,
        .num = Node->num,
    };
    iQueueHandle_t* iQueue = iQueueInterfaceToNode(Interface);
    if(iQueue) {
        i_status ret = iqueue_enqueue(iQueue->pHandle, (void*)&Node->RxMessage);
        res = iqueue_ret_res(ret);
    }
    return res;
}
#endif

static bool CANx_IRQHandler(const uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        can_isr_ll(Node);
        res = can_is_hand_on(Node);
        if(res) {
            res = can_interrupt_ctrl(num, false);
        }

        if(Node->pCanNode->hcan) {
            //  FLEXCAN_HandleType *hcan = pNode->hcan;
            FLEXCAN_InterruptProcess(Node->pCanNode->hcan);
            Node->ESR1.dword = Node->CANx->ESR1;
            Node->ESR2.dword = Node->CANx->ESR2;

            if(Node->pCanNode->rx_done) {
                // res= CanMsgToMessage(num, Node->pCanNode->hcan->tSettings.pRxBuf, &Node->RxMessage);
                res = CanMsgToMessage(num, &Node->pCanNode->rxMsg, &Node->RxMessage);
#ifdef HAS_IQUEUE
                res = can_fifo_push_rx_message(Node);
#endif

                Node->rx_done = true;
                Node->rx_cnt++;
                Node->pCanNode->rx_done = false;
                Node->unproc_rx_message = true;
            }

            if(Node->pCanNode->tx_done) {
                Node->tx_done = true;
                Node->tx_cnt++;
                Node->pCanNode->tx_done = false;
            }
        }
        can_proc_errors(Node);
    }
    return res;
}

void CAN0_IRQHandler(void) { CANx_IRQHandler(0); }
void CAN1_IRQHandler(void) { CANx_IRQHandler(1); }
void CAN2_IRQHandler(void) { CANx_IRQHandler(2); }
void CAN3_IRQHandler(void) { CANx_IRQHandler(3); }
void CAN4_IRQHandler(void) { CANx_IRQHandler(4); }
void CAN5_IRQHandler(void) { CANx_IRQHandler(5); }
void CAN6_IRQHandler(void) { CANx_IRQHandler(6); }
void CAN7_IRQHandler(void) { CANx_IRQHandler(7); }
void CAN8_IRQHandler(void) { CANx_IRQHandler(8); }
void CAN9_IRQHandler(void) { CANx_IRQHandler(9); }
