#include "font_commands.h"

#include <stdint.h>
#include <string.h>

#include "convert.h"
#include "log.h"
#include "fonts.h"
#include "font_diag.h"


bool font_diag_char_command(int32_t argc, char* argv[]) {
    bool res = false;
    char letter = '?';
    Font_t font = FONT_UNDEF;
    if(1 <= argc) {
    	letter = argv[0][0];
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &font);
        if(false == res) {
            LOG_ERROR(FONT, "ParseErr font %s", argv[1]);
        }
    }

    if(res){
        set_log_level(FONT,LOG_LEVEL_INFO);
        res = false;
#ifdef HAS_FONT_DIAG
        res = font_diag_char(letter, font);
#endif
        if(res){
        }
    }else{
        LOG_ERROR(FONT, "Usage: fdc char font");
    }
    set_log_level(FONT,LOG_LEVEL_INFO);

    return res;
}


bool font_diag_char_raw_command(int32_t argc, char *argv[]){
    bool res = false;
    char letter = '?';
    Font_t font = FONT_UNDEF;
    if(1 <= argc) {
        letter = argv[0][0];
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &font);
        if(false == res) {
            LOG_ERROR(FONT, "ParseErr font %s", argv[1]);
        }
    }

    if(res) {
        set_log_level(FONT, LOG_LEVEL_INFO);
        res = false;
#ifdef HAS_FONT_DIAG
        res = font_diag_char_raw(letter, font);
#endif
    } else {
        LOG_ERROR(FONT, "Usage: fdc char font");
    }
    set_log_level(FONT,LOG_LEVEL_INFO);

    return res;
}
