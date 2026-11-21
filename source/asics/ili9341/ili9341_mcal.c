#include "ili9341_mcal.h"

#include "gpio_mcal.h"
#include "spi_mcal.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"
#include "ili9341_const.h"
#include "utf8_str.h"
#include "fonts_english.h"
#include "fonts_russian.h"

static const Ili9341InitConfig_t Ili9341InitConfig[]={
        {.command = ILI9341_CMD_POWER_CONTROL_A, .data= (const uint8_t[]) {0x39,  0x2C,  0x00,  0x34,  0x02}, .size=5, },
        {.command = ILI9341_CMD_PWCTR_B, .data= (const uint8_t[]) {0x00, 0xC1, 0x30}, .size=3, },
        {.command=ILI9341_CMD_DRIVER_TIMING_CONTROL_A, .data= (const uint8_t[]) {0x85,  0x00,  0x78}, .size=3, },
        {.command=ILI9341_CMD_DRIVER_TIMING_CONTROL_B, .data= (const uint8_t[]) {0x00,  0x00}, .size=2, },
        {.command=ILI9341_CMD_POWER_ON, .data= (const uint8_t[]) {0x64,  0x03,  0x12,  0x81}, .size=4, },
        {.command=ILI9341_CMD_PUMP_RATIO_CONTROL, .data= (const uint8_t[]) {0x20}, .size=1, },
     {.command=ILI9341_CMD_PWCTR1, .data= (const uint8_t[]) {0x23}, .size=1, },
        {.command=ILI9341_CMD_PWCTR2, .data= (const uint8_t[]) {0x10}, .size=1, },

        {.command=ILI9341_CMD_VMCTR1, .data= (const uint8_t[]) {0x3E,  0x28}, .size=2, },
        {.command=ILI9341_CMD_VMCTR2, .data= (const uint8_t[]) {0x86}, .size=1, },

        //{.command=ILI9341_CMD_MADCTL, .data= (const uint8_t[]) {0x48}, .size=1, },
        {.command=ILI9341_CMD_MADCTL, .data= (const uint8_t[]) {0x28}, .size=1, },

        {.command=ILI9341_CMD_VSCRSADD, .data= (const uint8_t[]) {0x00,0x00}, .size=2, },
        {.command = ILI9341_CMD_PIXFMT,  .data= (const uint8_t[]) {0x55}, .size=1, },
        {.command=ILI9341_CMD_FRMCTR1, .data= (const uint8_t[]) {0x00,  0x18}, .size=2, },
        {.command=ILI9341_CMD_DFUNCTR, .data= (const uint8_t[]) {0x08,  0x82,  0x27}, .size=3, },
        {.command=ILI9341_CMD_ENABLE_3G, .data= (const uint8_t[]) {0x02}, .size=1, },
        {.command=ILI9341_CMD_GAMMASET,  .data= (const uint8_t[]) {0x01}, .size=1, },
        {.command=ILI9341_CMD_GMCTRP1,   .data= (const uint8_t[]) {0x0F,  0x31,  0x2B,  0x0C,  0x0E,  0x08,  0x4E,  0xF1,  0x37,  0x07,  0x10,  0x03,  0x0E,  0x09,  0x00}, .size=15, },
        {.command=ILI9341_CMD_GMCTRN1,   .data= (const uint8_t[]) {0x00,  0x0E,  0x14,  0x03,  0x11,  0x07,  0x31,  0xC1,  0x48,  0x08,  0x0F,  0x0C,  0x31,  0x36,  0x0F}, .size=15, },

};

COMPONENT_IS_VALID(Ili9341, ili9341)
COMPONENT_GET_NODE(Ili9341, ili9341)
COMPONENT_GET_CONFIG(Ili9341, ili9341)

static GpioLogicLevel_t ili9341_dc_gpio_level(const Ili9341DcCtrl_t dc_val) {
    GpioLogicLevel_t logic_level = GPIO_LVL_LOW;
    switch (dc_val) {
        case ILI9341_DXC_CTRL_DATA:
            logic_level = GPIO_LVL_HI;
            break;
        case ILI9341_DXC_CTRL_COMMAND:
            logic_level = GPIO_LVL_LOW;
            break;
        default:
            break;
    }
    return logic_level;
}

