#include "i2c_mcal.h"

#include <stdbool.h>
#include <string.h>

//#include "c_defines_generated.h"
#include "array_diag.h"
#include "artery_at32f4xx.h"
#include "byte_utils.h"
#include "data_types.h"
#include "data_utils.h"
#include "debug_info.h"
#include "hal_diag.h"
#ifdef HAS_I2C_FSM
#include "i2c_fsm.h"
#endif
#include "i2c_application.h"
#include "i2c_custom_drv.h"
#include "log.h"
#include "mcal_types.h"
#include "num_to_str.h"
#include "time_mcal.h"

#ifdef HAS_AT32F43X
#include "i2c_at32f43x.h"
#endif

static const I2cInfo_t I2cInfo[] = {
#ifdef I2C1
    {.valid = true,
     .I2Cx = I2C1,
     .clock_bus = CLOCK_BUS_AHB1,
     .irq_evt_n = I2C1_EVT_IRQn,
     .irq_err_n = I2C1_ERR_IRQn,
     .num = 1,
     .clock_type = CRM_I2C1_PERIPH_CLOCK},
#endif

#ifdef I2C2
    {.valid = true,
     .clock_bus = CLOCK_BUS_AHB1,
     .I2Cx = I2C2,
     .irq_evt_n = I2C2_EVT_IRQn,
     .irq_err_n = I2C2_ERR_IRQn,
     .num = 2,
     .clock_type = CRM_I2C2_PERIPH_CLOCK},
#endif

#ifdef I2C3
    {.valid = true,
     .I2Cx = I2C3,
     .clock_bus = CLOCK_BUS_AHB1,
     .irq_evt_n = I2C3_EVT_IRQn,
     .irq_err_n = I2C3_ERR_IRQn,
     .num = 3,
     .clock_type = CRM_I2C3_PERIPH_CLOCK},
#endif

};

const I2cInfo_t* I2cGetInfo(uint8_t num) {
    I2cInfo_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(I2cInfo);
    for(i = 0; i < cnt; i++) {
        if(num == I2cInfo[i].num) {
            if(I2cInfo[i].valid) {
                Node = &I2cInfo[i];
                break;
            }
        }
    }
    return Node;
}

bool i2c_clear_addr7f_flag(I2cHandle_t* Node) {
    bool res = false;
#ifdef HAS_AT32F413X
    res = i2c_at32f413x_clear_addr7f_flag(Node);
#endif

#ifdef HAS_AT32F43X
#endif
    return res;
}

bool i2c_tx_byte(I2cHandle_t* Node, uint8_t byte_data) {
    bool res = false;
    LOG_DEBUG(I2C, "TrySend:0x%02x", byte_data);
#ifdef HAS_AT32F413X
    res = i2c_at32f413x_tx_byte(Node, byte_data);
#endif

#ifdef HAS_AT32F43X
    res = i2c_at32f43x_tx_byte(Node, byte_data);
#endif
    return res;
}

#define I2Cx_CLKCTRL 0x80504C4E // 100K
static uint32_t I2cClockToArteryClock(uint32_t clock_speed, uint32_t apb1_hz) {
    uint32_t at_clock = I2Cx_CLKCTRL;
    double tick_time_s = 1.0 / ((double)apb1_hz);
    double scl_clock_s = 1.0 / ((double)clock_speed);
    at_clock = (uint32_t)(scl_clock_s / tick_time_s);
    LOG_INFO(I2C, "Need:%sHz", uint32ToStr(clock_speed));
    LOG_INFO(I2C, "Bus:%sHz,PSC:%u", uint32ToStr(apb1_hz), at_clock);
    return at_clock;
}

bool i2c_div_set(uint8_t num, uint8_t div) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        I2cClkCtrl_t ClkCtrl;
        LOG_INFO(I2C, "Set DIV:%u", div);
        ClkCtrl.qword = 0x80504C4E;
        ClkCtrl.divh = HI_NIBBLE((uint8_t)div - 1);
        ClkCtrl.divl = LO_NIBBLE((uint8_t)div - 1);

        LOG_INFO(I2C, "I2C_CLKCTRL:0x%08x", ClkCtrl.qword);
        i2c_init(Node->I2Cx, 0x0F, ClkCtrl.qword);
        res = true;
    }
    return res;
}

