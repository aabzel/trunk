
#ifndef BOARD_INFO_DRV_H
#define BOARD_INFO_DRV_H

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
#endif /*HAS_MCU*/

const Wire_t* Pad2WireInfio(Pad_t pad);
const Wire_t* Conn2WireInfio(ConnectorPin_t conn);
bool connectors_is_equal(const ConnectorPin_t* const conn1, const ConnectorPin_t* const conn2);
const WirePin_t* Conn2WirePinInfio(ConnectorPin_t conn, WirePin_t* WireList, uint32_t cnt);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_INFO_DRV_H  */
