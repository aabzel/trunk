#include "can_custom_isr.h"

bool CanSwIRQHandler(uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        Node->isr_cnt++;
        Node->isr_err_cnt++;
    }
    return res;
}

bool CanTxIRQHandler(uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        Node->isr_cnt++;
    }
    return res;
}
