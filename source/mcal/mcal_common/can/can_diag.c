#include "can_diag.h"

#include <stdio.h>

#include "can_mcal.h"
#include "num_to_str.h"
#include "log.h"

const char* CanFrameTypeToStr(CanTxFrame_t frame_type){
    char* name = "?";
    switch((uint8_t)frame_type){
        case CAN_TX_FRAME_DATA:name = "Dat"; break;
        case CAN_TX_FRAME_REMOTE:name = "Rem"; break;
    }
    return name;
}

const char* CanIdTypeToStr(CanIdentifier_t id_type){
    char* name = "?";
    switch((uint8_t)id_type) {
        case CAN_FRAME_ID_STANDARD:name = "Std"; break;
        case CAN_FRAME_ID_EXTENDED:name = "Ext"; break;
    }
    return name;
}

const char* CanMessage2Str(const CanMessage_t* const Message){
    static char text[80]="";
    if(Message){
        bool res=false;
        char data_text[20]={0};
        if(Message->dlc <=8) {
            res=array2str(Message->data,   Message->dlc,  data_text,   sizeof(data_text));
            if(res) {
                snprintf(text,sizeof(text),"ID:0x%x,DLC:%u,%s,%s,%s",
                        Message->identifier.extended,
                        Message->dlc,
                        CanFrameTypeToStr(Message->frame_type),
                        CanIdTypeToStr(Message->id_type),data_text
                        );
            }

        }
    }
    return text;
}

bool CanDiagNode(CanHandle_t* Node){
    bool res= false;
    if(Node){
        LOG_INFO(CAN,"IsrCnt:%u",Node->isr_cnt);
        LOG_INFO(CAN,"IsrErrCnt:%u",Node->isr_err_cnt);
        LOG_INFO(CAN,"IsrRxCcnt:%u",Node->isr_rx_cnt);
        LOG_INFO(CAN,"IsrTxCnt:%u",Node->isr_tx_cnt);
        LOG_INFO(CAN,"ErrCode:%u",Node->err_code);
        res = true;
    }
    return res;
}


bool can_diag(void ){
    bool res = false;
    uint8_t i=0;
    for(i=0; i<CAN_COUNT; i++) {
        CanHandle_t* Node=CanGetNode(1);
        if(Node){
            res = CanDiagNode(Node);

        }
    }
    return res;
}
