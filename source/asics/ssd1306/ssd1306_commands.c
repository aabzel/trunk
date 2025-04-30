#include "ssd1306_commands.h"


#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "ssd1306_diag.h"
#include "ssd1306_drv.h"
#include "log.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

bool ssd1306_read_reg_map(char* key_word1, char* key_word2) {
    bool res = false;

    return res;
}


bool ssd1306_reg_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t reg_addr = 0;
    uint8_t reg_val = 0;
    if(1 == argc) {
        res = try_str2uint8(argv[0], &reg_addr);
        if(false == res) {
            LOG_ERROR(SSD1306, "ParseErr RegAddr %s", argv[0]);
        }
    }
    if(res) {
        res = ssd1306_read_reg(reg_addr, &reg_val);
        if(false == res) {
            LOG_ERROR(SSD1306, "ReadErr [0x%02x]", reg_addr);
        } else {
            LOG_INFO(SSD1306, "ReadOk [0x%02x]=0x%02x", reg_addr, reg_val);
        }
    } else {
        LOG_ERROR(SSD1306, "Usage: fdar RegAddr");
    }
    return res;
}

bool ssd1306_reg_write_command(int32_t argc, char* argv[]) {
    bool res = false;

    return res;
}

bool ssd1306_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = ssd1306_reset();
    } else {
        LOG_ERROR(SSD1306, "Usage: fdat");
    }
    return res;
}




bool ssd1306_diag_command(int32_t argc, char* argv[]) {
    bool out_res = true;
  
    return out_res;
}

bool ssd1306_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = ssd1306_mcal_init();
        if(false == res) {
            LOG_ERROR(SSD1306, "Init" LOG_ER);
        } else {
            LOG_INFO(SSD1306, "Init" LOG_OK);
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
bool ssd1306_print_char(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t x = 1;
    uint8_t y = 1;
    char letter = '?';
    Font_t font = FONT_UNDEF;
    LOG_WARNING(SSD1306, "argc %u", argc);

    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SSD1306, "ParseErr RegAddr %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &x);
        if(false == res) {
            LOG_ERROR(SSD1306, "ParseErr X %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &y);
        if(false == res) {
            LOG_ERROR(SSD1306, "ParseErr Y %s", argv[2]);
        }
    }

    if(4 <= argc) {
        //memcpy(&letter,argv[3],1);
    	letter = argv[3][0];
        LOG_INFO(SSD1306, "ParseErr Letter [%s]", argv[3]);

    }

    if(5 <= argc) {
        res = try_str2uint8(argv[4], &font);
        if(false == res) {
            LOG_ERROR(SSD1306, "ParseErr font %s", argv[4]);
        }
    }

    if(res) {
    	 LOG_INFO(SSD1306, "TryPrint [%c]", letter);
        res = ssd1306_write_char(num, x, y, letter, font);
        if(res) {
        	 LOG_INFO(SSD1306, "PrintOk %c", letter);
        } else {
        	 LOG_ERROR(SSD1306, "PrintErr %c", letter);
        }
    }else{
    	LOG_ERROR(SSD1306, "Usage: ssdc Num x y letter Font");
    }

    return res;
}


bool ssd1306_sram_clean_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SSD1306, "ParseErr Num %s", argv[0]);
        }
    }
    if(res){

    	res= ssd1306_sram_clean(  num);
    }
    return res;
}


bool ssd1306_print_text(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t x = 1;
    uint8_t y = 1;
    Font_t font = FONT_UNDEF;
    LOG_WARNING(SSD1306, "argc %u", argc);

    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SSD1306, "ParseErr RegAddr %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &x);
        if(false == res) {
            LOG_ERROR(SSD1306, "ParseErr X %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &y);
        if(false == res) {
            LOG_ERROR(SSD1306, "ParseErr Y %s", argv[2]);
        }
    }

    if(4 <= argc) {

    	//letter = argv[3][0];
        LOG_INFO(SSD1306, "ParseErr Text [%s]", argv[3]);

    }

    if(5 <= argc) {
        res = try_str2uint8(argv[4], &font);
        if(false == res) {
            LOG_ERROR(SSD1306, "ParseErr font %s", argv[4]);
        }
    }

    if(res) {
        size_t len= strlen(argv[3]);
        LOG_INFO(SSD1306, "TryPrint [%s] %u byte", argv[3], len);
        res = ssd1306_write_string(num, x, y, argv[3],len, font);
        if(res) {
        	 LOG_INFO(SSD1306, "PrintTextOk %s", argv[3]);
        } else {
        	 LOG_ERROR(SSD1306, "PrintTextErr");
        }
    } else {
    	LOG_ERROR(SSD1306, "Usage: ssdx Num x y text Font");
    }

    return res;
}
