#ifndef SWD_MCAL_H
#define SWD_MCAL_H

#include "swd_types.h"
#include "swd_config.h"
#include "sys_constants.h"
#include "swd_isr.h"
#include "swd_custom_drv.h"


SwdHandle_t* SwdGetNode(uint8_t num);
const SwdConfig_t* SwdGetConfig(uint8_t num);

/*API*/
bool swd_is_allowed(uint8_t num);
bool swd_is_init(uint8_t num);
bool swd_init_one(uint8_t num);
bool swd_proc(void) ;
bool swd_mcal_init(void) ;
bool swd_proc_one(uint8_t num);
Interfaces_t  SwdNumToInterface(uint8_t num);

/*setters*/
bool swd_write(uint8_t* tx_array, uint16_t tx_array_len);


/*getters*/
bool swd_read( uint8_t* rx_array, uint16_t rx_array_len);

/*ISR code*/

#endif /* SWD_MCAL_H  */
