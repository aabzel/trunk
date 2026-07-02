#include "ext_int_custom_commands.h"

#include "convert.h"
#include "ext_int_custom_isr.h"
#include "log.h"

bool ext_int_test_isr_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t pin_num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &pin_num);
        log_info_res(EXT_INT, res, "Num");
    }

    if(res) {
        res = EXINTx_IRQHandler(pin_num);
        log_info_res(EXT_INT, res, "EXINTx_IRQHandler");
    }
    return res;
}
