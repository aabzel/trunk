#include "i2c_drv.h"

#include "debug_info.h"
#include "hal_nrfx_diag.h"
#include "i2c_isr.h"
#include "i2c_nrf_types.h"
#include "i2c_types.h"
#include "nrfx_twim.h"
#include <stdbool.h>
#ifdef HAS_GPIO_DIAG
#include "gpio_diag.h"
#endif
#include "hal_nrfx_diag.h"
#ifdef HAS_LOG
#include "log.h"
#endif
#include "i2c_database.h"
#ifdef HAS_TIME
#include "time_mcal.h"
#endif

static bool I2cWaitTxDone(I2cHandle_t* Node, uint32_t init_tx_cnt) {
    bool res = false;
    if(Node) {
        res = true;
#ifdef HAS_TIME
        uint32_t start_ms = time_get_ms32();
        uint32_t cur_ms = time_get_ms32();
#endif
        uint32_t diff_ms = 0;
        while(Node->tx_cnt <= init_tx_cnt) {
#ifdef HAS_TIME
            cur_ms = time_get_ms32();
            diff_ms = cur_ms - start_ms;
#endif
            if(I2C_SEND_TIME_OUT_MS < diff_ms) {
                LOG_ERROR(I2C, "I2C%u TxTimeOut Wait %u Limit:%u ms", Node->num, diff_ms, I2C_SEND_TIME_OUT_MS);
                res = false;
                break;
            }
        }
    }
    return res;
}

static bool I2cWaitRxDone(I2cHandle_t* Node, uint32_t init_rx_cnt) {
    bool res = false;
    if(Node) {
        res = true;
#ifdef HAS_TIME
        uint32_t start_ms = time_get_ms32();
        uint32_t cur_ms = time_get_ms32();
#endif
        uint32_t diff_ms = 0;
        while(Node->rx_cnt <= init_rx_cnt) {
#ifdef HAS_TIME
            cur_ms = time_get_ms32();
            diff_ms = cur_ms - start_ms;
#endif
            if(I2C_READ_TIME_OUT_MS < diff_ms) {
                res = false;
#ifdef HAS_LOG
                LOG_DEBUG(I2C, "RxTout %u", Node->num);
#endif
                break;
            }
        }
    }
    return res;
}

static NRF_TWIM_Type* I2cNum2Ptr(uint8_t num) {
    NRF_TWIM_Type* peripheral = NULL;
    switch(num) {
    case 0:
        peripheral = NRF_TWIM0_S /*NRF_TWIM0_NS*/;
        break;
    case 1:
        peripheral = NRF_TWIM1_S /*NRF_TWIM1_NS*/;
        break;
    case 2:
        peripheral = NRF_TWIM2_S /*NRF_TWIM2_NS*/;
        break;
    case 3:
        peripheral = NRF_TWIM3_S /*NRF_TWIM3_NS*/;
        break;
    default:
        peripheral = NULL;
        break;
    }
    return peripheral;
}

static const I2cAvailRates_t I2cAvailRates[] = {
    {
        .nrf_rate = NRF_TWIM_FREQ_100K,
        .rate_hz = 100000,
    },
    {
        .nrf_rate = NRF_TWIM_FREQ_250K,
        .rate_hz = 250000,
    },
    {
        .nrf_rate = NRF_TWIM_FREQ_400K,
        .rate_hz = 400000,
    },
    //{.nrf_rate=NRF_TWIM_FREQ_1000K, .rate_hz=1000000}
};

static nrf_twim_frequency_t I2cRate2NrfRate(uint32_t rate_hz) {
    nrf_twim_frequency_t nrf_twim_frequency = NRF_TWIM_FREQ_100K;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(I2cAvailRates); i++) {
        if(I2cAvailRates[i].rate_hz == rate_hz) {
            nrf_twim_frequency = I2cAvailRates[i].nrf_rate;
            break;
        }
    }
    return nrf_twim_frequency;
}

