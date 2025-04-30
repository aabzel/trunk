#include "ext_int_isr.h"

bool ExtIntRisingCallBack(ExtIntHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->rising_cnt++;
        Node->rising_done = true;
        res = true;
    }
    return res;
}

bool ExtIntFallingCallBack(ExtIntHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->falling_cnt++;
        Node->falling_done = true;
        res = true;
    }
    return res;
}