uint32_t I2cCalcArteryClkCtrlQword(double i2c_freq_hz, double apb1_freq_hz) {
    LOG_INFO(I2C, "Base:%f Hz,Need:%f Hz", apb1_freq_hz, i2c_freq_hz);
    I2cClkCtrl_t ClkCtrl;
    ClkCtrl.qword = 0;
    uint32_t need_div = I2cClockToArteryClock((uint32_t)i2c_freq_hz * 102, (uint32_t)apb1_freq_hz);
    uint32_t real_div = uint32_limiter(need_div, 0xFF);
    ClkCtrl.divh = HI_NIBBLE((uint8_t)(real_div - 1));
    ClkCtrl.divl = LO_NIBBLE((uint8_t)(real_div - 1));

    ClkCtrl.sdad = 0;  // SDAD Data hold time
    ClkCtrl.scld = 14; // Data setup time
    ClkCtrl.sclh = 44; // SCL high
    ClkCtrl.scll = 44; // SCL low
    LOG_INFO(I2C, "NeedDIV:%u,PossibleDIV:%u,Calc:I2C_CLKCTRL:0x%08x=%s", need_div, real_div, ClkCtrl.qword,
             I2cClkCtrlToStr(&ClkCtrl));
    i2c_clkctrl_diag(apb1_freq_hz, ClkCtrl.qword);
    return ClkCtrl.qword;
}

bool i2c_clear_events(I2cHandle_t* Node) {
    bool res = false;
    LOG_DEBUG(I2C, "ClearEvents");
#ifdef HAS_AT32F413X
    res = i2c_at32f413x_clear_events(Node);
#endif

#ifdef HAS_AT32F43X
    res = i2c_at32f43x_clear_events(Node);
#endif
    return res;
}

// Receive data buffer full flag
bool i2c_clear_rdbf_events(I2cHandle_t* Node) {
    LOG_DEBUG(I2C, "ClearRDBF");
    bool res = false;
#ifdef HAS_AT32F413X
    res = i2c_at32f413x_clear_rdbf_events(Node);
#endif

#ifdef HAS_AT32F43X
    res = i2c_at32f43x_clear_rdbf_events(Node);
#endif
    return res;
}

bool i2c_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(I2C, "I2C%u Init", num);

    const I2cConfig_t* Config = I2cGetConfig(num);
    if(Config) {
        I2cHandle_t* Node = I2cGetNode(num);
        if(Node) {
            Node->interrupt_on = Config->interrupt_on;
            memset(&Node->i2c_h, 0, sizeof(i2c_handle_type));
            const I2cInfo_t* Info = I2cGetInfo(num);
            if(Info) {
#ifdef HAS_I2C_FSM
                res = i2c_fsm_init_one_ll(Node);
#endif

#ifdef HAS_AT32F413
                crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
                gpio_pin_remap_config(I2C1_MUX + 2, TRUE);
#endif
                Node->I2Cx = Info->I2Cx;
                Node->i2c_h.i2cx = Info->I2Cx;
                i2c_reset(Info->I2Cx);
                //  i2c_refresh_txdt_register( &Node->i2c_h);
                // i2c low level init -
                crm_periph_clock_enable(Info->clock_type, TRUE);

                if(Config->interrupt_on) {
                    LOG_WARNING(I2C, "INT EVT:%u,ERR:%u on", Info->irq_evt_n, Info->irq_err_n);

                    nvic_irq_enable(Info->irq_evt_n, 3, 3);
                    nvic_irq_enable(Info->irq_err_n, 3, 3);
                    i2c_interrupt_enable(Node->I2Cx, I2C_ALL_INT, TRUE);
                }
                // i2c_transmit_set(Node->I2Cx, uint16_t address, uint8_t cnt, i2c_reload_stop_mode_type rld_stop,
                // i2c_start_mode_type start);
                I2cClkCtrl_t ClkCtrl;
#ifdef HAS_AT32F43X
                crm_clocks_freq_type clocks_struct = {0};
                crm_clocks_freq_get(&clocks_struct);
                ClkCtrl.qword = 0x40E02C2C; // APB1:50MHz 107.7 kHz 0x40E02C2C Works fine!
                i2c_clkctrl_diag((double)clocks_struct.apb1_freq, ClkCtrl.qword);
                LOG_INFO(I2C, "Reco:I2C_CLKCTRL:0x%08x=%s", ClkCtrl.qword, I2cClkCtrlToStr(&ClkCtrl));
#endif

#ifdef HAS_AT32F413
                ClkCtrl.qword = 100000; // APB1:50MHz 107.7 kHz 0x40E02C2C Works fine!
#endif
                // ClkCtrl.qword = I2cCalcArteryClkCtrlQword((double)Config->clock_speed,
                // (double)clocks_struct.apb1_freq);

                i2c_init(Node->I2Cx, 0x0F, ClkCtrl.qword);
                i2c_own_address1_set(Node->I2Cx, I2C_ADDRESS_MODE_7BIT, Config->own_addr);
#ifdef HAS_AT32F43X
                // i2c_addr10_mode_enable(Node->I2Cx, FALSE);
                // i2c_addr10_header_enable(Node->I2Cx, FALSE);
#endif // HAS_AT32F43X

#ifdef HAS_AT32F413X
                uint8_t rx_byte = i2c_data_receive(Node->I2Cx);
                LOG_DEBUG(I2C, "DT:0x%02x", rx_byte);
                i2c_master_receive_ack_set(Node->I2Cx, I2C_MASTER_ACK_NEXT);
                i2c_ack_enable(Node->I2Cx, TRUE);
                i2c_start_done_clear(Node);
#endif
                i2c_enable(Node->I2Cx, TRUE);
#ifdef HAS_AT32F43X
                res = i2c_clear_events(Node);
#endif // HAS_AT32F43X
                Node->init_done = true;
            } else {
                LOG_ERROR(I2C, "NoInfo");
            }
            /* reset i2c peripheral */
        } else {
            LOG_ERROR(I2C, "NoNode");
        }
    } else {
        LOG_DEBUG(I2C, "NoConfig");
    }

    /* i2c peripheral enable */
    return res;
}

