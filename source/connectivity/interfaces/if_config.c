#include "if_config.h"

#include "data_utils.h"
// TODO move to interfaces folder

const Interfaces_t AvailableInterfacesLUT[] = {
    IF_BLACK_HOLE, IF_LOOPBACK,
#ifdef HAS_LORA
    IF_LORA,
#endif

#ifdef HAS_SX1262
    IF_SX1262,
#endif

#ifdef HAS_UART0
    IF_UART0,
#endif

#ifdef HAS_UART1
    IF_UART1,
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

#ifdef HAS_RS232
    IF_RS232,
#endif

#ifdef HAS_CAN
    IF_CAN,
#endif

#ifdef HAS_GFSK
    IF_GFSK,
#endif

#ifdef HAS_BLE
    IF_BLE,
#endif

#ifdef HAS_SPI0
    IF_SPI0,
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

#ifdef HAS_PC
    IF_STDIO,
#endif
};

uint32_t interface_get_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(AvailableInterfacesLUT);
    return cnt;
}
