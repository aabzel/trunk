#ifndef PROTOCOLS_GENERAL_H
#define PROTOCOLS_GENERAL_H


#include "std_includes.h"
#include "protocol_types.h"
#include "sys_constants.h"
#ifdef HAS_INTERFACES
#include "interfaces_const.h"
#endif

bool protocol_check_flow_control(facility_t facility, FlowCrtl_t* const Node,
                                 uint16_t snum, Interfaces_t interface);
bool protocol_flow_init(FlowCrtl_t* const Node);

#endif /* PROTOCOLS_GENERAL_H */
