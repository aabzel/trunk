#include "spi_drv.h"

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "bit_utils.h"
#include "clock.h"
#include "data_utils.h"
#include "debug_info.h"
#include "gpio_drv.h"
#ifdef HAS_SPI_DIAG
#include "spi_diag.h"
#endif
#include "gpio_diag.h"
#include "hal_nrfx_diag.h"
#include "log.h"
#include "spi_config.h"
#include "spi_isr.h"
#include "spi_nrf_types.h"
#include "sys_config.h"
#include "time_mcal.h"

#ifdef NRFX_SPIM_ENABLED
#include "nrfx_spim.h"
#endif /*NRFX_SPIM_ENABLED*/

const static NrfSpiInfo_t NrfSpiInfoLut[] = {
#if NRFX_CHECK(NRFX_SPIM0_ENABLED)
    {
        .num = 0,
        .valid = true,
        .spi_inst_id = NRFX_SPIM0_INST_IDX,
        .event_handler = nrfx_spim0_event_handler,
        .spi_ptr = NRF_SPIM0_S,
    },
#endif /*NRFX_SPIM0_ENABLED*/

#if NRFX_CHECK(NRFX_SPIM1_ENABLED)
    {.num = 1,
     .valid = true,
     .spi_inst_id = NRFX_SPIM1_INST_IDX,
     .event_handler = nrfx_spim1_event_handler,
     .spi_ptr = NRF_SPIM1_S},
#endif

#if NRFX_CHECK(NRFX_SPIM2_ENABLED)
    {.num = 2,
     .valid = true,
     .spi_inst_id = NRFX_SPIM2_INST_IDX,
     .event_handler = nrfx_spim2_event_handler,
     .spi_ptr = NRF_SPIM2_S},
#endif

#if NRFX_CHECK(NRFX_SPIM3_ENABLED)
    {.num = 3,
     .valid = true,
     .spi_inst_id = NRFX_SPIM3_INST_IDX,
     .event_handler = nrfx_spim3_event_handler,
     .spi_ptr = NRF_SPIM3_S},
#endif

#if NRFX_CHECK(NRFX_SPIM4_ENABLED)
    {.num = 4,
     .valid = true,
     .spi_inst_id = NRFX_SPIM4_INST_IDX,
     .event_handler = nrfx_spim4_event_handler,
     .spi_ptr = NRF_SPIM4_S}
#endif
};

static const NrfSpiInfo_t* SpiNum2SpimInfoNode(uint8_t num) {
    const NrfSpiInfo_t* SpimInfoNode = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(NrfSpiInfoLut);
    for(i = 0; i < cnt; i++) {
        if(NrfSpiInfoLut[i].valid) {
            if(NrfSpiInfoLut[i].num == num) {
                SpimInfoNode = &NrfSpiInfoLut[i];
                break;
            }
        }
    }
    return SpimInfoNode;
}

#ifdef HAS_SPI_ISR
static bool spi_interupts_enable(uint8_t num) {
    bool res = false;
    LOG_WARNING(SPI, "SPI%u ISR Enable", num);
    switch(num) {
#ifdef NRFX_SPIM0_ENABLED
    case 0:
        NVIC_SetPriority(SPIM0_SPIS0_TWIM0_TWIS0_UARTE0_IRQn, 7);
        NVIC_EnableIRQ(SPIM0_SPIS0_TWIM0_TWIS0_UARTE0_IRQn);
        break;
#endif
#ifdef NRFX_SPIM1_ENABLED
    case 1:
        NVIC_SetPriority(SPIM1_SPIS1_TWIM1_TWIS1_UARTE1_IRQn, 7);
        NVIC_EnableIRQ(SPIM1_SPIS1_TWIM1_TWIS1_UARTE1_IRQn);
        break;
#endif
#ifdef NRFX_SPIM2_ENABLED
    case 2:
        NVIC_SetPriority(SPIM2_SPIS2_TWIM2_TWIS2_UARTE2_IRQn, 7);
        NVIC_EnableIRQ(SPIM2_SPIS2_TWIM2_TWIS2_UARTE2_IRQn);
        break;
#endif /*NRF_SPIM2_NS_BASE*/

#ifdef NRFX_SPIM3_ENABLED
    case 3:
        NVIC_SetPriority(SPIM3_SPIS3_TWIM3_TWIS3_UARTE3_IRQn, 7);
        NVIC_EnableIRQ(SPIM3_SPIS3_TWIM3_TWIS3_UARTE3_IRQn);
        break;
#endif /*NRF_SPIM3_NS_BASE*/

#ifdef NRFX_SPIM4_ENABLED
    case 4:
        NVIC_SetPriority(SPIM4_IRQn, 7);
        NVIC_EnableIRQ(SPIM4_IRQn);
        break;
#endif /*NRF_SPIM4_NS_BASE*/
    default:
        res = false;
        break;
    }
    return res;
}
#endif /* HAS_SPI_ISR*/

