#include "spi_drv.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/kernel.h>
#include <zephyr/zephyr.h>

#include "macro_utils.h"
#include "spi_config.h"
#include "spi_custom_types.h"

#ifdef HAS_LOG
#include "log.h"
#endif /*HAS_LOG*/

#ifndef HAS_ZEPHYR
#error "+HAS_ZEPHYR"
#endif

#define SPI_OP SPI_OP_MODE_MASTER | SPI_MODE_CPOL | SPI_MODE_CPHA | SPI_WORD_SET(8) | SPI_LINES_SINGLE

static const SpiInfo_t SpiInfoLut[] = {
#ifdef HAS_SPI0
    {
        .num = 0,
        .SpiDev = DEVICE_DT_GET(DT_NODELABEL(spi0)),
    },
#endif

#ifdef HAS_SPI1
    {
        .num = 1,
        .SpiDev = DEVICE_DT_GET(DT_NODELABEL(spi1)),
    },
#endif

#ifdef HAS_SPI2
    {
        .num = 2,
        .SpiDev = DEVICE_DT_GET(DT_NODELABEL(spi2)),
    },
#endif

#ifdef HAS_SPI3
    {
        .num = 3,
        .SpiDev = DEVICE_DT_GET(DT_NODELABEL(spi3)),
    },
#endif

#ifdef HAS_SPI4
    {
        .num = 4,
        .SpiDev = DEVICE_DT_GET(DT_NODELABEL(spi4)),
    },
#endif
};

static struct device* SpiNumToSpiDevPtr(uint8_t num) {
    struct device* Node = NULL;
    uint32_t cnt = ARRAY_SIZE(SpiInfoLut);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(SpiInfoLut[i].num == num) {
            Node = SpiInfoLut[i].SpiDev;
            break;
        }
    }
    return Node;
}

bool spi_api_read(uint8_t num, uint8_t* const rx_array, uint32_t rx_array_len) {
    bool res = false;
    LOG_DEBUG(SPI, "SPI%u Read %u byte", num, rx_array_len);
    if(rx_array) {
        SpiHandle_t* Node = SpiGetNode(num);
        struct device* SpiDev = SpiNumToSpiDevPtr(num);
        if(SpiDev) {
            if(0 < rx_array_len) {
                const struct spi_buf rx_buf = {.buf = rx_array, .len = rx_array_len};
                const struct spi_buf_set rx_bufs = {.buffers = &rx_buf, .count = 1};
                struct spi_config SpiConfig = {0};
                SpiConfig.frequency = spi_get_rate_conf(num);
                SpiConfig.slave = 0;
                SpiConfig.operation = SPI_WORD_SET(8) | SPI_OP_MODE_MASTER;
                int ret = spi_read(SpiDev, &SpiConfig, &rx_bufs);
                if(0 == ret) {
                    res = true;
                    Node->rx_byte_cnt += rx_array_len;
                    LOG_DEBUG(SPI, "SPI%u ReadOk %u Byte", num, rx_array_len);
                    log_level_t ll = log_level_get(SPI);
                    if(LOG_LEVEL_DEBUG == ll) {
                        print_hex(rx_array_len, rx_array_len);
                    }
#ifdef HAS_ZEPHYR_RTOS
                    // k_msleep(2);
#endif
                } else {
                    LOG_ERROR(SPI, "SPI%u ReadErr %d=%s", num, ret, ErrNo2Str(ret));
                }
            }
        } else {
            LOG_ERROR(SPI, "SPI%u DevErr", num);
        }
    }
    return res;
}

