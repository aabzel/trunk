#include "spi_drv.h"

#include <spi_master.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "bit_utils.h"
#include "clocks.h"
#include "gpio_drv.h"
#include "log.h"
#include "spi_common.h"
#include "sys_config.h"

#ifdef HAS_SPI_INT
static void SPI0_CallBack() {
    SpiInstance[0].it_cnt++;
    SpiInstance[0].it_done = true;
}
static void SPI1_CallBack() {
    SpiInstance[1].it_cnt++;
    SpiInstance[1].it_done = true;
}
#endif

const static uint32_t SpiBaseLut[SPI_CNT] = {SPI0_BASE, SPI1_BASE, SPI2_BASE, SPI3_BASE};

// This function is called (in irq context!) just before a transmission starts. It will
// set the D/C line to the value indicated in the user field.
void spi0_pre_transfer_callback(spi_transaction_t* transaction) {
    // int dc=(int)transaction->user;
    // gpio_set_state(DIO_SX1262_SS, 0);
}
void spi1_pre_transfer_callback(spi_transaction_t* transaction) {
    // int dc=(int)transaction->user;
    // gpio_set_state(DIO_SX1262_SS, 0);
}
void spi2_pre_transfer_callback(spi_transaction_t* transaction) {
    // int dc=(int)transaction->user;
    // gpio_set_state(DIO_SX1262_SS, 0);
}
void spi3_pre_transfer_callback(spi_transaction_t* transaction) {
    // int dc=(int)transaction->user;
    // gpio_set_state(DIO_SX1262_SS, 0);
}

void spi0_post_transfer_callback(spi_transaction_t* transaction) {
    // int dc=(int)transaction->user;
    // gpio_set_state(DIO_SX1262_SS, 1);
}
void spi1_post_transfer_callback(spi_transaction_t* transaction) {
    // int dc=(int)transaction->user;
    // gpio_set_state(DIO_SX1262_SS, 1);
}
void spi2_post_transfer_callback(spi_transaction_t* transaction) {
    // int dc=(int)transaction->user;
    // gpio_set_state(DIO_SX1262_SS, 1);
}
void spi3_post_transfer_callback(spi_transaction_t* transaction) {
    // int dc=(int)transaction->user;
    // gpio_set_state(DIO_SX1262_SS, 1);
}

const spi_device_interface_config_t SpiDevCfg[SPI_CNT] = {
    {
        .command_bits = 0,
        .address_bits = 0,
        .cs_ena_pretrans = 10,
        .dummy_bits = 0,
        // .flags=0,
        .flags = SPI_DEVICE_HALFDUPLEX,
        .duty_cycle_pos = 128,
        .cs_ena_posttrans = 10,
        .clock_speed_hz = SPI_CLK_FREQUENCY_HZ, // Clock out at 26 MHz
        .mode = 0,                              // SPI mode 0
        //.spics_io_num = DIO_SX1262_SS,                     // CS pin
        .spics_io_num = -1,                   // CS pin
        .queue_size = 1,                      // We want to be able to queue 7 transactions at a time
        .pre_cb = spi0_pre_transfer_callback, // Specify pre-transfer callback to handle D/C line
        .post_cb = spi0_post_transfer_callback,
    },
    {
        .command_bits = 0,
        .address_bits = 0,
        .cs_ena_pretrans = 10,
        .dummy_bits = 0,
        // .flags=0,
        .flags = SPI_DEVICE_HALFDUPLEX,
        .cs_ena_posttrans = 10,
        .duty_cycle_pos = 128,
        .clock_speed_hz = SPI_CLK_FREQUENCY_HZ, // Clock out at 26 MHz
        .mode = 0,                              // SPI mode 0
        //.spics_io_num = DIO_SX1262_SS,                     // CS pin
        .spics_io_num = -1,                   // CS pin
        .queue_size = 1,                      // We want to be able to queue 7 transactions at a time
        .pre_cb = spi1_pre_transfer_callback, // Specify pre-transfer callback to handle D/C line
        .post_cb = spi1_post_transfer_callback,
    },
    {
        .command_bits = 0,
        .address_bits = 0,
        .cs_ena_pretrans = 10,
        .cs_ena_posttrans = 10,
        .dummy_bits = 0,
        // .flags=0,
        .flags = SPI_DEVICE_HALFDUPLEX,
        .duty_cycle_pos = 128,
        .clock_speed_hz = SPI_CLK_FREQUENCY_HZ, // Clock out at 26 MHz
        .mode = 0,                              // SPI mode 0
        //.spics_io_num = DIO_SX1262_SS,                     // CS pin
        .spics_io_num = -1,                   // CS pin
        .queue_size = 1,                      // We want to be able to queue 7 transactions at a time
        .pre_cb = spi2_pre_transfer_callback, // Specify pre-transfer callback to handle D/C line
        .post_cb = spi2_post_transfer_callback,
    },
    {
        .command_bits = 0,
        .address_bits = 0,
        .dummy_bits = 0,
        .duty_cycle_pos = 128,
        .cs_ena_pretrans = 10,
        // .flags=0,
        .flags = SPI_DEVICE_HALFDUPLEX,
        .cs_ena_posttrans = 10,
        .clock_speed_hz = SPI_CLK_FREQUENCY_HZ, // Clock out at 26 MHz
        .mode = 0,                              // SPI mode 0
        //.spics_io_num = DIO_SX1262_SS,                     // CS pin
        .spics_io_num = -1,                   // CS pin
        .queue_size = 1,                      // We want to be able to queue 7 transactions at a time
        .pre_cb = spi3_pre_transfer_callback, // Specify pre-transfer callback to handle D/C line
        .post_cb = spi3_post_transfer_callback,
    },
};

