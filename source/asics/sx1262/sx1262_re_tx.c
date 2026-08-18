#include "sx1262_re_tx.h"

#include <string.h>

#include "sx1262_drv.h"

bool sx1262_retx_init(void){
    bool res = true;
    memset(Sx1262Instance.ReTxFsm.TxFrame, 0, sizeof(Sx1262Instance.ReTxFsm.TxFrame));
    Sx1262Instance.ReTxFsm.tx_frame_len= 0;
    Sx1262Instance.ReTxFsm.retx_cnt = 0;
    return res;
}

bool sx1216_retx_proc(void){
    bool res = false;
    if(Sx1262Instance.tx_done){
        if(0<Sx1262Instance.ReTxFsm.retx_cnt){
            Sx1262Instance.ReTxFsm.retx_cnt--;
            res= sx1262_start_tx(Sx1262Instance.ReTxFsm.TxFrame, Sx1262Instance.ReTxFsm.tx_frame_len, 0);
        }
    }
    return res;
}

bool sx1262_start_retx(uint8_t* array, uint16_t len, uint8_t try_cnt){
    bool res = false;
    if(len<sizeof(Sx1262Instance.ReTxFsm.TxFrame)){
       Sx1262Instance.ReTxFsm.retx_cnt = try_cnt;
       memcpy(Sx1262Instance.ReTxFsm.TxFrame,array,len);
       Sx1262Instance.ReTxFsm.tx_frame_len= len;

       res = sx1216_retx_proc();
    }
    return res;
}


bool is_sx1262_retx_idle(void){
    bool res = false;
    if(true==Sx1262Instance.tx_done){
       if(0== Sx1262Instance.ReTxFsm.retx_cnt){
           res = true;
       }

    }
    return res;
}