static bool ili9341_dxc_ctrl_ll(Ili9341Handle_t*  Node, const Ili9341DcCtrl_t dc_val) {
    bool res = false;
    GpioLogicLevel_t logic_level = ili9341_dc_gpio_level(dc_val);
    res = gpio_logic_level_set(Node->DcxPad, logic_level);
    return res;
}

static bool ili9341_send_command( Ili9341Handle_t* Node, const Ili9341Cmd_t command) {
    bool res = false;
    gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
    res = ili9341_dxc_ctrl_ll(Node, ILI9341_DXC_CTRL_COMMAND);
    res = spi_write_byte(Node->spi_num, command);
    return res;
}

bool ili9341_set_address_window_ll(  Ili9341Handle_t* Node,
                                     uint16_t x0,
                                     uint16_t y0,
                                     uint16_t x1,
                                     uint16_t y1){
    bool res = false;
    res = ili9341_column_address_set(Node->num, x0, x1);
    res = ili9341_page_address_set(Node->num, y0, y1);

    gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
    res = ili9341_send_command( Node, ILI9341_CMD_MEMORY_WRITE );
    return res;
}

static bool ili9341_init_node(Ili9341Handle_t* const Node) {
    bool res = false;
    if (Node) {
        Node->spin = 0;
        Node->init = false;
        Node->valid = true;
#ifdef HAS_ILI9341_FRAME_BUFFER
        memset(Node->frameBuffer,0,sizeof(Node->frameBuffer));
#endif
        res = true;
    }
    return res;
}

static bool ili9341_init_common(const Ili9341Config_t* const Config, Ili9341Handle_t* const Node) {
    bool res = false;
    if (Config) {
        if (Node) {
            Node->screen_orientation = Config->screen_orientation;
            Node->name = Config->name;
            Node->update_period_ms = Config->update_period_ms;
            Node->spi_num = Config->spi_num;
            Node->LedPad = Config->LedPad;
            Node->chip_select = Config->chip_select;
            Node->ResetPad = Config->ResetPad;
            Node->DcxPad = Config->DcxPad;
            res = true;
        }
    }
    return res;
}

uint16_t ili9341_mix_color( const uint16_t red,
                            const uint16_t green,
                            const uint16_t blue) {
    Ili9341Pixel_t Pixel={0};

    Pixel.red = red;
    Pixel.green = green;
    Pixel.blue = blue;

    return Pixel.word;
}


Ili9341Pixel_t ili9341_pix_color_set( const Color_t color, const uint8_t intensity) {
    Ili9341Pixel_t Pixel={0};
    Pixel.word = 0;
    switch(color) {
        case COLOR_RED:  Pixel.red = intensity;  break;
        case COLOR_GREEN: Pixel.green = intensity; break;
        case COLOR_BLUE:  Pixel.blue = intensity; break;

        case COLOR_YELLOW: {
            Pixel.red = intensity;
            Pixel.green = intensity;
        }break;

        case COLOR_CYANIC: {
            Pixel.blue = intensity;
            Pixel.green = intensity;
        }break;


        case COLOR_PURPLE: {
            Pixel.blue = intensity;
            Pixel.red = intensity;
        }break;

        case COLOR_WHITE: {
            Pixel.red = intensity;
            Pixel.green = intensity;
            Pixel.blue = intensity;
        }break;

        default :  break;
    }

    return Pixel;
}

