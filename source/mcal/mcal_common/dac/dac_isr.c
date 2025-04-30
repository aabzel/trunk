#include "dac_isr.h"

#include <string.h>

/*tx*/

bool DacTxCpltCallBack(DacHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->tx_cnt++;
        Node->tx_done = true;
        res = true;
    }
    return res;
}


/*Err*/

bool DacErrorCallBack(DacHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->error_cnt++;
        res = true;
    }
    return res;
}


