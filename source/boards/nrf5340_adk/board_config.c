#include "board_config.h"

#include "board_types.h"
#include "data_utils.h"
#include "log.h"

bool board_init(void) {
    bool res = true;
    LOG_INFO(SYS,"BoardInit");
    set_log_level(SYS,LOG_LEVEL_INFO);
    LOG_INFO(SYS,"XTall: %u Hz",XTAL_FREQ_HZ);
    return res;
}

const Wire_t Wires[]= {
        {.pad={.port=0, .pin=0}, .wire_name="XL1", },
        {.pad={.port=0, .pin=1}, .wire_name="XL2", },
        {.pad={.port=0, .pin=2}, .facility=GPIO, .wire_name="BUTTON1", .silk="NFC1",.conn={ .designator="J", .num=4, .pin=2,}, .facility=SYS,},
        {.pad={.port=0, .pin=3}, .facility=GPIO, .wire_name="BUTTON2", .silk="NFC2",.conn={ .designator="J", .num=4, .pin=4,}, .facility=SYS,},
        {.pad={.port=0, .pin=4}, .facility=GPIO, .wire_name="BUTTON3", .silk="A0",.conn={ .designator="P", .num=2, .pin=1,}, .facility=SYS,},
        {.pad={.port=0, .pin=5}, .facility=GPIO, .wire_name="BUTTON5", .silk="A1",.conn={ .designator="P", .num=2, .pin=2,},},
        {.pad={.port=0, .pin=6}, .facility=GPIO, .wire_name="BUTTON4", .silk="A2",.conn={ .designator="P", .num=2, .pin=3,},},
        {.pad={.port=0, .pin=7}, .facility=LED_RGB, .wire_name="RGB1_RED", .silk="RED/A3", .conn={ .designator="P", .num=2, .pin=4,},},
        {.pad={.port=0, .pin=8}, .wire_name="SCK(SD)", .silk="DATA3/D13", .conn={ .designator="P", .num=4, .pin=6,},}, /*??*/
        {.pad={.port=0, .pin=9}, .facility=SPI, .wire_name="MOSI(SD)", .silk="DATA2/D11",.conn={ .designator="P", .num=4, .pin=4,},},
        {.pad={.port=0, .pin=10}, .facility=SPI, .wire_name="MISO(SD)", .silk="DATA1/D12",.conn={ .designator="P", .num=4, .pin=5,},}, /* P13.16,  */
        {.pad={.port=0, .pin=11}, .facility=SYS, .wire_name="SWD3/CS(SD)", .silk="DATA0/SWO",.conn={ .designator="P", .num=13, .pin=6,},},
        {.pad={.port=0, .pin=12}, .wire_name="MCLK",.silk="CLK", .conn={ .designator="P", .num=10, .pin=6,},},
        {.pad={.port=0, .pin=13}, .wire_name="DIN",.silk="", .conn={ .designator="P", .num=10, .pin=10,},},
        {.pad={.port=0, .pin=14}, .wire_name="BCLK",.silk="", .conn={ .designator="P", .num=10, .pin=7,},},
        {.pad={.port=0, .pin=15}, .wire_name="DOUT",.silk="", .conn={ .designator="P", .num=10, .pin=9,},},
        {.pad={.port=0, .pin=16}, .wire_name="FSYNC",.silk="", .conn={ .designator="P", .num=10, .pin=8,},},
        {.pad={.port=0, .pin=17}, .facility=SPI, .wire_name="CS(DAC)",.silk="",.conn={ .designator="P", .num=10, .pin=11,},},
        {.pad={.port=0, .pin=18}, .facility=GPIO, .wire_name="RESET",.silk="",.conn={ .designator="P", .num=10, .pin=3,},},
        {.pad={.port=0, .pin=19}, .facility=GPIO, .wire_name="IRQ",.silk="",.conn={ .designator="P", .num=10, .pin=4,},},
        {.pad={.port=0, .pin=20}, .facility=GPIO, .wire_name="GPIO",.silk="",.conn={ .designator="P", .num=10, .pin=5,},},
        {.pad={.port=0, .pin=21}, .facility=GPIO, .wire_name="HW_CODEC_SELECT", },
        {.pad={.port=0, .pin=22}, .facility=SPI, .wire_name="SPI_SELECT", },
        {.pad={.port=0, .pin=23}, .wire_name="PMIC_ISET",},
        {.pad={.port=0, .pin=24}, .facility=GPIO, .wire_name="BOARD_ID_EN",},
        {.pad={.port=0, .pin=25}, .facility=LED_RGB, .wire_name="RGB1_GREEN", .silk="GREEN/A4",.conn={ .designator="P", .num=2, .pin=5,},},
        {.pad={.port=0, .pin=26}, .facility=LED_RGB, .wire_name="RGB1_BLUE", .silk="BLUE/A5",.conn={ .designator="P", .num=2, .pin=6,},},
        {.pad={.port=0, .pin=27}, .facility=SYS, .wire_name="BOARD_ID", .silk="A6",},
        {.pad={.port=0, .pin=28}, .facility=LED_RGB, .wire_name="RGB2", .silk="RED/AREF", .conn={ .designator="P", .num=4, .pin=8,},},
        {.pad={.port=0, .pin=29}, .facility=LED_RGB, .wire_name="RGB2", .silk="GREEN", .conn={ .designator="LD", .num=8, .pin=2,},},
        {.pad={.port=0, .pin=30}, .facility=LED_RGB, .wire_name="RGB2", .silk="BLUE", .conn={ .designator="LD", .num=8, .pin=3,},},
        {.pad={.port=0, .pin=31}, .facility=LED, .wire_name="LED1", .silk="D2",.conn={ .designator="P", .num=3, .pin=3,},},

        {.facility=SYS, .wire_name="SWD3", .silk="RESET", .conn={ .designator="P", .num=13, .pin=10,},},
        {.facility=SYS, .wire_name="SWD3", .silk="SWDIO", .conn={ .designator="P", .num=13, .pin=2,},},
        {.facility=SYS, .wire_name="SWD3", .silk="SWDCLK", .conn={ .designator="P", .num=13, .pin=4,},},

        {.pad={.port=1, .pin=0},  .facility=LED, .wire_name="LED2", .silk="D3", .conn={ .designator="P", .num=3, .pin=4,},},
        {.pad={.port=1, .pin=1},  .facility=LED, .wire_name="LED3", .silk="D4", .conn={ .designator="P", .num=3, .pin=5,},},
        {.pad={.port=1, .pin=2},   .wire_name="SDA", .silk="", .conn={ .designator="P", .num=4, .pin=9,},}, /*???*/
        {.pad={.port=1, .pin=3},   .wire_name="SCL", .silk="", .conn={ .designator="P", .num=4, .pin=10,},}, /*???*/
        {.pad={.port=1, .pin=4},  .facility=UART, .wire_name="UART1_RXD", .silk="RXD",.conn={ .designator="TP", .num=60, .pin=1,},},
        {.pad={.port=1, .pin=5},  .facility=UART, .wire_name="UART1_TXD", .silk="TXD",.conn={ .designator="TP", .num=61, .pin=1,},},
        {.pad={.port=1, .pin=7},  .facility=GPIO, .wire_name="UART1_RTS", .silk="D6",.conn={ .designator="P", .num=3, .pin=7,},},
        {.pad={.port=1, .pin=6},  .facility=GPIO, .wire_name="UART1_CTS", .silk="MIC_DOUT", .conn={ .designator="TP", .num=62, .pin=1,},},
        {.pad={.port=1, .pin=9},  .facility=UART, .wire_name="UART2_TXD", .silk="D0",.conn={ .designator="P", .num=3, .pin=1,},},
        {.pad={.port=1, .pin=8},  .facility=UART, .wire_name="UART2_RXD", .silk="D1",.conn={ .designator="P", .num=3, .pin=2,},},
        {.pad={.port=1, .pin=10}, .facility=GPIO, .wire_name="UART2_CTS", .silk="D8",.conn={ .designator="P", .num=4, .pin=1,},},
        {.pad={.port=2, .pin=2},                  .wire_name="GND",                  .conn={ .designator="P", .num=4, .pin=7,},},

        {.pad={.port=2, .pin=2},                  .wire_name="1V8",                  .conn={ .designator="P", .num=1, .pin=1,},},
        {.pad={.port=2, .pin=2},                  .wire_name="1V8",                  .conn={ .designator="P", .num=1, .pin=2,},},
        {.pad={.port=2, .pin=2},                  .wire_name="RESET_PIN",            .conn={ .designator="P", .num=1, .pin=3,},},
        {.pad={.port=2, .pin=2},                  .wire_name="1V8",                  .conn={ .designator="P", .num=1, .pin=4,},},
        {.pad={.port=2, .pin=2},                  .wire_name="5V0",                  .conn={ .designator="P", .num=1, .pin=5,},},
        {.pad={.port=2, .pin=2},                  .wire_name="GND",                  .conn={ .designator="P", .num=1, .pin=6,},},
        {.pad={.port=2, .pin=2},                  .wire_name="GND",                  .conn={ .designator="P", .num=1, .pin=7,},},
        {.pad={.port=2, .pin=2},                  .wire_name="NC",                   .conn={ .designator="P", .num=1, .pin=8,},},

        {.pad={.port=1, .pin=11}, .wire_name="UART2_RTS", .silk="D7",.conn={ .designator="P", .num=3, .pin=8,},},
        {.pad={.port=1, .pin=12}, .wire_name=SPARE_WIRE_NAME, .silk="D10", .conn={ .designator="P", .num=4, .pin=3,},},
        {.pad={.port=1, .pin=13}, .wire_name=SPARE_WIRE_NAME, .silk="D9", .conn={ .designator="P", .num=4, .pin=2,},},
        {.pad={.port=1, .pin=14}, .wire_name=SPARE_WIRE_NAME, .silk="D5", .conn={ .designator="P", .num=3, .pin=6,},},
        {.pad={.port=1, .pin=15}, .wire_name="CURR_MON_ALERT",},
};


uint32_t wires_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(Wires);

    return cnt;
}