/*ISO-26262 require verify configuration*/
bool Ili9341IsValidConfig(const Ili9341Config_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        bool lres = true;
        ifn(Config->name) {
            LOG_ERROR(ILI9341, "ILI9341_%u,Name,Err", Config->num);
            res = false;
        }

        lres = spi_is_init(Config->spi_num);
        ifn(lres) {
            LOG_ERROR(ILI9341, "ILI9341_%u,spi_num,Err", Config->num);
            res = false;
        }

        lres = gpio_is_valid_pad(Config->chip_select);
        ifn(lres) {
            LOG_ERROR(ILI9341, "ILI9341_%u,chip_select,Err", Config->num);
            res = false;
        }

        lres = gpio_is_valid_pad(Config->ResetPad);
        ifn(lres) {
            LOG_ERROR(ILI9341, "ILI9341_%u,chip_select,Err", Config->num);
            res = false;
        }

        lres = gpio_is_valid_pad(Config->LedPad);
        ifn(lres) {
            LOG_ERROR(ILI9341, "ILI9341_%u,LedPad,Err", Config->num);
            res = false;
        }

        lres = gpio_is_valid_pad(Config->DcxPad);
        ifn(lres) {
            LOG_ERROR(ILI9341, "ILI9341_%u,DcxPad,Err", Config->num);
            res = false;
        }

        ifn(0<Config->update_period_ms) {
            LOG_ERROR(ILI9341, "ILI9341_%u,update_period_ms,Err", Config->num);
            res = false;
        }
    }
    return res;
}


bool ili9341_init_custom(void) {
    bool res = false;
    uint32_t cnt = ili9341_get_cnt();
    LOG_INFO(ILI9341, "Version:%u", ILI9341_VERSION);
    LOG_INFO(ILI9341, "CNT:%u", cnt);
    if(cnt) {
        res = true;
    } else {
        LOG_ERROR(ILI9341, "NoConfig!");
        res = false;
    }
    return res;
}


bool ili9341_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(ILI9341, "ILI9341_%u,Proc", num);
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node) {
        Node->spin++;
    }
    return res;
}

static bool ili9341_send_param(Ili9341Handle_t* Node ,
                               const uint8_t * const param,
                               const uint32_t cnt) {
    bool res = false;
    res = ili9341_dxc_ctrl_ll(Node, ILI9341_DXC_CTRL_DATA);
    res = spi_mcal_write(Node->spi_num, param, cnt);
    return res;
}

static bool ili9341_send_word(Ili9341Handle_t* Node , const uint16_t word ) {
    bool res = false;
    res = ili9341_dxc_ctrl_ll(Node, ILI9341_DXC_CTRL_DATA);
    res = spi_write_word(Node->spi_num, word);
    return res;
}

static bool ili9341_read_words_ll(Ili9341Handle_t* Node ,
                               const uint16_t * const word,
                               const uint32_t cnt) {
    bool res = false;
    res = ili9341_dxc_ctrl_ll(Node, ILI9341_DXC_CTRL_DATA);
    res = spi_mcal_read_words(Node->spi_num, word, cnt);
    return res;
}

static bool ili9341_read_word_ll(Ili9341Handle_t* Node, const uint16_t * const word ) {
    bool res = false;
    res = ili9341_dxc_ctrl_ll(Node, ILI9341_DXC_CTRL_DATA);
    res = spi_mcal_read_word(Node->spi_num, word);
    return res;
}

static bool ili9341_send_words(Ili9341Handle_t* Node ,
                               const uint16_t * const word,
                               const uint32_t cnt) {
    bool res = false;
    res = ili9341_dxc_ctrl_ll(Node, ILI9341_DXC_CTRL_DATA);
    res = spi_mcal_write_words(Node->spi_num, word, cnt);
    return res;
}

bool ili9341_writer_set(const uint8_t num) {
    bool res = true;
    curWriterPtr = WriterGetNode(  WRITER_NUM_ILI9341);
    return res;
}


bool ili9341_write_cmd_param(const uint8_t num,
                             const Ili9341Cmd_t command,
                             const uint8_t * const param,
                             const uint32_t cnt) {
    bool res = false;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
        res = ili9341_send_command( Node, command);
        res = ili9341_send_param(Node,param,cnt);
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
    }
    return res;
}



bool ili9341_read_id(const uint8_t num, uint32_t * const pId) {
    bool res = false;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node) {

        res = ili9341_send_command( Node, ILI9341_CMD_RDDID);

        res = ili9341_dxc_ctrl_ll(Node, ILI9341_DXC_CTRL_DATA);
        Ili9341Id_t ID;
        res = spi_read_safe(Node->spi_num, ID.buff, 4);
        if(pId) {
            *pId = ID.dword;
        }
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
    }
    return res;
}