bool i2c_clear_ackfail_event(I2cHandle_t* Node) {
    bool res = true;
#ifdef HAS_AT32F413X
    res = i2c_at32f413x_clear_ackfail_event(Node);
#endif

#ifdef HAS_AT32F43X
    res = i2c_at32f43x_clear_ackfail_event(Node);
#endif

    return res;
}

bool i2c_clear_stop_event(I2cHandle_t* Node) {
    bool res = true;
#ifdef HAS_AT32F413X
    res = i2c_at32f413x_clear_stop_event(Node);
#endif

#ifdef HAS_AT32F43X
    res = i2c_at32f43x_clear_stop_event(Node);
#endif
    return res;
}

bool i2c_start_done_clear(I2cHandle_t* Node) {
    bool res = true;
#ifdef HAS_AT32F413X
    res = i2c_at32f413x_clear_start_done_event(Node);
#endif

#ifdef HAS_AT32F43X

#endif
    return res;
}

bool i2c_api_write(uint8_t num, uint8_t chip_addr, const uint8_t* const array, size_t size) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        i2c_interrupt_enable(Node->I2Cx, I2C_ALL_INT, TRUE);
        uint8_t wr_addr = i2c_compose_write_address(chip_addr);
#ifdef HAS_ARRAY_DIAG
        LOG_DEBUG(I2C, "I2C%u,Write,Data,Chip:0x%02x,Data:0x%s", num, wr_addr, ArrayToStr(array, 2));
#endif // HAS_ARRAY_DIAG
        Node->ack_fail = false;
        i2c_status_type ret =
            i2c_master_transmit_int(&Node->i2c_h, wr_addr, array, (uint16_t)size, I2C_SEND_TIME_OUT_MS);
        if(I2C_OK == ret) {
            res = true;
#if 0
            ret = i2c_wait_end(&Node->i2c_h, I2C_SEND_TIME_OUT_MS);
            if(I2C_OK == ret) {
                if(Node->ack_fail) {
                    res = false;
                } else {
                    res = true;
                }
            } else {
                LOG_ERROR(I2C, "Tx,TimeOut,Err,Ret:%u=%s", ret, I2cErrToStr(ret));
                res = false;
            }
#endif

        } else {
            LOG_ERROR(I2C, "Tx,Err,Ret:%u=%s,TO:%u", ret, I2cErrToStr(ret), I2C_SEND_TIME_OUT_MS);
            res = false;
        }
    }

    return res;
}

