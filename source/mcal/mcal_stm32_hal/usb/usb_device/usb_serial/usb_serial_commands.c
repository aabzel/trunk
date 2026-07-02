#include "usb_serial_commands.h"

#include <string.h>

#include "array_diag.h"
#include "convert.h"
#include "log.h"
#include "usb_serial.h"
#include "usb_serial_diag.h"

bool usb_serial_diag_command(int32_t argc, char* argv[]) {
    bool res;
    res = usb_serial_diag();
    log_info_res(USB_SERIAL, res, "Diag");
    return res;
}

/*
uss 1 hei!

 */
bool usb_serial_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t endline_type = 0;
    uint8_t data[256] = {0};
    uint32_t size = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(USB_SERIAL, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], data, sizeof(data), &size);
        if(false == res) {
            LOG_WARNING(USB_SERIAL, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)data, sizeof(data), "%s", argv[1]);
            size = strlen(argv[1]);
            res = true;
        } else {
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &endline_type);
        log_info_res(USB_SERIAL, res, "EndOfLine");
    }

    if(res) {
        res = usb_serial_send(num, data, size);

        memset(data, 0, sizeof(data));
        snprintf((char*)data, sizeof(data), "%s", LogEndOfLineToStr((LogEndOfLine_t)endline_type));
        size = strlen((char*)data);
        res = usb_serial_send(num, data, size);

        log_info_res(USB_SERIAL, res, "Send");
        if(res) {
#ifdef HAS_ARRAY_DIAG
            print_hex(data, size);
#endif
            LOG_INFO(USB_SERIAL, "UART%u,SendOk,%u byte", num, size);
            cli_printf(CRLF);
        }
    } else {
        LOG_ERROR(USB_SERIAL, "Usage: uss Num hex_string EndOfLine");
    }
    return res;
}
