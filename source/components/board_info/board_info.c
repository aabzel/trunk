#include "board_info.h"

#include <string.h>

#include "board_config.h"

bool connectors_is_equal(const ConnectorPin_t* const conn1,
                         const ConnectorPin_t* const conn2) {
    bool res = false;
    if(conn1->pin == conn2->pin) {
        if(conn1->num == conn2->num) {
            int ret = strcmp(conn1->designator, conn2->designator);
            if(0 == ret) {
                res = true;
            }
        }
    }
    return res;
}

const Wire_t* Pad2WireInfio(Pad_t pad) {
    const Wire_t* WireNode = NULL;
    uint32_t i = 0;
    uint32_t cnt = wires_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(Wires[i].pad.byte == pad.byte) {
            WireNode = &Wires[i];
            break;
        }
    }
    return WireNode;
}

const Wire_t* Conn2WireInfio(ConnectorPin_t conn) {
    const Wire_t* WireNode = NULL;
    uint32_t i = 0;
    uint32_t cnt = wires_get_cnt();
    for(i = 0; i < cnt; i++) {
        bool res = connectors_is_equal(&Wires[i].conn, &conn);
        if(res) {
            WireNode = &Wires[i];
            break;
        }
    }
    return WireNode;
}

const WirePin_t* Conn2WirePinInfio(ConnectorPin_t conn, WirePin_t* WireList, uint32_t cnt) {
    const WirePin_t* WireNode = NULL;
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        bool res = connectors_is_equal(&WireList[i].conn, &conn);
        if(res) {
            WireNode = &WireList[i];
            break;
        }
    }
    return WireNode;
}
