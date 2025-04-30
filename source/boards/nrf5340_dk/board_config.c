#include "board_config.h"

#ifdef HAS_ADC
#include "adc_drv.h"
#endif

#include "data_utils.h"
#include "float_utils.h"
#include "log.h"
#include "sys_config.h"

#ifdef HAS_BOARD_INFO
#include "board_types.h"
#endif

#ifdef HAS_BOARD_INFO

const BoardConfig_t BoardConfig = {
    .volt_id_pad = {.port=2, .pin=2,},
    .volt_id = 0.0,
    .name = BOARD_NAME,
    .xtall_freq_hz = XTALL_FREQ,
};

const Wire_t Wires[]={
        {.pad={.port=0, .pin=0}, .wire_name="XL1", .silk="D14", .conn={ .designator="P", .num=6, .pin=1,},},
        {.pad={.port=0, .pin=1}, .wire_name="XL2", .silk="D15", .conn={ .designator="P", .num=6, .pin=2,},},
//        {.pad.port=0, .pad.pin=1, .wire_name="", .silk="", .conn={ .designator="J", .num=5, .pin=2,},},
        {.pad={.port=0, .pin=2}, .wire_name="NFC1", .silk="D16", .conn={ .designator="P", .num=6, .pin=3,},},
//        {.pad.port=0, .pad.pin=2, .wire_name="NFC1", .silk="", .conn={ .designator="J", .num=5, .pin=2,},},
        {.pad={.port=0, .pin=3}, .wire_name="NFC2", .silk="D17", .conn={ .designator="P", .num=6, .pin=4,},},
//        {.pad.port=0, .pad.pin=3, .wire_name="NFC2", .silk="", .conn={ .designator="J", .num=5, .pin=4,},},
        {.pad={.port=0, .pin=4}, .silk="A0", .wire_name="A0", .conn={.designator="P", .num=2, .pin=1,}},
        {.pad={.port=0, .pin=5}, .silk="A1", .wire_name="A1", .conn={.designator="P", .num=2, .pin=2,}},
        {.pad={.port=0, .pin=6}, .silk="A2", .conn={.designator="P", .num=2, .pin=3,},},
        {.pad={.port=0, .pin=7}, .wire_name="A3", .silk="D18", .conn={ .designator="P", .num=6, .pin=5,},},
//        {.pad.port=0, .pad.pin=7, .silk="A3", .conn.designator="P", .conn.num=2, .conn.pin=4,},
        {.pad={.port=0, .pin=8}, .wire_name="SW3", .silk="D19", .conn={ .designator="P", .num=6, .pin=6,},},
        {.pad={.port=0, .pin=9}, .wire_name="SW4", .silk="D20", .conn={ .designator="P", .num=6, .pin=7,},},
        {.pad={.port=0, .pin=10}, .wire_name="UART1_CTS", .silk="D21", .conn={ .designator="P", .num=6, .pin=8,},},
        {.pad={.port=0, .pin=11}, .wire_name="UART1_RTS/TRACEDATA0", .silk="DATA0/D22", .conn={ .designator="P", .num=24, .pin=0,},},
        {.pad={.port=0, .pin=12}, .wire_name="TRACECLK", .silk="CLK/D23", .conn={ .designator="P", .num=24, .pin=0,},},
        {.pad={.port=0, .pin=13}, .wire_name="QSPI0", .silk="D24", .conn={ .designator="P", .num=24, .pin=0,},},
        {.pad={.port=0, .pin=14}, .wire_name="QSPI1", .silk="D25", .conn={ .designator="P", .num=24, .pin=0,},},
        {.pad={.port=0, .pin=15}, .wire_name="QSPI2", .silk="D26", .conn={ .designator="P", .num=24, .pin=0,},},
        {.pad={.port=0, .pin=16}, .wire_name="QSPI3", .silk="D27", .conn={ .designator="P", .num=24, .pin=0,},},
        {.pad={.port=0, .pin=17}, .wire_name="QSPI_CLK", .silk="D28", .conn={ .designator="P", .num=24, .pin=0,},},
        {.pad={.port=0, .pin=18}, .wire_name="QSPI_CS", .silk="D29", .conn={ .designator="P", .num=24, .pin=0,},},
        {.pad={.port=0, .pin=19}, .wire_name="UART2_RTS", .silk="D30", .conn={ .designator="P", .num=24, .pin=0,},},
        {.pad={.port=0, .pin=20}, .wire_name="UART2_TXD", .silk="D31", .conn={ .designator="P", .num=24, .pin=0,},},
        {.pad={.port=0, .pin=21}, .wire_name="UART2_CTS", .silk="D32", .conn={ .designator="P", .num=24, .pin=0,},},
        {.pad={.port=0, .pin=22}, .wire_name="UART2_RXD", .silk="D33", .conn={ .designator="P", .num=24, .pin=0,},},
        {.pad={.port=0, .pin=23}, .wire_name="SW1", .silk="D34", .conn={ .designator="P", .num=24, .pin=13,},},
        {.pad={.port=0, .pin=24}, .wire_name="SW2", .silk="D35", .conn={ .designator="P", .num=24, .pin=14,},},
        {.pad={.port=0, .pin=25}, .silk="", .silk="A4", .conn={.designator="P", .num=2, .pin=5,},},
        {.pad={.port=0, .pin=26}, .silk="", .silk="A5", .conn={.designator="P", .num=2, .pin=6,},},
        {.pad={.port=0, .pin=27}, .wire_name="AIN6", .silk="AREF", .conn={.designator="P", .num=4, .pin=8,},},
        {.pad={.port=0, .pin=28}, .wire_name="Led1Green", .silk="D36", .conn={ .designator="P", .num=24, .pin=15,},},
        {.pad={.port=0, .pin=29}, .wire_name="Led2Green", .silk="D37", .conn={ .designator="P", .num=24, .pin=16,},},
        {.pad={.port=0, .pin=30}, .wire_name="Led3Green", .silk="D38", .conn={ .designator="P", .num=24, .pin=17,},},
        {.pad={.port=0, .pin=31}, .wire_name="Led4Green", .silk="D39", .conn={ .designator="P", .num=24, .pin=18,},},
        {.pad={.port=1, .pin=0}, .wire_name="RxD", .silk="D0", .conn={ .designator="P", .num=3, .pin=1,},},
        {.pad={.port=1, .pin=1}, .wire_name="TxD", .silk="D1", .conn={ .designator="P", .num=3, .pin=2,},},
        {.pad={.port=1, .pin=2}, .wire_name="SDA", .silk="SDA", .conn={ .designator="P", .num=4, .pin=9,},},
        {.pad={.port=3, .pin=3}, .wire_name="GND", .silk="", .conn={ .designator="P", .num=4, .pin=7,},},
        {.pad={.port=1, .pin=3}, .wire_name="SCL", .silk="SCL", .conn={ .designator="P", .num=4, .pin=10,},},
        {.pad={.port=1, .pin=4}, .silk="D2", .conn={ .designator="P", .num=3, .pin=3,},},
        {.pad={.port=1, .pin=5}, .silk="D3", .conn={ .designator="P", .num=3, .pin=4,},},
        {.pad={.port=1, .pin=6}, .silk="D4", .conn={ .designator="P", .num=3, .pin=5,},},
        {.pad={.port=1, .pin=7}, .silk="D5", .conn={ .designator="P", .num=3, .pin=6,},},
        {.pad={.port=1, .pin=8}, .silk="D6", .conn={ .designator="P", .num=3, .pin=7,},},
        {.pad={.port=1, .pin=9}, .silk="D7", .conn={ .designator="P", .num=3, .pin=8,},},
        {.pad={.port=1, .pin=10}, .silk="D8", .conn={ .designator="P", .num=4, .pin=1,},},
        {.pad={.port=1, .pin=11}, .silk="D9", .conn={ .designator="P", .num=4, .pin=2,},},
        {.pad={.port=1, .pin=12}, .silk="D10", .conn={ .designator="P", .num=4, .pin=3,},},
        {.pad={.port=1, .pin=13}, .silk="D11", .conn={ .designator="P", .num=4, .pin=4,},},
        {.pad={.port=1, .pin=14}, .silk="D12", .conn={ .designator="P", .num=4, .pin=5,},},
        {.pad={.port=1, .pin=15}, .silk="D13", .conn={ .designator="P", .num=4, .pin=6,},}

};

uint32_t wires_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(Wires);
    return cnt;
}
#endif /*HAS_BOARD_INFO*/

bool board_init(void) {
    bool res = false;
#ifdef HAS_BOARD_INFO
    uint32_t cnt = wires_get_cnt();
    LOG_WARNING(SYS,"Init Board [%s] WireCnt %u",BoardConfig.name, cnt);
#else /*HAS_BOARD_INFO*/
    LOG_WARNING(SYS,"Init Board WireCnt");
#endif /*HAS_BOARD_INFO*/
    res = true;
#if defined(HAS_BT_BLE_UWB_TAG_CFG) || defined(HAS_BLE_SPEAKER_CFG)
    res = set_log_level(DECA, LOG_LEVEL_ERROR);
#endif
    return res;
}
