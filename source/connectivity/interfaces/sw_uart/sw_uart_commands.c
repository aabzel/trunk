#include "sw_uart_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "array_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "log.h"
#include "ostream.h"
#include "string_reader.h"
#include "test_sw_uart.h"
#include "table_utils.h"
#include "sw_uart_mcal.h"
#include "writer_config.h"

// us 8 byte
// us 8 hex_string
bool sw_uart_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t data[256];
    uint32_t size = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SW_UART, "ParseErr SwUartNum [1....8]");
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], data, sizeof(data), &size);
        if(false == res) {
            LOG_WARNING(SW_UART, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)data, sizeof(data), "%s", argv[1]);
            size = strlen(argv[1]);
            res = true;
        } else {
        }
    }

    if(res) {
        res = sw_uart_mcal_send(num, data, size);
        if(false == res) {
            LOG_ERROR(SW_UART, "%u SendErr", num);
        } else {
#ifdef HAS_ARRAY_DIAG
            print_hex(data, size);
#endif
            LOG_INFO(SW_UART, "%u SendOk %u byte", num, size);
            cli_printf(CRLF);
        }
    } else {
        LOG_ERROR(SW_UART, "Usage: sus Num hex_string");
    }
    return res;
}

bool sw_uart_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SW_UART, "ParseErr SwUartNum [1....8]");
        }
    }
    if(res) {
        res = sw_uart_init_one(num);
        if(res) {
            LOG_INFO(SW_UART, "InitOk");
        } else {
            LOG_ERROR(SW_UART, "InitErr");
        }
    } else {
        LOG_ERROR(SW_UART, "Usage: sui Num ");
    }
    return res;
}

bool sw_uart_set_baudrate_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t baudrate = 0;
    uint8_t num = 0;
    if(2 == argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SW_UART, "ParseErr SwUartNum [1....N]");
        }
        res = try_str2uint32(argv[1], &baudrate);
        if(false == res) {
            LOG_ERROR(SW_UART, "Err extract baudrate %s", argv[1]);
        }
    }
    if(res) {
        res = sw_uart_baudrate_set(num, baudrate);
        if(res) {
            LOG_INFO(SW_UART, LOG_OK);
        }
    } else {
        LOG_ERROR(SW_UART, "Usage: sui Num ");
    }
    return res;
}

bool sw_uart_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = sw_uart_diag();
    return res;
}


bool test_sw_uart_tx_all_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t time_out_ms = 0;
    if(2 == argc) {
        res = try_str2uint8(argv[0], &num);
        res = try_str2uint32(argv[1], &time_out_ms);
    }

    if(res) {
        res = test_sw_uart_tx_all(num, time_out_ms);
        if(res) {
            LOG_INFO(SW_UART, LOG_OK);
        }
    } else {
        LOG_ERROR(SW_UART, "Usage: suto Num TimeOutMs");
    }
    return res;
}