bool i2c_api_write_reg(uint8_t num, uint8_t chip_addr, uint8_t addr, uint8_t reg_val) {
    bool res = false;
    LOG_DEBUG(I2C, "I2C%u,WriteReg,Chip:0x%02x,Reg:0x%02x,Val:0x%02x", num, chip_addr, addr, reg_val);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->ack_fail = false;
        uint8_t frame[2] = {addr, reg_val};
        res = i2c_api_write(num, chip_addr, &frame[0], 2);
        if(res) {
            LOG_DEBUG(I2C, "WriteDataOk");
        } else {
            LOG_ERROR(I2C, "WriteDataErr");
        }
    }
    return res;
}

bool i2c_api_read(uint8_t num, uint8_t chip_addr, uint8_t* data, uint32_t size) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->ack_fail = false;
        i2c_status_type ret;
        ret = i2c_master_receive_int(&Node->i2c_h, chip_addr, data, (uint16_t)size, I2C_READ_TIME_OUT_MS);
        if(I2C_OK == ret) {
            res = true;
        } else {
            LOG_ERROR(I2C, "I2cTxErrRet:%u=%s", ret, I2cErrToStr(ret));
            res = false;
        }
    }

    return res;
}

bool i2c_send_signal(uint8_t num, I2cSignal_t signal) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        LOG_INFO(I2C, "I2C%u,Signal:%u=%s", num, signal, I2cSignalToStr(signal));
        if(Node->I2Cx) {
            switch((uint8_t)signal) {
            case I2C_START: {
                i2c_start_generate(Node->I2Cx);
                res = true;

            } break;

            case I2C_STOP: {
                i2c_stop_generate(Node->I2Cx);
                res = true;
            } break;

            default: {
                LOG_ERROR(I2C, "SignalErr:%u", signal);
                res = false;
            } break;
            }
        } else {
            LOG_ERROR(I2C, "%u,Instance,Err", num);
        }
    } else {
        LOG_ERROR(I2C, "%u NodeErr", num);
    }

    return res;
}

bool i2c_api_read_byte_naive(uint8_t num, uint8_t dev_addr, uint8_t addr, uint8_t* value) {
    bool res = false;
    LOG_DEBUG(I2C, "I2C%u Read, Chip 0x%x, Reg 0x%x", num, dev_addr, addr);
    res = i2c_api_write(num, dev_addr, &addr, 1);
    if(res) {
        res = i2c_api_read(num, dev_addr, value, 1);
    }
    return res;
}

bool i2c_api_read_byte(uint8_t num, uint8_t chip_addr, uint8_t addr, uint8_t* value) {
    bool res = false;
    LOG_DEBUG(I2C, "I2C%u,Read,Chip:0x%02x,Reg:0x%02x", num, chip_addr, addr);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        i2c_interrupt_enable(Node->I2Cx, I2C_ALL_INT, TRUE);
        uint8_t effective_addr = i2c_compose_read_address(chip_addr);
        i2c_status_type ret = 0;
        ret = i2c_memory_read_int(&Node->i2c_h, I2C_MEM_ADDR_WIDIH_8, effective_addr, addr, value, 1,
                                  I2C_READ_TIME_OUT_MS);
        if(I2C_OK == ret) {
            time_delay_ms(64); /*4 - ok 8 32  err*/
            res = true;
        } else {
            LOG_ERROR(I2C, "Read,Reg,Err,Ret:%u=%s", ret, I2cErrToStr(ret));
            res = false;
        }
    }

    return res;
}

bool i2c_interrupts_disable(uint8_t num) {
    bool res = false;
    I2cInfo_t* Info = I2cGetInfo(num);
    if(Info) {
        nvic_irq_disable(Info->irq_evt_n);
        nvic_irq_disable(Info->irq_err_n);

        I2cHandle_t* Node = I2cGetNode(num);
        if(Node) {
            res = i2c_interrupts_disable_ll(Node);
        }
    }
    return res;
}

