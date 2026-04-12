#include "protocol.h"

#include <string.h>

#include "data_utils.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_DIAG
#include "interfaces_diag.h"
#include "system_diag.h"
#endif

#ifdef HAS_MATH
#include "utils_math.h"
#endif

#ifndef MAX
#define MAX(n, m) (((n) < (m)) ? (m) : (n))
#endif

static inline bool protocol_check_flow_ok(const facility_t facility, const InterfaceType_t inter_face,
                                          FlowCrtl_t* const Node) {
    bool res = false;
    Node->torn = false;
    Node->lost_rx_frames = 0;
#ifdef HAS_DIAG
    LOG_DEBUG(facility, "%s,FlowOk,%u->%u", InterfaceTypeToStr(inter_face), Node->prev_s_num, Node->cur_sn);
#endif
    Node->cur++;
    Node->maximum_continuous = MAX(Node->maximum_continuous, Node->cur);
    res = true;
    return res;
}

static inline bool protocol_check_flow_lost_packets(const facility_t facility, const InterfaceType_t inter_face,
                                                    FlowCrtl_t* const Node) {
    bool res = false;
    /* flow disruption */
    Node->torn = true;
    Node->torn_cnt++;
    Node->lost_rx_frames = Node->cur_sn - Node->prev_s_num - 1;
    Node->total_lost_rx_frames += Node->lost_rx_frames;
#ifdef HAS_PROTOCOL_DIAG
    LOG_NOTICE(facility, "%s,FlowTorn!,SN:%u,Lost:%u", InterfaceTypeToStr(inter_face), Node->cur_sn,
               Node->lost_rx_frames);
    flow_ctrl_print_lost(facility, Node, Node->cur_sn, inter_face);
#endif
    Node->cur = 1;
    res = true;
    return res;
}

static inline bool protocol_check_flow_duplicat(const facility_t facility, const InterfaceType_t inter_face,
                                                FlowCrtl_t* const Node) {
    bool res = false;
    /* Spot Rx duplicate  */
    Node->torn = false;
    if(0 == Node->prev_s_num) {
        res = true;
        Node->cur = 1;
    } else {
        Node->duplicate_cnt++;
        res = false;
#ifdef HAS_LOG
        LOG_NOTICE(facility, "Duplicate!SN=%u", Node->cur_sn);
#endif
    }
    return res;
}

static inline bool protocol_check_flow_order_reverse(facility_t facility, InterfaceType_t inter_face,
                                                     FlowCrtl_t* const Node) {
    bool res = false;
    /* Unreal situation */
#ifdef HAS_LOG
    LOG_ERROR(facility, "SnOrderReverse!,SNcur:%u<=SNprev:%u", Node->cur_sn, Node->prev_s_num);
#endif
    Node->order_err++;
    Node->cur = 1;
    res = false;
    return res;
}

#ifdef HAS_PROTOCOL_EXT
bool protocol_check_flow_control(const facility_t facility, FlowCrtl_t* const Node, const uint16_t snum,
                                 const InterfaceType_t inter_face) {
    bool res = false;
    if(Node) {
        //Node->rx_cnt++;
        // LOG_PARN(facility, "%s PrevSN:%u SN:%u flow:%u", InterfaceTypeToStr(inter_face), Node->prev_s_num, snum,
        // Node->cur);
        Node->prev_flow = Node->cur;
        Node->cur_sn = snum;
        if(snum < Node->prev_s_num) {
            res = protocol_check_flow_order_reverse(facility, inter_face, Node);
        } else if(snum == (1 + Node->prev_s_num)) {
            res = protocol_check_flow_ok(facility, inter_face, Node);
        } else if((Node->prev_s_num + 1) < snum) {
            res = protocol_check_flow_lost_packets(facility, inter_face, Node);
        } else if(snum == Node->prev_s_num) {
            res = protocol_check_flow_duplicat(facility, inter_face, Node);
        } else {
            /*Unreal situation*/
            res = false;
        }

#ifdef HAS_INTERFACE_DIAG
        LOG_PARN(facility, "IF:%s,PrevSN:%u,SN:%u,CurFlow:%u", InterfaceTypeToStr(inter_face), Node->prev_s_num,
                 Node->cur_sn, Node->cur);
#endif
        Node->prev_s_num = snum;
    }

    return res;
}
#endif

#ifdef HAS_PROTOCOL_EXT
bool protocol_flow_init(FlowCrtl_t* const Node) {
    bool res = false;
    if(Node) {
        memset(Node, 0, sizeof(FlowCrtl_t));
        Node->prev_s_num = 0;
        res = true;
    }
    return res;
}
#endif
