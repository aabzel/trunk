#include "display_commands.h"


#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "display_diag.h"
#include "display_drv.h"
#include "log.h"
#include "fonts.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"








bool display_diag_command(int32_t argc, char* argv[]) {
    bool out_res = true;
  
    return out_res;
}

bool display_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = display_init();
        if(false == res) {
            LOG_ERROR(DISPLAY, "Init" LOG_ER);
        } else {
            LOG_INFO(DISPLAY, "Init" LOG_OK);
        }
    }
    return res;
}

/*
 ssdc 1 10 10 f 12
 ssdc 1 1 1 ! 12
 ssdl 1
 ssdc 1 12 12 h 12
 */
bool display_print_char(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t x = 1;
    uint8_t y = 1;
    char letter = '?';
    Font_t font = FONT_UNDEF;
    LOG_WARNING(DISPLAY, "argc %u", argc);

    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DISPLAY, "ParseErr RegAddr %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &x);
        if(false == res) {
            LOG_ERROR(DISPLAY, "ParseErr X %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &y);
        if(false == res) {
            LOG_ERROR(DISPLAY, "ParseErr Y %s", argv[2]);
        }
    }

    if(4 <= argc) {
        //memcpy(&letter,argv[3],1);
    	letter = argv[3][0];
        LOG_INFO(DISPLAY, "ParseErr Letter [%s]", argv[3]);

    }

    if(5 <= argc) {
        res = try_str2uint8(argv[4], &font);
        if(false == res) {
            LOG_ERROR(DISPLAY, "ParseErr font %s", argv[4]);
        }
    }

    if(res) {
    	 LOG_INFO(DISPLAY, "TryPrint [%c]", letter);
         res = display_write_char(num, x, y, letter, font);
         if(res) {
        	 LOG_INFO(DISPLAY, "PrintOk %c", letter);
         } else {
        	 LOG_ERROR(DISPLAY, "PrintErr %c", letter);
         }
    }else{
    	LOG_ERROR(DISPLAY, "Usage: ssdc Num x y letter Font");
    }

    return res;
}


bool display_print_text(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t x = 1;
    uint8_t y = 1;
    Font_t font = FONT_UNDEF;
    LOG_WARNING(DISPLAY, "argc %u", argc);

    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DISPLAY, "ParseErr RegAddr %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &x);
        if(false == res) {
            LOG_ERROR(DISPLAY, "ParseErr X %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &y);
        if(false == res) {
            LOG_ERROR(DISPLAY, "ParseErr Y %s", argv[2]);
        }
    }

    if(4 <= argc) {

    	//letter = argv[3][0];
        LOG_INFO(DISPLAY, "ParseErr Text [%s]", argv[3]);

    }

    if(5 <= argc) {
        res = try_str2uint8(argv[4], &font);
        if(false == res) {
            LOG_ERROR(DISPLAY, "ParseErr font %s", argv[4]);
        }
    }

    if(res) {
        size_t len = strlen(argv[3]);
        LOG_INFO(DISPLAY, "TryPrint [%s] %u byte", argv[3], len);
        res = display_write_string(num, x, y, argv[3],len, font);
        if(res) {
        	 LOG_INFO(DISPLAY, "PrintTextOk %s", argv[3]);
        } else {
        	 LOG_ERROR(DISPLAY, "PrintTextErr");
        }
    } else {
    	LOG_ERROR(DISPLAY, "Usage: ssdx Num x y text Font");
    }

    return res;
}
