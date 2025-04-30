#include "w25q32jv_diag.h"

#include <stdio.h>

#include "debug_info.h"
#include "convert.h"
#include "log.h"
#include "common_diag.h"
#include "w25q32jv_drv.h"
#include "none_blocking_pause.h"
#include "table_utils.h"
#include "writer_config.h"
#include "num_to_str.h"

bool W25q32jvDiagRegStatus1( const W25q32jvRegStatus_t* const Reg) {
	bool res = false ;
    if(Reg) {
        LOG_WARNING(W25Q32JV, "Status1 0x%x=%s", Reg->byte, utoa_bin8(Reg->byte));
        LOG_INFO(W25Q32JV, "busy:%u", Reg->busy );
        LOG_INFO(W25Q32JV, "wel:%u", Reg->wel );
        LOG_INFO(W25Q32JV, "bp:%u", Reg->bp);
        LOG_INFO(W25Q32JV, "tb:%u", Reg->tb );
        LOG_INFO(W25Q32JV, "sec:%u", Reg->sec);
        LOG_INFO(W25Q32JV, "srp:%u", Reg->srp);
        res = true;
    }
    return res;
}


bool W25q32jvDiagRegStatus2( const W25q32jvRegStatus2_t* const Reg){
	bool res = false ;
    if(Reg) {
        LOG_WARNING(W25Q32JV, "Status2 0x%x=%s", Reg->byte, utoa_bin8(Reg->byte));
        LOG_INFO(W25Q32JV, "srl:%u", Reg->srl );
        LOG_INFO(W25Q32JV, "qe:%u", Reg->qe );
        LOG_INFO(W25Q32JV, "lb:%u", Reg->lb );
        LOG_INFO(W25Q32JV, "cmp:%u", Reg->cmp);
        LOG_INFO(W25Q32JV, "sus:%u", Reg->sus);
        res = true;
    }
    return res;
}

bool W25q32jvDiagRegStatus3( const W25q32jvRegStatus3_t* const Reg){
	bool res = false ;
    if(Reg) {
        LOG_WARNING(W25Q32JV, "Status3 0x%x=%s", Reg->byte, utoa_bin8(Reg->byte));
        LOG_INFO(W25Q32JV, "wps:%u", Reg->wps );
        LOG_INFO(W25Q32JV, "drv:%u", Reg->drv );
        res = true;
    }
    return res;
}





bool W25q32jvDiagReg( const  W25q32jvRegUniversal_t* const  Node, uint8_t reg_num) {
	bool res = false ;
    switch(reg_num) {
        case 1: res= W25q32jvDiagRegStatus1(  &Node->Status1); break;
        case 2: res= W25q32jvDiagRegStatus2(  &Node->Status2); break;
        case 3: res= W25q32jvDiagRegStatus3(  &Node->Status3); break;
        default: break;
    }
    return res;
}
