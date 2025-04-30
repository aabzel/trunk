#include "interfaces_diag.h"

const char* IfBusRoleToStr(IfBusRole_t code) {
    const char* name = "?";
    switch((uint8_t)code) {
    case BUS_ROLE_MASTER:
        name = "Master";
        break;
    case BUS_ROLE_SLAVE:
        name = "Slave";
        break;
    }
    return name;
}

const char* IfBitOrderToStr(IfBitOrder_t bit_order) {
    const char* name = "?";
    switch(bit_order) {
    case BIT_ORDER_MSB:
        name = "Msb1st";
        break;
    case BIT_ORDER_LSB:
        name = "Lsb1st";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

/*TODO Make Table*/
const char* InterfaceToStr(const Interfaces_t interface) {
    const char* name = "?";
    switch(interface) {
#ifdef HAS_ISO_TP
    case IF_ISO_TP2:
        name = "ISO_TP2";
        break;

    case IF_ISO_TP1:
        name = "ISO_TP1";
        break;
#endif /*HAS_ISO_TP*/

#ifdef HAS_PC
    case IF_STDIO:
        name = "Stdio";
        break;
#endif

#ifdef HAS_CAN
    case IF_CAN:
        name = "CAN";
        break;
#endif /*HAS_CAN*/

#ifdef HAS_GFSK
    case IF_GFSK:
        name = "GFSK";
        break;
#endif /*HAS_GFSK*/

#ifdef HAS_LORA
    case IF_LORA:
        name = "LoRa";
        break;
#endif /*HAS_LORA*/

#ifdef HAS_RS232
    case IF_RS232:
        name = "Rs232";
        break;
#endif /*HAS_RS232*/

#ifdef HAS_SPI0
    case IF_SPI0:
        name = "SPI0";
        break;
#endif /*HAS_SPI0*/

#ifdef HAS_SPI1
    case IF_SPI1:
        name = "SPI1";
        break;
#endif /*HAS_SPI1*/

#ifdef HAS_SPI2
    case IF_SPI2:
        name = "SPI2";
        break;
#endif /*HAS_SPI2*/

#ifdef HAS_SPI3
    case IF_SPI3:
        name = "SPI3";
        break;
#endif /*HAS_SPI3*/

#ifdef HAS_SPI4
    case IF_SPI4:
        name = "SPI4";
        break;
#endif /*HAS_SPI4*/

#ifdef HAS_SX1262
    case IF_SX1262:
        name = "SX1262";
        break;
#endif /*HAS_SX1262*/

#ifdef HAS_UART0
    case IF_UART0:
        name = "UART0";
        break;
#endif /*HAS_UART0*/

#ifdef HAS_UART1
    case IF_UART1:
        name = "UART1";
        break;
#endif /*HAS_UART1*/

#ifdef HAS_UART2
    case IF_UART2:
        name = "UART2";
        break;
#endif /*HAS_UART2*/

#ifdef HAS_UWB
    case IF_UWB:
        name = "UWB";
        break;
#endif /*HAS_UWB*/

    case IF_LOOPBACK:
        name = "LoopBack";
        break;
    case IF_BLACK_HOLE:
        name = "BlackHole";
        break;

    default:
        break;
    }
    return name;
}