/*8.2.46. Read ID1 (DAh) */
bool ili9341_read_man_id1(const uint8_t num, uint8_t * const pId1) {
    bool res = false;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);

        res = ili9341_send_command( Node, ILI9341_CMD_RDID1);

        res = ili9341_dxc_ctrl_ll(Node, ILI9341_DXC_CTRL_DATA);
        Ili9341ManId1_t ID;
        res = spi_read_safe(Node->spi_num, ID.buff, 2);
        if(pId1) {
            *pId1 = ID.manufacturer_id;
        }
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
    }
    return res;
}

bool ili9341_software_reset(uint8_t num) {
    bool res = false;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
        res = ili9341_send_command( Node, ILI9341_CMD_SWRESET);
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
    }
    return res;
}



bool ili9341_column_address_set(const uint8_t num,
                                const uint16_t start_column,
                                const uint16_t end_column) {
    bool res = false;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
        res = ili9341_send_command( Node, ILI9341_CMD_COLUMN_ADDRESS_SET );

        Ili9341ColumnAddressSetParam_t Param;
        U16_bit_t startColumn;
        startColumn.u16=start_column;

        U16_bit_t endColumn;
        endColumn.u16=end_column;

        Param.sc15_8=startColumn.u8[1];
        Param.sc7_0=startColumn.u8[0];

        Param.ec15_8=endColumn.u8[1];
        Param.ec7_0=endColumn.u8[0];


        res = ili9341_send_param(Node,Param.buff,4);

        gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
    }
    return res;
}

bool ili9341_draw_horizontal_line(const uint8_t num, uint16_t x, uint16_t y, uint16_t width, uint16_t colour){
    bool res = false;
    //TODO
    return res;
}

bool ili9341_draw_vertical_line(const uint8_t num, uint16_t x, uint16_t y, uint16_t height, uint16_t colour){
    bool res = false;
    //TODO
    return res;
}

bool ili9341_set_orientation(uint8_t num, ScreenOrientation_t orientation) {
    bool res = false;

    Ili9341Handle_t* Node = Ili9341GetNode(num);
    Ili9341ParamMemoryAccessControl_t Param;
    //                    76543210
    Param.byte = 0x28; // 00101000 - horizontal
    //              0x48  01001000 - vertical
    Param.res = 0;
    Param.BGR = 1; // D3: RGB-BGR Order (0=RGB, 1=BGR)
    Param.MH = 0; // D2: Horizontal Refresh Order
    Param.ML = 0; // D4: Vertical Refresh Order
    Param.MY = 0; // D7: Row Address Order

    switch (orientation) {
        case SCREEN_ORIENTATION_VERTICAL: {
            Node->width = ILI9341_NARROW;
            Node->height =ILI9341_WIDE ;
            Param.MV = 0; // D5: Row / Column Exchange
            Param.MX = 1; // D6: Column Address Order
        } break;

        case SCREEN_ORIENTATION_HORIZONTAL: {
            Node->width = ILI9341_WIDE ;
            Node->height =ILI9341_NARROW ;
            Param.MV = 1; // D5: Row / Column Exchange
            Param.MX = 0; // D6: Column Address Order
        } break;

        default:
            break;
    }

    res = ili9341_write_cmd_param(num, ILI9341_CMD_MADCTL, &Param.byte, 1);
    return res;
}

bool ili9341_read_memory(const uint8_t num, uint16_t * const words, const uint32_t cnt){
    bool res = false;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
        res = ili9341_send_command( Node, ILI9341_CMD_MEMORY_READ );
        uint16_t dummy_word = 0xFFFF;
        res = ili9341_read_word_ll(Node, dummy_word);
        res = ili9341_read_words_ll(Node, words, cnt);
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);

    }
    return res;
}

bool ili9341_memory_write(const uint8_t num,  const uint16_t * const word, uint32_t cnt) {
    bool res = false;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
        res = ili9341_send_command( Node, ILI9341_CMD_MEMORY_WRITE );
        res = ili9341_send_words(Node, word, cnt);
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);

    }
    return res;
}

