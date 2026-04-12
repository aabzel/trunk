#ifndef CONNECTIVITY_CONST_H
#define CONNECTIVITY_CONST_H

#ifdef HAS_INTERFACES
#include "interfaces_const.h"
#endif

#ifdef HAS_PROTOCOLS
#include "protocols_const.h"
#endif

/* Used in I2C; I2S; SDIO; UART; SPI; CAN; CAN_MAILBOX e.g.*/
typedef enum {
    CONNECT_DIR_TRANSMIT = 1,    /* transmit (out)  */
    CONNECT_DIR_RECEIVER = 2,    /* receive (in)  */
    CONNECT_DIR_RX_TX= 3,    /* both receive and transmit */
    CONNECT_DIR_UNDEF = 0,
}ConnectivitDir_t;


#endif /* CONNECTIVITY_CONST_H */