bool i2c_interrupts_enable(uint8_t num) {
    bool res = false;
    I2cInfo_t* Info = I2cGetInfo(num);
    if(Info) {
        I2cConfig_t* Config = I2cGetConfig(num);
        if(Config) {
            nvic_irq_enable(Info->irq_evt_n, Config->interrupt_priority, Config->interrupt_priority);
            nvic_irq_enable(Info->irq_err_n, Config->interrupt_priority, Config->interrupt_priority);
            res = true;
        }
    }
    return res;
}

#ifdef HAS_AT32F413X
static bool i2c_at32f413_check_addr(uint8_t num, uint8_t i2c_addr) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        uint32_t start = 0;
        uint32_t diff = 0;
        flag_status ret = 0;
        i2c_master_receive_ack_set(Node->I2Cx, I2C_MASTER_ACK_NEXT);
        i2c_ack_enable(Node->I2Cx, TRUE);
        res = true;
        Node->ack_done = false;
        Node->ack_fail = false;
        i2c_start_generate(Node->I2Cx);
        start = time_get_ms32();
        while(1) {
            ret = i2c_flag_get(Node->I2Cx, I2C_STARTF_FLAG);
            if(SET == ret) {
                break;
            }
            uint32_t cur = time_get_ms32();
            diff = cur - start;
            if(50 < diff) {
                res = false;
                break;
            }
        }

        Node->I2Cx->dt_bit.dt = i2c_addr;

        // i2c_7bit_address_send(Node->I2Cx, i2c_addr, I2C_DIRECTION_RECEIVE);

        start = time_get_ms32();

        while(1) {
            ret = i2c_flag_get(Node->I2Cx, I2C_ADDR7F_FLAG);
            if(SET == ret) {
                break;
            }
            uint32_t cur = time_get_ms32();
            diff = cur - start;
            if(50 < diff) {
                res = false;
                break;
            }
        }

        if(Node->ack_fail) {
            res = false;
            res = i2c_wait_ack_ll(Node, 50);
        }

        i2c_stop_generate(Node->I2Cx);

        start = time_get_ms32();
        while(1) {
            ret = i2c_flag_get(Node->I2Cx, I2C_STOPF_FLAG);
            if(SET == ret) {
                break;
            }
            uint32_t cur = time_get_ms32();
            diff = cur - start;
            if(50 < diff) {
                // res = false;
                break;
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_AT32F43X
bool i2c_at32f43x_check_addr(uint8_t num, uint8_t i2c_addr) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        i2c_interrupt_enable(Node->I2Cx, I2C_ALL_INT, TRUE);
        Node->ack_fail = false;
        i2c_status_type ret = I2C_OK;
        uint8_t buff[2] = {0};

        // i2c_transmit_set(Node->I2Cx, i2c_addr, 0, I2C_AUTO_STOP_MODE, I2C_GEN_START_READ  );
#if 0
        /*Does not works for SA51034HFA*/
        uint8_t wr_addr = i2c_compose_write_address(i2c_addr);
        ret = i2c_master_transmit_int(&Node->i2c_h, wr_addr, buff, (uint16_t)2, I2C_SEND_TIME_OUT_MS);
        if(I2C_OK == ret) {
            ret = i2c_wait_end(&Node->i2c_h, I2C_SEND_TIME_OUT_MS) ;
            if(I2C_OK == ret) {
            } else {
                LOG_DEBUG(I2C, "I2cTxErrRet:%u=%s", ret, I2cErrToStr(ret));

                res = true;
            }
                if(Node->ack_fail) {
                    res = false;
                } else {
                    res = true;
                }
                time_delay_ms(64); /* */
        }
#endif
        // ret = i2c_master_receive(&Node->i2c_h, i2c_addr, buff, 1, I2C_CHECK_TIMEOUT);
        // ret = i2c_master_transmit(&Node->i2c_h, i2c_addr, buff, 2, I2C_CHECK_TIMEOUT);
#if 1
        ret = i2c_master_receive_int(&Node->i2c_h, i2c_addr, buff, 1, I2C_TIMEOUT / 200000);
        if(I2C_OK == ret) {
            time_delay_ms(64); /*4 - ok 8 32  err*/
            if(Node->ack_fail) {
                res = false;
                Node->ack_fail = false;
            } else {
                res = true;
            }
        } else {
            LOG_DEBUG(I2C, "Read,Mem,Err,Ret:%u=%s", ret, I2cErrToStr(ret));
            res = false;
        }
#endif
    }
    return res;
}
#endif

