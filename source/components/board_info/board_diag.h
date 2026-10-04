#ifndef BOARD_DIAG_H
#define BOARD_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "board_types.h"
#include "gpio_types.h"

#ifndef HAS_BOARD_INFO_DIAG
#error "+HAS_BOARD_INFO_DIAG"
#endif

char* Pad2ConnectorPin(Pad_t pad);
char* Connector2Str(ConnectorPin_t con);
const char* Pad2ValidWireName(Pad_t pad);
const char* Conn2ValidWireName(ConnectorPin_t conn);
const char* Pad2SilkName(Pad_t pad);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_DIAG_H  */