static const SpiFreqInto_t SpiFreqInto[] = {
    {
        .bit_rate_hz = KHZ_2_HZ(125),
        .nrf_bit_rate = NRF_SPIM_FREQ_125K,
    },
    {
        .bit_rate_hz = KHZ_2_HZ(250),
        .nrf_bit_rate = NRF_SPIM_FREQ_250K,
    },
    {
        .bit_rate_hz = KHZ_2_HZ(500),
        .nrf_bit_rate = NRF_SPIM_FREQ_500K,
    },
    {
        .bit_rate_hz = MHZ_2_HZ(1),
        .nrf_bit_rate = NRF_SPIM_FREQ_1M,
    },
    {
        .bit_rate_hz = MHZ_2_HZ(2),
        .nrf_bit_rate = NRF_SPIM_FREQ_2M,
    },
    {
        .bit_rate_hz = MHZ_2_HZ(4),
        .nrf_bit_rate = NRF_SPIM_FREQ_4M,
    },
    {
        .bit_rate_hz = MHZ_2_HZ(8),
        .nrf_bit_rate = NRF_SPIM_FREQ_8M,
    },
    {
        .bit_rate_hz = MHZ_2_HZ(16),
        .nrf_bit_rate = NRF_SPIM_FREQ_16M,
    },
    {
        .bit_rate_hz = MHZ_2_HZ(32),
        .nrf_bit_rate = NRF_SPIM_FREQ_32M,
    },
};

static nrf_spim_frequency_t SpiBitRate2NrfBitRate(uint32_t des_bit_rate_hz) {
    nrf_spim_frequency_t final_nrf_bit_rate = NRF_SPIM_FREQ_125K;
    uint32_t final_bit_rate_hz = 0;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(SpiFreqInto);
    int32_t min_error = INT_MAX;
    for(i = 0; i < cnt; i++) {
        int32_t cur_error = abs(((int32_t)SpiFreqInto[i].bit_rate_hz) - ((int32_t)des_bit_rate_hz));
        if(cur_error < min_error) {
            min_error = cur_error;
            final_nrf_bit_rate = SpiFreqInto[i].nrf_bit_rate;
            final_bit_rate_hz = SpiFreqInto[i].bit_rate_hz;
        }
    }
    LOG_INFO(SPI, "Set SCL %u Hz", final_bit_rate_hz);
    return final_nrf_bit_rate;
}

static nrf_spim_bit_order_t SpiBitOrdef2NrfBitOrdef(BitOrder_t bit_order) {
    nrf_spim_bit_order_t nrf_bit_order = NRF_SPIM_BIT_ORDER_MSB_FIRST;
    switch((uint8_t)bit_order) {
    case SPI_MOST_SIGNIFICANT_BIT_FIRST:
        nrf_bit_order = NRF_SPIM_BIT_ORDER_MSB_FIRST;
        break;
    case SPI_LEAST_SIGNIFICANT_BIT_FIRST:
        nrf_bit_order = NRF_SPIM_BIT_ORDER_LSB_FIRST;
        break;

    default:
        nrf_bit_order = NRF_SPIM_BIT_ORDER_MSB_FIRST;
        break;
    }
    return nrf_bit_order;
}

static nrf_spim_mode_t SpiLatchRisingMode2NrfMode(SpiPhase_t phase) {
    nrf_spim_mode_t mode = NRF_SPIM_MODE_0;
    switch((uint8_t)phase) {
    case SPI_PHASE_0:
        mode = NRF_SPIM_MODE_0; ///< SCK active high, sample on leading edge of clock.
        break;
    case SPI_PHASE_1:
        mode = NRF_SPIM_MODE_2; ///< SCK active low, sample on leading edge of clock.
        break;
    }
    return mode;
};

static nrf_spim_mode_t SpiLatchFalingMode2NrfMode(SpiPhase_t phase) {
    nrf_spim_mode_t mode = NRF_SPIM_MODE_2;
    switch((uint8_t)phase) {
    case SPI_PHASE_0:
        mode = NRF_SPIM_MODE_1; ///< SCK active high, sample on trailing edge of clock.
        break;
    case SPI_PHASE_1:
        mode = NRF_SPIM_MODE_3; ///< SCK active low, sample on trailing edge of clock.
        break;
    }
    return mode;
};

static nrf_spim_mode_t SpiMode2NrfMode(SpiPolarity_t porarity, SpiPhase_t phase) {
    nrf_spim_mode_t mode = NRF_SPIM_MODE_0;
    switch((uint8_t)porarity) {
    case SPI_POLARITY_LATCH_RISING:
        mode = SpiLatchRisingMode2NrfMode(phase);
        break;
    case SPI_POLARITY_LATCH_FALING:
        mode = SpiLatchFalingMode2NrfMode(phase);
        break;
    }
    return mode;
};

