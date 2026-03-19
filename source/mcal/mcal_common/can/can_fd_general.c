#include "can_fd_mcal.h"

#include <stdio.h>

#include "compiler_const.h"
#include "can_mcal.h"
#include "log.h"
#include "array.h"

_WEAK_FUN_
bool can_filter_allow_id(uint8_t num, const uint32_t id) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool can_filter_ban_id(uint8_t num, const uint32_t id) {
    bool res = false;
    return res;
}

_WEAK_FUN_ bool can_fd_baudrate_set(uint8_t num, uint32_t bit_rate) {
    bool res = false;
    return res;
}

_WEAK_FUN_ bool can_fd_baudrate_get(uint8_t num, uint32_t* const bit_rate) {
    bool res = false;
    return res;
}

_WEAK_FUN_ bool can_fd_rec_get(uint8_t num, uint32_t* const rec) {
    bool res = false;
    return res;
}

_WEAK_FUN_ bool can_fd_tec_get(uint8_t num, uint32_t* const tec) {
    bool res = false;
    return res;
}

_WEAK_FUN_ bool can_fd_send(uint8_t num, const CanMessage_t* const Message) {
    bool res = false;
    return res;
}

bool can_fd_heartbeat_proc_one(uint8_t num) {
    bool res = false;

    CanHandle_t *Node = CanGetNode(num);
    if(Node) {
        if(Node->heart_beat) {
            LOG_PARN(CAN, "CAN%u,HeartBeat,Proc", num);
            CanMessage_t Message = { 0 };
            Message.id_type = CAN_FRAME_ID_STANDARD;
            Message.frame_type = CAN_TX_FRAME_DATA;
            Message.identifier.standard = Node->tx_id;
            Message.size = 64;
            res = array_incr((uint8_t* const ) Message.data, Message.size, (uint8_t) 0);
            snprintf((char*) Message.data, sizeof(Message.data), "From,CAN%u,SN:%u", num, Node->heart_beat_sn);
            res = can_fd_send(num, &Message);
            // log_res_num(CAN_FD, res, num, "Tx");
            Node->heart_beat_sn++;
        }
    }
    return res;
}

bool can_fd_heartbeat_proc(void) {
    bool res = true;
    uint32_t ok = 0;
    LOG_PARN(CAN_FD, "ProcAll:%u", CAN_COUNT);
    uint32_t num = 0;
    for (num = 0; num <= CAN_COUNT; num++) {
        res = can_fd_heartbeat_proc_one(num);
        // log_res_num(CAN_FD, res, num, "Proc");
        if(res) {
            ok++;
        }
    }

    if(ok) {
        res = true;
        LOG_PARN(CAN_FD, "Proc,Cnt:%u", ok);
    } else {
        res = false;
    }
    return res;
}

