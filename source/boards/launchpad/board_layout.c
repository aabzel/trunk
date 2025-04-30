#include "board_layout.h"

#include <stdlib.h>
#include <ti/drivers/gpio/GPIOCC26XX.h>

#include "data_utils.h"
#include "gpio_mcal.h"
#include "sys_config.h"

#if 0
/*line order does not  matters!*/
const Pin_t PinTable[] = {
 {DIO_LED_GREEN,      12,   "G_LED", NULL, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW, PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MED},
 {DIO_LED_RED,        11,   "R_LED", NULL, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW, PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MED},
 {DIO_UART_CLI_RX,    7,   "MCU_RX", NULL, GPIO_CFG_IN_NOPULL, PIN_INPUT_EN},
 {DIO_UART_CLI_TX,    8,   "MCU_TX", NULL, GPIO_CFG_OUTPUT, PIN_PUSHPULL},
 {DIO_BUTTON1,        19,  "BTN1",   NULL, GPIO_CFG_IN_NOPULL, PIN_INPUT_EN},
 {DIO_BUTTON2,        20,  "BTN2",   NULL, GPIO_CFG_IN_NOPULL, PIN_INPUT_EN},
};
#endif

#if 0
uint32_t pin_get_cnt(void){
    uint32_t cnt = ARRAY_SIZE(PinTable);
    return cnt;
}
#endif

