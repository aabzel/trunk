#include "swd_commands.h"

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
#include "swd_mcal.h"
#include "swd_types.h"
#include "writer_config.h"

bool swd_wait_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t data[256];
    size_t size = 0;

    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SWD, "ParseErr SwdNum [1....8]");
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], data, sizeof(data), &size);
        if(false == res) {
            LOG_WARNING(SWD, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)data, sizeof(data), "%s", argv[1]);
            size = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = swd_wait_send(num, data, size);
        if(false == res) {
            LOG_ERROR(SWD, "%u SendErr", num);
        } else {
            cli_printf(CRLF);
        }
    } else {
        LOG_ERROR(SWD, "Usage: uws Num hex_string");
        LOG_INFO(SWD, "Num [1...%u]", SWD_COUNT);
        LOG_INFO(SWD, "hex_string 0x[0...F]+");
    }
    return res;
}

bool swd_dma_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    size_t size = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SWD, "ParseErr SwdNum [1....%u]", SWD_COUNT);
        }
    }

    uint8_t data[256] = {0};
    if(2 <= argc) {
        res = try_str2array(argv[1], data, sizeof(data), &size);
        if(false == res) {
            LOG_WARNING(SWD, "ExtractHexArrayErr [%s]", argv[1]);
            snprintf((char*)data, sizeof(data), "%s", argv[1]);
            size = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = true;
#ifdef HAS_DMA
        res = swd_dma_send_wait(num, data, size);
        if(res) {
            cli_printf(CRLF);
            LOG_INFO(SWD, "SWD%u,SendOk", num);
        } else {
            LOG_ERROR(SWD, "SWD%u,SendErr", num);
        }
#endif
    } else {
        LOG_ERROR(SWD, "Usage: udms Num hex_string");
        LOG_INFO(SWD, "Num [1...%u]", SWD_COUNT);
        LOG_INFO(SWD, "hex_string 0x[0...F]+");
    }
    return res;
}

bool swd_send_wait_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t data[256];
    size_t size = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SWD, "ParseErr SwdNum [1....8]");
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], data, sizeof(data), &size);
        if(false == res) {
            LOG_WARNING(SWD, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)data, sizeof(data), "%s", argv[1]);
            size = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = swd_send_wait(num, data, size);
        if(false == res) {
            LOG_ERROR(SWD, "%u SendErr", num);
        } else {
            cli_printf(CRLF);
        }
    } else {
        LOG_ERROR(SWD, "Usage: usw Num hex_string");
        LOG_INFO(SWD, "Num [1...%u]", SWD_COUNT);
        LOG_INFO(SWD, "hex_string 0x[0...F]+");
    }
    return res;
}
// us 8 byte
// us 8 hex_string
bool swd_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t data[256];
    size_t size = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SWD, "ParseErr SwdNum [1....8]");
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], data, sizeof(data), &size);
        if(false == res) {
            LOG_WARNING(SWD, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)data, sizeof(data), "%s", argv[1]);
            size = strlen(argv[1]);
            res = true;
        } else {
        }
    }

    if(res) {
        res = swd_send_api(num, data, size);
        if(false == res) {
            LOG_ERROR(SWD, "%u SendErr", num);
        } else {
            print_hex(data, size);
            LOG_INFO(SWD, "%u SendOk %u byte", num, size);
            cli_printf(CRLF);
        }
    } else {
        LOG_ERROR(SWD, "Usage: us Num hex_string");
        LOG_INFO(SWD, "Num [1...%u]", SWD_COUNT);
        LOG_INFO(SWD, "hex_string 0x[0...F]+");
    }
    return res;
}

bool swd_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SWD, "ParseErr SwdNum [1....8]");
        }
    }
    if(res) {
        res = swd_init_one(num);
        if(res) {
            LOG_INFO(SWD, "InitOk");
        } else {
            LOG_ERROR(SWD, "InitErr");
        }
    } else {
        LOG_ERROR(SWD, "Usage: ui Num ");
        LOG_INFO(SWD, "Num [1...%u]", SWD_COUNT);
        LOG_INFO(SWD, "baudrate ");
    }
    return res;
}

bool swd_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    const table_col_t cols[] = {{5, "Num"}, {7, "manti"}, {7, "fract"}, {7, "overS"}, {10, "baudRate"}, {10, "name"}};
    uint32_t baud_rate = 0;
    uint16_t mantissa = 0;
    uint16_t fraction = 0;
    uint8_t num = 0;
    uint8_t over_sampling = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 1; num <= SWD_COUNT; num++) {
        cli_printf(TSEP);
        cli_printf(" %2u  " TSEP, num);
        baud_rate = swd_get_baud_rate(num, &mantissa, &fraction, &over_sampling);
        cli_printf(" %5u " TSEP, mantissa);
        cli_printf(" %5u " TSEP, fraction);
        cli_printf(" %2u    " TSEP, over_sampling);
        cli_printf(" %7u  " TSEP, baud_rate);
        const SwdConfig_t* Config = SwdGetConfig(num);
        if(Config) {
            cli_printf(" %7s  " TSEP, Config->name);
        }
        res = true;
        cli_printf(CRLF);
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool swd_set_baudrate_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t baudrate = 0;
    uint8_t num = 0;
    if(2 == argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SWD, "ParseErr SwdNum [1....N]");
        }
        res = try_str2uint32(argv[1], &baudrate);
        if(false == res) {
            LOG_ERROR(SWD, "Err extract baudrate %s", argv[1]);
        }
    }
    if(res) {
        res = swd_set_baudrate(num, baudrate);
        if(res) {
            LOG_INFO(SWD, LOG_OK);
        }
    }
    return res;
}

/*TODO: calculate */
bool swd_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    const table_col_t cols[] = {{5, "Num"}, {7, "manti"},    {7, "fract"}, {7, "overS"},   {10, "baudRate"}, {9, "rx"},
                                {9, "tx"},  {9, "ByteTxUs"}, {10, "name"}, {9, "ErrHeap"}, {9, "TxTimeOut"}

    };
    uint32_t baud_rate = 0;
    uint16_t mantissa = 0;
    uint16_t fraction = 0;
    uint8_t num = 0;
    uint8_t over_sampling = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 0; num < SWD_COUNT; num++) {
        SwdHandle_t* SwdNode = SwdGetNode(num);
        if(SwdNode) {
            cli_printf(TSEP);
            cli_printf(" %2u  " TSEP, num);
            baud_rate = swd_get_baud_rate(num, &mantissa, &fraction, &over_sampling);
            cli_printf(" %5u " TSEP, mantissa);
            cli_printf(" %5u " TSEP, fraction);
            cli_printf(" %2u    " TSEP, over_sampling);
            if(0 < baud_rate) {
                cli_printf(" %7u  " TSEP, baud_rate);
            } else {
                cli_printf("          " TSEP, baud_rate);
            }
            cli_printf(" %7u " TSEP, SwdNode->rx_cnt);
            cli_printf(" %7u " TSEP, SwdNode->tx_cnt);
            cli_printf(" %7u " TSEP, SwdNode->real_byte_tx_time_us);
            const SwdConfig_t* Config = SwdGetConfig(num);
            if(Config) {
                cli_printf(" %7s  " TSEP, Config->name);
            }
            cli_printf(" %7u " TSEP, SwdNode->err_heap);
            cli_printf(" %7u " TSEP, SwdNode->tx_time_out_cnt);
            res = true;

            cli_printf(CRLF);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
