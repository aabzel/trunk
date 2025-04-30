
#ifndef BOARD_DIAG_H
#define BOARD_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "board_types.h"
#include "gpio_types.h"

#ifndef HAS_MCU
#error "+HAS_MCU"
#endif /*HAS_MCU*/

#ifndef HAS_BOARD_INFO
#error "+HAS_BOARD_INFO"
#endif /*HAS_BOARD_INFO*/

#ifndef HAS_BOARD_INFO_DIAG
#error "+HAS_BOARD_INFO_DIAG"
#endif /*HAS_BOARD_INFO_DIAG*/

const char* Pad2SilkName(Pad_t pad);
char* Pad2ConnectorPin(Pad_t pad);
char* Connector2Str(ConnectorPin_t con);
const char* Pad2ValidWireName(Pad_t pad);
const char* Conn2ValidWireName(ConnectorPin_t conn);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_DIAG_H  */
