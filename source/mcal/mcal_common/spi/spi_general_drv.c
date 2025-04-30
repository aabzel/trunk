#include "spi_drv.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "byte_utils.h"
#include "data_types.h"
#include "log.h"
#include "spi_config.h"
#include "spi_dep.h"
#include "spi_types.h"
#include "time_mcal.h"

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif /*HAS_SPI*/

SpiHandle_t* SpiGetNode(uint8_t num) {
    SpiHandle_t* SpiNode = NULL;
    uint32_t i = 0;
    uint32_t spi_cnt = spi_get_cnt();
    for(i = 0; i < spi_cnt; i++) {
        if(num == SpiInstance[i].num) {
            if(SpiInstance[i].valid) {
                SpiNode = &SpiInstance[i];
                break;
            }
        }
    }
    return SpiNode;
}

const SpiConfig_t* SpiGetConfig(uint8_t num) {
    const SpiConfig_t* SpiConfNode = NULL;
    uint32_t i = 0;
    uint32_t spi_cnt = spi_get_cnt();
    for(i = 0; i < spi_cnt; i++) {
        if(num == SpiConfig[i].num) {
            if(SpiConfig[i].valid) {
                SpiConfNode = &SpiConfig[i];
                break;
            }
        }
    }
    return SpiConfNode;
}

bool spi_is_init(uint8_t num) {
    bool res = false;
    SpiHandle_t* SpiNode = SpiGetNode(num);
    if(SpiNode) {
        res = SpiNode->init_done;
    }
    return res;
}

bool spi_is_allowed(uint8_t num) {
    bool res = false;
    SpiHandle_t* SpiNode = SpiGetNode(num);
    if(SpiNode) {
        const SpiConfig_t* SpiConfNode = SpiGetConfig(num);
        if(SpiConfNode) {
            res = true;
        }
    }

    return res;
}

bool spi_wait_tx_ll(SpiHandle_t* SpiNode) {
    bool res = true;
    if(SpiNode) {
        uint32_t start_ms = time_get_ms32();
        uint32_t cur_ms = start_ms;
        uint32_t diff_ms = 0;
        while(false == SpiNode->tx_int) {
            cur_ms = time_get_ms32();
            diff_ms = cur_ms - start_ms;
            if(SPI_TX_DONE_TIME_OUT_MS < diff_ms) {
                res = false;
                LOG_ERROR(SPI, "%u TxTimeOut", SpiNode->num);
                break;
            }
        }
    }
    return res;
}

bool spi_wait_rxtx_ll(SpiHandle_t* SpiNode) {
    bool res = true;
    if(SpiNode) {
        uint32_t start_ms = time_get_ms32();
        uint32_t cur_ms = start_ms;
        uint32_t diff_ms = 0;
        while(false == SpiNode->it_cnt) {
            cur_ms = time_get_ms32();
            diff_ms = cur_ms - start_ms;
            if(SPI_RX_DONE_TIME_OUT_MS < diff_ms) {
                res = false;
                LOG_ERROR(SPI, "%u RxTimeOut", SpiNode->num);
                break;
            }
        }
    }
    return res;
}

bool spi_wait_rx_ll(SpiHandle_t* SpiNode) {
    bool res = true;
    if(SpiNode) {
        uint32_t start_ms = time_get_ms32();
        uint32_t cur_ms = start_ms;
        uint32_t diff_ms = 0;
        while(false == SpiNode->rx_int) {
            cur_ms = time_get_ms32();
            diff_ms = cur_ms - start_ms;
            if(SPI_RX_DONE_TIME_OUT_MS < diff_ms) {
                res = false;
                LOG_ERROR(SPI, "%u RxTimeOut", SpiNode->num);
                break;
            }
        }
    }
    return res;
}

