#ifndef INTERFACES_DIAG_H
#define INTERFACES_DIAG_H

#include <stdint.h>

#include "interfaces_const.h"

const char* IfBusRoleToStr(IfBusRole_t code);
const char* IfBitOrderToStr(IfBitOrder_t bit_order);
const char* InterfaceToStr(const Interfaces_t inter_face);

#endif /* INTERFACES_DIAG_H */