bool i2c_init_ll(uint8_t num) {
    bool res = true;
#ifdef HAS_LOG
    LOG_INFO(I2C, "I2C%u Init ", num);
#endif
    I2cHandle_t* Node = I2cGetNode(num);

    const I2cConfig_t* Config = I2cGetConfig(num);
    if(Config) {
#ifdef HAS_LOG
        LOG_INFO(I2C, "I2C%u SpotConfig", num);
#endif
        res = true;
    } else {
#ifdef HAS_LOG
        LOG_ERROR(I2C, "I2C%u ConfigErr", num);
#endif
        res = false;
    }

    if(Node && res) {
        res = false;
        NRF_TWIM_Type* InstNode = I2cNum2Ptr(num);
        if(InstNode) {
            nrfx_twim_config_t twim_config = {0};
            nrfx_err_t ret = NRFX_ERROR_NULL;
#ifdef HAS_GPIO_DIAG
            LOG_INFO(I2C, "I2C%u StartPreInit.. SDA:%s", num, GpioPad2Str(Config->PadSda.byte));
            LOG_INFO(I2C, "I2C%u StartPreInit.. SCL:%s", num, GpioPad2Str(Config->PadScl.byte));
#endif
            twim_config.sda = (uint32_t)Config->PadSda.byte;
            twim_config.scl = (uint32_t)Config->PadScl.byte;
#ifdef HAS_LOG
            LOG_INFO(I2C, "I2C%u StartPostInit.. SDA:%u SCL:%u", num, twim_config.sda, twim_config.scl);
#endif

            twim_config.frequency = I2cRate2NrfRate(Config->clock_speed); ///< TWIM frequency.
            twim_config.interrupt_priority = 4;                           ///< Interrupt priority.
            twim_config.hold_bus_uninit = true; ///< Hold pull up state on GPIO pins after uninit.

            nrfx_twim_evt_handler_t IsrHandler = I2cNum2IsrHandler(num);
            ret = nrfx_twim_init(&Node->i2c_h, &twim_config, IsrHandler, NULL);
            if(NRFX_SUCCESS == ret) {
#ifdef HAS_LOG
                LOG_INFO(I2C, "I2C%u InitOk ", num);
#endif
                nrfx_twim_enable(&Node->i2c_h);
                res = true;
#ifdef HAS_I2C_SCAN_IN_INIT
                res = i2c_scan(num);
#endif /*HAS_I2C_SCAN_IN_INIT*/
            } else {
#ifdef HAS_LOG
                LOG_ERROR(I2C, "I2C%u InitError %u %s", num, ret, HalStatus2Str(ret));
#endif
                res = false;
            }
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(I2C, "I2C%u HandleErr", num);
#endif
        res = false;
    }

    return res;
}

bool i2c_init(void) {
    bool res = false;
    uint8_t cnt = 0;
#ifdef HAS_LOG
    LOG_INFO(I2C, "Init");
#endif
#ifdef HAS_I2C0
    cnt += (uint8_t)i2c_init_ll(0);
#endif /*HAS_I2C0*/

#ifdef HAS_I2C1
    cnt += (uint8_t)i2c_init_ll(1);
#endif /*HAS_I2C1*/

#ifdef HAS_I2C2
    cnt += (uint8_t)i2c_init_ll(2);
#endif /*HAS_I2C2*/

#ifdef HAS_I2C3
    cnt += (uint8_t)i2c_init_ll(3);
#endif /*HAS_I2C3*/

#ifdef HAS_I2C4
    cnt += (uint8_t)i2c_init_ll(4);
#endif /*HAS_I2C4*/
    if(cnt) {
        res = true;
#ifdef HAS_LOG
        LOG_INFO(I2C, "Init %u I2Cs", cnt);
#endif
    } else {
#ifdef HAS_LOG
        LOG_ERROR(I2C, "NoInit");
#endif
        res = false;
    }
    return res;
}

bool i2c_write_wait(uint8_t num, uint8_t chip_addr, const uint8_t* const data, size_t size) {
    bool res = false;
    /*NRF I2C core independently shifts bits to the right*/
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        res = nrfx_twim_is_busy(&Node->i2c_h);
        if(false == res) {
            Node->xfer.type = NRFX_TWIM_XFER_TX;
            Node->xfer.address = chip_addr;
            Node->xfer.primary_length = size;
            Node->xfer.p_primary_buf = data;
            Node->xfer.secondary_length = 0;
            Node->xfer.p_secondary_buf = NULL;

            Node->tx_int = false;

            uint32_t init_tx_cnt = Node->tx_cnt;
            nrfx_err_t ret = nrfx_twim_xfer(&Node->i2c_h, &Node->xfer, 0); // NRFX_TWIM_FLAG_TX_POSTINC);
            if(NRFX_SUCCESS == ret) {
                res = true;
                res = I2cWaitTxDone(Node, init_tx_cnt);
                LOG_DEBUG(I2C, "I2C%u Write Chip:0x%x Ok %u Byte", num, chip_addr, size);
            } else {
                LOG_ERROR(I2C, "I2C%u Write Chip:0x%x Error 0x%x=%s", num, chip_addr, ret, HalStatus2Str(ret));
            }
        } else {
            LOG_ERROR(I2C, "I2C%u BusyInWrite", num);
            res = false;
        }
    }
    return res;
}

bool i2c_api_write(uint8_t num, uint8_t chip_addr, const uint8_t* const data, size_t size) {
    LOG_DEBUG(I2C, "I2C%u WriteChip 0x%x Size %u Byte", num, chip_addr, size);
    bool res = i2c_write_wait(num, chip_addr, data, size);
    return res;
}