bool ili9341_page_address_set(const uint8_t num,
                                const uint16_t start_page,
                                const uint16_t end_page) {
    bool res = false;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
        res = ili9341_send_command( Node, ILI9341_CMD_PAGE_ADDRESS_SET );

        Ili9341PageAddressSetParam_t Param;
        U16_bit_t startPage;
        startPage.u16=start_page;

        U16_bit_t endPage;
        endPage.u16 = end_page;

        Param.sp15_8 = startPage.u8[1];
        Param.sp7_0 = startPage.u8[0];

        Param.ep15_8=endPage.u8[1];
        Param.ep7_0=endPage.u8[0];


        res = ili9341_send_param(Node,Param.buff,4);

        gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
    }
    return res;
}



//8.2.12. Sleep Out (11h)
bool ili9341_sleep_out(const uint8_t num) {
    bool res = false;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
        res = ili9341_send_command( Node, ILI9341_CMD_SLEEP_OUT);
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
    }
    return res;
}



bool ili9341_normal_mode_on(const uint8_t num) {
    bool res = false;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
        res = ili9341_send_command( Node, ILI9341_CMD_NORMAL_MODE_ON);
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
    }
    return res;
}


bool ili9341_display_on(const uint8_t num) {
    bool res = false;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
        res = ili9341_send_command( Node, ILI9341_CMD_DISPLAY_ON);
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
    }
    return res;
}

bool ili9341_draw_rec(const uint8_t num,
                      const uint16_t color,
                      uint16_t start_x,
                      uint16_t start_y,
                      uint16_t width,
                      uint16_t height ) {
    bool res = true;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if (Node) {
        res= ili9341_set_address_window_ll(Node,
                                           start_x, start_y,
                                           start_x + width-1,
                                           start_y + height-1);
        res = ili9341_dxc_ctrl_ll(Node, ILI9341_DXC_CTRL_DATA);
        uint32_t pix_cnt = (width) * (height);
        uint32_t i = 0;
        for (i = 0; i < pix_cnt; i++) {
            res = spi_write_word(Node->spi_num, color);
        }
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
    }

    return res;
}

bool ili9341_fill_screen(const uint8_t num, uint16_t colour) {
    bool res = false;
    LOG_INFO(ILI9341, "FillScreen,N:%u,Color:0x%08x", num, colour);
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node){
        switch(Node->screen_orientation){
            case SCREEN_ORIENTATION_VERTICAL: {
              res = ili9341_draw_rec( num, colour,  0, 0,ILI9341_NARROW, ILI9341_WIDE );
            }break;

            case SCREEN_ORIENTATION_HORIZONTAL: {
              res = ili9341_draw_rec( num, colour,  0, 0, ILI9341_WIDE, ILI9341_NARROW );
            }break;
            default:{
                res = false;
            } break;
        }
    }
    return res;
}

bool ili9341_read_pixel(uint8_t num,
                        uint16_t start_x,
                        uint16_t start_y,
                        uint16_t * const colour) {
    bool res = false;
    res = ili9341_column_address_set(num, start_x, start_x + 1);
    res = ili9341_page_address_set(num, start_y, start_y + 1);
    res = ili9341_read_memory(num, colour, 1);
    return res;
}

bool ili9341_draw_pixel(uint8_t num, uint16_t start_x,uint16_t start_y,uint16_t colour){
    bool res = false;
    res = ili9341_column_address_set(num, start_x, start_x + 1);
    res = ili9341_page_address_set(num, start_y, start_y + 1);
    res = ili9341_memory_write(num, &colour, 1);
    return res;
}

/*8.2.47. Read ID2 (DBh)*/
bool ili9341_read_driver_version_id2(const uint8_t num, uint8_t * const pId2) {
    bool res = false;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);

        res = ili9341_send_command( Node, ILI9341_CMD_RDID2);

        res = ili9341_dxc_ctrl_ll(Node, ILI9341_DXC_CTRL_DATA);
        Ili9341ManId2_t ID2;
        res = spi_read_safe(Node->spi_num, ID2.buff, 2);
        if(pId2) {
            *pId2 = ID2.driver_version;
        }
        gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
    }
    return res;
}

