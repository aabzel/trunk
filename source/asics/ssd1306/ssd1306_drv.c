#include "ssd1306_drv.h"

#include <string.h>

#ifdef HAS_COMMON
#include "common_const.h"
#include "common_diag.h"
#endif

#ifdef HAS_FONT
#include "fonts.h"
#endif

#include "ssd1306_dep.h"
#ifdef HAS_SSD1306_DIAG
#include "ssd1306_diag.h"
#include "str_utils.h"
#endif

#include "log.h"
#include "none_blocking_pause.h"
#ifdef HAS_TEST_SSD1306
#include "test_ssd1306.h"
#endif

#ifdef HAS_I2C
#include "i2c_mcal.h"
#endif /*HAS_I2C*/


#include "code_generator.h"

COMPONENT_GET_NODE(Ssd1306, ssd1306)
COMPONENT_GET_CONFIG(Ssd1306, ssd1306)
COMPONENT_INIT_PATTERT(SSD1306, SSD1306, ssd1306)
COMPONENT_PROC_PATTERT(SSD1306, SSD1306, ssd1306)



#if 0
const Ssd1306Config_t* Ssd1306GetConfig(uint8_t num) {
    const Ssd1306Config_t* Config = NULL;
    uint32_t ssd1306_cnt = ssd1306_get_cnt();
    uint32_t i = 0;
    for(i = 0; i < ssd1306_cnt; i++) {
        if(Ssd1306Config[i].num == num) {
            Config = &Ssd1306Config[i];
            break;
        }
    }
    return Config;
}

Ssd1306Handle_t* Ssd1306GetNode(uint8_t num) {
    Ssd1306Handle_t* Config = NULL;
    uint32_t ssd1306_cnt = ssd1306_get_cnt();
    uint32_t i = 0;
    for(i = 0; i < ssd1306_cnt; i++) {
        if(Ssd1306Config[i].num == num) {
            Config = &Ssd1306Instance[i];
            break;
        }
    }
    return Config;
}
#endif

bool ssd1306_update(uint8_t num) {
    bool res = false;
    Ssd1306Handle_t* Node = Ssd1306GetNode(num);
    if(Node) {
        res = ssd1306_write_data(num, Node->FrameBuffer, FRAME_BUFFER_SIZE);
    }
    return res;
}