spi_bus_config_t SpiBusCfg[SPI_CNT] = {{
                                           /*SPI0*/
                                           .miso_io_num = DIO_SPI0_MISO,
                                           .mosi_io_num = DIO_SPI0_MOSI,
                                           .sclk_io_num = DIO_SPI0_SCLK,
                                           .quadwp_io_num = -1,
                                           .quadhd_io_num = -1,
                                           .max_transfer_sz = 1,
                                       },
                                       {/*SPI1*/
                                        .miso_io_num = DIO_SPI0_MISO,
                                        .mosi_io_num = DIO_SPI0_MOSI,
                                        .sclk_io_num = DIO_SPI0_SCLK,
                                        .quadwp_io_num = -1,
                                        .quadhd_io_num = -1,
                                        .max_transfer_sz = 1},
                                       {/*SPI2*/
                                        .miso_io_num = DIO_SPI0_MISO,
                                        .mosi_io_num = DIO_SPI0_MOSI,
                                        .sclk_io_num = DIO_SPI0_SCLK,
                                        .quadwp_io_num = -1,
                                        .quadhd_io_num = -1,
                                        .max_transfer_sz = 1},
                                       {/*SPI3*/
                                        .miso_io_num = DIO_SPI0_MISO,
                                        .mosi_io_num = DIO_SPI0_MOSI,
                                        .sclk_io_num = DIO_SPI0_SCLK,
                                        .quadwp_io_num = -1,
                                        .quadhd_io_num = -1,
                                        .max_transfer_sz = 1}};

spi_host_device_t SpiNum2HostId(SpiName_t spi_num) {
    spi_host_device_t host_id = SPI1_HOST;
    switch(spi_num) {
    case SPI0_INX:
        host_id = SPI1_HOST;
        break;
    case SPI1_INX:
        host_id = SPI1_HOST;
        break;
    case SPI2_INX:
        host_id = SPI2_HOST;
        break;
    case SPI3_INX:
        host_id = SPI3_HOST;
        break;
    default:
        break;
    }
    return host_id;
}

