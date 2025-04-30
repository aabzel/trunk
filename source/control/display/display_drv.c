#include "display_drv.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef HAS_COMMON
#include "common_const.h"
#include "common_diag.h"
#endif

#include "display_dep.h"
#ifdef HAS_DISPLAY_DIAG
#include "display_diag.h"
#include "str_utils.h"
#endif

#include "log.h"
#include "none_blocking_pause.h"
#ifdef HAS_TEST_DISPLAY
#include "test_display.h"
#endif


const DisplayConfig_t* DisplayGetConfig(uint8_t num) {
    const DisplayConfig_t* Config = NULL;
    uint32_t display_cnt = display_get_cnt();
    uint32_t i = 0;
    for(i = 0; i < display_cnt; i++) {
        if(DisplayConfig[i].num == num) {
            Config = &DisplayConfig[i];
            break;
        }
    }
    return Config;
}

DisplayHandle_t* DisplayGetNode(uint8_t num) {
    DisplayHandle_t* Config = NULL;
    uint32_t display_cnt = display_get_cnt();
    uint32_t i = 0;
    for(i = 0; i < display_cnt; i++) {
        if(DisplayConfig[i].num == num) {
            Config = &DisplayInstance[i];
            break;
        }
    }
    return Config;
}


bool display_update(uint8_t num) {
    bool res = false;
    DisplayHandle_t* Node = DisplayGetNode(num);
    if(Node) {
        res = display_render_ll(Node, Node->FrameBuffer, Node->frame_buffer_size);
    }
    return res;
}

bool display_proc(void) {
    bool res = false;
    uint32_t cnt = display_get_cnt();
    LOG_DEBUG(DISPLAY, "Proc %u", cnt);
    uint32_t i = 0;
    uint32_t ok = 0;

    for(i = 0; i <= cnt; i++) {
        DisplayHandle_t* Node = DisplayGetNode(i);
        if(Node) {
            LOG_DEBUG(DISPLAY, "Proc %u", i);
            res = display_update(i);
            if(res) {
                ok++;
            }
        }
    }

    if(ok) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool display_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(DISPLAY, "DISPLAY_%u", num);
    const DisplayConfig_t* Config = DisplayGetConfig(num);
    if(Config) {
        LOG_WARNING(DISPLAY, "SpotConfig DISPLAY_%u", num);
        DisplayHandle_t* Node = DisplayGetNode(num);
        if(Node) {
            LOG_WARNING(DISPLAY, "SpotNode DISPLAY_%u", num);
            Node->height = Config->height;
            Node->page_cnt = Config->page_cnt;
            Node->pixel_size = Config->pixel_size;
            Node->width = Config->width;
            strcpy(Node->name,Config->name);
            Node->valid = true;
            Node->frame_buffer_size = (Config->height*Config->width)/8;
            Node->FrameBuffer = (uint8_t*) malloc(Node->frame_buffer_size);
            if(Node->FrameBuffer ) {
                LOG_WARNING(DISPLAY, "MemAllocOk %u Size:%u Byte", num,Node->frame_buffer_size);
                memset(Node->FrameBuffer, 0, Node->frame_buffer_size);

                res = display_sram_clean(num);
                Node->init = true;
                char Text[300] = "";
                sprintf(Text,"DisplayStart\n\rNewLine");
                res = display_write_string(  num, 0, 0, Text, strlen(Text), FONT_12);
            }
        } else {
            LOG_ERROR(DISPLAY, "NodeErr %u", num);
        }
    } else {
        LOG_ERROR(DISPLAY, "ConfigErr %u", num);
    }
    return res;
}

bool display_init(void) {
    bool res = false;
    set_log_level(DISPLAY, LOG_LEVEL_DEBUG);
    uint32_t cnt = display_get_cnt();
    LOG_WARNING(DISPLAY, "display %u", cnt);
    uint32_t i = 0;
    uint32_t ok = 0;
    for(i = 0; i <= cnt; i++) {
        res = display_init_one(i);
        if(res) {
            ok++;
        }
    }
    if(ok) {
        res = true;
    } else {
        res = false;
    }
    set_log_level(DISPLAY, LOG_LEVEL_INFO);
    return res;
}


