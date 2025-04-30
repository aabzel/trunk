#include "protocol.h"

#include <string.h>

#include "data_utils.h"
#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_DIAG
#include "interfaces_diag.h"
#include "protocol_diag.h"
#include "system_diag.h"
#endif

#ifdef HAS_MATH
#include "utils_math.h"
#endif

#ifndef MAX
#define MAX(n, m) (((n) < (m)) ? (m) : (n))
#endif

#ifdef HAS_PROTOCOL_EXT
bool protocol_check_flow_control(facility_t facility, FlowCrtl_t* const Node, uint16_t snum, Interfaces_t interface) {
    bool res = false;
    if(Node) {
        // LOG_PARN(facility, "%s PrevSN:%u SN:%u flow:%u", InterfaceToStr(interface), Node->prev_s_num, snum,
        // Node->cur);
        Node->prev_flow = Node->cur;
        Node->cur_sn = snum;
        if(snum < Node->prev_s_num) {
            /*Unreal situation*/
#ifdef HAS_LOG
            LOG_DEBUG(facility, "SNorderError SNcur:%u<=SNprev:%u", snum, Node->prev_s_num);
#endif
            Node->order_err++;
            //  con_flow = 1;
            Node->cur = 1;
            res = false;
        } else if(snum == (1 + Node->prev_s_num)) {
            /*Flow ok*/
            Node->torn = false;
            Node->lost_rx_frames = 0;
#ifdef HAS_DIAG
            LOG_DEBUG(facility, "%s,FlowOk,%u->%u", InterfaceToStr(interface), Node->prev_s_num, snum);
#endif
            Node->cur++;
            Node->maximum_continuous = MAX(Node->maximum_continuous, Node->cur);
            res = true;
        } else if((Node->prev_s_num + 1) < snum) {
            /*Lost rx packets*/
            Node->torn = true;
            Node->torn_cnt++;
            Node->lost_rx_frames = snum - Node->prev_s_num - 1;
#ifdef HAS_PROTOCOL_DIAG
            LOG_DEBUG(facility, "%s,FlowTorn!,SN:%u,Lost:%u", InterfaceToStr(interface), snum, Node->lost_rx_frames);
            flow_ctrl_print_lost(facility, Node, snum, interface);
#endif
            Node->cur = 1;
            res = true;
        } else if(snum == Node->prev_s_num) {
            /*Spot Rx Retx*/
            Node->torn = false;
            if(0 == Node->prev_s_num) {
                res = true;
                Node->cur = 1;
            } else {
#ifdef HAS_LOG
                LOG_DEBUG(facility, "Duplicate! SN=%u", snum);
#endif
                Node->duplicate_cnt++;
                res = false;
            }
        } else {
            /*Unreal situation*/
            res = false;
        }
#ifdef HAS_LOG
        LOG_PARN(facility, "%s prev_SN:%u SN:%u flow:%u", InterfaceToStr(interface), Node->prev_s_num, snum, Node->cur);
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
