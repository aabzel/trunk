#include "load_detect_diag.h"

#include "board_info.h"
#include "common_diag.h"
#include "gpio_diag.h"
#include "load_detect_const.h"
#include "load_detect_drv.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

const char* LoadDetectOut2Str(LoadDetectOut_t decision) {
    const char* name = "?";
    switch((uint8_t)decision) {
    case LOAD_DETECT_OUT_SHORT_VCC:
        name = "ShortVcc";
        break;
    case LOAD_DETECT_OUT_OPEN:
        name = "Open";
        break;
    case LOAD_DETECT_OUT_SHORT_GND:
        name = "ShortGnd";
        break;
    }
    return name;
}

const char* LoadDetectGpioClass2Str(GpioClass_t gpio_class) {
    const char* name = "?";
    switch((uint8_t)gpio_class) {
    case GPIO_CLASS_MCU:
        name = "MCU";
        break;
    case GPIO_CLASS_DW1000:
        name = "DW1000";
        break;
    case GPIO_CLASS_DW3000:
        name = "DW3000";
        break;
    }
    return name;
}

bool load_detect_pin_diag(void) {
    bool res = true;
    static const table_col_t cols[] = {
        {5, "Num"},  {7, "Pad"},   {7, "OnOff"},     {7, "P-Air"},
        {6, "P-Up"}, {7, "P-Dwn"}, {10, "solution"}, {15, "WireName"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t pad_cnt = load_detect_get_pin_cnt();
    for(int i = 1; i <= pad_cnt; i++) {
        LoadDetectPinInfo_t* Node = LoadDetectGetPinNode(i);
        if(Node) {
            cli_printf(TSEP);
            cli_printf(" %2u  " TSEP, i + 1);
            cli_printf(" %5s " TSEP, GpioPad2Str(Node->pad.byte));
            cli_printf(" %5s " TSEP, OnOffToStr(Node->on_off));
            cli_printf(" %5s " TSEP, GpioLevel2Str(Node->llevel_at_pullair));
            cli_printf(" %4s " TSEP, GpioLevel2Str(Node->llevel_at_pullup));
            cli_printf(" %5s " TSEP, GpioLevel2Str(Node->llevel_at_pulldown));
            cli_printf(" %8s " TSEP, LoadDetectOut2Str(Node->state));
            const Wire_t* WireInfio = Pad2WireInfio(Node->pad);
            if(WireInfio) {
                cli_printf(" %13s " TSEP, WireInfio->wire_name);
            } else {
                cli_printf(" %13s " TSEP, "?");
            }
            cli_printf(CRLF);
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    LOG_INFO(LOAD_DETECT, "spin cnt: %u", pad_cnt);

    return res;
}

bool load_detect_diag(void) {
    bool res = false;

    static const table_col_t cols[] = {
        {5, "Num"}, {7, "Class"}, {7, "OnOff"}, {7, "State"}, {6, "Spin"}, {6, "Err"}, {6, "pause"}, {7, "Start"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t cnt = load_detect_get_cnt();
    for(int i = 1; i <= cnt; i++) {
        LoadDetectHandle_t* Node = LoadDetectGetNode(i);
        if(Node) {
            cli_printf(TSEP);
            cli_printf(" %2u  " TSEP, i + 1);
            cli_printf(" %5s " TSEP, LoadDetectGpioClass2Str(Node->gpio_class));
            cli_printf(" %5s " TSEP, OnOffToStr(Node->on_off));
            cli_printf(" %5s " TSEP, GpioPull2Str(Node->state));
            cli_printf(" %4u " TSEP, Node->spin_cnt);
            cli_printf(" %4u " TSEP, Node->err_cnt);
            cli_printf(" %4u " TSEP, Node->pause_ms);
            cli_printf(" %5u " TSEP, Node->time_start);

            cli_printf(CRLF);
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
