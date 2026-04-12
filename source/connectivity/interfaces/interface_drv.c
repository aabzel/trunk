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

#ifdef HAS_SPI
#include "spi_mcal.h"
#endif

#ifdef HAS_CAN
#include "can_mcal.h"
#endif

#ifdef HAS_SX1262
static bool sys_sent_sx1262(uint8_t* array, uint32_t size, IfRetx_t retx) {
    bool res = false;
    switch(retx) {
    case RETX_NEED:
#ifdef HAS_TBFP
        res = tbfp_retx_start(&TbfpProtocol[INTERFACE_NAME_SX1262], array, size);
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
bool interface_send(const uint8_t* const array, const uint32_t size, const InterfaceType_t interface_if,
                    const IfRetx_t retx) {
    bool res = false;
#ifdef HAS_SYSTEM_DIAG
    LOG_DEBUG(SYS, "Send,IF:%s,SZ:%u Byte", InterfaceTypeToStr(interface_if), size);
#endif

    switch(interface_if.interface_name) {
    case INTERFACE_NAME_LOOPBACK: {
        res = interface_rx(interface_if, array, size);
        log_res(SYS, res, "LoopBack");
    } break;

#ifdef HAS_INTERFACE_EXT
    case INTERFACE_NAME_BLACKHOLE:
        /*That is interface for test and debug*/
        res = true;
        break;
#endif

#ifdef HAS_CAN
    case INTERFACE_NAME_CAN: {
        CanHandle_t* Can = CanGetNode(interface_if.num);
        if(Can) {
            res = can_mcal_transmit_buff(interface_if.num, Can->my_id, array, size);
            log_res(SYS, res, "CanSen");
        }
    } break;
#endif

#ifdef HAS_SERIAL_PORT
    case INTERFACE_NAME_SERIAL_PORT: {
        res = serial_port_send(interface_if.num, array, size);
        log_res(SYS, res, "SerialPortSend");
    } break;
#endif /**/

#ifdef HAS_SPI
    case INTERFACE_NAME_SPI: {
        res = spi_mcal_write(interface_if.num, array, size);
    } break;
#endif

#ifdef HAS_UART
    case INTERFACE_NAME_UART: {
        res = uart_mcal_send(interface_if.num, array, size);
    } break;
#endif

#ifdef HAS_RS232
    case INTERFACE_NAME_RS232: {
        res = rs232_send(interface_if.num, array, size);
    } break;
#endif

#ifdef HAS_PC
    case INTERFACE_NAME_STDIO: {
        res = stdio_send(array, size);
    } break;
#endif

#ifdef HAS_BLE
    case INTERFACE_NAME_BLE: {
        res = ble_send(array, size);
    } break;
#endif /**/

#ifdef HAS_SX1262
    case INTERFACE_NAME_SX1262: {
        res = sys_sent_sx1262(array, size, retx);
        if(false == res) {
            LOG_ERROR(SX1262, "SysSentSx1262");
        }
    } break;
#endif /**/

    /*ForUnitTest on PC*/
#ifdef HAS_TBFP
    // res = tbfp_proc(&array[0], size, INTERFACE_NAME_SX1262, true);
#endif /*HAS_TBFP*/

#ifdef HAS_LORA
    case INTERFACE_NAME_LORA: {
        res = radio_send_queue(array, size);
        if(false == res) {
            LOG_ERROR(RADIO, "SendErr");
        }
    } break;
#endif

#ifdef HAS_UWB
    case INTERFACE_NAME_UWB: {
        res = uwb_send(array, size);
    } break;
#endif /*HAS_UWB*/

    default: {
#ifdef HAS_SYSTEM_DIAG
        LOG_ERROR(SYS, "UndefIf: %u=%s", interface_if, InterfaceTypeToStr(interface_if));
#endif
        res = false;
    } break;
    }

    if(false == res) {
#ifdef HAS_SYSTEM_DIAG
        LOG_DEBUG(SYS, "SendIfErr: %u=%s", interface_if, InterfaceTypeToStr(interface_if));
#endif
    }
    return res;
}

#if 0
bool sys_available_interfaces(void) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok_cnt = 0;

    for(i = 0; i < INTERFACE_NAME_CNT; i++) {
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

#ifdef HAS_SERIAL_PORT
InterfaceType_t InterfaceComPortToInterface(uint8_t com_port_num) {
    InterfaceType_t inter_face = {0};
    inter_face.interface_name = INTERFACE_NAME_SERIAL_PORT;
    inter_face.num = com_port_num;
    return inter_face;
}
#endif

bool interface_rx(const InterfaceType_t interface_if, const uint8_t* const array, const uint32_t len) {
    bool res = false;
    return res;
}