static bool spi_gpio_init(const SpiConfig_t* const Config, nrfx_spim_config_t* const config_ptr) {
    bool res = false;
    LOG_INFO(SPI, "InitGPIO");
    if(Config) {
        if(config_ptr) {
            config_ptr->dcx_pin = 0xFF;
            if(config_ptr->use_hw_ss) {
                config_ptr->ss_pin = pad_assign((uint32_t)Config->PadCs.byte, "ChipSelect");
            } else {
                config_ptr->ss_pin = 0xFF;
            }
            config_ptr->sck_pin = pad_assign((uint32_t)Config->PadSck.byte, "SCK");
            config_ptr->mosi_pin = pad_assign((uint32_t)Config->PadMosi.byte, "MOSI");
            config_ptr->miso_pin = pad_assign((uint32_t)Config->PadMiso.byte, "MISO");
            res = true;
        }
    }
    return res;
}

static bool SpiChipSelect2NrfChipSelect(ChipSelect_t chip_select) {
    bool res = false;
    switch((uint8_t)chip_select) {
    case SPI_CHIP_SEL_HW:
        LOG_INFO(SPI, "HwChipSel");
        res = true;
        break;
    case SPI_CHIP_SEL_SW:
        LOG_INFO(SPI, "SwChipSel");
        LOG_INFO(SPI, "Init");
        res = false;
        break;
    }
    return res;
}

bool spi_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SPI, "%u Init", num);
    const SpiConfig_t* Config = SpiGetConfig(num);
    if(Config) {
        LOG_INFO(SPI, "SPI%u SpotConfig", num);
#ifdef HAS_SPI_DIAG
        SpiDiagConfig(Config);
#endif
        SpiHandle_t* Node = SpiGetNode(num);
        if(Node) {
            const NrfSpiInfo_t* NrfSpiInfo = SpiNum2SpimInfoNode(num);
            if(NrfSpiInfo) {
                nrfx_err_t ret = NRFX_ERROR_NULL;
                Node->config.use_hw_ss = SpiChipSelect2NrfChipSelect(Config->chip_select);
                Node->config.rx_delay = 2;
                Node->config.ss_duration = 100;
                Node->config.ss_active_high = false; /*TODO: check that in data sheet*/

                res = spi_gpio_init(Config, &(Node->config));

                Node->config.frequency = SpiBitRate2NrfBitRate(Config->bit_rate_hz);
                Node->config.mode = SpiMode2NrfMode(Config->polarity, Config->phase);
                Node->config.bit_order = SpiBitOrdef2NrfBitOrdef(Config->bit_order);
                Node->config.orc = 0xFF;
                Node->config.miso_pull = NRF_GPIO_PIN_NOPULL;
#ifdef HAS_SPI_ISR
                Node->config.irq_priority = Config->irq_priority;
                res = spi_interupts_enable(num);
#endif /*HAS_SPI_ISR*/

                Node->handle.p_reg = NrfSpiInfo->spi_ptr;
                Node->handle.drv_inst_idx = NrfSpiInfo->spi_inst_id;
#warning TODO Use local config
                /*TODO Use local config*/
                ret = nrfx_spim_init(&Node->handle, &Node->config, NrfSpiInfo->event_handler, NULL);
                if(NRFX_SUCCESS == ret) {
                    LOG_INFO(SPI, "SPI%u InitOk", num);
                    Node->init_done = true;
                    res = true;
                } else {
                    LOG_ERROR(SPI, "SPI%u InitError %u=%s", num, ret, HalStatus2Str(ret));
                    res = false;
                }
            } else {
                LOG_ERROR(SPI, "%u InstErr", num);
            }
        } else {
            LOG_ERROR(SPI, "SPI%u HandleErr", num);
            res = false;
        }
    } else {
        LOG_DEBUG(SPI, "SPI%u NoConfig", num);
        res = false;
    }
    return res;
}

bool spi_api_write(uint8_t num, const uint8_t* const tx_array, uint32_t tx_size) {
    bool res = false;
    LOG_DEBUG(SPI, "%u Write Len:%u", num, tx_size);
    /*TODO Add Raw data diag in debug log level*/
    log_level_t log_lev = log_level_get(SPI);
    if(LOG_LEVEL_DEBUG == log_lev) {
        print_hex(tx_array, tx_size);
    }

    SpiHandle_t* Node = SpiGetNode(num);
    if(Node && tx_array && tx_size) {
        Node->tx_int = false;

        nrfx_spim_xfer_desc_t xfer_desc;
        xfer_desc.p_tx_buffer = tx_array;
        xfer_desc.tx_length = tx_size;
        xfer_desc.p_rx_buffer = NULL;
        xfer_desc.rx_length = 0;

        nrfx_err_t ret = NRFX_ERROR_BUSY;
        ret = nrfx_spim_xfer(&Node->handle, &xfer_desc, 0);
        if(NRFX_SUCCESS == ret) {
            LOG_DEBUG(SPI, "TxOk");
            res = spi_wait_tx_ll(Node);
            Node->tx_byte_cnt += tx_size;
        } else {
            LOG_ERROR(SPI, "TxErr 0x%x %s", ret, HalStatus2Str(ret));
        }
    }
    return res;
}

