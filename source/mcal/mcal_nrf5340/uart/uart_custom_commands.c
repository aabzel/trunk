#include "uart_custom_commands.h"

#include <inttypes.h>
#include <stdio.h>

//#include "base_cmd.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "ostream.h"
#include "table_utils.h"
#include "uart_mcal.h"
#include "uart_types.h"
#include "writer_config.h"
#include "string_reader.h"

#if 0
bool diag_uarts(ostream_t* stream) {
    LOG_NOTICE(SYS, "%s()", __FUNCTION__);

    static const table_col_t cols[] = {
        {16, "Name"}, {17, "Total chars"}, {13, "Lost chars"}, {11, "Strings"}, {11, "Errors"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    cli_printf(TABLE_LEFT "%15s " TABLE_SEPARATOR "%16" PRId64 " " TABLE_SEPARATOR "%12" PRId64 " " TABLE_SEPARATOR
                         "%10" PRId64 " " TABLE_SEPARATOR "%10" PRId64 " " TABLE_RIGHT CRLF,
              "cmd_reader", cmd_reader.total_char_count, cmd_reader.lost_char_count, cmd_reader.total_string_count,
              cmd_reader.error_count);

    cli_printf(TABLE_LEFT "dbg_o " T_SEP);
    cli_printf("%16d " T_SEP, dbg_o.total_char_count);
    cli_printf("%12d " T_SEP, dbg_o.lost_char_count);
    cli_printf("%10d " T_SEP CRLF, dbg_o.error_count);

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
#if 0
    cli_printf("rx %u byte " CRLF, huart[0].rx_byte_cnt);
    cli_printf("tx %u byte " CRLF, huart[0].tx_byte_cnt);
    cli_printf("tx cpl %u cnt " CRLF, huart[0].tx_cpl_cnt);
#endif
    return true;
}

bool cmd_uarts(int32_t argc, char* argv[]) {
    (void)argv;
    bool res = false;
    if (0==argc) {
        res = diag_uarts(&(curWriterPtr->stream));
    }
    return res;
}

// us 8 byte
// us 8 hex_string
bool uart_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(2 == argc) {
        res = true;
        uint8_t uart_num = 0;
        uint8_t array[256];
        uint32_t array_len = 0;
        res = try_str2uint8(argv[0], &uart_num);
        if(false == res) {
            LOG_ERROR(UART, "ParseErr UartNum [1....8]");
        }

        if(res) {
            res = try_str2array(argv[1], array, sizeof(array), &array_len);
            if(false == res) {
                LOG_ERROR(UART, "Unable to extract array %s", argv[1]);
                snprintf((char*)array, sizeof(array), "%s", argv[1]);
                array_len = strlen(argv[1]);
                res = true;
            }
        }

        if(res) {
            res = uart_send(uart_num, array, array_len);
            if(false == res) {
                LOG_ERROR(UART, "Unable to send UART");
            } else {
                cli_printf(CRLF);
            }
        }
    } else {
        LOG_ERROR(UART, "Usage: us instance hex_string");
        LOG_INFO(UART, "instance [1...8]");
        LOG_INFO(UART, "hex_string 0x[0...F]+");
    }
    return res;
}

bool uart_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(2 == argc) {
        res = true;
        uint8_t uart_num = 0;
        uint32_t baudrate = 0;
        res = try_str2uint8(argv[0], &uart_num);
        if(false == res) {
            LOG_ERROR(UART, "ParseErr UartNum [1....8]");
        }

        if(res) {
            res = try_str2uint32(argv[1], &baudrate);
            if(false == res) {
                LOG_ERROR(UART, "Unable to extract baudrate %s", argv[1]);
            }
        }

        if(res) {
            res = uart_set_baudrate(uart_num, baudrate);
            if(false == res) {
                LOG_ERROR(UART, "Unable to set baudrate");
            }
        }
    } else {
        LOG_ERROR(UART, "Usage: us instance baudrate");
        LOG_INFO(UART, "instance [0...1]");
        LOG_INFO(UART, "baudrate ");
    }
    return res;
}

