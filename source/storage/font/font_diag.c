#include "font_diag.h"

#include <string.h>

#include "byte_utils.h"
#include "convert.h"
#include "data_types.h"
#include "log.h"

#ifndef HAS_FONT_DIAG
#error "+HAS_FONT_DIAG"
#endif

bool font_diag_char_raw(char letter, Font_t font) {
    bool res = false;
    int8_t i = 0;

    cli_printf(CRLF);
    uint16_t code = 0;
    uint8_t chr_ind = letter - ' ';
    uint8_t byte_cnt = Font2Size(font);
    int8_t byte_in_row = Font2ByteInRow(font);
    LOG_INFO(FONT, "Print [%c] Font %u Size %u byte", letter, font, byte_cnt);
    cli_printf("0123456701234567" CRLF);
    for(i = byte_cnt - byte_in_row; 0 <= i; i -= byte_in_row) {
        res = true;
        switch((uint8_t)font) {
#ifdef HAS_FONT_12_X_6
        case FONT_12: {
            memcpy(&code, &gsc_ascii_1206[chr_ind][i], byte_in_row);
            code = reverse_byte_order_uint16(code);
            cli_printf("%s" CRLF, utoa_bin16_plain(code));
        } break;
#endif

#ifdef HAS_FONT_16_X_8
        case FONT_16: {
            memcpy(&code, &gsc_ascii_1608[chr_ind][i], byte_in_row);
            code = reverse_byte_order_uint16(code);
            cli_printf("%s" CRLF, utoa_bin16_plain(code));
        } break;
#endif

#ifdef HAS_FONT_24_X_12
        case FONT_24: {
            Type32Union_t un32;
            un32.u32 = 0;
            memcpy(&un32.u8[0], &gsc_ascii_2412[chr_ind][i], byte_in_row);
            // un32.u16[0] = reverse_byte_order_uint16(un32.u16[0]);
            un32.u32 = reverse_byte_order_uint24(un32.u32);
            cli_printf("%s" CRLF, utoa_bin24_plain(un32.u32));
        } break;
#endif
        default:
            res = false;
            break;
        }
    }
    return res;
}

char Bin2Char(Pixel_t pix_val) {
    char cha = '?';
    switch((uint8_t)pix_val) {
    case PIXEL_OFF:
        cha = '.';
        break;
    case PIXEL_ON:
        cha = 'X';
        break;
    }
    return cha;
}

bool font_diag_char(char letter, Font_t font) {
    bool res = false;
    cli_printf(CRLF);

    uint8_t byte_cnt = Font2Size(font);
    LOG_INFO(FONT, "Print [%c] Font %u Size %u byte", letter, font, byte_cnt);
    uint8_t x = 0;
    uint8_t y = 0;
    Pixel_t bit = 0;

    uint8_t byte_in_row = Font2ByteInRow(font);

    for(y = 0; y < (byte_in_row * 8); y++) {
        for(x = 0; x < (byte_cnt / byte_in_row); x++) {
            bit = FontPixelGet(x, y, letter, font);
            cli_printf("%c", Bin2Char(bit));
            res = true;
        }
        cli_printf(CRLF);
    }

    return res;
}
