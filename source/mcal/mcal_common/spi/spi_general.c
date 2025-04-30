#include "spi_mcal.h"

#include <stdio.h>
#include <string.h>

#include "std_includes.h"
#include "byte_utils.h"
#include "code_generator.h"
#include "data_types.h"
#include "log.h"
#include "time_mcal.h"

COMPONENT_GET_NODE(Spi, spi)
COMPONENT_GET_CONFIG(Spi, spi)

__attribute__((weak)) bool spi_init_one(uint8_t num){
    bool res = false;
    return res;
}

__attribute__((weak)) bool spi_init_custom(void){
    bool res = false;
    return res;
}

__attribute__((weak)) bool spi_proc_one(uint8_t num){
    bool res = false;
    return res;
}

__attribute__((weak)) bool spi_api_read(uint8_t num, uint8_t* const rx_array, uint32_t array_len){
    bool res = false;
    return res;
}

__attribute__((weak)) bool spi_api_write(uint8_t num, const uint8_t* const tx_array, uint32_t tx_array_len){
    bool res = false;
    return res;
}

__attribute__((weak)) bool spi_api_write_read(uint8_t num, const uint8_t* const tx_array, uint8_t* rx_array, uint32_t size){
    bool res = false;
    return res;
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
        while(false == SpiNode->tx_done) {
            cur_ms = time_get_ms32();
            diff_ms = cur_ms - start_ms;
            if(SPI_TX_DONE_TIME_OUT_MS < diff_ms) {
                res = false;
                LOG_ERROR(SPI, "SPI%u TxTimeOut", SpiNode->num);
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
                LOG_ERROR(SPI, "SPI%u RxTimeOut", SpiNode->num);
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
        while(false == SpiNode->rx_done) {
            cur_ms = time_get_ms32();
            diff_ms = cur_ms - start_ms;
            if(SPI_RX_DONE_TIME_OUT_MS < diff_ms) {
                res = false;
                LOG_ERROR(SPI, "SPI%u RxTimeOut", SpiNode->num);
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
        while(false == SpiNode->txrx_done) {
            cur_ms = time_get_ms32();
            diff_ms = cur_ms - start_ms;
            if(SPI_RX_DONE_TIME_OUT_MS < diff_ms) {
                res = false;
                LOG_ERROR(SPI, "SPI%u TxRxTimeOut", SpiNode->num);
                break;
            }
        }
    }
    return res;
}

bool spi_write_byte(uint8_t num, const uint8_t tx_byte) {
    bool res = false;
    LOG_DEBUG(SPI, "SPI%u Write Byte 0x%02x", num, tx_byte);
    res = spi_api_write(num, &tx_byte, 1);
    return res;
}

uint8_t spi_read_byte(uint8_t num) {
    LOG_PARN(SPI, "SPI%u ReadByte", num);
    uint8_t rx_byte = 0x00;
    uint8_t tx_byte = 0xFF;
    bool res = spi_api_write_read(num, &tx_byte, &rx_byte, 1);
    if(res) {
        LOG_PARN(SPI, "SPI%u Read Byte 0x%02x", num, rx_byte);
    } else {
        LOG_DEBUG(SPI, "SPI%u ReadByteErr", num);
    }
    return rx_byte;
}

uint16_t spi_read_word(uint8_t num) {
    LOG_PARN(SPI, "SPI%u ReadWord", num);
    U16_bit_t un16Read = {
        .u16 = 0,
    };
    U16_bit_t un16Write = {
        .u16 = 0xFFFF,
    };

    bool res = spi_api_write_read(num, un16Write.u8, un16Read.u8, 2);
    if(res) {
        LOG_PARN(SPI, "SPI%u Read Word 0x%04x", num, un16Read.u16);
    }
    return un16Read.u16;
}

bool spi_read_safe(uint8_t num, uint8_t* rx_array, uint32_t size) {
    bool res = false;
    LOG_PARN(SPI, "SPI%u ReadByte %u Byte", num, size);
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
    LOG_PARN(SPI, "SPI%u ReadWord", num);
    res = spi_api_read(num, (uint8_t*)word, 2);
    if(false == res) {
        LOG_ERROR(SPI, "SPI%u ReadWordErr", num);
    }
    return res;
}

bool spi_write_word(uint8_t num, const uint16_t word) {
    bool res = false;
    LOG_PARN(SPI, "SPI%u WriteWord 0x%04x", num, word);
    U16_bit_t Un16;
    Un16.u16 = reverse_byte_order_uint16(word);
    res = spi_api_write(num, Un16.u8, 2);
    if(res) {
        LOG_PARN(SPI, "SPI%u WriteWord 0x%04x Ok", num, word);
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

COMPONENT_INIT_PATTERT_CNT(SPI, SPI, spi, SPI_COUNT)
COMPONENT_PROC_PATTERT_CNT(SPI, SPI, spi, SPI_COUNT)
