#ifndef BOARD_INFO_DRV_H
#define BOARD_INFO_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "board_types.h"
#include "gpio_types.h"
#include "board_config.h"

#ifndef HAS_BOARD_INFO
#error "+HAS_BOARD_INFO"
#endif 

const Wire_t* PadToWireInfo(const Pad_t pad);
const Wire_t* Conn2WireInfio(ConnectorPin_t conn);
const WirePin_t* Conn2WirePinInfio(ConnectorPin_t conn, WirePin_t* WireList, uint32_t cnt);
bool board_indicate_init_error(void);
bool connectors_is_equal(const ConnectorPin_t* const conn1, const ConnectorPin_t* const conn2);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_INFO_DRV_H  */