bool spi_api_write(uint8_t num, const uint8_t* const tx_array, uint32_t tx_array_len) {
    bool res = false;
    LOG_DEBUG(SPI, "SPI%u Write Len: %u", num, tx_array_len);
    log_level_t ll = log_level_get(SPI);
    if(LOG_LEVEL_DEBUG == ll) {
        print_hex(tx_array, tx_array_len);
    }
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node && tx_array && (0 < tx_array_len)) {
        struct device* SpiDev = SpiNumToSpiDevPtr(num);
        if(SpiDev) {
            if(tx_array_len) {
                const struct spi_buf tx_buf = {.buf = tx_array, .len = tx_array_len};
                const struct spi_buf_set tx_bufs = {.buffers = &tx_buf, .count = 1};
                struct spi_config SpiConfig = {0};
                SpiConfig.frequency = spi_get_rate_conf(num);
                SpiConfig.slave = 0;
                SpiConfig.operation = SPI_WORD_SET(8) | SPI_OP_MODE_MASTER;
                int ret = spi_write(SpiDev, &SpiConfig, &tx_bufs);
                if(0 == ret) {
                    res = true;
                    LOG_DEBUG(SPI, "SPI%u WriteOk %u byte", num, tx_array_len);
                    Node->tx_byte_cnt += tx_array_len;
#ifdef HAS_ZEPHYR_RTOS
                    //          k_msleep(2);
#endif
                } else {
                    LOG_ERROR(SPI, "%u WriteErr %d=%s %u Hz", num, ret, ErrNo2Str(ret), SpiConfig.frequency);
                }
            }
        } else {
            LOG_ERROR(SPI, "%u DevError", num);
        }
    }
    return res;
}

bool spi_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SPI, "Init SPI%u", num);
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        res = true;
    } else {
        LOG_ERROR(SPI, "HandleErr");
        res = false;
    }

    if(res) {
        /*Zephyr kernel will init SPI periphery*/
        Node->init_done = true;
        LOG_INFO(SPI, "%u InitOk", num);
    } else {
        LOG_ERROR(SPI, "%u InitErr " LOG_ER, num);
    }
    return res;
}

#if 0
bool spi_init(void) {
    bool res = true;
    uint8_t cnt = 0;
#ifdef HAS_LOG
    LOG_WARNING(SPI, "Init");
#endif

#ifdef HAS_SPI0
    cnt += (uint8_t)spi_init_one(0);
#endif /*HAS_SPI0*/

#ifdef HAS_SPI1
    cnt += (uint8_t)spi_init_one(1);
#endif /*HAS_SPI1*/

#ifdef HAS_SPI2
    cnt += (uint8_t)spi_init_one(2);
#endif /*HAS_SPI2*/

#ifdef HAS_SPI3
    cnt += (uint8_t)spi_init_one(3);
#endif /*HAS_SPI3*/

#ifdef HAS_SPI4
    cnt += (uint8_t)spi_init_one(4);
#endif /*HAS_SPI4*/
    if(cnt) {
        LOG_INFO(SPI, "Init %u SPIs", cnt);
        res = true;
    } else {
        LOG_ERROR(SPI, "InitSPIerr");
        res = false;
    }
    return res;
}
#endif

uint32_t spi_get_clock(uint8_t num) {
    uint32_t spi_bit_rate = 0xFF;
    (void)num;
    if(SpiInstance[num].init_done) {
    }
    return spi_bit_rate;
}

uint8_t spi_get_phase(uint8_t num) {
    uint32_t phase = 9;
    (void)num;
    if(SpiInstance[num].init_done) {
        phase = 99;
    }
    return phase;
}

uint8_t spi_get_polarity(uint8_t num) {
    uint32_t polarity = 9;
    (void)num;
    if(SpiInstance[num].init_done) {
    }
    return polarity;
}

uint8_t spi_get_data_size(uint8_t num) {
    uint32_t data_size = 0xFF;
    (void)num;
    if(SpiInstance[num].init_done) {
    }
    return data_size;
}

uint8_t spi_get_transmit_int(uint8_t num) {
    uint8_t val = 0xFF;
    (void)num;
    if(SpiInstance[num].init_done) {
    }
    return val;
}

uint8_t spi_get_receive_int(uint8_t num) {
    uint8_t val = 0xFF;
    (void)num;
    if(SpiInstance[num].init_done) {
    }
    return val;
}

uint8_t spi_get_receive_timeout_interrupt(uint8_t num) {
    uint8_t val = 0xFF;
    (void)num;
    if(SpiInstance[num].init_done) {
    }
    return val;
}

uint8_t spi_get_receive_overrun_interrupt(uint8_t num) {
    uint8_t val = 0xFF;
    (void)num;
    if(SpiInstance[num].init_done) {
    }
    return val;
}

bool spi_api_write_read(uint8_t spi_num, const uint8_t* const tx_array, uint8_t* rx_array, uint32_t size) {
    return false;
}
