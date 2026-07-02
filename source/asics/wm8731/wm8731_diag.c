#include "wm8731_diag.h"

#include <stdio.h>
#include <string.h>

#include "wm8731_const.h"

const char* Wm8731I2sBusRole2Str(uint8_t bus_role) {
    const char* name = "?";
    switch(bus_role) {
    case BUS_MODE_SLAVE:
        name = "Slave";
        break;
    case BUS_MODE_MASTER:
        name = "Master";
        break;
    }
    return name;
}

const char* Wm8731NodeToStr(const Wm8731Handle_t* const Node) {
    static char name[100] = "";
    if(Node) {
        strcpy(name, "Node:");
        snprintf(name, sizeof(name), "%sN:%u,", name, Node->num);
        snprintf(name, sizeof(name), "%sVolume:%d dB,", name, Node->cur_volume);
        snprintf(name, sizeof(name), "%sState:%u,", name, Node->state);
        snprintf(name, sizeof(name), "%sRecOffTs:%u ms,", name, Node->rec_off_time_stamp_ms);
        snprintf(name, sizeof(name), "%sPlayOffTs:%u ms,", name, Node->play_off_time_stamp_ms);
        snprintf(name, sizeof(name), "%sInit:%u", name, Node->init);
    }
    return name;
}

const char* Wm8731ConfigToStr(const Wm8731Config_t* const Config) {
    static char name[250] = "";
    if(Config) {
        strcpy(name, "CFG:");
        snprintf(name, sizeof(name), "%sN:%u,", name, Config->num);
        snprintf(name, sizeof(name), "%sAddr:0x%02x", name, Config->chip_addr);
        snprintf(name, sizeof(name), "%sI2C:%u,", name, Config->i2c_num);
        snprintf(name, sizeof(name), "%sRegCnt:%u,", name, Config->reg_cnt);
        snprintf(name, sizeof(name), "%sI2Srx:%u,", name, Config->i2s_rx_num);
        snprintf(name, sizeof(name), "%sI2Stx:%u,", name, Config->i2s_tx_num);
        snprintf(name, sizeof(name), "%sRegs:%p,", name, Config->RegArray);
        snprintf(name, sizeof(name), "%sLeft:%d", name, Config->left);
        snprintf(name, sizeof(name), "%sRight:%d", name, Config->right);
        snprintf(name, sizeof(name), "%sName:%s", name, Config->name);
    }
    return name;
}
