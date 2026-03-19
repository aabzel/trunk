#include "mpu_isr.h"

#include "mpu_mcal.h"

bool MpuIntHandler(void) {
    bool res = false;
    MpuHandle_t* Node = MpuGetNode(0);
    if(Node) {
        Node->it_cnt++;
        Node->it_done = true;
        res = true;
        res = mpu_ctrl(0, false);
    }
    return res;
}