bool display_is_valid_pixel(DisplayHandle_t* Node,int16_t x, int16_t y) {
    bool res = false;
    if((0 <= x) && (x < Node->width )) {
        if((0 <= y) && (y < Node->height)) {
            res = true;
        }
    }
    return res;
}

DisplayPage_t display_y_cord_2_page(DisplayHandle_t* Node,int16_t y) {
    DisplayPage_t page;
    page = y / Node->page_cnt;
    return page;
}

bool display_write_dot_ll(DisplayHandle_t* Node, int16_t x, int16_t y, bool on_off) {
    bool res = false;
    LOG_PARN(DISPLAY, "PrintDot [%x,%x] OnOff:%u", x, y, on_off);
    if(Node) {
        res = display_is_valid_pixel(Node, x, y);
        if(res) {
            DisplayPage_t page = display_y_cord_2_page(Node,y);
            uint8_t pos = y % Node->page_cnt;
            uint8_t byte = 1 << pos;
            switch(on_off) {
            case true: {
                Node->FrameBuffer[page * Node->width + x] |= byte;
            } break;
            case false: {
                Node->FrameBuffer[page * Node->width + x] &= ~byte;
            } break;
            }
        } else {
            LOG_ERROR(DISPLAY, "DotErr %u,%u", x, y);
            res = false;
            Node->err_cnt++;
        }
    }
    return res;
}

bool display_write_char_ll(DisplayHandle_t* Node, int16_t x, int16_t y, char letter, Font_t font) {
    bool res = false;
    /*TODO: Add Check that letter is real*/
    LOG_DEBUG(DISPLAY, "Print %d,%d=[%c] Font %u", x, y, letter, font);
    int16_t yy;
    int16_t xx;
    FontFrame_t Dimension = Font2FontDimension(font);
    for(xx = x; xx < Dimension.dx + x; xx++) {
        for(yy = y; yy < (Dimension.dy + y); yy++) {
            // res = font_is_dot_on(letter, font, xx - x, yy - y);
            Pixel_t pix = FontPixelGet(xx - x, yy - y, letter, font);
            if(PIXEL_ON == pix) {
                res = display_write_dot_ll(Node, xx, yy, true);
            } else {
                res = display_write_dot_ll(Node, xx, yy, false);
            }
        }
    }
    return res;
}

bool display_write_char(uint8_t num, int16_t x, int16_t y, char str, Font_t font) {
    bool res = false;
    DisplayHandle_t* Node = DisplayGetNode(num);
    if(Node) {
        res = display_write_char_ll(Node, x, y, str, font);
    } else {
        LOG_INFO(DISPLAY, "NodeErr %u", num);
    }
    return res;
}

bool display_sram_clean(uint8_t num){
    bool res = false;
    DisplayHandle_t* Node = DisplayGetNode(num);
    if (Node) {
    	memset(Node->FrameBuffer, 0, Node->frame_buffer_size);
    	res = true;
    }
    return res;
}

bool display_write_string(uint8_t num, int16_t x_start, int16_t y_start, char* const str, size_t len, Font_t font) {
    bool res = false;
    LOG_DEBUG(DISPLAY, "PrintText %u (%d,%d) [%s] Len:%u Font:%u", num, x_start, y_start, str, len, font);
    DisplayHandle_t* Node = DisplayGetNode(num);
    int16_t x = x_start;
    int16_t y = y_start;
    if(Node) {
        if(str) {
            if(len) {
                res = true;
            }
        }
    }

    if(res) {
        FontFrame_t Dimension = Font2FontDimension(font);
        uint32_t i = 0;
        for(i = 0; i < len; i++) {
            bool is_real = true;
            switch(str[i]) {
            case '\b': {
                x -= Dimension.dx;
                is_real = false;
            } break;
            case '\r': {
                x = 0;
                is_real = false;
            } break;
            case '\n': {
                y += Dimension.dy;
                is_real = false;
            } break;
            default: {
            } break;
            }
            if(is_real) {
                res = display_write_char_ll(Node, x, y, str[i], font);
                x += Dimension.dx;
            }
        }
    }
    return res;
}
