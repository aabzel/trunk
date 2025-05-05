#ifndef INTERFACES_CONST_H
#define INTERFACES_CONST_H

/*for I2S SPI MDIO I2C MII PDM SDIO 1wire*/
typedef enum {
    BUS_ROLE_MASTER = 1,
    BUS_ROLE_SLAVE = 2,

    BUS_ROLE_UNDEF = 0,
} IfBusRole_t;



typedef enum {
    RETX_NO_NEED = 0,
    RETX_NEED = 1,
} IfRetx_t;

//
typedef enum {
    BIT_ORDER_MSB = 1,
    BIT_ORDER_LSB = 2,

    BIT_ORDER_UNDEF = 0,
} IfBitOrder_t;


typedef enum {
    IF_UNDEF=0,
    IF_LOOPBACK = 1, /*for self Test*/
    IF_BLACK_HOLE = 2,
#ifdef HAS_LORA
    IF_LORA, /*RTCM3 source*/
#endif

#ifdef HAS_SX1262
    IF_SX1262,
#endif

#ifdef HAS_UART0
    IF_UART0, /*for CLI*/
#endif

#ifdef HAS_UART1
    IF_UART1,
#endif

#ifdef HAS_STACK_FRAME
    STACK_FRAME,
#endif

#ifdef HAS_UART2
    IF_UART2,
#endif

#ifdef HAS_UART3
    IF_UART3,
#endif

#ifdef HAS_UART6
    IF_UART6,
#endif

#ifdef HAS_UART8
    IF_UART8,
#endif

#ifdef HAS_USB
    IF_USB,
    IF_USB_HID,
#endif

#ifdef HAS_UART4
    IF_UART4,
#endif

#ifdef HAS_RS232
    IF_RS232, /*for Debug*/
#endif

#ifdef HAS_CAN
    IF_CAN, /*for Debug*/
#endif

#ifdef HAS_CAN1
    IF_CAN1,
#endif

#ifdef HAS_CAN2
    IF_CAN2,
#endif

#ifdef HAS_GFSK
    IF_GFSK,
#endif

#ifdef HAS_BLE
    IF_BLE,
#endif

#ifdef HAS_CALCULATOR
    CALC,
#endif

#ifdef HAS_SPI0
    IF_SPI0,
#endif

#ifdef HAS_I2C0
    IF_I2C0,
#endif

#ifdef HAS_I2C1
    IF_I2C1,
#endif

#ifdef HAS_I2C2
    IF_I2C2,
#endif

#ifdef HAS_I2C3
    IF_I2C3,
#endif

#ifdef HAS_SPI1
    IF_SPI1,
#endif

#ifdef HAS_SPI2
    IF_SPI2,
#endif

#ifdef HAS_SPI3
    IF_SPI3,
#endif

#ifdef HAS_SPI4
    IF_SPI4,
#endif

#ifdef HAS_UWB
    IF_UWB,
#endif

#ifdef HAS_SERIAL_PORT
    IF_SERIAL_PORT,
#endif

#ifdef HAS_PC
    IF_STDIO,
#endif

#ifdef HAS_ISO_TP
    IF_ISO_TP1,
    IF_ISO_TP2,
#endif

#ifdef HAS_KEYBOARD
    IF_USB_KEYBOARD,
#endif

#ifdef HAS_FAT_FS
    IF_FAT_FS,
#endif
    IF_CNT,

} Interfaces_t;

#endif /* INTERFACES_CONST_H */
