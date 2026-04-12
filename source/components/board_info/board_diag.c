#include "board_diag.h"

#include <stdio.h>
#include <string.h>

#include "board_config.h"
#include "board_info.h"
#include "gpio_diag.h"

char* Connector2Str(ConnectorPin_t conn) {
    static char temp[10] = "??";
    snprintf(temp, sizeof(temp), "%s%u.%u", conn.designator, conn.num, conn.pin);
    return temp;
}

char* Pad2ConnectorPin(Pad_t pad) {
    char* conn_name = "??";
    const Wire_t* WireNode = Pad2WireInfio(pad);
    if(WireNode) {
        conn_name = Connector2Str(WireNode->conn);
    }
    return conn_name;
}

const char* Pad2ValidWireName(Pad_t pad) {
    const char* wire_name = "??";
    const Wire_t* WireNode = Pad2WireInfio(pad);
    if(WireNode) {
        int ret = strcmp(SPARE_WIRE_NAME, WireNode->wire_name);
        if(0 == ret) {
            wire_name = GpioPad2WireName(pad.byte);
        } else {
            wire_name = WireNode->wire_name;
        }
    }
    return wire_name;
}

const char* Pad2SilkName(Pad_t pad) {
    const char* silk_name = "??";
    const Wire_t* WireNode = Pad2WireInfio(pad);
    if(WireNode) {
        silk_name = WireNode->silk;
    }
    return silk_name;
}

const char* Conn2ValidWireName(ConnectorPin_t conn) {
    const char* wire_name = "??";
    const Wire_t* WireNode = Conn2WireInfio(conn);
    if(WireNode) {
        int ret = strcmp(SPARE_WIRE_NAME, WireNode->wire_name);
        if(0 == ret) {
            wire_name = GpioPad2WireName(WireNode->pad.byte);
        } else {
            wire_name = WireNode->wire_name;
        }
    }
    return wire_name;
}
