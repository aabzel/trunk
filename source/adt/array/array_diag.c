#include "array_diag.h"

#include <stdio.h>

#ifdef HAS_NUM_DIAG
#include "num_to_str.h"
#endif

#include "convert.h"
#include "debug_info.h"
#include "log.h"
#include "shared_array.h"
#include "table_utils.h"
#include "writer_config.h"

bool array_i32_print(const int32_t* const array, size_t size, double step) {
    bool res = false;
    static const table_col_t cols[] = {
        {7, "i"}, {7, "step"}, {12, "DataHex"}, {12, "DataDec"}, {43, "DataBin"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    size_t i = 0;
    char log_line[150];
    double up_time = 0.0;
    for(i = 0; i < size; i++) {
        up_time = ((double)i) * step;
        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, i);
        snprintf(log_line, sizeof(log_line), "%s %5.3f " TSEP, log_line, up_time);
        snprintf(log_line, sizeof(log_line), "%s 0x%08x " TSEP, log_line, (uint32_t)array[i]);
        snprintf(log_line, sizeof(log_line), "%s %10d " TSEP, log_line, (int32_t)array[i]);
#ifdef HAS_BIN_2_STR
        snprintf(log_line, sizeof(log_line), "%s 0b%s " TSEP, log_line, utoa_bin32(array[i]));
#endif
        cli_printf("%s" CRLF, log_line);
        res = true;
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool array_double_i16_print(const int16_t* const array1, const int16_t* const array2, size_t size, double step) {
    bool res = false;
    static const table_col_t cols[] = {
        {7, "i"}, {7, "step"}, {8, "Data1Hex"}, {7, "Data1Dec"}, {8, "Data2Hex"}, {7, "Data2Dec"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    size_t i = 0;
    char log_line[150];
    double up_time = 0.0;
    for(i = 0; i < size; i++) {
        up_time = ((double)i) * step;
        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, i);
        snprintf(log_line, sizeof(log_line), "%s %5.3f " TSEP, log_line, up_time);
        snprintf(log_line, sizeof(log_line), "%s 0x%04x " TSEP, log_line, (uint16_t)array1[i]);
        snprintf(log_line, sizeof(log_line), "%s %5d " TSEP, log_line, (int16_t)array1[i]);
        snprintf(log_line, sizeof(log_line), "%s 0x%04x " TSEP, log_line, (uint16_t)array2[i]);
        snprintf(log_line, sizeof(log_line), "%s %5d " TSEP, log_line, (int16_t)array2[i]);
        cli_printf("%s" CRLF, log_line);
        res = true;
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool array_i16_print(const int16_t* const array, size_t size, double step) {
    bool res = false;
    static const table_col_t cols[] = {
        {7, "i"}, {7, "step"}, {8, "DataHex"}, {7, "DataDec"}, {23, "DataBin"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    size_t i = 0;
    char log_line[150];
    double up_time = 0.0;
    for(i = 0; i < size; i++) {
        up_time = ((double)i) * step;
        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, i);
        snprintf(log_line, sizeof(log_line), "%s %5.3f " TSEP, log_line, up_time);
        snprintf(log_line, sizeof(log_line), "%s 0x%04x " TSEP, log_line, (uint16_t)array[i]);
        snprintf(log_line, sizeof(log_line), "%s %5d " TSEP, log_line, (int16_t)array[i]);

#ifdef HAS_BIN_2_STR
        snprintf(log_line, sizeof(log_line), "%s 0b%s " TSEP, log_line, utoa_bin16(array[i]));
#endif
        cli_printf("%s" CRLF, log_line);
        res = true;
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool array_i8_print(const int8_t* const data, size_t size) {
    uint32_t i = 0;
    bool res = false;
    if(data) {
        if(size) {
            for(i = 0; i < size; i++) {
                cli_printf("%d,", data[i]);
            }
            res = true;
        }
    }
    return res;
}

bool array_u32_print(const uint32_t* const data, size_t size) {
    uint32_t i = 0;
    bool res = false;
    if(data) {
        if(size) {
            for(i = 0; i < size; i++) {
                cli_printf("%08X", data[i]);
            }
            res = true;
        }
    }
    return res;
}

bool array_u16_print(const uint16_t* const data, size_t size) {
    uint32_t i = 0;
    bool res = false;
    if(data) {
        if(size) {
            for(i = 0; i < size; i++) {
                cli_printf("%04X", data[i]);
            }
            res = true;
        }
    }
    return res;
}

bool array_u16_print_bin(const uint16_t* const data, size_t size) {
    uint32_t i = 0;
    bool res = false;
    if(data) {
        if(size) {
            for(i = 0; i < size; i++) {
#ifdef HAS_BIN_2_STR
                cli_printf("%s", utoa_bin16_plain(data[i]));
#endif
            }
            res = true;
        }
    }
    return res;
}

bool array_u8_print(const uint8_t* const data, size_t size) {
    uint32_t i = 0;
    bool res = false;
    if(data) {
        if(size) {
            for(i = 0; i < size; i++) {
                cli_printf("%02X", data[i]);
            }
            res = true;
        }
    }
    return res;
}

bool array_u8_print_dec(const uint8_t* const data, size_t size) {
    uint32_t i = 0;
    bool res = false;
    if(data) {
        if(size) {
            for(i = 0; i < size; i++) {
                cli_printf("%1u,", data[i]);
            }
            res = true;
        }
    }
    return res;
}

bool array_i8_print_dec(const int8_t* const data, size_t size) {
    uint32_t i = 0;
    bool res = false;
    if(data) {
        if(size) {
            for(i = 0; i < size; i++) {
                cli_printf("%1d,", data[i]);
            }
            res = true;
        }
    }
    return res;
}

const char* ArrayToAsciiStr(const uint8_t* const array, size_t size) {
    if(array) {
        memset(text, 0, sizeof(text));
        if(size < sizeof(text)) {
            memcpy(text, array, size);
        }
    }
    return text;
}

const char* ArrayToStr(const uint8_t* const array, size_t size) {
	static char lText[200]={0};
    if(array) {
        if(size) {
            strcpy(lText, "");
            array2str(array, size, lText, sizeof(lText));
        }
    }
    return text;
}

bool print_bin(uint8_t const* const buff, uint32_t size, uint16_t indent) {
    uint32_t i = 0;
    bool res = false;
    res = print_indent(indent);
    for(i = 0; i < size; i++) {
        cli_printf("%02x", buff[i]);
    }
    return res;
}

bool print_mem(const uint8_t* const addr, int32_t len, bool is_bin, bool is_ascii, bool new_line, bool is_packed) {
    bool res = false;
    LOG_DEBUG(ARRAY, "Rx:%u Byte", len);
    if(len && addr) {
        uint32_t pos = 0;
        uint32_t print_len = 0;
        int32_t rem = 0;
        if(16 <= len) {
            for(pos = 0; pos < (len - 16); pos += 16) {
                res = true;
                if(is_bin) {
                    print_bin(&addr[pos], 16, 0);
                }
                if(is_ascii) {
                    print_ascii_line((char*)&addr[pos], 16, 4);
                }
                print_len += 16;
                if(is_packed) {
                    cli_printf(CRLF);
                }
            }
        }
        rem = len - print_len;

        if(0 < rem) {
            res = true;
            pos = len / 16;
            if(is_bin) {
                print_bin(&addr[print_len], rem, 0);
            }
            if(is_ascii) {
                print_ascii_line((char*)&addr[print_len], rem, 2 * (16 - rem) + 4);
            }
        }
        if(new_line) {
            cli_printf(CRLF);
        }
    }
    return res;
}

bool print_hex(const uint8_t* const buff, const uint32_t size) {
    bool res = false;
    LOG_DEBUG(ARRAY, "Start:0x%p,size:%u", buff, size);
    if(0 < size) {
        if(buff) {
            res = print_bin(buff, size, 0);
            if(false == res) {
                LOG_ERROR(ARRAY, "PrintErr");
            }
        }
    }
    cli_printf(CRLF);
    return res;
}