static bool spi_init_ll(SpiName_t spi_num, char* spi_name, uint32_t bit_rate) {
    bool res = false;
    SpiInstance[spi_num].init_done = false;

    strncpy(SpiInstance[spi_num].name, spi_name, SPI_NAME_SIZE_BYTE);
    SpiInstance[spi_num].rx_byte_cnt = 0;
    SpiInstance[spi_num].tx_byte_cnt = 0;
    SpiInstance[spi_num].it_done = true;
    SpiInstance[spi_num].base_addr = SpiBaseLut[spi_num];

    esp_err_t ret = ESP_ERR_INVALID_ARG;
    // ret = spi_bus_initialize(SpiNum2HostId(spi_num), &SpiBusCfg[spi_num], SPI_DMA_CH_AUTO);
    ret = spi_bus_initialize(SpiNum2HostId(spi_num), &SpiBusCfg[spi_num], 1);
    if(ESP_OK == ret) {
        res = true;
        SpiInstance[spi_num].init_done = true;
#ifdef INIT_SPI_SEND
        uint8_t tx_buff[4] = {0x55, 0xaa, 0x55, 0xaa};
        res = spi_write(index, tx_buff, 4) && res;
#endif
    }

    if(res) {
        ret = spi_bus_add_device(SpiNum2HostId(spi_num), (const spi_device_interface_config_t*)&SpiDevCfg[spi_num],
                                 &SpiInstance[spi_num].spi_device_handle);
        if(ESP_OK == ret) {
            res = true;
            SpiInstance[spi_num].init_done = true;
        } else {
            res = false;
        }
    }
    SpiInstance[spi_num].mutex = xSemaphoreCreateMutexStatic(&SpiInstance[spi_num].xMutexBuffer);
    if(NULL == SpiInstance[spi_num].mutex) {
        res = false;
        LOG_ERROR(SPI, "MutexInitError");
    } else {
        LOG_INFO(SPI, "MutexInitOk");
    }
    return res;
}

bool spi_init(void) {
    bool res = true;
#ifdef HAS_SPI0
    res = spi_init_ll(SPI0_INX, "SPI0", SPI0_BIT_RATE_HZ) && res;
#endif /*HAS_SPI0*/
#ifdef HAS_SPI1
    res = spi_init_ll(SPI1_INX, "SPI1", SPI1_BIT_RATE_HZ) && res;
#endif /*HAS_SPI1*/
#ifdef HAS_SPI2
    res = spi_init_ll(SPI2_INX, "SPI2", SPI2_BIT_RATE_HZ) && res;
#endif /*HAS_SPI2*/
#ifdef HAS_SPI3
    res = spi_init_ll(SPI3_INX, "SPI3", SPI3_BIT_RATE_HZ) && res;
#endif /*HAS_SPI3*/
    return res;
}

#if 0
static bool spi_wait_tx(SpiName_t spi_num, uint32_t init_it_cnt) {
    bool res = false;
    uint32_t cnt = 0;
    (void)spi_num;
    while(1) {
        if(init_it_cnt < SpiInstance[spi_num].it_cnt) {
            res = true;
            break;
        }
        cnt++;
        if(1500000 < cnt) {
            res = false;
            break;
        }
    }
    return res;
}
#endif

bool spi_wait_tx_done(SpiName_t spi_num) {
    bool res = false;
    (void)spi_num;
    uint32_t cnt = 0;
    while(1) {
        if(true == SpiInstance[spi_num].it_done) {
            res = true;
            break;
        }
        cnt++;
        if(1500000 < cnt) {
            res = false;
            break;
        }
    }
    return res;
}

spi_device_handle_t SpiNum2SpiHandle(SpiName_t spi_num) {
    spi_device_handle_t spi_device_handle = 0;
    return spi_device_handle;
}

#ifdef SPI_DISCRET_WRITE
bool spi_wait_write_wait(SpiName_t spi_num, const uint8_t* const tx_array, uint16_t tx_array_len) {
    bool res = false;
    (void)spi_num;
    if(true == SpiInstance[spi_num].init_done) {
        LOG_DEBUG(SPI, "SPI:%u tx:%u", spi_num, tx_array_len);
        SpiInstance[spi_num].it_done = false;
        spi_transaction_t Transaction;
        uint16_t i = 0;
        for(i = 0; i < tx_array_len; i++) {
            LOG_DEBUG(SPI, "SPI write: i:%u", i);
            memset(&Transaction, 0, sizeof(Transaction)); // Zero out the transaction
            // Transaction.user = (void*)0; // D/C needs to be set to 1
            Transaction.flags = SPI_TRANS_USE_TXDATA | SPI_TRANS_MODE_OCT | SPI_DEVICE_HALFDUPLEX;
            Transaction.length = 8; // Len is in bytes, transaction length is in bits.
            // Transaction.tx_buffer = (tx_array+i);
            Transaction.rxlength = 0;
            Transaction.rx_buffer = NULL;
            Transaction.tx_data[0] = *(tx_array + i);
            if(SpiInstance[spi_num].spi_device_handle) {
                esp_err_t ret;
                ret = spi_device_transmit(SpiInstance[spi_num].spi_device_handle, &Transaction);
                // ret = spi_device_polling_transmit(SpiInstance[spi_num].spi_device_handle, &Transaction);
                if(ESP_OK == ret) {
                    res = true;
                    LOG_DEBUG(SPI, "SPItxOK");
                } else {
                    res = false;
                    LOG_ERROR(SPI, "SPItx");
                }
            }
        }
    } /*true==init_done*/
    return res;
}
#endif

