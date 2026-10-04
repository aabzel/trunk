#include "sw_uart_diag.h"

#include "sw_uart_mcal.h"
#include "common_diag.h"
#include "gpio_diag.h"
#include "diag_inc.h"
#include "log.h"
#ifdef HAS_EXT_INT
#include "ext_int_diag.h"
#endif


const char* SwUartRxFrameToStr(const SwUartRxFrameState_t rx_frame_state) {
    char* name = "?";
    switch(rx_frame_state) {
        case SW_UART_RX_FRAME_STATE_IDLE:name = "Idle";  break;
        case SW_UART_RX_FRAME_STATE_REC:name = "Rec";  break;
        default:name = "?"; break;
    }
    return name;
}

const char* SwUartParityAlgoToStr(const SwUartParity_t parity) {
    char* name = "?";
    switch(parity) {
        case SW_UART_PARITY_NONE:name = "None";  break;
        case SW_UART_PARITY_ODD:name = "Odd";  break;
        case SW_UART_PARITY_EVEN:name = "Even";  break;
        default:name = "?"; break;
    }
    return name;
}

const char* SwUartFrameToStr(const SwUartFrameRx_t RxFrame) {
    strcpy(text, "");
    snprintf(text, sizeof(text), "%sFrame:0x%04x,", text, RxFrame.word);
    snprintf(text, sizeof(text), "%sSTART:%u,", text, RxFrame.start_bit);
    snprintf(text, sizeof(text), "%sDATA:%u=0x%02x,", text, RxFrame.byte, RxFrame.byte);
    snprintf(text, sizeof(text), "%sPARITY:%u,", text, RxFrame.parity);
    snprintf(text, sizeof(text), "%sSTOP1:%u,", text, RxFrame.stop1);
    snprintf(text, sizeof(text), "%sSTOP2:%u,", text, RxFrame.stop2);
    snprintf(text, sizeof(text), "%sRES:%u", text, RxFrame.res);
    return text;
}

const char* SwUartConfigTxToStr(const SwUartConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sGPIO_DAC%u,", text, Config->bin_dac_num);
        snprintf(text, sizeof(text), "%sTxOverSam:%u,", text, Config->tx_over_sampling);
        snprintf(text, sizeof(text), "%sTxTIM%u,", text, Config->tx_timer_num);
        snprintf(text, sizeof(text), "%sTx:%s,", text, GpioPadToStr(Config->Tx));
    }
    return text;
}

const char* SwUartConfigToStr(const SwUartConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sGPIO_DAC%u,", text, Config->bin_dac_num);
        snprintf(text, sizeof(text), "%sTxOverSam:%u,", text, Config->tx_over_sampling);
        snprintf(text, sizeof(text), "%sTxTIM%u,", text, Config->tx_timer_num);
        snprintf(text, sizeof(text), "%sBaudRate:%u,", text, Config->baud_rate);
        snprintf(text, sizeof(text), "%sSTOP:%u,", text, Config->stop_bit_cnt);
        snprintf(text, sizeof(text), "%sRxOverSam:%u,", text, Config->rx_over_sampling);
        snprintf(text, sizeof(text), "%sRxTIM%u,", text, Config->rx_timer_num);
        snprintf(text, sizeof(text), "%sPAR:%u,", text, Config->parity_check);
        snprintf(text, sizeof(text), "%sTx:%s,", text, GpioPadToStr(Config->Tx));
        snprintf(text, sizeof(text), "%sParity:%s,", text, SwUartParityAlgoToStr(Config->parity_check));
        snprintf(text, sizeof(text), "%sRx:%s,", text, GpioPadToStr(Config->Rx));
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* SwUartNodeToStr(const SwUartHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sRxState:%s,", text, SwUartRxFrameToStr(Node->rx_frame_state));
        snprintf(text, sizeof(text), "%sErrorCnt:%u,", text, Node->error_cnt);
        snprintf(text, sizeof(text), "%sParityOkCnt:%u,", text, Node->parity_ok);
        snprintf(text, sizeof(text), "%sParityErrCnt:%u,", text, Node->parity_err);
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
        snprintf(text, sizeof(text), "%sRxByte:0x%x=", text, Node->rx_byte);
        snprintf(text, sizeof(text), "%s[%c],", text, Node->rx_byte);
        //snprintf(text, sizeof(text), "%sEventCnt:%u,", text, Node->event_cnt);
        //snprintf(text, sizeof(text), "%sEvent:[%s],", text, ExtIntEventToStr1(&Node->Event));
        //snprintf(text, sizeof(text), "%sRxState:%s,", text, GpioLevelToStr(Node->rx_state));
        //snprintf(text, sizeof(text), "%sEvPause:%u us,", text, Node->event_pause_us);
        //snprintf(text, sizeof(text), "%sBitDuration:%u us,", text, Node->bit_duration_us);
        //snprintf(text, sizeof(text), "%sRxBitDiff:%u us,", text, Node->rx_bit_diff);
        //snprintf(text, sizeof(text), "%sPrevEvent:[%s],", text, ExtIntEventToStr1(&Node->PrevEvent));
    }
    return text;
}

bool sw_uart_diag_one(const uint8_t num) {
    bool res = false;
    const SwUartConfig_t *Config = SwUartGetConfig(num);
    if (Config) {
        LOG_INFO(SW_UART, "Cfg:%s", SwUartConfigToStr(Config));
        SwUartHandle_t *Node = SwUartGetNode(num);
        if (Node) {
            LOG_INFO(SW_UART, "Node:%s", SwUartNodeToStr(Node));
            res = true;
        }
    }
    return res;
}

bool sw_uart_diag(void) {
    bool res = false;
    const table_col_t cols[] = {
            {5, "Num"},
            {10, "baudRate"},
            {9, "rx"},
            {9, "tx"},
            {10, "name"},
    };
    uint32_t cnt = sw_uart_get_cnt() ;
    uint8_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 0; num < cnt; num++) {
        SwUartHandle_t* Node = SwUartGetNode(num);
        if(Node) {
            uint32_t baud_rate = 0;
            res = sw_uart_baudrate_get(num, &baud_rate);

            cli_printf(TSEP);
            cli_printf(" %2u  " TSEP, num);
            cli_printf(" %7u  " TSEP, baud_rate);
            cli_printf(" %7u " TSEP, Node->rx_cnt);
            cli_printf(" %7u " TSEP, Node->tx_cnt);
            cli_printf(" %7s  " TSEP, Node->name);
            cli_printf(CRLF);
            res = true;

        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