bool i2c_api_read(uint8_t num, uint8_t chip_addr, uint8_t* data, uint32_t size) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        res = nrfx_twim_is_busy(&Node->i2c_h);
        if(false == res) {
            res = false;
            Node->xfer.type = NRFX_TWIM_XFER_RX;
            Node->xfer.address = chip_addr;
            Node->xfer.primary_length = size;
            Node->xfer.p_primary_buf = data;
            Node->xfer.secondary_length = 0;
            Node->xfer.p_secondary_buf = NULL;

            Node->rx_int = false;

            uint32_t init_rx_cnt = Node->rx_cnt;
            nrfx_err_t ret =
                nrfx_twim_xfer(&Node->i2c_h, &Node->xfer, NRFX_TWIM_FLAG_RX_POSTINC); // NRFX_TWIM_FLAG_TX_NO_STOP
            if(NRFX_SUCCESS == ret) {
                res = true;
                res = I2cWaitRxDone(Node, init_rx_cnt);
                LOG_DEBUG(I2C, "%u ReadOk %u Byte", num, size);
            } else {
                LOG_ERROR(I2C, "%u ReadError %u %s", num, ret, HalStatus2Str(ret));
                res = false;
            }
        } else {
            LOG_ERROR(I2C, "%u BusyRead", num);
            res = false;
        }
    }
    return res;
}

bool i2c_send_signal(uint8_t num, I2cSignal_t signal) {
    bool res = false;
#ifdef HAS_LOG
    LOG_ERROR(I2C, "Unimplemented");
#endif
    return res;
}

bool i2c_check_addr(uint8_t num, uint8_t chip_addr) {
    bool res = false;

    LOG_DEBUG(I2C, "%u Check ChipAddr: 0x%02x", num, chip_addr);

#if 0
    static uint8_t array[2]={0,0};
    res= i2c_read(num, chip_addr, array, 1);
    if(res){
        if(0<array[0] ){
              res = true;
          }else{
              res = false;
          }
    }
#endif
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        res = false;
        res = nrfx_twim_is_busy(&Node->i2c_h);
        if(false == res) {
            uint8_t array[1] = {0};
            Node->xfer.type = NRFX_TWIM_XFER_RX;
            Node->xfer.address = chip_addr;
            Node->xfer.primary_length = 1;
            Node->xfer.p_primary_buf = array;
            Node->xfer.secondary_length = 0;
            Node->xfer.p_secondary_buf = NULL;

            Node->rx_int = false;

            uint32_t init_tx_cnt = Node->tx_cnt;
            uint32_t init_error_cnt = Node->error_cnt;
            uint32_t init_rx_cnt = Node->rx_cnt;
            uint32_t init_errNack_cnt = Node->error_nack_cnt;
            nrfx_err_t ret = nrfx_twim_xfer(&Node->i2c_h, &Node->xfer, 0); // NRFX_TWI_FLAG_NO_XFER_EVT_HANDLER
            if(NRFX_SUCCESS == ret) {
                res = I2cWaitRxDone(Node, init_rx_cnt);
                if(res) {
                    res = false;
                    if(init_errNack_cnt == Node->error_nack_cnt) {
                        if(init_error_cnt == Node->error_cnt) {
                            if(init_tx_cnt == Node->tx_cnt) {
#ifdef HAS_LOG
                                LOG_DEBUG(I2C, "%u Addr 0x%02x Exist Data:0x%02x", num, chip_addr, array[0]);
#endif
                                res = true;
                            }
                        }
                    }
                }
            } else {
                /*No Need */
#ifdef HAS_LOG
                LOG_DEBUG(I2C, "%u Addr 0x%x Lack", num, chip_addr);
#endif
                res = false;
            }
        } else {
#ifdef HAS_LOG
            LOG_ERROR(I2C, "%u Busy", num);
#endif
            res = false;
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(I2C, "%u NodeErr", num);
#endif
        res = false;
    }
    return res;
}

// Old
bool i2c_api_read_byte_old(uint8_t num, uint8_t chip_addr, uint8_t reg_addr, uint8_t* reg_val) {
    bool res = false;
    res = i2c_api_write(num, chip_addr, &reg_addr, 1);
    if(res) {
        res = i2c_api_read(num, chip_addr, reg_val, 1);
        if(false == res) {
            LOG_ERROR(I2C, "%u ReadRegErr Chip 0x%02x Reg:0x%02X", num, chip_addr, reg_addr);
        } else {
            LOG_DEBUG(I2C, "%u ReadRegOk Chip 0x%02x Reg:0x%02X RegVal:0x%02X", num, chip_addr, reg_addr, *reg_val);
        }
    } else {
        LOG_ERROR(I2C, "%u SetRegAddrErr ChipAddr:0x%02x Reg:0x%02X", num, chip_addr, reg_addr);
    }
    return res;
}

