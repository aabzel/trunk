#include "w25q32jv_commands.h"

#include <stdio.h>

#include "convert.h"
#include "log.h"
#include "w25q32jv_drv.h"

#ifdef HAS_SPIFI
#include "spifi_mcal.h"
#endif


bool w25q32jv_reg_read_command(int32_t argc, char* argv[]){
    bool res = false ;

    uint8_t reg_num = 0;

    if(0 <= argc) {
        res = true;
        reg_num = 1;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &reg_num);
        log_res(W25Q32JV,res,"RegCnt");
    }

    if(res) {
        res = false ;
#ifdef HAS_SPIFI

        W25q32jvRegUniversal_t RegUniversal;
        RegUniversal.byte = 0 ;

        W25q32jvOpCodes_t reg_code = w25q32jv_reg_num_to_op_code(reg_num);
        res = spifi_read_reg(0,   reg_code, &RegUniversal.byte);
        log_res(W25Q32JV,res,"ReadReg");
        if(res){
            W25q32jvDiagReg(&RegUniversal,reg_num);
        }
#endif
    }else {
        LOG_ERROR(W25Q32JV, "Usage: w25rr RegNum");
    }

    return res;
}
