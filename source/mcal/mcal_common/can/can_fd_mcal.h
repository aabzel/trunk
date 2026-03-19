#ifndef CAN_FD_MCAL_DRV_H
#define CAN_FD_MCAL_DRV_H

#include "can_types.h"


/*API*/
bool can_fd_proc(void);
bool can_fd_proc_one(uint8_t num);

/*setter*/
bool can_fd_send(uint8_t num, const CanMessage_t* const Message);
bool can_fd_heartbeat_proc(void);
bool can_fd_heartbeat_proc_one(uint8_t num) ;
bool can_fd_baudrate_set(uint8_t num, uint32_t bit_rate);

/*getter*/
bool can_fd_baudrate_get(uint8_t num, uint32_t *const bit_rate);
bool can_fd_tec_get( uint8_t num, uint32_t* const tec);
bool can_fd_rec_get( uint8_t num, uint32_t* const rec);

#endif /* CAN_FD_MCAL_DRV_H  */