bool spi_api_read(uint8_t num, uint8_t* rx_array, uint32_t rx_array_len) {
    bool res = false;
    LOG_DEBUG(SPI, "%u Read Len:%u", num, rx_array_len);
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node && rx_array && rx_array_len) {
        Node->rx_int = false;
        Node->it_done = false;

        nrfx_spim_xfer_desc_t xfer_desc = {0};
        xfer_desc.p_tx_buffer = NULL;
        xfer_desc.tx_length = 0;
        xfer_desc.p_rx_buffer = rx_array;
        xfer_desc.rx_length = rx_array_len;

        nrfx_err_t ret = NRFX_ERROR_BUSY;
        ret = nrfx_spim_xfer(&Node->handle, &xfer_desc, 0);
        if(NRFX_SUCCESS == ret) {
            LOG_DEBUG(SPI, "RxOk");
            res = spi_wait_rx_ll(Node);
            if(res) {
                Node->rx_byte_cnt += rx_array_len;
            }
            log_level_t log_level = log_level_get(SPI);
            if(LOG_LEVEL_DEBUG == log_level) {
                print_hex(rx_array, rx_array_len);
            }
        } else {
            LOG_ERROR(SPI, "RxErr %u %s", ret, HalStatus2Str(ret));
        }
    }
    return res;
}

bool spi_api_write_read(uint8_t num, const uint8_t* const tx_array, uint8_t* rx_array, uint32_t size) {
    bool res = false;
    LOG_PARN(SPI, "SPI%u WriteRead Len:%u", num, size);
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node && tx_array && rx_array && size) {
        Node->tx_int = false;
        Node->rx_int = false;
        nrfx_spim_xfer_desc_t xfer_desc = {0};

        xfer_desc.p_tx_buffer = tx_array;
        xfer_desc.tx_length = size;
        xfer_desc.p_rx_buffer = rx_array;
        xfer_desc.rx_length = size;

        nrfx_err_t ret = NRFX_ERROR_BUSY;
        ret = nrfx_spim_xfer(&Node->handle, &xfer_desc, 0);
        if(NRFX_SUCCESS == ret) {
            res = spi_wait_rxtx_ll(Node);
            if(res) {
                LOG_PARN(SPI, "TxRxOk");
            }
        } else {
            LOG_DEBUG(SPI, "TxRxErr %d=%s", ret, HalStatus2Str(ret));
        }
    }
    return res;
}

bool spi_set_clock(uint8_t num, uint32_t bit_rate_hz) {
    bool res = false;
    LOG_INFO(SPI, "%u SetClk %u Hz", num, bit_rate_hz);
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        Node->config.frequency = SpiBitRate2NrfBitRate(bit_rate_hz);
        if(Node->init_done) {
            nrfx_spim_uninit(&Node->handle);
            nrfx_err_t ret = NRFX_ERROR_NULL;
            const NrfSpiInfo_t* NrfSpiInfo = SpiNum2SpimInfoNode(num);
            if(NrfSpiInfo) {
                ret = nrfx_spim_init(&Node->handle, &Node->config, NrfSpiInfo->event_handler, NULL);
                if(NRFX_SUCCESS == ret) {
                    LOG_INFO(SPI, "%u ReInitOk", num);
                    res = true;
                } else {
                    LOG_DEBUG(SPI, "SPI%u ReInitError %u %s", num, ret, HalStatus2Str(ret));
                    res = false;
                }
            } else {
                LOG_ERROR(SPI, "%u InstErr", num);
            }
        }
    }
    return res;
}

uint8_t spi_get_data_size(uint8_t num) {
    uint8_t bits_per_tx = 0;
    /*TODO*/
    return bits_per_tx;
}

uint32_t spi_get_clock(uint8_t num) {
    uint32_t spi_bit_rate = 0;
    /*TODO*/
    return spi_bit_rate;
}

SpiPhase_t spi_get_phase(uint8_t num) {
    SpiPhase_t phase = SPI_PHASE_UNDEF;
    /*TODO*/
    return phase;
}

SpiPolarity_t spi_get_polarity(uint8_t num) {
    SpiPolarity_t polarity = SPI_POLARITY_UNDEF;
    /*TODO*/
    return polarity;
}
