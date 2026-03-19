#include "usb_device_commands.h"

#include "convert.h"
#include "std_includes.h"
#include "usb_device.h"


bool usb_device_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = usb_device_diag();
    return res;
}
