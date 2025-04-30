#ifndef BOARD_NRF5340_DK_H
#define BOARD_NRF5340_DK_H

#include "nrf5340.h"
#include "board_config.h"

#define BOARD_NAME "NRF5340-DK"
#define XTALL_FREQ 32000000U

#ifdef 	HAS_CORE_APP
#define SYS_FREQ (XTALL_FREQ*4)
#endif /*HAS_CORE_APP*/

#ifdef 	HAS_CORE_NET
#define SYS_FREQ (XTALL_FREQ*2)
#endif /*HAS_CORE_NET*/

#define BUTTON_COUNT 4
#define LED_COUNT 4


#endif /* BOARD_NRF5340_DK_H   */
