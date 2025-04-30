#include "bluetooth_commands.h"

#include <bluetooth/bluetooth.h>
#include <settings/settings.h>

#include "ble_core.h"
#include "log.h"

bool bluetooth_init_command(int32_t argc, char* argv[]){
    return false;
}

bool bluetooth_unpair_command(int32_t argc, char* argv[]){
    bool res = false;
    LOG_INFO(BLUETOOTH,"Clearing all bonds");
    int ret = bt_unpair(BT_ID_DEFAULT, NULL);
    if (0==ret) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool bluetooth_write_command(int32_t argc, char* argv[]){
    return false;
}

bool bluetooth_read_command(int32_t argc, char* argv[]){
    return false;
}

bool bluetooth_diag_command(int32_t argc, char* argv[]){
    return false;
}

bool bluetooth_scan_command(int32_t argc, char* argv[]){
    return false;
}

bool bluetooth_load_settings_command(int32_t argc, char* argv[]){
    bool res = false;

    LOG_INFO(BLUETOOTH,"SettingsLoad");
    int ret = settings_load();
    if(0==ret){
        res = true;
    }else{
        res = false;
    }
    return res;
}
