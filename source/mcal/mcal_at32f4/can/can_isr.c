#include "can_isr.h"

bool CanSwIRQHandler(uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        Node->isr_cnt++;
        Node->isr_err_cnt++;
        flag_status ret = 0;

        ret = can_interrupt_flag_get(Node->CANx, CAN_ETR_FLAG);
        if(SET == ret) {
            res = true; // err

            // err_index = Node->CANx->ests & 0x70;
            Node->err_code = Node->CANx->ests_bit.etr; /**/
            can_flag_clear(Node->CANx, CAN_ETR_FLAG);
        }

        ret = can_interrupt_flag_get(Node->CANx, CAN_EAF_FLAG);
        if(SET == ret) {
            res = true;
            can_flag_clear(Node->CANx, CAN_EAF_FLAG);
        }

        ret = can_interrupt_flag_get(Node->CANx, CAN_EPF_FLAG);
        if(SET == ret) {
            res = true;
            can_flag_clear(Node->CANx, CAN_EPF_FLAG);
        }

        ret = can_interrupt_flag_get(Node->CANx, CAN_BOF_FLAG);
        if(SET == ret) {
            res = true;
            can_flag_clear(Node->CANx, CAN_BOF_FLAG);
        }

        ret = can_interrupt_flag_get(Node->CANx, CAN_EOIF_FLAG);
        if(SET == ret) {
            res = true; // err
            can_flag_clear(Node->CANx, CAN_EOIF_FLAG);
        }
    }
    return res;
}

bool CanRxFifoxIRQHandler(uint8_t num, uint32_t can_flag, can_rx_fifo_num_type rx_fifo_num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        Node->isr_cnt++;
        flag_status ret;
        ret = can_interrupt_flag_get(Node->CANx, can_flag);
        if(SET == ret) {
            Node->isr_rx_cnt++;
            can_rx_message_type rx_message_struct = {0};
            can_message_receive(Node->CANx, rx_fifo_num, &rx_message_struct);
            res = CanAt32MsgToCanMsg(&rx_message_struct, &Node->RxMessage);
            Node->unproc_rx_message = true;
        } else {
            CanInfo_t* Info = CanGetInfo(num);
            if(Info) {
                nvic_irq_disable(Info->irqn_rx0);
                nvic_irq_disable(Info->irqn_rx1);
            }
        }
    }
    return res;
}

static bool CanCheckIsrMailBox(CanHandle_t* Node, uint32_t can_flag) {
    bool res = false;
    flag_status ret = 0;
    ret = can_interrupt_flag_get(Node->CANx, can_flag);
    if(SET == ret) {
        Node->isr_tx_cnt++;
        res = true;
        can_flag_clear(Node->CANx, can_flag);
    }
    return res;
}

bool CanTxIRQHandler(uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        Node->isr_cnt++;
        bool res = true;
        res = CanCheckIsrMailBox(Node, CAN_TM0TCF_FLAG) && res;
        res = CanCheckIsrMailBox(Node, CAN_TM1TCF_FLAG) && res;
        res = CanCheckIsrMailBox(Node, CAN_TM2TCF_FLAG) && res;
    }
    return res;
}
