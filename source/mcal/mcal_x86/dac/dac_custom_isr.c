#include "dac_custom_isr.h"

#include "dac_mcal.h"

bool DacIRQHandler(uint8_t num) {
    bool res = false;
    DacHandle_t* Node = DacGetNode(num);
    if(Node) {
        Node->it_cnt++;
        res = true;
    }
    return res;
}
