#ifndef BOARD_NUCLEO_F446RE_H
#define BOARD_NUCLEO_F446RE_H

#include "stm32f446re.h"

#define BOARD_NAME "Nucleo-F446RE"

#ifndef HSE_VALUE
#define HSE_VALUE 8000000
#endif

#define LED_COUNT 1
#define BUTTON_COUNT 1
#define XTALL_FREQ_HZ 8000000

#endif /* BOARD_NUCLEO_F446RE_H   */