#ifdef SPI_CON_WRITE
bool spi_wait_write_wait(SpiName_t spi_num, const uint8_t* const tx_array, uint16_t tx_array_len) {
    bool res = false;
    (void)spi_num;
    if(true == SpiInstance[spi_num].init_done) {
        LOG_DEBUG(SPI, "SPI:%u tx:%u", spi_num, tx_array_len);
        SpiInstance[spi_num].it_done = false;
        spi_transaction_t Transaction;

        memset(&Transaction, 0, sizeof(Transaction)); // Zero out the transaction
        // Transaction.user = (void*)0; // D/C needs to be set to 1
        Transaction.flags = SPI_TRANS_MODE_OCT;
        Transaction.length = 8 * tx_array_len; // Len is in bytes, transaction length is in bits.
        // Transaction.tx_buffer = (tx_array+i);
        Transaction.rxlength = 8 * tx_array_len;
        Transaction.tx_buffer = (void*)tx_array;
        Transaction.rx_buffer = (void*)NULL;
        // Transaction.tx_data[0] = *(tx_array + i);
        if(SpiInstance[spi_num].spi_device_handle) {
            esp_err_t ret;
            ret = spi_device_transmit(SpiInstance[spi_num].spi_device_handle, &Transaction);
            // ret = spi_device_polling_transmit(SpiInstance[spi_num].spi_device_handle, &Transaction);
            if(ESP_OK == ret) {
                res = true;
                LOG_DEBUG(SPI, "SPItxOK");
            } else {
                res = false;
                LOG_ERROR(SPI, "SPItx");
            }
        }

    } /*true==init_done*/
    return res;
}
#endif

#define WAIT_MUTEX 1000
bool spi_write(SpiName_t spi_num, const uint8_t* const tx_array, uint16_t tx_array_len) {
    bool res = false;
    if(NULL != SpiInstance[spi_num].mutex) {
        if(pdTRUE == xSemaphoreTake(SpiInstance[spi_num].mutex, WAIT_MUTEX)) {
            res = spi_wait_write_wait(spi_num, tx_array, tx_array_len);
            xSemaphoreGive(SpiInstance[spi_num].mutex);
        } else {
            LOG_ERROR(SPI, "MutexBusy");
        }
    } else {
        LOG_ERROR(SPI, "MutexInitError SPI:%u", spi_num);
    }
    // res = spi_wait_write(spi_num, tx_array, tx_array_len);
    return res;
}

#ifdef SPI_DISCRET_READ
static bool spi_wait_read_wait(SpiName_t spi_num, uint8_t* rx_array, uint16_t rx_array_len) {
    bool res = false;
    if(true == SpiInstance[spi_num].init_done) {
        spi_wait_tx_done(spi_num);
        SpiInstance[spi_num].it_done = false;
        spi_transaction_t Transaction;
        uint16_t i = 0;
        for(i = 0; i < rx_array_len; i++) {
            LOG_DEBUG(SPI, "SPI read: i:%u", i);
            memset(&Transaction, 0, sizeof(Transaction));
            Transaction.flags = SPI_TRANS_USE_RXDATA | SPI_TRANS_MODE_OCT | SPI_DEVICE_HALFDUPLEX;
            Transaction.length = 8;
            Transaction.rxlength = 8;
            Transaction.tx_buffer = NULL;
            Transaction.rx_buffer = rx_array;
            esp_err_t err;
            err = spi_device_transmit(SpiInstance[spi_num].spi_device_handle, &Transaction);
            // esp_err_t err = spi_device_polling_transmit(SpiInstance[spi_num].spi_device_handle, &Transaction);
            if(ESP_OK == err) {
                LOG_DEBUG(SPI, "SPIrxOK");
                SpiInstance[spi_num].rx_byte_cnt += 1;
                *(rx_array + i) = Transaction.rx_data[0];
                res = true;
            } else {
                res = false;
                LOG_ERROR(SPI, "SPI read error i:%u", i);
            }
        }
    }
    return res;
}
#endif

