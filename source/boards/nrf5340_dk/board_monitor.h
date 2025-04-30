#ifndef BOARD_MONITOR_H
#define BOARD_MONITOR_H

#include <stdbool.h>

#if defined(HAS_WM8731_I2S_MASTER) && defined(HAS_I2S0_MASTER)
#error "Double I2S master on the single bus"
#endif

#if defined(HAS_WM8731_I2S_SLAVE) && defined(HAS_I2S0_SLAVE)
//#warning "Double I2S slave on the single bus"
#endif

bool board_check(void);

#endif /* BOARD_MONITOR_H  */
