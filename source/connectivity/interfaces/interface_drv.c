#include "interface_drv.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_TBFP
#include "tbfp.h"
#endif

#ifdef HAS_SERIAL_PORT
#include "serial_port.h"
#endif

#ifdef HAS_INTERFACE_DIAG
#include "interfaces_diag.h"
#endif

#ifdef HAS_UART
#include "uart_mcal.h"
#endif

#ifdef HAS_INTERFACE_EXT
bool interface_valid(Interfaces_t interface_if) {
    bool res = false;
    uint32_t i = 0;
    uint32_t cnt = interface_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(AvailableInterfacesLUT[i] == interface_if) {
            res = true;
            break;
        }
    }
    return res;
}
#endif

#if defined(HAS_HARVESTER_V1) && defined(UART_NUM_ZED_F9P) && defined(HAS_UART)
bool sys_bypass_nmea_rs232(void) {
    bool res = true;
    UartHandle_t* UartNode = uart_get_int_node(UART_NUM_ZED_F9P);
    if(UartNode) {
        UartNode->is_uart_fwd[UART_NUM_CLI] = true;
    }
    return res;
}
#endif

#ifdef HAS_SX1262
static bool sys_sent_sx1262(uint8_t* array, uint32_t size, IfRetx_t retx) {
    bool res = false;
    switch(retx) {
    case RETX_NEED:
#ifdef HAS_TBFP
        res = tbfp_retx_start(&TbfpProtocol[IF_SX1262], array, size);
        if(false == res) {
            LOG_ERROR(TBFP, "TbfpRetxStartErr");
        }
#endif
        break;
    case RETX_NO_NEED:
        res = sx1262_start_tx(array, size, TX_SINGLE_MODE);
        if(false == res) {
            LOG_ERROR(SX1262, "Sx1262StartTx");
        }
        break;
    default:
        res = false;
        break;
    }
    return res;
}
#endif /*HAS_SX1262*/

#ifdef HAS_INTERFACE_EXT
bool system_calc_byte_rate(void) {
#ifdef HAS_RTCM3
    rtcm3_calc_byte_rate();
#endif
#ifdef HAS_TBFP
    tbfp_calc_byte_rate();
#endif
#ifdef HAS_UART
    uart_calc_byte_rate();
#endif
#ifdef HAS_SX1262
    sx1262_calc_byte_rate();
#endif
    return false;
}
#endif

/*
  array - raw data to send (byte array)
  size - length to send
  interface_if - interface to send
  retx - retransmit
  */
bool sys_send_if(const uint8_t* const array,
                 const uint32_t size,
                 const Interfaces_t interface_if,
                 const IfRetx_t retx) {
    bool res = false;
#ifdef HAS_SYSTEM_DIAG
    LOG_DEBUG(SYS, "%s Send", InterfaceToStr(interface_if));
#endif

    switch(interface_if) {

#ifdef HAS_SERIAL_PORT
    case IF_SERIAL_PORT: {
        res = serial_port_send( 0, array, size) ;
        log_res(SYS, res, "SerialPortSend");
    } break;
#endif /**/

#ifdef HAS_UART0
    case IF_UART0: {
        res = uart_mcal_send(0, array, size);
    } break;
#endif

#ifdef HAS_UART1
    case IF_UART1: {
        res = uart_mcal_send(1, array, size);
    } break;
#endif

    case IF_LOOPBACK: {
#ifdef HAS_TBFP_EXT
        res = tbfp_rx(array, size, IF_LOOPBACK);
        log_res(SYS, res, "TbfpProcLoopBack");
#endif
    } break;

#ifdef HAS_PC
    case IF_STDIO: {
        res = stdio_send(array, size);
    } break;
#endif

#ifdef HAS_INTERFACE_EXT
    case IF_BLACK_HOLE:
        /*That is interface for test and debug*/
        res = true;
        break;
#endif

#ifdef HAS_BLE
    case IF_BLE: {
        res = ble_send(array, size);
    } break;
#endif /*HAS_BLE*/

#ifdef HAS_SX1262
    case IF_SX1262: {
        res = sys_sent_sx1262(array, size, retx);
        if(false == res) {
            LOG_ERROR(SX1262, "SysSentSx1262");
        }
    } break;
#endif /*HAS_SX1262*/

    /*ForUnitTest on PC*/
#ifdef HAS_TBFP
    // res = tbfp_proc(&array[0], size, IF_SX1262, true);
#endif /*HAS_TBFP*/

#ifdef HAS_LORA
    case IF_LORA: {
        res = radio_send_queue(array, size);
        if(false == res) {
            LOG_ERROR(RADIO, "SendErr");
        }
    } break;
#endif

#ifdef HAS_CAN
    case IF_CAN: {
        res = can_if_send(array, size);
    } break;
#endif

#ifdef HAS_SPI0
    case IF_SPI0: {
        res = spi_write(SPI0_INX, array, size);
    } break;
#endif

#ifdef HAS_RS232
    case IF_RS232: {
        res = rs232_send(1, array, size);
    } break;
#endif

#ifdef HAS_UWB
    case IF_UWB: {
        res = uwb_send(array, size);
    } break;
#endif /*HAS_UWB*/

    default: {
#ifdef HAS_SYSTEM_DIAG
        LOG_ERROR(SYS, "UndefIf: %u=%s", interface_if, InterfaceToStr(interface_if));
#endif
        res = false;
    } break;
    }
    if(false == res) {
#ifdef HAS_SYSTEM_DIAG
        LOG_DEBUG(SYS, "SendIfErr: %u=%s", interface_if, InterfaceToStr(interface_if));
#endif
        // send_err_cnt++;
    }
    return res;
}

#ifdef HAS_INTERFACE_EXT
bool sys_available_interfaces(void) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok_cnt = 0;

    for(i = 0; i < IF_CNT; i++) {
        res = interface_valid(i);
        if(res) {
            ok_cnt++;
#ifdef HAS_LOG
            LOG_INFO(SYS, "%u=%s", i, InterfaceToStr(i));
#endif
        }
    }

    if(ok_cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
#endif


#ifdef HAS_PC
Interfaces_t InterfaceComPortToInterface(uint8_t com_port_num){
    Interfaces_t inter_face = IF_SERIAL_PORT;
    (void)com_port_num;
    return inter_face;
}
#endif
