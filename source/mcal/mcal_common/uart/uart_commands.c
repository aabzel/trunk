#include "uart_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "array_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "log.h"
#include "ostream.h"
#include "string_reader.h"
#include "table_utils.h"
#include "uart_mcal.h"
#include "uart_types.h"
#include "writer_config.h"

bool uart_wait_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t size = 0;

    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(UART, "ParseErr UartNum [1....8]");
        }
    }

    uint8_t data[256];
    if(2 <= argc) {
        res = try_str2array(argv[1], data, sizeof(data), &size);
        if(false == res) {
            LOG_WARNING(UART, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)data, sizeof(data), "%s", argv[1]);
            size = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = uart_wait_send(num, data, size);
        if(false == res) {
            LOG_ERROR(UART, "%u SendErr", num);
        } else {
            cli_printf(CRLF);
        }
    } else {
        LOG_ERROR(UART, "Usage: uws Num hex_string");
        LOG_INFO(UART, "Num [1...%u]", UART_COUNT);
        LOG_INFO(UART, "hex_string 0x[0...F]+");
    }
    return res;
}

bool uart_dma_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t size = 0;
    uint8_t data[256] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(UART, "ParseErr UartNum [1....%u]", UART_COUNT);
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], data, sizeof(data), &size);
        if(false == res) {
            LOG_WARNING(UART, "ExtractHexArrayErr [%s]", argv[1]);
            snprintf((char*)data, sizeof(data), "%s", argv[1]);
            size = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = true;
#ifdef HAS_DMA
        res = uart_dma_send_wait(num, data, size);
        if(res) {
            cli_printf(CRLF);
            LOG_INFO(UART, "UART%u,SendOk", num);
        } else {
            LOG_ERROR(UART, "UART%u,SendErr", num);
        }
#endif
    } else {
        LOG_ERROR(UART, "Usage: udms Num hex_string");
        LOG_INFO(UART, "Num [1...%u]", UART_COUNT);
        LOG_INFO(UART, "hex_string 0x[0...F]+");
    }
    return res;
}

bool uart_send_wait_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t data[256] = {0};
    uint32_t size = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(UART, "ParseErr UartNum [1....8]");
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], data, sizeof(data), &size);
        if(false == res) {
            LOG_WARNING(UART, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)data, sizeof(data), "%s", argv[1]);
            size = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = uart_send_wait(num, data, size);
        if(false == res) {
            LOG_ERROR(UART, "%u SendErr", num);
        } else {
            cli_printf(CRLF);
        }
    } else {
        LOG_ERROR(UART, "Usage: usw Num hex_string");
        LOG_INFO(UART, "Num [1...%u]", UART_COUNT);
        LOG_INFO(UART, "hex_string 0x[0...F]+");
    }
    return res;
}
// us 8 byte
// us 8 hex_string
bool uart_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t data[256];
    uint32_t size = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(UART, "ParseErr UartNum [1....8]");
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], data, sizeof(data), &size);
        if(false == res) {
            LOG_WARNING(UART, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)data, sizeof(data), "%s", argv[1]);
            size = strlen(argv[1]);
            res = true;
        } else {
        }
    }

    if(res) {
        res = uart_mcal_send(num, data, size);
        if(false == res) {
            LOG_ERROR(UART, "%u SendErr", num);
        } else {
#ifdef HAS_ARRAY_DIAG
            print_hex(data, size);
#endif
            LOG_INFO(UART, "%u SendOk %u byte", num, size);
            cli_printf(CRLF);
        }
    } else {
        LOG_ERROR(UART, "Usage: us Num hex_string");
        LOG_INFO(UART, "Num [1...%u]", UART_COUNT);
        LOG_INFO(UART, "hex_string 0x[0...F]+");
    }
    return res;
}

bool uart_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(UART, "ParseErr UartNum [1....8]");
        }
    }
    if(res) {
        res = uart_init_one(num);
        if(res) {
            LOG_INFO(UART, "InitOk");
        } else {
            LOG_ERROR(UART, "InitErr");
        }
    } else {
        LOG_ERROR(UART, "Usage: ui Num ");
        LOG_INFO(UART, "Num [1...%u]", UART_COUNT);
        LOG_INFO(UART, "baudrate ");
    }
    return res;
}

bool uart_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    const table_col_t cols[] = {{5, "Num"}, {7, "overS"}, {10, "baudRate"}, {10, "name"}};
    uint32_t baud_rate = 0;
    uint8_t num = 0;
    uint8_t over_sampling = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 1; num <= UART_COUNT; num++) {
        cli_printf(TSEP);
        cli_printf(" %2u  " TSEP, num);
        res = uart_get_baud_rate(num, &baud_rate);

        cli_printf(" %2u    " TSEP, over_sampling);
        cli_printf(" %7u  " TSEP, baud_rate);
        const UartConfig_t* Config = UartGetConfig(num);
        if(Config) {
            cli_printf(" %7s  " TSEP, Config->name);
        }
        res = true;
        cli_printf(CRLF);
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool uart_set_baudrate_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t baudrate = 0;
    uint8_t num = 0;
    if(2 == argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(UART, "ParseErr UartNum [1....N]");
        }
        res = try_str2uint32(argv[1], &baudrate);
        if(false == res) {
            LOG_ERROR(UART, "Err extract baudrate %s", argv[1]);
        }
    }
    if(res) {
        res = uart_set_baudrate(num, baudrate);
        if(res) {
            LOG_INFO(UART, LOG_OK);
        }
    }
    return res;
}

/*TODO: calculate */
bool uart_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    const table_col_t cols[] = {{5, "Num"},   {10, "baudRate"}, {9, "rx"},       {9, "tx"}, {9, "ByteTxUs"},
                                {10, "name"}, {9, "ErrHeap"},   {9, "TxTimeOut"}

    };
    uint32_t baud_rate = 0;
    uint8_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 0; num < UART_COUNT; num++) {
        UartHandle_t* Node = UartGetNode(num);
        if(Node) {
            cli_printf(TSEP);
            cli_printf(" %2u  " TSEP, num);
            res = uart_get_baud_rate(num, &baud_rate);
            cli_printf(" %7u  " TSEP, baud_rate);
            cli_printf(" %7u " TSEP, Node->rx_cnt);
            cli_printf(" %7u " TSEP, Node->tx_cnt);
            cli_printf(" %7u " TSEP, Node->real_byte_tx_time_us);
            const UartConfig_t* Config = UartGetConfig(num);
            if(Config) {
                cli_printf(" %7s  " TSEP, Config->name);
            }
            cli_printf(" %7u " TSEP, Node->err_heap);
            cli_printf(" %7u " TSEP, Node->tx_time_out_cnt);
            res = true;

            cli_printf(CRLF);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