bool i2c_api_read_mem(uint8_t num, uint8_t chip_addr, uint8_t* const addr, size_t addr_size, uint8_t* const data,
                      size_t size) {
    bool res = false;
    LOG_DEBUG(I2C, "I2C%u ReadMem", num);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        res = nrfx_twim_is_busy(&Node->i2c_h);
        if(false == res) {
            Node->xfer.type = NRFX_TWIM_XFER_TXRX;
            Node->xfer.address = chip_addr;

            Node->xfer.p_primary_buf = (uint8_t*)addr;
            Node->xfer.primary_length = addr_size;

            Node->xfer.secondary_length = size;
            Node->xfer.p_secondary_buf = (uint8_t*)data;
            Node->tx_int = false;
            Node->rx_int = false;
            uint32_t init_tx_cnt = Node->tx_cnt;
            nrfx_err_t ret = nrfx_twim_xfer(&Node->i2c_h, &Node->xfer, 0); // NRFX_TWIM_FLAG_TX_POSTINC);
            if(NRFX_SUCCESS == ret) {
                res = true;
                res = I2cWaitTxDone(Node, init_tx_cnt);
                LOG_DEBUG(I2C, "%u ReadMemOk %u Byte", num, 1);
            } else {
                LOG_ERROR(I2C, "%u ReadError 0x%x %s", num, ret, HalStatus2Str(ret));
            }
        } else {
            LOG_ERROR(I2C, "I2C%u BusyInRead", num);
            res = false;
        }
    }
    return res;
}

// Max9860
bool i2c_api_read_byte(uint8_t num, uint8_t chip_addr, uint8_t reg_addr, uint8_t* const reg_val) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        res = nrfx_twim_is_busy(&Node->i2c_h);
        if(false == res) {
            Node->xfer.type = NRFX_TWIM_XFER_TXRX;
            Node->xfer.address = chip_addr;

            Node->xfer.primary_length = 1;
            Node->xfer.p_primary_buf = &reg_addr;

            Node->xfer.secondary_length = 1;
            Node->xfer.p_secondary_buf = reg_val;
            Node->tx_int = false;
            Node->rx_int = false;

            uint32_t init_tx_cnt = Node->tx_cnt;
            nrfx_err_t ret = nrfx_twim_xfer(&Node->i2c_h, &Node->xfer, 0); // NRFX_TWIM_FLAG_TX_POSTINC);
            if(NRFX_SUCCESS == ret) {
                res = true;
                res = I2cWaitTxDone(Node, init_tx_cnt);
                LOG_DEBUG(I2C, "%u ReadRegOk %u Byte", num, 1);
            } else {
                LOG_ERROR(I2C, "%u ReadRegError 0x%x %s", num, ret, HalStatus2Str(ret));
            }
        } else {
            LOG_ERROR(I2C, "I2C%u BusyInWrite", num);
            res = false;
        }
    }
    return res;
}

bool i2c_api_write_mem(uint8_t num, uint8_t chip_addr, uint16_t address, const uint8_t* const data, size_t size) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        res = nrfx_twim_is_busy(&Node->i2c_h);
        if(false == res) {
            Node->xfer.type = NRFX_TWIM_XFER_TX;
            Node->xfer.address = chip_addr;
            Node->xfer.p_primary_buf = (uint8_t*)&address;
            Node->xfer.primary_length = 2;
            Node->xfer.secondary_length = size;
            Node->xfer.p_secondary_buf = (uint8_t*)data;

            Node->tx_int = false;

            uint32_t init_tx_cnt = Node->tx_cnt;
            nrfx_err_t ret = nrfx_twim_xfer(&Node->i2c_h, &Node->xfer, 0); // NRFX_TWIM_FLAG_TX_POSTINC);
            if(NRFX_SUCCESS == ret) {
                res = true;
                res = I2cWaitTxDone(Node, init_tx_cnt);
                LOG_DEBUG(I2C, "%u WriteMemOk %u Byte", num, 1);
            } else {
                LOG_ERROR(I2C, "%u WriteMemError 0x%x %s", num, ret, HalStatus2Str(ret));
            }
        } else {
            LOG_ERROR(I2C, "I2C%u BusyInWrite", num);
            res = false;
        }
    }
    return res;
}

bool i2c_api_write_reg(uint8_t num, uint8_t chip_addr, uint8_t reg_addr, uint8_t reg_val) {
    bool res = false;
    LOG_DEBUG(I2C, "%u WriteReg ChipID 0x%02x RegAddr:0x%02X Val:0x%02X", num, chip_addr, reg_addr, reg_val);
    uint8_t frame[2] = {reg_addr, reg_val};
    res = i2c_api_write(num, chip_addr, &frame[0], 2);
    if(false == res) {
        // i2c_init_ll(  num); /*reinit cause  InitError 195887109 InvalState*/
    }
    return res;
}