bool i2c_check_addr(uint8_t num, uint8_t chip_addr) {
    bool res = false;
#ifdef HAS_AT32F413X
    res = i2c_at32f413_check_addr(num, chip_addr);
#endif

#ifdef HAS_AT32F43X
    res = i2c_at32f43x_check_addr(num, chip_addr);
#endif
    return res;
}

uint16_t RegAddr2Word(uint8_t* const addr, size_t addr_size) {
    uint16_t word_addr = 0;
    switch(addr_size) {
    case 1:
        memcpy(&word_addr, addr, 1);
        break;
    case 2:
        memcpy(&word_addr, addr, 2);
        break;
    default:
        word_addr = 0;
        break;
    }
    return word_addr;
}

bool i2c_init_custom(void) {
    bool res = false;
    // NVIC_DisableIRQ(XMC_IRQn);
    return res;
}

static i2c_mem_address_width_type AddrSizeToAddrWidth(size_t addr_size) {
    i2c_mem_address_width_type address_width = I2C_MEM_ADDR_WIDIH_8;
    switch(addr_size) {
    case 1: {
        address_width = I2C_MEM_ADDR_WIDIH_8;
    } break;
    case 2: {
        address_width = I2C_MEM_ADDR_WIDIH_16;
    } break;
    default:
        break;
    }
    return address_width;
}

bool i2c_api_read_mem(uint8_t num, uint8_t chip_addr, uint8_t* const addr, size_t addr_size, uint8_t* const data,
                      size_t size) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        i2c_interrupt_enable(Node->I2Cx, I2C_ALL_INT, TRUE);
        uint8_t chip_addr_eff = i2c_compose_read_address(chip_addr);
        i2c_status_type ret;
        i2c_mem_address_width_type mem_address_width;
        mem_address_width = AddrSizeToAddrWidth(addr_size);
        uint16_t mem_address = 0;

        switch(addr_size) {
        case 1: {
            U16_bit_t un16;
            un16.u16 = 0;
            uint8_t mem_address_u8 = 0;
            memcpy(&mem_address_u8, addr, 1);
            // un16.u8[1]=mem_address_u8; // zero on bus
            un16.u8[0] = mem_address_u8; // zero
            mem_address = un16.u16;
        } break;
        case 2: {
            uint16_t mem_address_u16 = 0;
            memcpy(&mem_address_u16, addr, 2);
            mem_address = (uint16_t)mem_address_u16;
        } break;
        }
        LOG_DEBUG(I2C, "ReadMem,Chip:0x%02x,Addr:0x%04x,Size:%u,AddrSZ:%u", chip_addr, mem_address, size, addr_size);
        // mem_address=reverse_byte_order_uint16(mem_address);
        ret = i2c_memory_read_int(&Node->i2c_h, mem_address_width, chip_addr_eff, mem_address, data, size,
                                  I2C_READ_TIME_OUT_MS);
#if 0
        ret = i2c_memory_read(&Node->i2c_h, mem_address_width, chip_addr_eff, mem_address, data, size,
                                  I2C_READ_TIME_OUT_MS);
#endif
        if(I2C_OK == ret) {
            time_delay_ms(1); // 2 10 25 50 ok
            res = true;
#ifdef HAS_AT32F43X
            if(Node->ack_fail) {
                res = false;
            } else {
                res = true;
            }
#endif
        } else {
            LOG_ERROR(I2C, "Read,Mem,Err,Ret:%u=%s", ret, I2cErrToStr(ret));
            i2c_init_one(num);
            i2c_stop_generate(Node->I2Cx);
            res = false;
        }
    }

    return res;
}

