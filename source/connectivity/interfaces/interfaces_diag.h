#ifndef INTERFACES_DIAG_H
#define INTERFACES_DIAG_H

#include "std_inc.h"
#include "interfaces_types.h"

const char* IfOperationToStr(const IfOperation_t operation);
const char* IfBusRoleToStr(const IfBusRole_t bus_role);
const char* IfBitOrderToStr(const IfBitOrder_t bit_order);
const char* InterfaceNameToStr(const InterfaceName_t if_name) ;
const char* InterfaceTypeToStr(const InterfaceType_t inter_face);
const char* InterfaceTypeToStrShort(const InterfaceType_t inter_face) ;
const char* InterfaceToStr(const InterfaceType_t inter_face);
const InterfaceNameInfo_t* InterfaceNameToInfo(const InterfaceName_t if_name);

#endif /* INTERFACES_DIAG_H */
