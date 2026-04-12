#include "spi_mcal.h"

#include "byte_utils.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"
#include "mcal_diag.h"
#include "std_includes.h"
#include "super_cycle.h"
#include "time_mcal.h"
#ifdef HAS_SPI_POLLING
#include "spi_polling.h"
#endif

#ifdef HAS_SPI_CUSTOM

#ifdef HAS_SPI_INTERRUPT
#include "spi_interrupt.h"
#endif

#endif

#ifdef HAS_SPI_DMA
#include "spi_dma.h"
#endif

COMPONENT_GET_NODE(Spi, spi)
COMPONENT_GET_CONFIG(Spi, spi)

_WEAK_FUN_
uint32_t spi_get_clock(uint8_t num) {
    uint32_t cloch_hz = 0;
    return cloch_hz;
}

_WEAK_FUN_
uint8_t spi_get_data_size(uint8_t num) {
    uint32_t data_size = 0;
    return data_size;
}

_WEAK_FUN_
SpiClkIdleLevel_t spi_get_phase(uint8_t num) {
    SpiClkIdleLevel_t phase = SPI_CLK_IDLE_LEVEL_UNDEF;
    return phase;
}

_WEAK_FUN_
SpiPolarity_t spi_get_polarity(uint8_t num) {
    SpiPolarity_t polarity = SPI_POLARITY_UNDEF;
    return polarity;
}

_WEAK_FUN_
bool spi_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SPI, "SPI%u", num);
    const SpiConfig_t* Config = SpiGetConfig(num);
    if(Config) {
        res = SpiIsValidConfig(Config);
        if(res) {
#ifdef HAS_SPI_DIAG
            LOG_WARNING(SPI, "%s", SpiConfigToStr(Config));
#endif
            SpiHandle_t* Node = SpiGetNode(num);
            if(Node) {
                Node->valid = true;
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(SPI, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(SPI, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(SPI, "ConfigErr %u", num);
    }
    return res;
}

_WEAK_FUN_
bool spi_init_custom(void) {
    bool res = false;
    LOG_INFO(SPI, "Version:%s", SPI_VERSION);
    return res;
}

_WEAK_FUN_
bool spi_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(SPI, "Proc %u", i);
    SpiHandle_t* Node = SpiGetNode(i);
    if(Node) {
        Node->spin++;
    }
    return res;
}

_WEAK_FUN_
bool spi_move_mode_set(const uint8_t num, const MoveMode_t move_mode) {
    bool res = false;
    LOG_INFO(SPI, "SPI%u,MoveMode:%s", num, McalMoveModeToStr(move_mode));
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        Node->move_mode = move_mode;
        res = true;
    }
    return res;
}

_WEAK_FUN_
bool spi_move_mode_get(const uint8_t num, MoveMode_t* const move_mode) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        *move_mode = Node->move_mode;
        LOG_INFO(SPI, "SPI%u,MoveMode:%s", num, McalMoveModeToStr(Node->move_mode));
        res = true;
    }
    return res;
}

/*
 Read array from MISO pin
 num - SPI transceiver serial number (0, 1, 2, ... )
 rxData - array into which the read data must be placed
 size - Number of bytes to read
 */
_WEAK_FUN_
bool spi_mcal_read(uint8_t num, uint8_t* const rxData, uint32_t size) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        Node->operation = INTERFACE_OPERATION_RECEPTION;
        Node->rx_done = false;
        const SpiConfig_t* Config = SpiGetConfig(num);
        if(Config) {
            res = false;
            /* res = spi_role_set(num, SPI_MODE_MASTER_RX);*/
            switch((uint32_t)Node->move_mode) {
            case MOVE_MODE_POLLING: {
#ifdef HAS_SPI_POLLING
                res = spi_read_polling(num, rxData, size);
#endif
            } break;

            case MOVE_MODE_INTERRUPT: {
#ifdef HAS_SPI_INTERRUPT
                res = spi_read_interrupt(num, rxData, size);
#endif
            } break;
            case MOVE_MODE_DMA: {
#ifdef HAS_SPI_DMA
                res = spi_read_dma(num, rxData, size);
#endif
            } break;
            default:
                res = false;
                break;
            }
        }
        Node->operation = INTERFACE_OPERATION_IDLE;
    }
    return res;
}