bool i2c_proc_one(uint8_t num) {
    bool res = false;
    const I2cConfig_t* Config = I2cGetConfig(num);
    if(Config) {
        LOG_PARN(I2C, "I2C_%u,Proc", num);
        I2cHandle_t* Node = I2cGetNode(num);
        if(Node) {
            // i2c_proc_status_reg(Node->I2Cx->sts_bit);
            // i2c_interrupt_enable(Node->I2Cx,I2C_ALL_INT, TRUE);

            res = true;
            flag_status ret;
            /* i2c transmit data buffer empty flag */
            ret = i2c_flag_get(Node->I2Cx, I2C_TDBE_FLAG);
            if(SET == ret) {
                LOG_PARN(I2C, "I2C_%u,I2C_TDBE_FLAG", num);
                i2c_flag_clear(Node->I2Cx, I2C_TDBE_FLAG);
            }
#ifdef HAS_AT32F43X
            ret = i2c_flag_get(Node->I2Cx, I2C_TDIS_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_TDIS_FLAG", num);
                // i2c_flag_clear(Node->I2Cx, I2C_TDIS_FLAG);
            }

            ret = i2c_flag_get(Node->I2Cx, I2C_TCRLD_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_TCRLD_FLAG", num);
                // i2c_flag_clear(Node->I2Cx, I2C_TCRLD_FLAG);
            }

            ret = i2c_flag_get(Node->I2Cx, I2C_SDIR_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_SDIR_FLAG", num);
                // i2c_flag_clear(Node->I2Cx, I2C_SDIR_FLAG);
            }

            ret = i2c_interrupt_flag_get(Node->I2Cx, I2C_TCRLD_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_TCRLD_FLAG", num);
            }

            ret = i2c_interrupt_flag_get(Node->I2Cx, I2C_TDIS_FLAG);
            if(SET == ret) {
                // LOG_INFO(I2C, "I2C_%u,I2C_TDIS_FLAG", num);
            }

            ret = i2c_flag_get(Node->I2Cx, I2C_ADDRF_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_ADDRF_FLAG", num);
                // i2c_flag_clear(Node->I2Cx, I2C_ADDRF_FLAG);
            }

            ret = i2c_interrupt_flag_get(Node->I2Cx, I2C_ADDRF_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_ADDRF_FLAG", num);
            }
#endif // HAS_AT32F43X

            ret = i2c_flag_get(Node->I2Cx, I2C_RDBF_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_RDBF_FLAG", num);
                // i2c_flag_clear(Node->I2Cx, I2C_RDBF_FLAG);
            }

            ret = i2c_flag_get(Node->I2Cx, I2C_ACKFAIL_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_ACKFAIL_FLAG", num);
                // i2c_flag_clear(Node->I2Cx, I2C_ACKFAIL_FLAG);
            }

            ret = i2c_flag_get(Node->I2Cx, I2C_STOPF_FLAG);
            if(SET == ret) {
                LOG_DEBUG(I2C, "I2C_%u,I2C_STOPF_FLAG", num);
                // i2c_flag_clear(Node->I2Cx, I2C_STOPF_FLAG);
            }

            ret = i2c_flag_get(Node->I2Cx, I2C_TDC_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_TDC_FLAG", num);
                // i2c_flag_clear(Node->I2Cx, I2C_TDC_FLAG);
            }

            ret = i2c_flag_get(Node->I2Cx, I2C_BUSERR_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_BUSERR_FLAG", num);
                // i2c_flag_clear(Node->I2Cx, I2C_BUSERR_FLAG);
            }

            ret = i2c_flag_get(Node->I2Cx, I2C_ARLOST_FLAG);
            if(SET == ret) {
                LOG_DEBUG(I2C, "I2C_%u,I2C_ARLOST_FLAG", num);
                // i2c_flag_clear(Node->I2Cx, I2C_ARLOST_FLAG);
            }

            ret = i2c_flag_get(Node->I2Cx, I2C_OUF_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_OUF_FLAG", num);
                // i2c_flag_clear(Node->I2Cx, I2C_OUF_FLAG);
            }

            ret = i2c_flag_get(Node->I2Cx, I2C_PECERR_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_PECERR_FLAG", num);
                // i2c_flag_clear(Node->I2Cx, I2C_PECERR_FLAG);
            }

            ret = i2c_flag_get(Node->I2Cx, I2C_TMOUT_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_TMOUT_FLAG", num);
                // i2c_flag_clear(Node->I2Cx, I2C_TMOUT_FLAG);
            }

            ret = i2c_flag_get(Node->I2Cx, I2C_ALERTF_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_ALERTF_FLAG", num);
                // i2c_flag_clear(Node->I2Cx, I2C_ALERTF_FLAG);
            }

            ret = i2c_flag_get(Node->I2Cx, I2C_BUSYF_FLAG);
            if(SET == ret) {
                LOG_DEBUG(I2C, "I2C_%u,I2C_BUSYF_FLAG", num);
                // i2c_flag_clear(Node->I2Cx, I2C_BUSYF_FLAG);
            }

            ret = i2c_interrupt_flag_get(Node->I2Cx, I2C_TDBE_FLAG);
            if(SET == ret) {
                // LOG_INFO(I2C, "I2C_%u,I2C_TDBE_FLAG", num);
            }

            ret = i2c_interrupt_flag_get(Node->I2Cx, I2C_RDBF_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_RDBF_FLAG", num);
            }

            ret = i2c_interrupt_flag_get(Node->I2Cx, I2C_ACKFAIL_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_ACKFAIL_FLAG", num);
            }

            ret = i2c_interrupt_flag_get(Node->I2Cx, I2C_STOPF_FLAG);
            if(SET == ret) {
                LOG_DEBUG(I2C, "I2C_%u,I2C_STOPF_FLAG", num);
                // i2c_flag_clear(Node->I2Cx, I2C_STOPF_FLAG);
            }

            ret = i2c_interrupt_flag_get(Node->I2Cx, I2C_TDC_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_TDC_FLAG", num);
            }

            ret = i2c_interrupt_flag_get(Node->I2Cx, I2C_BUSERR_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_BUSERR_FLAG", num);
            }

            ret = i2c_interrupt_flag_get(Node->I2Cx, I2C_ARLOST_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_ARLOST_FLAG", num);
            }

            ret = i2c_interrupt_flag_get(Node->I2Cx, I2C_OUF_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_OUF_FLAG", num);
            }

            ret = i2c_interrupt_flag_get(Node->I2Cx, I2C_PECERR_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_PECERR_FLAG", num);
            }

            ret = i2c_interrupt_flag_get(Node->I2Cx, I2C_TMOUT_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_TMOUT_FLAG", num);
            }

            ret = i2c_interrupt_flag_get(Node->I2Cx, I2C_ALERTF_FLAG);
            if(SET == ret) {
                LOG_INFO(I2C, "I2C_%u,I2C_ALERTF_FLAG", num);
            }
        }
    }
    return res;
}