bool ili9341_init_one(uint8_t num) {
    bool res = false;
    uint32_t cnt = ili9341_get_cnt();
    LOG_WARNING(ILI9341, "ILI9341_%u/%u", num, cnt);
    const Ili9341Config_t *Config = Ili9341GetConfig(num);
    res = Ili9341IsValidConfig(Config);
    if(res) {
#ifdef HAS_ILI9341_DIAG
        LOG_WARNING(ILI9341, "%s", Ili9341ConfigToStr(Config));
#endif
        Ili9341Handle_t *Node = Ili9341GetNode(num);
        if(Node) {
            res = ili9341_init_common(Config, Node);
            res = ili9341_init_node(Node);

            res = ili9341_software_reset(num);

            uint32_t i = 0 ;
            uint32_t cfg_cnt = ARRAY_SIZE(Ili9341InitConfig) ;
            for(i=0;i<cfg_cnt;i++) {
                if(0<Ili9341InitConfig[i].size) {
                    LOG_INFO(ILI9341, "ApplyCfg:%u/%u", i, cfg_cnt);
                    res = ili9341_write_cmd_param(num,
                                                  Ili9341InitConfig[i].command,
                                                  Ili9341InitConfig[i].data,
                                                  Ili9341InitConfig[i].size);
                }
            }

            res = ili9341_sleep_out(num);
            res = ili9341_display_on(num);
            res = ili9341_normal_mode_on(num);
            res = ili9341_set_orientation(  num, Node->screen_orientation);
            res = ili9341_fill_screen(num, 0x0000);
            uint32_t id = 0;
            res = ili9341_read_id(num, &id);
            LOG_INFO(ILI9341, "N:%u,ID:0x%08x", num, id);
            Node->init = res;
        } else {
            LOG_ERROR(ILI9341, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(ILI9341, "ConfigErr %u", num);
    }
    return res;
}


bool ili9341_write_font(uint8_t num,
                        uint16_t x,
                        uint16_t y,
                        uint16_t offset,
                        FontDef font,
                        uint16_t color,
                        uint16_t bgcolor) {
    bool res = false ;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node) {
            res = ili9341_set_address_window_ll(Node, x, y, x+font.width-1, y+font.height-1);
            uint32_t i = 0;
            for(i = 0; i < font.height; i++) {
                uint32_t h_raw = 0;
                h_raw = font.data[offset* font.height + i];
                uint32_t j = 0;
                for(j = 0; j < font.width; j++) {
                    uint16_t pix_color  = color;
                    if((h_raw << j) & 0x8000)  {
                        pix_color  = color;
                    } else {
                        pix_color  = bgcolor;
                    }
                    res = ili9341_send_word( Node ,  pix_color ) ;
                }
            }
    }
    return res;
}

bool ili9341_write_utf8_char(uint8_t num ,
                             uint16_t x,
                             uint16_t y,
                             char* start,
                             FontDef font,
                             uint16_t color,
                             uint16_t bgcolor) {
    bool res = false ;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node) {
        if('\n'==start[0]) {
            Node->y += font.height;
        } else if ('\b'==start[0]) {
            Node->y -= font.height;
        } else if('\r'==start[0]) {
            Node->x = 0;
            //Node->y += font.height;
        } else {
            if( Node->width < Node->x) {
                Node->x = 0;
                Node->y += font.height;
            }

            if ( Node->height < Node->y) {
                Node->y = 0;
            }

            const FontLettetInfo_t* Info = FontLetterToInfo(start);
            if(Info) {
                res = ili9341_write_font(num , x, y, Info->index, font, color, bgcolor);
                Node->x += font.width;
            }
        }
    }
    return res;
}



bool ili9341_write_char(uint8_t num ,
                        uint16_t x,
                        uint16_t y,
                        char ch,
                        FontDef font,
                        uint16_t color,
                        uint16_t bgcolor) {
    bool res = false ;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node) {
        if('\n'==ch) {
            Node->y += font.height;
        } else if ('\b'==ch) {
            Node->y -= font.height;
        } else if('\r'==ch) {
            Node->x = 0;
            //Node->y += font.height;
        } else {
            if( Node->width<Node->x) {
                Node->x=0;
                Node->y += font.height;
            }

            if ( Node->height<Node->y) {
                Node->y=0;
            }
            res = ili9341_write_font(num , x, y, (ch - 32), font, color, bgcolor);
            Node->x += font.width;
        }
    }
    return res;
}