bool ssd1306_proc_one(uint8_t i) {
    bool res = false;
    uint32_t ok = 0;
        Ssd1306Handle_t* Node = Ssd1306GetNode(i);
        if(Node) {
            LOG_DEBUG(SSD1306, "Proc %u", i);
            res = ssd1306_update(i);
            if(res) {
                ok++;
            }
        }


    if(ok) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool ssd1306_read_reg(uint8_t reg_addr, uint8_t* reg_val) {
    bool res = false;

    return res;
}

bool ssd1306_write_reg(uint8_t reg_addr, uint8_t reg_val) {
    bool res = false;

    return res;
}

bool ssd1306_write_lazy_reg(uint8_t reg_addr, uint8_t reg_val) {
    bool res = false;

    return res;
}

bool ssd1306_write_reg_by_bitmask(uint8_t reg_addr, char* bit_mask) {
    bool res = false;

    return res;
}

bool ssd1306_check(void) {
    bool res = false;

    return res;
}

bool ssd1306_reset(void) {
    bool res = false;
    return res;
}

bool ssd1306_write_frame(uint8_t num, Ssd1306Command_t cmd, uint8_t data) {
    bool res = false;
    Ssd1306Handle_t* Node = Ssd1306GetNode(num);
    if(Node) {
        uint8_t array[2] = {cmd, data};
        // uint8_t address = i2c_compose_write_address(Node->i2c_addr);
        res = i2c_api_write(Node->i2c_num, Node->i2c_addr, array, 2);
    }
    return res;
}

bool ssd1306_write_cmd_ll(Ssd1306Handle_t* Node, Ssd1306Command_t cmd) {
    bool res = false;
    if(Node) {
        ControlByte_t ctrl;
        ctrl.control = 0;
        ctrl.data_command_sel = SSD1306_DC_CMD;
        ctrl.continuation = 1;

        uint8_t array[2] = {ctrl.byte, cmd};
        array[0] = ctrl.byte;
        array[1] = cmd;
        // uint8_t address = i2c_compose_write_address(Node->i2c_addr);
        res = i2c_api_write(Node->i2c_num, Node->i2c_addr, array, 2);
    }
    return res;
}

bool ssd1306_write_data_ll(Ssd1306Handle_t* const Node, Ssd1306Command_t cmd) {
    bool res = false;
    if(Node) {
        ControlByte_t ctrl;
        ctrl.control = 0;
        ctrl.data_command_sel = SSD1306_DC_DATA;
        ctrl.continuation = 1;

        uint8_t array[2];
        array[0] = ctrl.byte;
        array[1] = cmd;

        // uint8_t address = i2c_compose_write_address(Node->i2c_addr);
        res = i2c_api_write(Node->i2c_num, Node->i2c_addr, array, sizeof(array));
    }
    return res;
}

static bool ssd1306_set_display_clock_ll(Ssd1306Handle_t* Node) {
    bool res= false;
    if(Node) {
        DivideRatio_t Reg;
        Reg.oscillator_frequency = 0x8;
        Reg.divide_ratio = 0x1;
        res = ssd1306_write_cmd2_ll(Node, SSD1306_CMD_DISPLAY_CLOCK, Reg.byte);
    }
    return res;
}

bool ssd1306_write_cmd2_ll(Ssd1306Handle_t* Node, Ssd1306Command_t cmd1, Ssd1306Command_t cmd2) {
    bool res = false;
    if(Node) {
        ControlByte_t ctrl;
        ctrl.byte = 0;

        uint8_t array[4] = {0};
        memset(array, 0, sizeof(array));

        ctrl.continuation = 1;
        ctrl.control = 0;
        ctrl.data_command_sel = SSD1306_DC_CMD;
        array[0] = ctrl.byte;
        array[1] = cmd1;

        ctrl.continuation = 1;
        ctrl.control = 0;
        ctrl.data_command_sel = SSD1306_DC_CMD;
        array[2] = ctrl.byte;
        array[3] = cmd2;
        // uint8_t address = i2c_compose_write_address(Node->i2c_addr);

        res = i2c_api_write(Node->i2c_num, Node->i2c_addr, array, sizeof(array));
    }
    return res;
}

bool ssd1306_write_cmd(uint8_t num, Ssd1306Command_t cmd) {
    bool res = false;
    Ssd1306Handle_t* Node = Ssd1306GetNode(num);
    if(Node) {
        res = ssd1306_write_cmd_ll(Node, cmd);
    }
    return res;
}

bool ssd1306_set_display_start_line(uint8_t num, uint8_t start_line) {
    bool res = false;
    Ssd1306Handle_t* Node = Ssd1306GetNode(num);
    if(Node) {
        if(start_line <= 63) {
            uint8_t cmd = 0x40 | start_line;
            res = ssd1306_write_cmd(num, cmd);
        }
    }
    return res;
}

bool ssd1306_set_contrast_ll(Ssd1306Handle_t* Node, uint8_t contrast) {
    bool res = false;
    if(Node) {
        res = ssd1306_write_cmd2_ll(Node, SSD1306_CMD_SET_CONTRAST_CONTROL, contrast);
    }
    return res;
}

bool ssd1306_set_multiplex_ratio(uint8_t num, uint8_t multiplex_ratio) {
    bool res = false;
    if((14 < multiplex_ratio) && (multiplex_ratio < 64)) {
        Ssd1306Handle_t* Node = Ssd1306GetNode(num);
        if(Node) {
            res = ssd1306_write_cmd2_ll(Node, SSD1306_CMD_SET_MULTIPLEX_RATIO, multiplex_ratio);
        }
    }
    return res;
}

/* page 64 Figure 2 : Software Initialization Flow Chart */
bool ssd1306_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SSD1306, "SSD1306_%u", num);
    const Ssd1306Config_t* Config = Ssd1306GetConfig(num);
    if(Config) {
        LOG_WARNING(SSD1306, "SpotConfig SSD1306_%u", num);
        Ssd1306Handle_t* Node = Ssd1306GetNode(num);
        if(Node) {
            res = true;
            LOG_WARNING(SSD1306, "SpotNode SSD1306_%u", num);
            Node->i2c_num = Config->i2c_num;
            Node->i2c_addr = Config->i2c_addr;
            Node->valid = true;
            Node->init = true;

            res = ssd1306_set_multiplex_ratio(num, 63) && res;
            res = ssd1306_set_display_offset(num, 0) && res;
            res = ssd1306_set_display_start_line(num, 0) && res;

            res = ssd1306_write_cmd_ll(Node, 0xA0) && res;
            res = ssd1306_write_cmd_ll(Node, 0xC0) && res;
            res = ssd1306_set_contrast_ll(Node, 0x7E) && res;
            res = ssd1306_write_cmd_ll(Node, SSD1306_CMD_ENTIRE_DISPLAY_RESET) && res;
            res = ssd1306_write_cmd_ll(Node, SSD1306_CMD_NORMAL_DISPLAY) && res;
            res = ssd1306_set_display_clock_ll(Node) && res;
            res = ssd1306_write_cmd2_ll(Node, SSD1306_CMD_CHARGE_PUMP_SETTING, 0x14) && res;
            res = ssd1306_write_cmd_ll(Node, SSD1306_CMD_DISPLAY_ON) && res;

            res = ssd1306_set_memory_addressing_mode(num, Config->mem_addressing_mode) && res;

            // res = ssd1306_set_page_start_addr(num, SSD1306_PAGE_0);
#ifdef HAS_TEST_SSD1306
            test_ssd1306_screen();
#endif
            wait_ms(100);
            res = ssd1306_sram_clean(num) && res;

            res = ssd1306_write_string(num, 0, 0, "DisplayOk!", 10, FONT_12) && res;
        } else {
            LOG_ERROR(SSD1306, "NodeErr %u", num);
        }
    } else {
        LOG_ERROR(SSD1306, "ConfigErr %u", num);
    }
    return res;
}

