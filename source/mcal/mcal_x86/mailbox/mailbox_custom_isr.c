#include "mailbox_isr.h"

#include <string.h>

#include "bit_utils.h"
#include "gpio_mcal.h"
#include "mailbox_custom_drv.h"
#include "mailbox_mcal.h"
#include "microcontroller_const.h"

bool CoreX_MB_IRQHandler(uint8_t num, uint8_t core_num) {
    bool res = false;
    MailBoxHandle_t* Node = MailBoxGetNode(num);
    if(Node) {
        Node->it_done = true;
        Node->it_cnt++;
        Node->it_core_num = core_num;
        Node->Handle.tStatus.u8CoreIndex = core_num;
        MB_IRQProcess(&(Node->Handle));
        res = true;
    }
    return res;
}

#if 0
bool MailBoxIRQHandler(uint8_t num) {
    bool res = false;
    return res;
}
#endif

/*!< Callback of the request events */
void MailBoxRequestCallback(MB_HandleType* pHandle, MB_ReceiveType* RxNode) {
    PROCESS_UNUSED_VAR(pHandle);
    uint8_t core_my = Cpm_HWA_GetCoreId();
    uint8_t num = core_my + 1;
    MailBoxHandle_t* Node = MailBoxGetNode(num);
    if(Node) {
        Node->Rx.u8Channel = RxNode->u8Channel;
        Node->Rx.u8MasterCoreIndex = RxNode->u8MasterCoreIndex;
        Node->Rx.bSecure = RxNode->bSecure;
        Node->Rx.bSupervisor = RxNode->bSupervisor;
        uint8_t* rx_data = RxNode->aData[0];
        uint32_t size = RxNode->aData[1];
        memcpy(Node->Rx.aData, RxNode->aData, sizeof(uint32_t)*2);
        // Node->Rx.aData[0] = RxNode->aData[0];
        // Node->Rx.aData[1] = RxNode->aData[1];
        bool res = fifo_push_array(&Node->RxFifo, rx_data, size);
        (void) res;
        Node->rx_done = true;
        Node->rx_cnt++;
    }
}

void MailBoxDoneCallBack(MB_HandleType* pHandle, uint32_t channel) {
    MailBoxHandle_t* Node = MailBoxGetNode(1);
    if(Node) {
        Node->done_done = true;
        Node->done_cnt++;
        SET_BIT_NUM(Node->done_flags, channel);
    }
}