#ifdef SPI_CON_READ
static bool spi_wait_read_wait(SpiName_t spi_num, uint8_t* rx_array, uint16_t rx_array_len) {
    bool res = false;
    if(true == SpiInstance[spi_num].init_done) {
        spi_wait_tx_done(spi_num);
        SpiInstance[spi_num].it_done = false;
        spi_transaction_t Transaction;

        memset(&Transaction, 0, sizeof(Transaction));
        Transaction.flags = SPI_TRANS_MODE_OCT;
        Transaction.length = 8 * rx_array_len;
        Transaction.rxlength = 8 * rx_array_len;
        Transaction.tx_buffer = NULL;
        Transaction.rx_buffer = rx_array;
        esp_err_t err;
        err = spi_device_transmit(SpiInstance[spi_num].spi_device_handle, &Transaction);
        // esp_err_t err = spi_device_polling_transmit(SpiInstance[spi_num].spi_device_handle, &Transaction);
        if(ESP_OK == err) {
            LOG_DEBUG(SPI, "SPIrxOK");
            SpiInstance[spi_num].rx_byte_cnt += 1;
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}
#endif

bool spi_read(SpiName_t spi_num, uint8_t* rx_array, uint16_t rx_array_len) {
    bool res = false;
    if(SpiInstance[spi_num].mutex) {
        if(pdTRUE == xSemaphoreTake(SpiInstance[spi_num].mutex, WAIT_MUTEX)) {

            res = spi_wait_read_wait(spi_num, rx_array, rx_array_len);
            xSemaphoreGive(SpiInstance[spi_num].mutex);
        } else {
            LOG_ERROR(SPI, "MutexBusy");
        }
    } else {
        LOG_ERROR(SPI, "MutexInitError SPI:%u", spi_num);
    }
    return res;
}

uint32_t spi_get_clock(SpiName_t spi_num) {
    uint32_t spi_bit_rate = 0xFF;
    (void)spi_num;
    if(SpiInstance[spi_num].init_done) {
    }
    return spi_bit_rate;
}

uint8_t spi_get_phase(SpiName_t spi_num) {
    uint32_t phase = 9;
    (void)spi_num;
    if(SpiInstance[spi_num].init_done) {
        phase = 99;
    }
    return phase;
}

uint8_t spi_get_polarity(SpiName_t spi_num) {
    uint32_t polarity = 9;
    (void)spi_num;
    if(SpiInstance[spi_num].init_done) {
        polarity = 99;
    }
    return polarity;
}

uint8_t spi_get_data_size(SpiName_t spi_num) {
    uint32_t data_size = 0xFF;
    (void)spi_num;
    if(SpiInstance[spi_num].init_done) {
        data_size = 0;
    }
    return data_size;
}

uint8_t spi_get_transmit_int(SpiName_t spi_num) {
    uint8_t val = 0xFF;
    (void)spi_num;
    if(SpiInstance[spi_num].init_done) {
    }
    return val;
}

uint8_t spi_get_receive_int(SpiName_t spi_num) {
    uint8_t val = 0xFF;
    (void)spi_num;
    if(SpiInstance[spi_num].init_done) {
    }
    return val;
}

uint8_t spi_get_receive_timeout_interrupt(SpiName_t spi_num) {
    uint8_t val = 0xFF;
    (void)spi_num;
    if(SpiInstance[spi_num].init_done) {
    }
    return val;
}

uint8_t spi_get_receive_overrun_interrupt(SpiName_t spi_num) {
    uint8_t val = 0xFF;
    (void)spi_num;
    if(SpiInstance[spi_num].init_done) {
        val = 0xF0;
    }
    return val;
}