bool ssd1306_init_custom(void) {
    return true;
}


bool ssd1306_set_page_start_addr(uint8_t num, Ssd1306Page_t page) {
    bool res = false;
    Ssd1306Command_t cmd = SSD1306_CMD_SET_PAGE_START_ADDR | page;
    res = ssd1306_write_cmd(num, cmd);
    return res;
}

bool ssd1306_is_connected(uint8_t num) {
    bool res = false;
    Ssd1306Handle_t* Node = Ssd1306GetNode(num);
    if(Node) {
        res = ssd1306_write_cmd_ll(Node, SSD1306_CMD_NOP);
    }
    return res;
}

bool ssd1306_write_data(uint8_t num, uint8_t* array, uint32_t size) {
    bool res = false;
    Ssd1306Handle_t* Node = Ssd1306GetNode(num);
    if(Node) {
        ControlByte_t ctrl;
        ctrl.control = 0;
        ctrl.data_command_sel = SSD1306_DC_DATA;
        ctrl.continuation = 0;

        uint8_t buff[1024 + 1];
        buff[0] = ctrl.byte;
        memcpy(&buff[1], array, size);
        res = i2c_api_write(Node->i2c_num, Node->i2c_addr, buff, size + 1);
    }
    return res;
}

bool ssd1306_write_data2(uint8_t num, uint8_t* array, uint32_t size) {
    bool res = false;
    Ssd1306Handle_t* Node = Ssd1306GetNode(num);
    if(Node) {
        uint32_t i = 0;
        uint32_t ok = 0;
        for(i = 0; i < size; i++) {
            res = ssd1306_write_data_ll(Node, array[i]);
            if(res) {
                ok++;
            }
        }
        if(ok == size) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

bool ssd1306_set_memory_addressing_mode(uint8_t num, Ssd1306MemoryAddressingMode_t mem_addressing_mode) {
    bool res = false;
    Ssd1306Handle_t* Node = Ssd1306GetNode(num);
    if(Node) {
        res = ssd1306_write_cmd2_ll(Node,
        		SSD1306_CMD_SET_MEMORY_ADDRESSING_MODE,
        		(Ssd1306Command_t) mem_addressing_mode);
    }
    return res;
}

bool ssd1306_set_display_offset(uint8_t num, uint8_t offset) {
    bool res = false;
    Ssd1306Handle_t* Node = Ssd1306GetNode(num);
    if(Node) {
        if(offset < 64) {
            res = ssd1306_write_cmd2_ll(Node, SSD1306_CMD_SET_DISPLAY_OFFSET, offset);
        }
    }
    return res;
}

bool is_valid_pixel(int16_t x, int16_t y) {
    bool res = false;
    if((0 <= x) && (x < 128)) {
        if((0 <= y) && (y < 64)) {
            res = true;
        }
    }
    return res;
}

Ssd1306Page_t ssd1306_y_cord_2_page(int16_t y) {
    Ssd1306Page_t page;
    page = y / 8;
    return page;
}

bool ssd1306_sram_clean(uint8_t num) {
    bool res = false;
    Ssd1306Handle_t* Node = Ssd1306GetNode(num);
    if(Node) {
        memset(Node->FrameBuffer, 0, FRAME_BUFFER_SIZE);
        res = true;
    }
    return res;
}

bool ssd1306_write_dot_ll(Ssd1306Handle_t* Node, int16_t x, int16_t y, bool on_off) {
    bool res = false;
    LOG_PARN(SSD1306, "PrintDot [%x,%x] OnOff:%u", x, y, on_off);
    if(Node) {
        res = is_valid_pixel(x, y);
        if(res) {
            Ssd1306Page_t page = ssd1306_y_cord_2_page(y);
            uint8_t pos = y % 8;
            uint8_t byte = 1 << pos;
            switch((uint8_t)on_off) {
            case true: {
                Node->FrameBuffer[page * SSD1306_PAGE_SIZE + x] |= byte;
            } break;
            case false: {
                Node->FrameBuffer[page * SSD1306_PAGE_SIZE + x] &= ~byte;
            } break;
            }
        } else {
            LOG_DEBUG(SSD1306, "DotErr %u,%u", x, y);
            res = false;
            Node->err_cnt++;
        }
    }
    return res;
}

/**/
bool ssd1306_write_dot(uint8_t num, int16_t x, int16_t y, bool on_off) {
    bool res = false;
    Ssd1306Handle_t* Node = Ssd1306GetNode(num);
    if(Node) {
        res = ssd1306_write_dot_ll(Node, x, y, on_off);
    }
    return res;
}

/*TODO move to font driver*/
bool ssd1306_write_char_ll(Ssd1306Handle_t* Node, int16_t x, int16_t y, char letter, Font_t font) {
    bool res = false;
    /*TODO: Add Check that letter is real*/
    LOG_DEBUG(SSD1306, "Print %u,%u=[%c] Font %u", x, y, letter, font);
    int16_t yy;
    int16_t xx;
    FontFrame_t Dimension = Font2FontDimension(font);
    for(xx = x; xx < Dimension.dx + x; xx++) {
        for(yy = y; yy < (Dimension.dy + y); yy++) {
            // res = font_is_dot_on(letter, font, xx - x, yy - y);
            Pixel_t pix = FontPixelGet(xx - x, yy - y, letter, font);
            if(PIXEL_ON == pix) {
                res = ssd1306_write_dot_ll(Node, xx, yy, true);
            } else {
                res = ssd1306_write_dot_ll(Node, xx, yy, false);
            }
        }
    }
    return res;
}

bool ssd1306_write_char(uint8_t num, int16_t x, int16_t y, char str, Font_t font) {
    bool res = false;
    Ssd1306Handle_t* Node = Ssd1306GetNode(num);
    if(Node) {
        res = ssd1306_write_char_ll(Node, x, y, str, font);
    } else {
        LOG_INFO(SSD1306, "NodeErr %u", num);
    }
    return res;
}
/*
 * num-ssd1306 inst
 * x_start-pixel
 * y_start-pixel
 * */
bool ssd1306_write_string(uint8_t num, int16_t x_start, int16_t y_start, char* const str, size_t len, Font_t font) {
    bool res = false;
    LOG_DEBUG(SSD1306, "SSD1306%u,Print,Text,(%d,%d),[%s],Len:%u,Font:%u", num, x_start, y_start, str, len, font);
    Ssd1306Handle_t* Node = Ssd1306GetNode(num);
    int16_t x = x_start;
    int16_t y = y_start;
    if(Node) {
        if(str) {
            if(len) {
                res = true;
            } else {
                LOG_ERROR(SSD1306, "ZeroText");
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
                res = ssd1306_write_char_ll(Node, x, y, str[i], font);
                if(false == res) {
                    LOG_DEBUG(SSD1306, "Write [%c] (%u,%u),Font %u err", str[i], x, y, font);
                    Node->err_cnt++;
                    res = true;
                }
                x += Dimension.dx;
            }
        }
    }
    return res;
}
