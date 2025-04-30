#include "uart_commands.h"

#include <inttypes.h>

#include "base_cmd.h"
#include "convert.h"
#include "data_utils.h"
#include "io_utils.h"
#include "log.h"
#include "ostream.h"
#include "table_utils.h"
#include "uart_common.h"
#include "uart_drv.h"
#include "writer_config.h"
#include "uart_string_reader.h"

bool diag_page_uarts(ostream_t* stream) {
    LOG_NOTICE(SYS, "%s()", __FUNCTION__);

    static const table_col_t cols[] = {
        {16, "Name"}, {17, "Total chars"}, {13, "Lost chars"}, {11, "Strings"}, {11, "Errors"},
    };

    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    io_printf(TABLE_LEFT "%15s " TABLE_SEPARATOR "%16" PRId64 " " TABLE_SEPARATOR "%12" PRId64 " " TABLE_SEPARATOR
                         "%10" PRId64 " " TABLE_SEPARATOR "%10" PRId64 " " TABLE_RIGHT CRLF,
              "cmd_reader", cmd_reader.total_char_count, cmd_reader.lost_char_count, cmd_reader.total_string_count,
              cmd_reader.error_count);

    io_printf(TABLE_LEFT "dbg_o " T_SEP);
    io_printf("%16lld " T_SEP, dbg_o.total_char_count);
    io_printf("%12lld " T_SEP, dbg_o.lost_char_count);
    io_printf("%10lld " T_SEP CRLF, dbg_o.error_count);

    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));

   // io_printf("rx %u byte " CRLF, huart[0].rx_byte_cnt);
   // io_printf("tx %u byte " CRLF, huart[0].tx_byte_cnt);
    io_printf("tx cpl %u cnt " CRLF, huart[0].tx_cpl_cnt);
    return true;
}

bool cmd_uarts(int32_t argc, char* argv[]) {
    (void)argv;
    if(argc != 0) {
        LOG_ERROR(UART, "Usage: uarts: help");
        return dump_cmd_result(false);
    }
    return diag_page_uarts(&(curWriterPtr->s));
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
            LOG_ERROR(UART, "Unable to parse UART Number [1....8]");
        }

        if(true == res) {
            res = try_str2array(argv[1], array, sizeof(array), &array_len);
            if(false == res) {
                LOG_ERROR(UART, "Unable to extract array %s", argv[1]);
            }
        }

        if(true == res) {
            res = uart_send(uart_num, array, array_len, true);
            if(false == res) {
                LOG_ERROR(UART, "Unable to send UART");
            } else {
                io_printf(CRLF);
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
            LOG_ERROR(UART, "Unable to parse UART Number [1....8]");
        }

        if(true == res) {
            res = try_str2uint32(argv[1], &baudrate);
            if(false == res) {
                LOG_ERROR(UART, "Unable to extract baudrate %s", argv[1]);
            }
        }

        if(true == res) {
            res = usart_set_baudrate(uart_num, baudrate);
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

/*TODO: calculate */
bool uart_diag_command(int32_t argc, char* argv[]) {
    const table_col_t cols[] = {{5, "Num"},       {7, "manti"}, {7, "fract"}, {7, "overS"},
                                {10, "baudRate"}, {9, "rx"},    {9, "tx"},    {10, "name"}};
    uint32_t baud_rate = 0;
    uint16_t mantissa = 0;
    uint16_t fraction = 0;
    uint8_t uart_num = 0;
    uint8_t over_sampling = 0;
    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    for(uart_num = 0; uart_num < UART_COUNT; uart_num++) {
        io_printf(TSEP);
        io_printf(" %02u  " TSEP, uart_num);
        baud_rate = uart_get_baud_rate(uart_num, &mantissa, &fraction, &over_sampling);
        io_printf(" %05u " TSEP, mantissa);
        io_printf(" %05u " TSEP, fraction);
        io_printf(" %02u    " TSEP, over_sampling);
        if(0 < baud_rate) {
            io_printf(" %07u  " TSEP, baud_rate);
        } else {
            io_printf("          " TSEP);
        }
        io_printf(" %07u " TSEP, huart[uart_num].rx_cnt);
        io_printf(" %07u " TSEP, huart[uart_num].tx_cnt);
        io_printf(" %7s  " TSEP, huart[uart_num].name);
        io_printf(CRLF);
    }
    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    return false;
}