_WEAK_FUN_
bool spi_mcal_write_read(uint8_t num, const uint8_t* const tx_array, uint8_t* const rx_array, uint32_t size) {
    bool res = false;
    LOG_DEBUG(SPI, "SPI%u,WriteRead,Size:%u byte", num, size);
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        res = false;
        Node->tx_done = false;
        Node->operation = INTERFACE_OPERATION_RECEPTION_AND_TRANSMISSION;
        const SpiConfig_t* Config = SpiGetConfig(num);
        if(Config) {
            switch(Node->move_mode) {
            case MOVE_MODE_POLLING: {
#ifdef HAS_SPI_POLLING
                res = spi_write_read_polling(num, tx_array, rx_array, size);
#endif
            } break;

            case MOVE_MODE_INTERRUPT: {
#ifdef HAS_SPI_INTERRUPT
                res = spi_write_read_interrupt(num, tx_array, rx_array, size);
#endif
            } break;
            case MOVE_MODE_DMA: {
#ifdef HAS_SPI_DMA
                res = spi_write_read_dma(num, tx_array, rx_array, size);
#endif
            } break;
            default:
                res = false;
                break;
            }
        }
        Node->operation = INTERFACE_OPERATION_IDLE;
    }
    return res;
}

_WEAK_FUN_
bool spi_mcal_write(uint8_t num, const uint8_t* const array, uint32_t size) {
    bool res = false;
    LOG_DEBUG(SPI, "SPI%u,Write,Size:%u byte", num, size);
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        res = false;
        Node->operation = INTERFACE_OPERATION_SEND;
        Node->tx_done = false;
        const SpiConfig_t* Config = SpiGetConfig(num);
        if(Config) {
            switch(Node->move_mode) {
            case MOVE_MODE_POLLING: {
#ifdef HAS_SPI_POLL
                res = spi_write_polling(num, array, size);
#endif
            } break;

            case MOVE_MODE_INTERRUPT: {
#ifdef HAS_SPI_INTERRUPT
                res = spi_write_interrupt(num, array, size);
#endif
            } break;
            case MOVE_MODE_DMA: {
#ifdef HAS_SPI_DMA
                res = spi_write_dma(num, array, size);
#endif
            } break;
            default:
                res = false;
                break;
            }
        }
        Node->operation = INTERFACE_OPERATION_IDLE;
    }
    return res;
}

_WEAK_FUN_
bool spi_is_init(uint8_t num) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        res = Node->init;
    }
    return res;
}

#if 0
_WEAK_FUN_
bool spi_reg_map(uint8_t num) {
    bool res = false;
    return res;
}
_WEAK_FUN_
bool spi_is_allowed(uint8_t num) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        const SpiConfig_t* Config = SpiGetConfig(num);
        if(Config) {
            res = true;
        }
    }

    return res;
}
#endif

_WEAK_FUN_
bool spi_wait_tx_ll(SpiHandle_t* Node) {
    bool res = true;
    if(Node) {
        uint32_t start_ms = time_get_ms32();
        while(false == Node->tx_done) {
            // super_cycle_proc();
            res = time_wait_timeout(start_ms, SPI_RX_DONE_TIME_OUT_MS);
            if(!res) {
                res = false;
                LOG_ERROR(SPI, "SPI%u TxTimeOut", Node->num);
                break;
            }
        }
    }
    return res;
}

_WEAK_FUN_
bool spi_wait_rxtx_ll(SpiHandle_t* Node) {
    bool res = true;
    if(Node) {
        uint32_t start_ms = time_get_ms32();
        uint32_t cur_ms = start_ms;
        uint32_t diff_ms = 0;
        while(false == Node->it_done) {
            // super_cycle_proc();
            cur_ms = time_get_ms32();
            diff_ms = cur_ms - start_ms;
            if(SPI_RX_DONE_TIME_OUT_MS < diff_ms) {
                res = false;
                LOG_ERROR(SPI, "SPI%u RxTimeOut", Node->num);
                break;
            }
        }
    }
    return res;
}

