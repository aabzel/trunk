#include "uart_diag.h"

#include "common_diag.h"
#include "debugger.h"
#include "diag_inc.h"
#include "mcal_diag.h"
#include "uart_mcal.h"
#ifdef HAS_GPIO_DIAG
#include "gpio_diag.h"
#endif

#ifdef HAS_UART_CUSTOM
#include "uart_custom_types.h"
#endif

#ifdef HAS_DMA_CHANNEL
#include "dma_channel_diag.h"
#endif

const char* UartConfigToStr(const UartConfig_t* const Config) {
    if(Config) {
        memset(text, 0, sizeof(text));
        strcpy(text, "");
        sprintf(text, "UART%u,", Config->num);
        snprintf(text, sizeof(text), "%sBaudRate:%u Hz,", text, Config->baud_rate);
        snprintf(text, sizeof(text), "%sS%u,", text, Config->stop_bit_cnt);
        snprintf(text, sizeof(text), "%sParity:%u,", text, Config->parity_check);
        snprintf(text, sizeof(text), "%sWordLen:%u,", text, Config->word_len_bit);
        snprintf(text, sizeof(text), "%sMvMode:%s,", text, McalMoveModeToStr(Config->momve_method));
        snprintf(text, sizeof(text), "%sINT:%s,", text, OnOffToStr(Config->interrupts_on));
#ifdef HAS_GPIO_DIAG
        snprintf(text, sizeof(text), "%sMOSI:%s,", text, GpioPadToStr(Config->RxPad));
        snprintf(text, sizeof(text), "%sMISO:%s,", text, GpioPadToStr(Config->TxPad));
#endif
        snprintf(text, sizeof(text), "%sIRQp:%u,", text, Config->irq_priority);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sRxBuff:0x%p,", text, Config->RxFifoArray);
        snprintf(text, sizeof(text), "%sRxSz:%u,", text, Config->rx_buff_size);
        snprintf(text, sizeof(text), "%sTxBuff:0x%p,", text, Config->TxFifoArray);
        snprintf(text, sizeof(text), "%sTxSz:%u,", text, Config->tx_buff_size);
#ifdef HAS_DMA_CHANNEL
        snprintf(text, sizeof(text), "%sDmaTx:%s,", text, DmaPadToStr(Config->DmaTx));
        snprintf(text, sizeof(text), "%sDmaRx:%s,", text, DmaPadToStr(Config->DmaRx));
#endif
    }

    return text;
}

bool UartDiagConfig(const UartConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(UART, "%s", UartConfigToStr(Config));
    }

    return res;
}

bool uart_raw_reg_diag(uint8_t num) {
    bool res = false;
#ifdef HAS_UART_CUSTOM
    const UartInfo_t* Info = UartGetInfo(num);
    if(Info) {
        LOG_INFO(UART, "UART%u,Base:0x%p", num, Info->UARTx);
        uint32_t reg_cnt = uart_reg_cnt();
        res = debug_raw_reg_diag(UART, (uint32_t)Info->UARTx, UartRegs, reg_cnt);
    }
#endif
    return res;
}

bool uart_diag(void) {
    bool res = false;
    const table_col_t cols[] = {{5, "Num"}, {10, "baudRate"}, {10, "name"},    {9, "rx"},
                                {9, "tx"},  {9, "ByteTxUs"},  {9, "TxTimeOut"}};
    uint8_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 0; num < UART_COUNT; num++) {
        UartHandle_t* Node = UartGetNode(num);
        if(Node) {
            uint32_t baud_rate = 0;
            res = uart_get_baud_rate(num, &baud_rate);
            char temp_str[120];
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, num);
            snprintf(temp_str, sizeof(temp_str), "%s %8u " TSEP, temp_str, baud_rate);
            snprintf(temp_str, sizeof(temp_str), "%s   %7s " TSEP, temp_str, Node->name);
            snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, Node->rx_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, Node->tx_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s  %7u  " TSEP, temp_str, Node->real_byte_tx_time_us);
            snprintf(temp_str, sizeof(temp_str), "%s  %7u " TSEP, temp_str, Node->tx_time_out_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s" CRLF, temp_str);
            cli_printf("%s" CRLF, temp_str);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