bool ili9341_write_data(uint8_t num , const uint8_t * const data, const  uint32_t size) {
    bool  res = true;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node){
        uint32_t i=0;
        for(i=0;i<size;i++) {
            res = ili9341_write_char(num,
                                     Node->x,
                                     Node->y,
                                     data[i],
                                     Node->cur_font,
                                     Node->text_color,
                                     Node->bgcolor);
        }
    }
    return res;
}


bool ili9341_write_string(uint8_t num ,
                          uint16_t xi, uint16_t yi,
                          const char* str,
                          FontDef font,
                          uint16_t color,
                          uint16_t bgcolor) {
    bool  res = true;
    int32_t x = (int32_t) xi;
    int32_t y = (int32_t) yi;
    Ili9341Handle_t* Node=Ili9341GetNode(num);
    while(*str) {
        if(x + font.width >= Node->width) {
            x = 0;
            y += font.height;
            if(y + font.height >= Node->height) {
                break;
            }

            if(*str == ' ') {
                // skip spaces in the beginning of the new line
                str++;
                continue;
            }
        }

        res = ili9341_write_char(num, x, y, *str, font, color, bgcolor);
        x += font.width;
        str++;
    }

    return res;
}


bool ili9341_pix_array_color_set( const Color_t color, const uint8_t intensity,
                                  uint16_t *const data, const uint32_t cnt) {
    bool  res = true;
    uint32_t i = 0;
    Ili9341Pixel_t Pixel = ili9341_pix_color_set( color, intensity);
    for(i=0; i < cnt; i++) {
        data[i] = Pixel.word;
    }
    return res;
}

bool ili9341_writer_transmit(void* base) {
    bool res = false;
    WriterHandle_t* Writer = (WriterHandle_t*)base;
    if(Writer) {
        strcpy((char*)Writer->data, "");
        uint32_t out_len = 0;
        Writer->in_transmit = 0;
        res = fifo_pull_array(&Writer->fifo, Writer->data, 200, &out_len);
        if(false == res) {
            Writer->fifo.err_cnt++;
        } else {
            Writer->in_transmit = out_len;
        }
        if(0 < Writer->in_transmit) {
            Writer->tx_cnt += Writer->in_transmit;
            if(Writer->enable) {
                res = ili9341_write_data(Writer->inter_face.num, Writer->data,Writer->in_transmit);
            }
            Writer->in_transmit = 0;
        }
    }
    return res;
}


void ili9341_1_putc(void* stream_ptr, char ch) {

    Ili9341Handle_t *Node = Ili9341GetNode(1);
    if (Node) {
        ili9341_write_char(1, Node->x, Node->y, ch, Font_7x10, 0xFFFF, 0);
    }
}

void ili9341_1_puts(void* stream_ptr, const char* str, int32_t len) {
    if (str) {
        if (len) {
            Ili9341Handle_t *Node = Ili9341GetNode(1);
            if (Node) {
                ili9341_write_string(1, Node->x, Node->y, str, Font_7x10, 0xFFFF, 0);
            }
        }
    }
}

bool ili9341_write_utf8_string(uint8_t num ,
                               uint16_t xi, uint16_t yi,
                               const char* const str,
                               FontDef font,
                               uint16_t color,
                               uint16_t bgcolor) {
    bool  res = true;
    int32_t x = (int32_t) xi;
    int32_t y = (int32_t) yi;
    Ili9341Handle_t* Node = Ili9341GetNode(num);
    if(Node) {
        uint32_t i = 0;
        uint32_t cnt = utf8_strlen(str);
        for(i=0; i<cnt; i++) {
            if(x + font.width >= Node->width) {
                x = 0;
                y += font.height;
                if( Node->height  <= (y + font.height) ) {
                    break;
                }
            }

            char* start = utf8_str_get_i(str, i);
            res = ili9341_write_utf8_char(num, x, y, start, font, color, bgcolor);
            x += font.width;
        }
    }

    return res;
}


COMPONENT_INIT_PATTERT(ILI9341, ILI9341, ili9341)
COMPONENT_PROC_PATTERT(ILI9341, ILI9341, ili9341)