_WEAK_FUN_
bool spi_init_common(const SpiConfig_t* const Config, SpiHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->bit_rate_hz = Config->bit_rate_hz;
            Node->bus_role = Config->bus_role;
            Node->bit_order = Config->bit_order;
            Node->tx_mode = Config->tx_mode;
            Node->chip_select = Config->chip_select;
            Node->irq_priority = Config->irq_priority;
            Node->polarity = Config->polarity;
            Node->phase = Config->phase;
            Node->frame_size = Config->frame_size;
            Node->PadCs = Config->PadCs;
            Node->move_mode = Config->move_mode;
            Node->name = Config->name;
            Node->num = Config->num;
            Node->interrupt_on = Config->interrupt_on;
            Node->PadSck = Config->PadSck;
            Node->PadMiso = Config->PadMiso;
            Node->PadMosi = Config->PadMosi;
            Node->GpioTxDebug = Config->GpioTxDebug;
            Node->GpioRxDebug = Config->GpioRxDebug;
#ifdef HAS_SPI_DMA
            Node->DmaTx = Config->DmaTx;
            Node->DmaRx = Config->DmaRx;
#endif
            res = true;
        }
    }
    return res;
}

_WEAK_FUN_
bool SpiIsValidConfig(const SpiConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;

        if(false == Config->interrupt_on) {
            LOG_WARNING(SPI, "SPI%u,InterruptOff");
        }

        ifn(Config->name) {
            res = false;
            LOG_ERROR(SPI, "SPI%u,NameErr", Config->num);
        }

        ifn(Config->bit_rate_hz) {
            res = false;
            LOG_ERROR(SPI, "SPI%u,RateErr", Config->num);
        }

        ifn(Config->frame_size) {
            res = false;
            LOG_ERROR(SPI, "SPI%u,FrameErr", Config->num);
        }

        ifn(Config->bus_role) {
            res = false;
            LOG_ERROR(SPI, "SPI%u,BusRoleErr", Config->num);
        }

        ifn(Config->tx_mode) {
            res = false;
            LOG_ERROR(SPI, "SPI%u,TxModeErr", Config->num);
        }

        ifn(Config->move_mode) {
            res = false;
            LOG_ERROR(SPI, "SPI%u,MoveModeErr", Config->num);
        }

        ifn(Config->bit_order) {
            res = false;
            LOG_ERROR(SPI, "SPI%u,BitOrderErr", Config->num);
        }

        ifn(Config->polarity) {
            res = false;
            LOG_ERROR(SPI, "SPI%u,PolarityErr", Config->num);
        }

        ifn(Config->phase) {
            res = false;
            LOG_ERROR(SPI, "SPI%u,PhaseErr", Config->num);
        }

        ifn(Config->chip_select) {
            res = false;
            LOG_ERROR(SPI, "SPI%u,ChipSelErr", Config->num);
        }
    }
    return res;
}

_WEAK_FUN_
bool spi_wait_rx_ll(SpiHandle_t* Node) {
    bool res = true;
    if(Node) {
        uint32_t start_ms = time_get_ms32();
        while(false == Node->rx_done) {
            // super_cycle_proc();
            res = time_wait_timeout(start_ms, SPI_RX_DONE_TIME_OUT_MS);
            if(!res) {
                LOG_ERROR(SPI, "SPI%u,RxTimeOut", Node->num);
                break;
            }
        }
    }
    return res;
}

_WEAK_FUN_
bool spi_wait_txrx_ll(SpiHandle_t* Node) {
    bool res = true;
    if(Node) {
        uint32_t start_ms = time_get_ms32();
        while(false == Node->txrx_done) {
            // super_cycle_proc();
            res = time_wait_timeout(start_ms, SPI_RX_DONE_TIME_OUT_MS);
            if(!res) {
                res = false;
                LOG_ERROR(SPI, "SPI%u xRxTimeOut", Node->num);
                break;
            }
        }
    }
    return res;
}

_WEAK_FUN_
bool spi_write_byte(uint8_t num, const uint8_t tx_byte) {
    bool res = false;
    LOG_DEBUG(SPI, "SPI%u,Write Byte 0x%02x", num, tx_byte);
    res = spi_mcal_write(num, &tx_byte, 1);
    return res;
}