bool i2c_div_get(uint8_t num, uint8_t* const div) {
    bool res = false;
    const I2cInfo_t* Info = I2cGetInfo(num);
    if(Info) {
        if(div) {
#ifdef HAS_AT32F43X
            Type8Union_t Union8;
            Union8.u8 = 0;
            Union8.nibble_h = Info->I2Cx->clkctrl_bit.divh;
            Union8.nibble_l = Info->I2Cx->clkctrl_bit.divl;
            //
            *div = Union8.u8 + 1;
            LOG_INFO(I2C, "I2C_%u,Div:%u", num, *div);
            res = true;
#endif // HAS_AT32F43X
        }
    }
    return res;
}

bool i2c_api_read_word(uint8_t num, uint8_t chip_addr, uint8_t word_addr, uint16_t* const word) {
    bool res = false;
    LOG_DEBUG(I2C, "I2C%u,Chip:0x%02x,RegAddr:0x%02x", num, chip_addr, word_addr);
#ifdef HAS_I2C_FSM
    uint16_t reg_word = 0;
    res = i2c_fsm_read_word(num, chip_addr, word_addr, &reg_word);
    if(res) {
        *word = reverse_byte_order_uint16(reg_word);
        LOG_PARN(I2C, "ReadMemOk,Reg:0x%02x,Word:0x%04x", word_addr, reg_word);
    } else {
        LOG_ERROR(I2C, "I2C%u,Read,Word,Err,Reg:0x%02x", num, word_addr);
    }
#endif
    return res;
}

bool i2c_write_word(uint8_t num, uint8_t chip_addr, const uint16_t word) {
    bool res = false;
    LOG_DEBUG(I2C, "I2C%u,Write,Word,Chip:0x%02x,Word:0x%04x", num, chip_addr, word);
#ifdef HAS_I2C_FSM
    res = i2c_fsm_write_word(num, chip_addr, word);
#endif
    return res;
}