bool uart_diag_low_level_command(int32_t argc, char* argv[]){
    bool res=false;
    const table_col_t cols[] = {{5, "Num"},       {7, "manti"}, {7, "fract"}, {7, "overS"},
                                {10, "baudRate"},    {10, "name"}};
    uint32_t baud_rate = 0;
    uint16_t mantissa = 0;
    uint16_t fraction = 0;
    uint8_t uart_num = 0;
    uint8_t over_sampling = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(uart_num = 1; uart_num <= UART_COUNT; uart_num++) {
            cli_printf(TSEP);
            cli_printf(" %02u  " TSEP, uart_num);
            baud_rate = uart_get_baud_rate(uart_num, &mantissa, &fraction, &over_sampling);
            cli_printf(" %5u " TSEP, mantissa);
            cli_printf(" %5u " TSEP, fraction);
            cli_printf(" %2u    " TSEP, over_sampling);
            cli_printf(" %7u  " TSEP, baud_rate);
            const UartConfig_t* UartConfNode = UartGetConfNode(uart_num);
            if(UartConfNode) {
                cli_printf(" %7s  " TSEP, UartConfNode->name);
            }
            res=true;
            cli_printf(CRLF);

    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool uart_set_baudrate_command(int32_t argc, char* argv[]){
    bool res=false;
    uint32_t baudrate=0;
    uint8_t uart_num = 0;
    if(2==argc){
        res = try_str2uint8(argv[0], &uart_num);
        if(false == res) {
            LOG_ERROR(UART, "ParseErr UartNum [1....N]");
        }
        res = try_str2uint32(argv[1], &baudrate);
        if(false == res) {
            LOG_ERROR(UART, "Unable to extract baudrate %s", argv[1]);
        }
    }
    if(res){
        res = uart_set_baudrate(uart_num, baudrate);
        if(res){
            LOG_INFO(UART,LOG_OK);
        }
    }
    return res;
}

/*TODO: calculate */
bool uart_diag_command(int32_t argc, char* argv[]) {
    bool res=false;
    const table_col_t cols[] = {{5, "Num"},       {7, "manti"}, {7, "fract"}, {7, "overS"},
                                {10, "baudRate"}, {9, "rx"},    {9, "tx"},  {9, "ByteTxUs"},     {10, "name"}
    ,     {9, "ErrHeap"},{9,"TxTimeOut"}

    };
    uint32_t baud_rate = 0;
    uint16_t mantissa = 0;
    uint16_t fraction = 0;
    uint8_t uart_num = 0;
    uint8_t over_sampling = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(uart_num = 0; uart_num < UART_COUNT; uart_num++) {
        UartHandle_t* UartNode = UartGetNode(uart_num);
        if(UartNode){
            cli_printf(TSEP);
            cli_printf(" %02u  " TSEP, uart_num);
            baud_rate = uart_get_baud_rate(uart_num, &mantissa, &fraction, &over_sampling);
            cli_printf(" %05u " TSEP, mantissa);
            cli_printf(" %05u " TSEP, fraction);
            cli_printf(" %02u    " TSEP, over_sampling);
            if(0 < baud_rate) {
                cli_printf(" %07u  " TSEP, baud_rate);
            } else {
                cli_printf("          " TSEP, baud_rate);
            }
            cli_printf(" %07u " TSEP, UartNode->rx_cnt);
            cli_printf(" %07u " TSEP, UartNode->tx_cnt);
            cli_printf(" %07u " TSEP, UartNode->real_byte_tx_time_us);
            const UartConfig_t* UartConfNode = UartGetConfNode(uart_num);
            if(UartConfNode) {
                cli_printf(" %7s  " TSEP, UartConfNode->name);
            }
            cli_printf(" %07u " TSEP, UartNode->err_heap);
            cli_printf(" %07u " TSEP, UartNode->tx_time_out_cnt);
            res = true;

            cli_printf(CRLF);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

#endif
