#ifndef SX1262_CONFIG_H
#define SX1262_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sx1262_constants.h"


//#define DFLT_SYNC_WORD 0x1122334455667788
//#define DFLT_NODE_ADDR 0x00
//#define DFLT_BROADCAST_ADDR 0x01

#define RX_BASE_ADDRESS 0x00
#define TX_BASE_ADDRESS 0x00

#define BUSY_CNT_LIMIT 1000

/* TODO find out real number */
#define SX1262_SPI_NUM 1

#define DIO_SX1262_SS (gpio_port_pin2pad(PORT_A,8))
#define DIO_SX1262_BUSY (gpio_port_pin2pad(PORT_B,3))
#define DIO_SX1262_RST (gpio_port_pin2pad(PORT_A,0))
#define DIO_SX1262_INT (gpio_port_pin2pad(PORT_B,4))


#define DFLT_TX_PAUSE_MS 50U /*TODO Find least possible value*/
#define DFLT_FREQ_MHZ 868950000
#define DFLT_OUT_POWER 14 /*dBm*/

//#define DFLT_SYNC_WORD 0x1122334455667788
//#define DFLT_NODE_ADDR 0x00
//#define DFLT_BROADCAST_ADDR 0x01

#define RX_BASE_ADDRESS 0x00
#define TX_BASE_ADDRESS 0x00

#define BUSY_CNT_LIMIT 1000

#ifdef __cplusplus
}
#endif

#endif /* SX1262_CONFIG_H */
