#include "system_commands.h"

#include "if_config.h"
#include "interface_drv.h"
#include "log.h"
#include "system.h"
#include "system_diag.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_TBFP
#include "tbfp.h"
#endif

#ifdef HAS_RTCM3
#include "rtcm3_protocol.h"
#endif

#ifdef HAS_UART
#include "uart_mcal.h"
#endif

#ifdef HAS_SX1262
#include "sx1262_drv.h"
#endif

#ifdef HAS_GNSS
bool sys_bypass_nmea_rs232_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
#ifdef HAS_HARVESTER_V1
        res = sys_bypass_nmea_rs232();
#endif
        if(res) {
            LOG_INFO(SYS, "Ok!");
        }
    } else {
        LOG_ERROR(SYS, "Usage: nmrs");
    }
    return res;
}
#endif

bool sys_rate_command(int32_t argc, char* argv[]) {
    bool res = true;
    static const table_col_t cols[] = {{11, "interf"}, {7, "proto"}, {9, "rxMin"}, {9, "rx"},
                                       {9, "rxMax"},   {9, "txMin"}, {9, "tx"},    {9, "txMax"}};

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
#if defined(HAS_RTCM) || defined(HAS_TBFP)
    uint8_t interface = 0;
#endif
    uint8_t uart_num = 0;
    const UartConfig_t* Config = NULL;
    for(uart_num = 0; uart_num <= UART_COUNT; uart_num++) {
        Config = UartGetConfig(uart_num);
        if(Config) {
            cli_printf(TSEP);
            cli_printf(" %9s " TSEP, Config->name);
            cli_printf(" ----- " TSEP);
            UartHandle_t* UartNode = UartGetNode(uart_num);
            if(UartNode) {
                cli_printf(" %7u " TSEP, UartNode->rx_rate.min);
                cli_printf(" %7u " TSEP, UartNode->rx_rate.cur);
                cli_printf(" %7u " TSEP, UartNode->rx_rate.max);
                cli_printf(" %7u " TSEP, UartNode->tx_rate.min);
                cli_printf(" %7u " TSEP, UartNode->tx_rate.cur);
                cli_printf(" %7u " TSEP, UartNode->tx_rate.max);
                cli_printf(CRLF);
            }
        }
    }

    uint32_t if_cnt = interface_get_cnt();
    LOG_ERROR(SYS, "InterafaceCnt: %u", if_cnt);
#ifdef HAS_RTCM3
    for(interface = 0; interface < if_cnt; interface++) {
        Rtcm3Protocol_t* Rtcm3Node = If2Rtcm3Node(interface);
        if(Rtcm3Node) {
            cli_printf(TSEP);
            cli_printf(" %9s " TSEP, InterfaceToStr((Interfaces_t)Rtcm3Node->interface));
            cli_printf(" RTCM3 " TSEP);
            cli_printf(" %7u " TSEP, Rtcm3Node->rx_rate.min);
            cli_printf(" %7u " TSEP, Rtcm3Node->rx_rate.cur);
            cli_printf(" %7u " TSEP, Rtcm3Node->rx_rate.max);
            cli_printf(" %7u " TSEP, Rtcm3Node->tx_rate.min);
            cli_printf(" %7u " TSEP, Rtcm3Node->tx_rate.cur);
            cli_printf(" %7u " TSEP, Rtcm3Node->tx_rate.max);
            cli_printf(CRLF);
            res = true;
        }
    }
#endif

#ifdef HAS_TBFP
    for(interface = (Interfaces_t)0; interface < if_cnt; interface++) {
        TbfpHandle_t* Node = TbfpInterfaceToNode(interface);
        if(Node) {
            cli_printf(TSEP);
            cli_printf(" %9s " TSEP, InterfaceToStr(Node->interface));
            cli_printf("  TBFP " TSEP);
            cli_printf(" %7u " TSEP, Node->rx_rate.min);
            cli_printf(" %7u " TSEP, Node->rx_rate.cur);
            cli_printf(" %7u " TSEP, Node->rx_rate.max);
            cli_printf(" %7u " TSEP, Node->tx_rate.min);
            cli_printf(" %7u " TSEP, Node->tx_rate.cur);
            cli_printf(" %7u " TSEP, Node->tx_rate.max);
            cli_printf(CRLF);
            res = true;
        }
    }
#endif /*HAS_TBFP*/

#ifdef HAS_SX1262
    cli_printf(TSEP);
    cli_printf(" %6s " TSEP, InterfaceToStr(IF_SX1262));
    cli_printf("  ---- " TSEP);
    cli_printf(" %7u " TSEP, Sx1262Instance.rx_rate.min);
    cli_printf(" %7u " TSEP, Sx1262Instance.rx_rate.cur);
    cli_printf(" %7u " TSEP, Sx1262Instance.rx_rate.max);
    cli_printf(" %7u " TSEP, Sx1262Instance.tx_rate.min);
    cli_printf(" %7u " TSEP, Sx1262Instance.tx_rate.cur);
    cli_printf(" %7u " TSEP, Sx1262Instance.tx_rate.max);
    cli_printf(CRLF);
#endif /*HAS_SX1262*/
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool sys_available_interfaces_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = sys_available_interfaces();
    return res;
}

bool sys_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = system_diag();
    return res;
}
