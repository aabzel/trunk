#ifndef BOARD_LAYOUT_H
#define BOARD_LAYOUT_H

#include <ti/drivers/GPIO.h>
#include <ti/drivers/PIN.h>

#include "sys_config.h"

#ifndef CC26XX
#error "that wile only for CC26CC MCUs"
#endif /*USE_HAL_DRIVER*/
#define DIO_CNT 4
#define GPIO_COUNT 2U

#define CONF_GPIO_LED_0 0
#define CONF_GPIO_LED_1 1

#if 0
extern const Pin_t PinTable[];
uint32_t pin_get_cnt(void);
#endif


#endif /* BOARD_LAYOUT_H  */