_WEAK_FUN_
/*For SD cards*/
uint8_t spi_read_byte(uint8_t num) {
    LOG_PARN(SPI, "SPI%u,ReadByte", num);
    uint8_t rx_byte = 0x00;
    SpiConfig_t* Config = SpiGetConfig(num);
    if(Config) {
        uint8_t tx_byte = 0xFF;
        bool res = spi_mcal_write_read(num, &tx_byte, &rx_byte, 1);
        if(res) {
            LOG_PARN(SPI, "SPI%u,Read Byte 0x%02x", num, rx_byte);
        } else {
            LOG_ERROR(SPI, "SPI%u,ReadByte,Err", num);
        }
    }
    return rx_byte;
}

bool spi_read_until_pattern(const uint8_t num, const uint8_t exp_rx, const uint32_t try) {
    LOG_PARN(SPI, "SPI%u,ReadUntil,Pattern:0x%02x,Try:%u", num, exp_rx, try);
    bool res = false;
    uint32_t i = 0;
    for(i = 0; i < try; i++) {
        uint8_t rx_byte = spi_read_byte(num);
        LOG_PARN(SPI, "%02x,", rx_byte);
        if(exp_rx == rx_byte) {
            res = true;
            break;
        }
    }
    LOG_DEBUG(SPI, "SPI%u,ReadUntil,Pattern:0x%02x,Try:%u/%u", num, exp_rx, i, try);
    return res;
}

_WEAK_FUN_
uint16_t spi_read_word(uint8_t num) {
    LOG_PARN(SPI, "SPI%u,ReadWord", num);
    U16_bit_t un16Read = {
        .u16 = 0,
    };
    U16_bit_t un16Write = {
        .u16 = 0xFFFF,
    };

    bool res = spi_mcal_write_read(num, un16Write.u8, un16Read.u8, 2);
    if(res) {
        LOG_PARN(SPI, "SPI%u,Read Word 0x%04x", num, un16Read.u16);
    }
    return un16Read.u16;
}

_WEAK_FUN_
bool spi_read_safe(uint8_t num, uint8_t* rx_array, uint32_t size) {
    bool res = false;
    LOG_PARN(SPI, "SPI%u,ReadArray,To:0x%p,Size:%u Byte", num, rx_array, size);
    if(rx_array) {
        if(size) {
            SpiHandle_t* Node = SpiGetNode(num);
            if(Node) {
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

_WEAK_FUN_
bool spi_mcal_read_word(uint8_t num, uint16_t* word) {
    bool res = false;
    LOG_PARN(SPI, "SPI%u,ReadWord", num);
    res = spi_mcal_read(num, (uint8_t*)word, 2);
    if(false == res) {
        LOG_ERROR(SPI, "SPI%u ReadWordErr", num);
    }
    return res;
}

_WEAK_FUN_
bool spi_write_word(uint8_t num, const uint16_t word) {
    bool res = false;
    LOG_PARN(SPI, "SPI%u,WriteWord,0x%04x", num, word);
    U16_bit_t Un16;
    Un16.u16 = reverse_byte_order_uint16(word);
    res = spi_mcal_write(num, Un16.u8, 2);
    if(res) {
        LOG_PARN(SPI, "SPI%u,WriteWord,0x%04x Ok", num, word);
    } else {
        LOG_ERROR(SPI, "SPI%u,WriteWord,0x%04x Err", num, word);
    }
    return res;
}

_WEAK_FUN_
bool spi_write_dword(uint8_t num, const uint32_t dword) {
    bool res = false;
    LOG_PARN(SPI, "SPI%u,WriteDword,0x%08x", num, dword);
    U32_bit_t Un32;
    Un32.u32 = reverse_byte_order_uint32(dword);
    res = spi_mcal_write(num, Un32.u8, 4);
    if(res) {
        LOG_PARN(SPI, "SPI%u,WriteDword,0x%08x Ok", num, dword);
    } else {
        LOG_ERROR(SPI, "SPI%u,WriteDword,0x%08x Err", num, dword);
    }
    return res;
}

_WEAK_FUN_
uint32_t spi_get_rate_conf(uint8_t num) {
    uint32_t bit_rate_hz = 1000000;
    const SpiConfig_t* Config = SpiGetConfig(num);
    if(Config) {
        bit_rate_hz = Config->bit_rate_hz;
    }
    return bit_rate_hz;
}

COMPONENT_INIT_PATTERT_CNT(SPI, SPI, spi, SPI_COUNT)
COMPONENT_PROC_PATTERT_CNT(SPI, SPI, spi, SPI_COUNT)