bool spi_wait_txrx_ll(SpiHandle_t* SpiNode) {
    bool res = true;
    if(SpiNode) {
        uint32_t start_ms = time_get_ms32();
        uint32_t cur_ms = start_ms;
        uint32_t diff_ms = 0;
        while(false == SpiNode->txrx_int) {
            cur_ms = time_get_ms32();
            diff_ms = cur_ms - start_ms;
            if(SPI_RX_DONE_TIME_OUT_MS < diff_ms) {
                res = false;
                LOG_ERROR(SPI, "%u TxRxTimeOut", SpiNode->num);
                break;
            }
        }
    }
    return res;
}

bool spi_write_byte(uint8_t num, const uint8_t tx_byte) {
    bool res = false;
    LOG_DEBUG(SPI, "%u Write Byte 0x%02x", num, tx_byte);
    res = spi_api_write(num, &tx_byte, 1);
    return res;
}

uint8_t spi_read_byte(uint8_t num) {
    LOG_PARN(SPI, "%u ReadByte", num);
    uint8_t rx_byte = 0x00;
    uint8_t tx_byte = 0xFF;
    bool res = spi_api_write_read(num, &tx_byte, &rx_byte, 1);
    if(res) {
        LOG_PARN(SPI, "%u Read Byte 0x%02x", num, rx_byte);
    } else {
        LOG_DEBUG(SPI, "SPI%u ReadByteErr", num);
    }
    return rx_byte;
}

uint16_t spi_read_word(uint8_t num) {
    LOG_PARN(SPI, "%u ReadWord", num);
    U16_bit_t un16Read = {
        .u16 = 0,
    };
    U16_bit_t un16Write = {
        .u16 = 0xFFFF,
    };

    bool res = spi_api_write_read(num, un16Write.u8, un16Read.u8, 2);
    if(res) {
        LOG_PARN(SPI, "%u Read Word 0x%04x", num, un16Read.u16);
    }
    return un16Read.u16;
}

bool spi_read_safe(uint8_t num, uint8_t* rx_array, uint32_t size) {
    bool res = false;
    LOG_PARN(SPI, "%u ReadByte %u Byte", num, size);
    if(rx_array) {
        if(size) {
            SpiHandle_t* SpiNode = SpiGetNode(num);
            if(SpiNode) {
                uint32_t i = 0;
                for(i = 0; i < size; i++) {
                    rx_array[i] = spi_read_byte(num);
                    res = true;
                }
            }
        }
    }
    return res;
}

bool spi_api_read_word(uint8_t num, uint16_t* word) {
    bool res = false;
    LOG_PARN(SPI, "%u ReadWord", num);
    res = spi_api_read(num, (uint8_t*)word, 2);
    if(false == res) {
        LOG_ERROR(SPI, "%u ReadWordErr", num);
    }
    return res;
}

bool spi_write_word(uint8_t num, const uint16_t word) {
    bool res = false;
    LOG_PARN(SPI, "%u WriteWord 0x%04x", num, word);
    U16_bit_t Un16;
    Un16.u16 = reverse_byte_order_uint16(word);
    res = spi_api_write(num, Un16.u8, 2);
    if(res) {

    } else {
        LOG_ERROR(SPI, "SPI%u WriteWord 0x%04x Err", num, word);
    }
    return res;
}

uint32_t spi_get_rate_conf(uint8_t num) {
    uint32_t bit_rate_hz = 1000000;
    const SpiConfig_t* ConfNode = SpiGetConfig(num);
    if(ConfNode) {
        bit_rate_hz = ConfNode->bit_rate_hz;
    }
    return bit_rate_hz;
}

bool spi_init(void) {
    bool res = true;
    LOG_WARNING(SPI, "Init..");
    uint8_t num = 0;
    uint32_t ok = 0;
    for(num = 0; num <= SPI_COUNT; num++) {
        res = spi_init_one(num);
        if(res) {
            LOG_INFO(SPI, "SPI%u InitOk", num);
            ok++;
        } else {
            LOG_DEBUG(SPI, "SPI%u InitErr", num);
        }
    }

    if(ok) {
        res = true;
        LOG_INFO(SPI, "Init %u SPIs", ok);
    } else {
        res = false;
    }
    return res;
}
