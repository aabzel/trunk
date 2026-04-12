#include "usb_commands.h"

#include "convert.h"
#include "log.h"
#include "usb_mcal.h"

bool usb_re_plug_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(USB, res, "Num");
    }

    if(res) {
        res = usb_re_plug(num);
        log_info_res(USB, res, "RePlug");
    } else {
        LOG_ERROR(UART, "Usage: urp Num");
    }
    return res;
}
