
#ifndef DECADRIVER_TYPES_H
#define DECADRIVER_TYPES_H

#include "data_types.h"
#include "deca_device_api.h"
#include "decadriver_const.h"
#include "decadriver_dependencies.h"
#include "log_types.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif /*HAS_GPIO*/

typedef union {
    uint16_t word;
    struct {
        uint8_t voltage;
        uint8_t temperature;
    };
} TempVbat_t;

#define COMMON_VARIABLE                                                                                                \
    bool valid;                                                                                                        \
    uint8_t spi_num;

typedef struct {
    COMMON_VARIABLE
    int init_arg;
#ifdef HAS_GPIO
    GpioLogicLevel_t reset_active_level;
    GpioLogicLevel_t irq_active_level_dflt;
    Pad_t reset;
    Pad_t irq;
    Pad_t chip_select;
    Pad_t wakeup;
    Pad_t gpio5;
    Pad_t gpio6;
#endif /*HAS_GPIO*/
    uint32_t rx_delay_us;
    uint16_t rx_timeout_us;
    uint16_t preamble_detect_timeout_pac;
    log_level_t log_level;
    dwt_config_t config;
} DecaDriverConfig_t;

typedef struct {
    COMMON_VARIABLE

    volatile bool tx_it;
    volatile bool rx_it;
    uint32_t it_cnt;
    volatile uint32_t tx_cnt;
    volatile uint32_t rx_cnt;
    uint32_t rx_byte_cnt;
    volatile uint32_t rx_time_out_cnt;
    uint32_t status_reg;
    volatile uint32_t err_cnt;
    uint32_t part_id;
    uint32_t dev_id;

    uint32_t lot_id;
    uint32_t tx_time_stamp_hi32;
    uint32_t rx_time_stamp_hi32;
    dwt_rxdiag_t diagnostics;
    dwt_deviceentcnts_t counters;

    TempVbat_t temp_vbat;
    uint8_t wakeup_temp;
    int32_t carrier_integrator;
    int32_t spi_link_err_cnt;
    int32_t proc_cnt;
    uint8_t wakeup_vbat;
    uint64_t eui;

    volatile MindValU64_t tx_time_stamp;
    volatile MindValU64_t rx_time_stamp;

    uint64_t sys_time;
    double sys_time_s;
    uint8_t xtal_trim;
    uint8_t icref_volt;
    uint8_t icref_temp;
    bool connected;
    uint8 buff[RX_BUF_LEN];
} DecaDriverInstance_t;

#endif /* DECADRIVER_TYPES_H*/
