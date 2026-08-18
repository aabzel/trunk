#include "tcan4550_drv.h"

#include <gpio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "TCAN4550.h"
#include "TCAN_hl.h"
#include "bit_utils.h"
#include "byte_utils.h"
#include "can_drv.h"
#include "clocks.h"
#include "data_utils.h"
#include "debug_info.h"
#include "float_utils.h"
#ifdef HAS_LOG
#include "log.h"
#endif
#include "spi_drv.h"
#include "sys_config.h"
#include "tcan4550_diag.h"
#ifdef HAS_CLI
#include "writer_config.h"
#endif

#ifdef HAS_LED
#include "led_drv.h"
#endif

const uint64_t exp_dev_id = 0x343535305443414E;

const Tcan4550Reg_t tCan4550RegLUT[] = {
    {ADDR_MCAN_PSR, "ProtStat"},
    {ADDR_IE, "IntEn"},
    {ADDR_IF, "IntFlgs"},
    {ADDR_MIF, "CANIntFlags"},
    {ADDR_TEST_REGISTERS, "rwTest"},
    {ADDR_MCAN_TEST, "Test"},
    {ADDR_MCAN_CREL, "CoreRelease"},
    {ADDR_MCAN_RXF0S, "FiFo0Stat"},
    {ADDR_MCAN_RXF1S, "FiFo1Stat"},
    {ADDR_MCAN_NBTP, "BitTiming"},
    {ADDR_DEV_CONFIG, "DevCfg"},
    {ADDR_DEVICE_ID0, "DevId0"},
    {ADDR_DEVICE_ID1, "DevId1"},
    {ADDR_SPI_2_REV, "SPIrev"},
    {ADDR_SPI_STATUS, "Status"},
    {ADDR_MCAN_CCCR, "CcCtrl"},
    {ADDR_MCAN_TXBAR, "TxBufRqst"},
    {ADDR_MCAN_TXBC, "TxBufCfg"},
    {ADDR_MCAN_TXESC, "TxBufElSzCfg"},
    {ADDR_MCAN_ENDN, "Endian"},
    {ADDR_MCAN_DBTP, "DatBitTimPscr"},
    {ADDR_MCAN_RWD, "RAMWtd"},
    {ADDR_MCAN_TSCC, "TimStmpCntCfg"},
    {ADDR_MCAN_TSCV, "TimStmpCntVal"},
    {ADDR_MCAN_CUST, ""},
    {ADDR_TIMESTAMP_PRESCALER, "TimeStampPscr"},
    {ADDR_MCAN_TOCC, ""},
    {ADDR_MCAN_TOCV, "TimOutCntVal"},
    {ADDR_MCAN_ECR, ""},
    {ADDR_MCAN_TDCR, ""},
    {ADDR_MCAN_IR, "IntRegister"},
    {ADDR_MCAN_IE, "IntEnable"},
    {ADDR_MCAN_ILS, "IntLineSel"},
    {ADDR_MCAN_ILE, "IntLineEn"},
    {ADDR_MCAN_GFC, "GlobalFilterCfg"},
    {ADDR_MCAN_SIDFC, "StdIDFilterCfg"},
    {ADDR_MCAN_XIDFC, "ExtIDFiltCfg"},
    {ADDR_MCAN_XIDAM, ""},
    {ADDR_MCAN_HPMS, ""},
    {ADDR_MCAN_NDAT1, ""},
    {ADDR_MCAN_NDAT2, ""},
    {ADDR_MCAN_RXF0C, "RxFIFO0Cfg"},
    {ADDR_MCAN_RXF0A, ""},
    {ADDR_MCAN_RXBC, "RxBufferCnfg"},
    {ADDR_MCAN_RXF1C, "RxFIFO1Cfg"},
    {ADDR_MCAN_RXF1A, ""},
    {ADDR_MCAN_RXESC, "RxBuffIFOElmSzCfg"},
    {ADDR_MCAN_TXFQS, ""},
    {ADDR_MCAN_TXBRP, ""},
    {ADDR_MCAN_TXBCR, ""},
    {ADDR_MCAN_TXBTO, ""},
    {ADDR_MCAN_TXBCF, ""},
    {ADDR_MCAN_TXBTIE, ""},
    {ADDR_MCAN_TXBCIE, ""},
    {ADDR_MCAN_TXEFC, "TxEvFIFOCfg"},
    {ADDR_MCAN_TXEFS, ""},
    {ADDR_MCAN_TXEFA, ""},
};

Can4550_t CanPhy;

const char* tcan4550_get_reg_name(uint16_t addr) {
    const char* reg_name = "undef";
    uint16_t cnt = tcan4550_get_reg_cnt();
    uint16_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(tCan4550RegLUT[i].addr == addr) {
            reg_name = tCan4550RegLUT[i].name;
        }
    }
    return reg_name;
}

bool tcan4550_int_isr(void) {
    CanPhy.cur.int_cnt++;
    return true;
}

uint16_t tcan4550_get_reg_cnt(void) {
    uint16_t reg_cnt = ARRAY_SIZE(tCan4550RegLUT);
    return reg_cnt;
}

bool tcan4550_chip_select(bool state) {
    bool res = false;
    if(state) {
#ifdef DIO_SX1262_SS
        GPIO_writeDio(DIO_SX1262_SS, 1);
#endif
        GPIO_writeDio(DIO_CAN_SS, 0);
        res = true;
    } else if(false == state) {
#ifdef DIO_SX1262_SS
        GPIO_writeDio(DIO_SX1262_SS, 1);
#endif
        GPIO_writeDio(DIO_CAN_SS, 1);
        res = true;
    } else {
        res = false;
    }
    return res;
}

#define TCAN4550_CHIP_SELECT(CALL_BACK)                                                                                \
    do {                                                                                                               \
        res = tcan4550_chip_select(true);                                                                              \
        delay_ms(1);                                                                                                   \
        res = CALL_BACK;                                                                                               \
        delay_ms(1);                                                                                                   \
        res = tcan4550_chip_select(false);                                                                             \
    } while(0);

static bool init_spi_header(HeaderCom_t* header, uint8_t op_code, uint16_t address, uint8_t words_cnt) {
    bool res = false;
    if(header) {
        header->op_code = op_code;
        header->addr = reverse_byte_order_uint16(address);
        header->words_cnt = words_cnt;
        res = true;
    }
    return res;
}
static bool tcan4550_read_proc(uint16_t address, uint8_t len, uint8_t* out_array, uint32_t size) {
    bool res = true;
    uint8_t tx_array[4];
    res = init_spi_header((HeaderCom_t*)tx_array, OP_CODE_READ, address, len);
    // tx_array[0] = OP_CODE_READ;
    //  memcpy(&tx_array[1], &address, 2);
    //  tx_array[3] = len;
    res = spi_write((SpiName_t)CAN_SPI_NUM, tx_array, sizeof(tx_array)) && res;
    res = spi_read((SpiName_t)CAN_SPI_NUM, out_array, (uint16_t)(len * 4)) && res;
    return res;
}

bool tcan4550_read(uint16_t address, uint8_t len, uint8_t* out_array, uint32_t size) {
    bool res = true;
    if((NULL != out_array) && ((len * 4) <= size)) {
        TCAN4550_CHIP_SELECT(tcan4550_read_proc(address, len, out_array, size));
    } else {
        res = false;
    }
    return res;
}

bool is_tcan4550_connected(void) {
    bool res = false;
    uint64_t read_dev_id = 0;
    res = tcan4550_read(ADDR_DEVICE_ID0, 2, (uint8_t*)&read_dev_id, sizeof(read_dev_id));
    if(res) {
        if(exp_dev_id == read_dev_id) {
            res = true;
#ifdef HAS_TCAN_DIAG
            LOG_INFO(CAN, "spot dev id: 0x%llx", read_dev_id);
            print_mem((uint8_t*)&read_dev_id, sizeof(read_dev_id), true, true);
#endif
        } else {
            res = false;
#ifdef HAS_TCAN_DIAG
            LOG_ERROR(CAN, "Unable to spot dev id: 0x%llx", read_dev_id);
#endif
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(CAN, "Unable to read reg");
#endif
    }
    return res;
}

bool tcan4550_reset(void) {
    bool res = true;
    LOG_WARNING(CAN, "Reset");
    /*see page 25 in spec 8.3.8 RST Pin*/
    GPIO_writeDio(DIO_CAN_RST, 1);
    delay_ms(1);
    GPIO_writeDio(DIO_CAN_RST, 0);
    /*tPULSE_WIDTH Width of the input pulse 30 us*/
    delay_ms(1);
    return res;
}

bool tcan4550_send_spi_header(uint8_t opcode, uint16_t address, uint8_t words) {
    bool res = true;
    uint8_t tx_array[4] = {0};
    res = init_spi_header((HeaderCom_t*)tx_array, opcode, address, words);
    res = spi_write((SpiName_t)CAN_SPI_NUM, tx_array, sizeof(tx_array)) && res;
    return res;
}

static bool tcan4550_read_reg_proc(uint16_t address, uint32_t* out_reg) {
    bool res = true;
    // see page 44 Figure 8-18. Read (Command OpCode 8h41)
    uint32_t read_reg = 0;
    res = tcan4550_send_spi_header(OP_CODE_READ, address, 1);
    res = spi_read((SpiName_t)CAN_SPI_NUM, (uint8_t*)&read_reg, 4) && res; /*Error Here*/
    (*out_reg) = reverse_byte_order_uint32(read_reg);
    return res;
}

bool tcan4550_read_reg(uint16_t address, uint32_t* out_reg) {
    bool res = true;
    if(NULL != out_reg) {
        TCAN4550_CHIP_SELECT(tcan4550_read_reg_proc(address, out_reg));
    } else {
        res = false;
    }
    return res;
}

bool tcan4550_send_spi_burst(uint32_t word) {
    bool res = true;
    uint32_t tx_word = reverse_byte_order_uint32(word);
    res = spi_write((SpiName_t)CAN_SPI_NUM, (uint8_t*)&tx_word, sizeof(tx_word)) && res;
    return res;
}

uint32_t tcan4550_read_spi_burst(void) {
    uint32_t rx_word = 0;
    spi_read((SpiName_t)CAN_SPI_NUM, (uint8_t*)&rx_word, sizeof(rx_word));
    rx_word = reverse_byte_order_uint32(rx_word);
    return rx_word;
}

static bool tcan4550_write_reg_proc(uint16_t address, uint32_t reg_val) {
    bool res = true;
    res = tcan4550_send_spi_header(OP_CODE_WRITE, address, 1);
    res = tcan4550_send_spi_burst(reg_val) && res;
    return res;
}

bool tcan4550_write_reg(uint16_t address, uint32_t reg_val) {
    bool res = true;
    TCAN4550_CHIP_SELECT(tcan4550_write_reg_proc(address, reg_val));
    return res;
}

bool tcan4550_write_verify_reg(uint16_t address, uint32_t reg_val) {
    bool res = true;
    uint32_t read_reg = 0;
    TCAN4550_CHIP_SELECT(tcan4550_write_reg_proc(address, reg_val));
    TCAN4550_CHIP_SELECT(tcan4550_read_reg_proc(address, &read_reg));
    if(read_reg == reg_val) {
        res = true;
    }
    return res;
}

bool tcan4550_write_reg_lazy(uint16_t address, uint32_t reg_val) {
    bool res = false;
    return res;
}

bool tcan4550_clear_mram(void) {
    bool res = true;
    uint16_t curAddr = ADDR_MRAM;
    for(curAddr = ADDR_MRAM; curAddr < (ADDR_MRAM + MRAM_SZ - 4); curAddr += 4) {
        res = tcan4550_write_reg(curAddr, 0) && res;
    }
    return res;
}

/**
 * @brief Clears a SPIERR flag that may be set
 */
bool tcan4550_clear_spi_err(void) {
    bool res = false;
    // Simply write all 1s to attempt to clear a SPIERR that was set
    res = tcan4550_write_reg(ADDR_SPI_STATUS, 0xFFFFFFFF);
    return res;
}

CanDevMode_t tcan4550_get_mode(void) {
    CanDevMode_t dev_mode = MODE_UNDEF;
    bool res = false;
    tCanRegModeOpPinCfg_t read_reg;
    read_reg.word = 0;
    res = tcan4550_read_reg(ADDR_DEV_CONFIG, &read_reg.word);
    if(res) {
        dev_mode = (CanDevMode_t)read_reg.mode_sel;
    }
    return dev_mode;
}

bool tcan4550_set_mode(CanDevMode_t dev_mode) {
    bool res = false;
    tCanRegModeOpPinCfg_t read_reg = {0};
    read_reg.word = 0;
    res = tcan4550_read_reg(ADDR_DEV_CONFIG, &read_reg.word);
    if(res) {
        read_reg.mode_sel = dev_mode;
        res = tcan4550_write_reg(ADDR_DEV_CONFIG, read_reg.word);
    }
    return res;
}

/**
 * @brief Converts the ESC (Element Size) value to number of bytes that it corresponds to
 *
 * @param inputESCValue is the value from an element size configuration register
 * @return The number of bytes of data (8-64 bytes)
 */
uint8_t txrxesc_2data_bytes(uint8_t code) {
    static const uint8_t lookUpTable[8] = {8, 12, 16, 20, 24, 32, 48, 64};
    return lookUpTable[code & 0x07];
}

/**
 * @brief Converts the CAN message DLC hex value to the number of bytes it corresponds to
 *
 * @param inputDLC is the DLC value from/to a CAN message struct
 * @return The number of bytes of data (0-64 bytes)
 */
uint8_t dlc_2_bytes(uint8_t dlc_code) {
    static const uint8_t dlcLUT_9[7] = {12, 16, 20, 24, 32, 48, 64};
    uint8_t size = 0;
    if(dlc_code < 9) {
        size = dlc_code;
    } else if(dlc_code < 16) {
        size = dlcLUT_9[(dlc_code - 9)];
    } else {
        size = 0;
    }
    return size;
}

uint8_t bytes_2_dlc(uint8_t len) {
    uint8_t dlc = 0;
    if(len < 9) {
        dlc = len;
    } else {
        if((8 < len) && (len <= 12)) {
            dlc = 9;
        } else if((12 < len) && (len <= 16)) {
            dlc = 10;
        } else if((16 < len) && (len <= 20)) {
            dlc = 11;
        } else if((20 < len) && (len <= 24)) {
            dlc = 12;
        } else if((24 < len) && (len <= 32)) {
            dlc = 13;
        } else if((32 < len) && (len <= 48)) {
            dlc = 14;
        } else if((48 < len) && (len <= 64)) {
            dlc = 15;
        } else {
            dlc = 15;
        }
    }
    return dlc;
}

bool tcan4550_write_tx_buff(uint8_t buf_index, tCanTxHeader_t* header, uint8_t* data_payload) {
    bool res = false;
    tCanRegTxBufCfg_t read_reg = {0};
    read_reg.word = 0;
    uint8_t element_size = 0;
    uint16_t start_address = 0;
    res = tcan4550_read_reg(ADDR_MCAN_TXBC, &read_reg.word);
    if(res) {
        res = false;
        start_address = ADDR_MRAM + read_reg.tx_buf_start_addr;
        read_reg.tfqs = uint8_limiter(read_reg.tfqs, 32);
        read_reg.ndtb = uint8_limiter(read_reg.ndtb, 32);
        element_size = read_reg.tfqs + read_reg.ndtb;
        if((element_size - 1) < buf_index) {
            res = false;
        } else {
            res = true;
        }
    }

    element_size = 0;
    if(res) {
        tCanRegTxBufElmSzCfg_t reg;
        reg.word = 0;
        res = tcan4550_read_reg(ADDR_MCAN_TXESC, &reg.word);
        element_size = txrxesc_2data_bytes(reg.tx_buff_data_size) + 8;
        start_address += ((uint32_t)element_size * buf_index);
        // Convert it to words for easier reading by dividing by 4, and only look at data payload
        element_size = (dlc_2_bytes(header->dlc & 0x0F) + 8) >> 2;
        if(0 < (dlc_2_bytes(header->dlc & 0x0F) % 4)) { // If we don't have a whole word worth of data...
            // We need to round up to the nearest word (by default it truncates).
            // Can be done by simply adding another word.
            element_size += 1;
        }
        tcan4550_chip_select(true);
        delay_ms(1);
        res = tcan4550_send_spi_header(OP_CODE_WRITE, start_address, element_size);
        W0_t reg_w0 = {0};
        reg_w0.word = 0;
        reg_w0.esi = header->esi;
        reg_w0.xtd = header->xtd;
        reg_w0.rtr = header->rtr;
        if(header->xtd) {
            reg_w0.id = header->id & MASK_29BIT;
        } else {
            reg_w0.id = ((uint32_t)header->id & MASK_11BIT) << 18;
        }
        tcan4550_send_spi_burst(reg_w0.word);
        // see Figure 12. Tx FIFO / Buffer Element
        TxBuffW1_t reg_w1;
        reg_w1.word = 0;
        reg_w1.dlc = header->dlc;
        reg_w1.brs = header->brs;
        reg_w1.fdf = header->fdf;
        reg_w1.efc = header->efc;
        reg_w1.mm = header->mm;
        tcan4550_send_spi_burst(reg_w1.word);

        element_size = dlc_2_bytes(header->dlc & 0x0F); // Returns the number of data bytes
        Type32Union_t un32 = {0};
        un32.u32 = 0;
        uint16_t i = 0;
        for(i = 0; i < element_size; i += 4) {
            un32.u8[0] = data_payload[i];
            un32.u8[1] = data_payload[i + 1];
            un32.u8[2] = data_payload[i + 2];
            un32.u8[3] = data_payload[i + 3];
            res = tcan4550_send_spi_burst(un32.u32);
        }
        delay_ms(1);
        tcan4550_chip_select(false);
    }

    return res;
}

bool is_tcan4550_protected_reg_locked(tCanRegCCctrl_t* ctrl_reg) {
    bool res = false;
    tCanRegCCctrl_t reg;
    reg.word = 0;
    res = tcan4550_read_reg(ADDR_MCAN_CCCR, &reg.word);
    if(true == res) {
        *ctrl_reg = reg;
        res = false;
        if(0 == reg.cce) {
            res = true;
        }
    }
    return res;
}

/**
 * @brief Disable Protected MCAN Registers
 *
 * Attempts to disable CCCR.CCE and CCCR.INIT to disallow writes to protected registers
 *
 * @return @c true if successfully enabled, otherwise return @c false
 */
bool tcan4550_protected_registers_lock(void) {
    bool res = false;
    tCanRegCCctrl_t reg;
    reg.word = 0;

    res = is_tcan4550_protected_reg_locked(&reg);

    if(false == res) {
        uint8_t i;
        for(i = 0; i < 5; i++) {
            reg.csr = 0;
            reg.csa = 0;
            reg.cce = 0;
            reg.init = 0;
            res = tcan4550_write_reg(ADDR_MCAN_CCCR, reg.word);
            if(res) {
                res = is_tcan4550_protected_reg_locked(&reg);
                if(res) {
                    break;
                }
            }
        }
    }

    return res;
}

static bool tcan4550_mram_fifo0_cfg(TCAN4550_MRAM_Config* MramConfig, uint16_t* start_address) {
    bool res = true;
    tCanRegRxFifo0Cfg_t RxFiFo0Cfg;
    RxFiFo0Cfg.word = 0;
    RxFiFo0Cfg.f0s = MramConfig->rx0_num_elements;
    if(MAX_NUM_RX_FIFO_0_EL < RxFiFo0Cfg.f0s) {
        RxFiFo0Cfg.f0s = MAX_NUM_RX_FIFO_0_EL;
    }

    if(0 < RxFiFo0Cfg.f0s) {
        RxFiFo0Cfg.f0sa = *start_address;
        RxFiFo0Cfg.f0om = FIFO_OP_MODE_OVERWRITE;
    }
    res = tcan4550_write_reg(ADDR_MCAN_RXF0C, RxFiFo0Cfg.word) && res;
    *start_address += txrxesc_2data_bytes((((uint8_t)MramConfig->rx0_element_size) + 8) * ((uint16_t)RxFiFo0Cfg.f0s));
    return res;
}

static bool tcan4550_mram_fifo1_cfg(TCAN4550_MRAM_Config* MramConfig, uint16_t* start_address) {
    bool res = true;
    tCanRegRxFifo1Cfg_t RxFiFo1Cfg;
    RxFiFo1Cfg.word = 0;

    RxFiFo1Cfg.f1s = MramConfig->rx1_num_elements;
    if(64 < RxFiFo1Cfg.f1s) {
        RxFiFo1Cfg.f1s = 64;
    }

    if(0 < RxFiFo1Cfg.f1s) {
        RxFiFo1Cfg.f1sa = *start_address;
    }

    res = tcan4550_write_reg(ADDR_MCAN_RXF1C, RxFiFo1Cfg.word) && res;
    *start_address += txrxesc_2data_bytes((((uint8_t)MramConfig->rx1_element_size) + 8) * ((uint16_t)RxFiFo1Cfg.f1s));
    return res;
}

static bool tcan4550_mram_rx_buff_cfg(TCAN4550_MRAM_Config* MramConfig, uint16_t* start_address) {
    bool res = true;
    tCanRegRxBufCgf_t RxBuffCfg;
    RxBuffCfg.word = 0;
    uint8_t val;
    val = MramConfig->rx_buf_num_elements;
    if(64 < val) {
        val = 64;
    }

    if(0 < val) {
        RxBuffCfg.rbsa = *start_address;
    }
    res = tcan4550_write_reg(ADDR_MCAN_RXBC, RxBuffCfg.word) && res;
    *start_address += (((uint32_t)txrxesc_2data_bytes((uint8_t)MramConfig->rx_buf_element_size) + 8) * (uint16_t)val);

    return res;
};

static bool tcan4550_mram_tx_event_fifo_cfg(TCAN4550_MRAM_Config* MramConfig, uint16_t* start_address) {
    bool res = true;
    tCanRegTxEventFifoCgf_t TxEvFiFoCfg = {0};
    TxEvFiFoCfg.word = 0;
    TxEvFiFoCfg.efs = MramConfig->tx_event_fifo_num_elements;
    TxEvFiFoCfg.efs = uint8_limiter(TxEvFiFoCfg.efs, 32);
    if(0 < TxEvFiFoCfg.efs) {
        TxEvFiFoCfg.efsa = *start_address;
    }
    res = tcan4550_write_reg(ADDR_MCAN_TXEFC, TxEvFiFoCfg.word) && res;
    *start_address += (8 * ((uint16_t)TxEvFiFoCfg.efs));
    return res;
}

bool tcan4550_mram_tx_buff_cfg(TCAN4550_MRAM_Config* MramConfig, uint16_t* start_address) {
    bool res = true;
    tCanRegTxBufCfg_t TxBufCfg = {0};
    TxBufCfg.word = 0;
    TxBufCfg.tfqs = MramConfig->tx_buffer_num_elements;
    TxBufCfg.tfqs = uint8_limiter(TxBufCfg.tfqs, 32);

    if(0 < TxBufCfg.tfqs) {
        TxBufCfg.tx_buf_start_addr = *start_address;
    }

    res = tcan4550_write_reg(ADDR_MCAN_TXBC, TxBufCfg.word) && res;
    *start_address +=
        (((uint32_t)txrxesc_2data_bytes((uint8_t)MramConfig->tx_buffer_element_size) + 8) * (uint16_t)TxBufCfg.tfqs);
    return res;
}

bool tcan4550_mram_cfg(TCAN4550_MRAM_Config* MramConfig) {
    bool res = true;
    uint16_t start_address = 0x0000;
    tCanRegStdIdFiltCfg_t StdIdRegFilCfg;

    // First the 11-bit filter section can be setup.
    StdIdRegFilCfg.lss = MramConfig->sid_num_elements;
    if(MAX_NUM_STD_ID_FIL < StdIdRegFilCfg.lss) {
        StdIdRegFilCfg.lss = MAX_NUM_STD_ID_FIL;
    }
    StdIdRegFilCfg.flssa = start_address;
    res = tcan4550_write_reg(ADDR_MCAN_SIDFC, StdIdRegFilCfg.word) && res;

    start_address += (4 * (uint16_t)StdIdRegFilCfg.lss);
    tCanRegExtIdFiltCfg_t ExtIdFilCfg;

    // The 29-bit extended filter section
    ExtIdFilCfg.lse = MramConfig->xid_num_elements;
    if(MAX_NUM_EXT_ID_FIL < ExtIdFilCfg.lse) { // TODO add limitter function
        ExtIdFilCfg.lse = MAX_NUM_EXT_ID_FIL;
    }
    if(0 < ExtIdFilCfg.lse) {
        ExtIdFilCfg.flsea = start_address;
    }

    res = tcan4550_write_reg(ADDR_MCAN_XIDFC, ExtIdFilCfg.word) && res;
    start_address += (8 * (uint16_t)ExtIdFilCfg.lse);
    // RX FIFO 0
    res = tcan4550_mram_fifo0_cfg(MramConfig, &start_address) && res;

    // RX FIFO 1
    res = tcan4550_mram_fifo1_cfg(MramConfig, &start_address) && res;

    // RX Buffers
    res = tcan4550_mram_rx_buff_cfg(MramConfig, &start_address) && res;

    // TX Event FIFO
    res = tcan4550_mram_tx_event_fifo_cfg(MramConfig, &start_address) && res;

    // TX Buffer
    res = tcan4550_mram_tx_buff_cfg(MramConfig, &start_address) && res;

    if((ADDR_MRAM + MRAM_SZ) < (start_address - 1)) {
        res = false;
    }

    if(res) {
        tCanRegRxBufFiFoElemSzCgf_t RxBuffFiFoElemSz;
        RxBuffFiFoElemSz.f0ds = MramConfig->rx0_element_size;
        RxBuffFiFoElemSz.f1ds = MramConfig->rx1_element_size;
        RxBuffFiFoElemSz.rbds = MramConfig->rx_buf_element_size;
        res = tcan4550_write_reg(ADDR_MCAN_RXESC, RxBuffFiFoElemSz.word) && res;

        tCanRegTxBufElmSzCfg_t TxBuffElmSz = {0};
        TxBuffElmSz.word = 0;
        TxBuffElmSz.tx_buff_data_size = MramConfig->tx_buffer_element_size;
        res = tcan4550_write_reg(ADDR_MCAN_TXESC, TxBuffElmSz.word) && res;
    }
    return res;
}

bool tcan4550_tx_buff_content(uint8_t buf_index) {
    bool res = false;
    if(buf_index < 31U) {
        uint32_t write_value = 0;
        write_value = 1U << buf_index;
        res = tcan4550_write_reg(ADDR_MCAN_TXBAR, write_value);
    }
    return res;
}

bool tcan4550_send_std(uint32_t id, uint64_t data, uint8_t len) {
    bool res = false;

    res = false;
    tCanTxHeader_t header = {0};
    // memset(&header, 0x00, sizeof(header));
    header.dlc = bytes_2_dlc(uint8_limiter(len, 8));
    header.id = id; // CAN ID to send
    header.fdf = 0; // CAN FD Format flag
    header.brs = 0; // Bit rate switch used flag
    header.efc = 0; // Event FIFO Control flag, to store tx events or not
    header.mm = 0;  // Message Marker, used if @c EFC is set to 1
    header.rtr = 0; // Remote Transmission Request flag
    header.xtd = 0; // Extended Identifier flag
#ifdef LED_INDEX_RED
    led_blink(&Led[LED_INDEX_RED], 50);
#endif
    res = tcan4550_write_tx_buff(0, &header, (uint8_t*)&data);
    if(res) {
        res = tcan4550_tx_buff_content(0);
    }

    return res;
}

bool tcan4550_send_ext(uint32_t id, uint64_t data, uint8_t len) {
    bool res = false;
    res = false;
    tCanTxHeader_t header = {0};
    // memset(&header, 0x00, sizeof(header));
    header.dlc = bytes_2_dlc(uint8_limiter(len, 8));
    header.id = id; // CAN ID to send
    header.fdf = 0; // CAN FD Format flag
    header.brs = 0; // Bit rate switch used flag
    header.efc = 0; // Event FIFO Control flag, to store tx events or not
    header.mm = 0;  // Message Marker, used if @c EFC is set to 1
    header.rtr = 0; // Remote Transmission Request flag
    header.xtd = 1; // Extended Identifier flag

    res = tcan4550_write_tx_buff(0, &header, (uint8_t*)&data);
    if(res) {
        res = tcan4550_tx_buff_content(0);
    }

    return res;
}

/**
 * @brief Writes the MCAN nominal timing settings, using the simple nominal timing struct
 *
 * Writes the data timing information to MCAN using the input from the @c *nomTiming pointer
 *
 * @warning This function writes to protected MCAN registers
 * @note Requires that protected registers have been unlocked using @c TCAN4550_MCAN_EnableProtectedRegisters() and @c
 * TCAN4550_MCAN_DisableProtectedRegisters() be used to lock the registers after configuration
 *
 * @param *nomTiming is a pointer of a @c TCAN4550_MCAN_Nominal_Timing_Simple struct containing the simplified nominal
 * timing information
 * @return @c true if successfully enabled, otherwise return @c false
 */
bool tcan4550_configure_timing_simple(tCanRegBitTime_t* bit_time) {
    bool res = false;
    res = tcan4550_write_reg(ADDR_MCAN_NBTP, bit_time->word);
    return res;
}

bool tcan4550_configure_data_timing_simple(tCanRegDataBitTime_t* data_time) {
    bool res = false;
    res = tcan4550_write_reg(ADDR_MCAN_DBTP, data_time->word);
    return res;
}

bool tcan4550_configure_interrupt(tCanRegIntEn_t* ie) {
    bool res = tcan4550_write_reg(ADDR_IE, ie->word);
    return res;
}

/**
 * @brief Read the device interrupts
 *
 * Reads the device interrupts and updates a @c TCAN4550_Device_Interrupts struct that is passed to the function
 *
 * @param *ir is a pointer to a @c TCAN4550_Device_Interrupts struct containing the interrupt bit fields that will be
 * updated
 */
bool tcan4550_read_interrupt(tCanRegIntFl_t* ir) {
    bool res = false;
    res = tcan4550_read_reg(ADDR_IF, &ir->word);
    return res;
}

/**
 * @brief Clear the device interrupts
 *
 * Will attempt to clear any interrupts that are marked as a '1' in the passed @c TCAN4550_Device_Interrupts struct
 *
 * @param *ir is a pointer to a @c TCAN4550_Device_Interrupts struct containing the interrupt bit fields that will be
 * updated
 */
bool tcan4550_clear_interrupt(tCanRegIntFl_t* ir) {
    bool res = false;
    res = tcan4550_write_reg(ADDR_IF, ir->word);
    return res;
}

bool is_tcan4550_protected_reg_unlock(tCanRegCCctrl_t* const reg) {
    bool res = false;
    tCanRegCCctrl_t ctr_reg = {0};
    ctr_reg.word = 0;
    res = tcan4550_read_reg(ADDR_MCAN_CCCR, &ctr_reg.word);
    if(res) {
        res = false;
        *reg = ctr_reg;
        if(1 == ctr_reg.cce) {
            /*For step by step debugging*/
            if(1 == ctr_reg.init) {
                res = true;
            }
        }
    }
    return res;
}

/**
 * @brief Enable Protected MCAN Registers
 * Attempts to enable CCCR.CCE and CCCR.INIT to allow writes to protected registers, needed for MCAN configuration
 * @return @c true if successfully enabled, otherwise return @c false
 */
bool tcan4550_protected_registers_unlock(void) {
    bool res = false;
    tCanRegCCctrl_t ctr_reg = {0};
    ctr_reg.word = 0;

    res = is_tcan4550_protected_reg_unlock(&ctr_reg);
    if(true == res) {
        res = true;
    }

    // Try up to 5 times to set the CCCR register, if not, then fail config, since we need these bits set to configure
    // the device.
    ctr_reg.csa = 0;
    ctr_reg.csr = 0;
    uint8_t i = 0;
    for(i = 0; i < 10; i++) {
        // Unset the CSA and CSR bits since those will be set if we're in standby mode.
        // Writing a 1 to these bits will force a clock stop event and prevent the return to normal mode
        ctr_reg.cce = 1;
        ctr_reg.init = 1;
        res = tcan4550_write_reg(ADDR_MCAN_CCCR, ctr_reg.word);
        if(res) {
            res = is_tcan4550_protected_reg_unlock(&ctr_reg);
            if(true == res) {
                break;
            }
        }
    }
    return res;
}

bool tcan4550_set_lock(bool state) {
    bool res = false;
    if(state) {
        res = tcan4550_protected_registers_lock();
    } else {
        res = tcan4550_protected_registers_unlock();
    }
    return res;
}

/**
 * @brief Configures the MCAN global filter configuration register, using the passed Global Filter Configuration struct.
 *
 * Configures the default behavior of the MCAN controller when receiving messages. This can include accepting or
 * rejecting CAN messages by default.
 *
 * @warning This function writes to protected MCAN registers
 * @note Requires that protected registers have been unlocked using @c TCAN4550_MCAN_EnableProtectedRegisters() and @c
 * TCAN4550_MCAN_DisableProtectedRegisters() be used to lock the registers after configuration
 *
 * @param *gfc is a pointer of a @c TCAN4550_MCAN_Global_Filter_Configuration struct containing the register values
 * @return @c true if successfully enabled, otherwise return @c false
 */
bool tcan4550_configure_global_filter(tCanRegGloFiltCfg_t* gfc) {
    bool res = false;
    res = tcan4550_write_reg(ADDR_MCAN_GFC, gfc->word);

    return res;
}

bool tcan4550_configure_mcan_interrupt(tCanRegIntEn_t* mcan_ie) {
    bool res = true;
    res = tcan4550_write_reg(ADDR_MCAN_IE, mcan_ie->word) && res;
    tCanRegIntLine_t it_reg;
    it_reg.word = 0;
    it_reg.eint0 = 1;
    // This is necessary to enable the MCAN Int mux to the output nINT pin
    res = tcan4550_write_reg(ADDR_MCAN_ILE, it_reg.word) && res;
    return res;
}

bool tcan4550_device_configure(tCanRegModeOpPinCfg_t* dev_cfg) {
    bool res = false;
    tCanRegModeOpPinCfg_t OldRegModeOpPinCfg = {0}, NewRegModeOpPinCfg = {0};
    NewRegModeOpPinCfg.word = 0;
    OldRegModeOpPinCfg.word = 0;
    res = tcan4550_read_reg(ADDR_DEV_CONFIG, &OldRegModeOpPinCfg.word);
    if(res) {
        OldRegModeOpPinCfg.test_mode_en = 0;
        OldRegModeOpPinCfg.device_reset = 0;
        OldRegModeOpPinCfg.wd_en = 0;
        OldRegModeOpPinCfg.mode_sel = 0;
        OldRegModeOpPinCfg.wd_action = 0;
        OldRegModeOpPinCfg.fail_safe_en = 0;
        OldRegModeOpPinCfg.nwkrq_voltage = 0;
        OldRegModeOpPinCfg.wake_config = 0;
        OldRegModeOpPinCfg.clk_ref = 0;
        OldRegModeOpPinCfg.gpo2_config = 0;
        OldRegModeOpPinCfg.gpio1_config = 0;
        OldRegModeOpPinCfg.wd_bit_set = 0;
        OldRegModeOpPinCfg.inh_dis = 0;
        OldRegModeOpPinCfg.gpio1_gpo_config = 0;

        NewRegModeOpPinCfg.word = dev_cfg->word | OldRegModeOpPinCfg.word;

        NewRegModeOpPinCfg.rsvd1 = 2;
        NewRegModeOpPinCfg.rsvd2 = 0;
        NewRegModeOpPinCfg.rsvd3 = 0;
        NewRegModeOpPinCfg.rsvd4 = 0;
        res = tcan4550_write_reg(ADDR_DEV_CONFIG, NewRegModeOpPinCfg.word);
    }
    return res;
}

bool tcan4550_write_sid_filter(uint8_t filter_index, tCan4550SidFilter_t* filter) {
    bool res = false;
    tCanRegStdIdFiltCfg_t reg;
    uint16_t start_address = 0;

    res = tcan4550_read_reg(ADDR_MCAN_SIDFC, &reg.word);
    if(res) {
        if(reg.lss < filter_index) {
            res = false;
        } else {
            reg.lss = filter_index;
        }
    }

    if(true == res) {
        start_address = reg.flssa + ADDR_MRAM;
        start_address += (reg.lss * 4);
        res = tcan4550_write_reg(start_address, filter->word) && res;
    }
    return res;
}

bool tcan4550_configure_cccr_register(tCanRegCCctrl_t* CrtlReg) {
    bool res = true;

    tCanRegCCctrl_t newCrtlReg = {0};
    newCrtlReg.word = CrtlReg->word;
    newCrtlReg.csa = 0;
    newCrtlReg.cce = 1;
    newCrtlReg.init = 1;
    res = tcan4550_write_reg(ADDR_MCAN_CCCR, newCrtlReg.word);
    return res;
}

bool tcan4550_init(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_INFO(CAN, "init");
#endif
    CanPhy.cur.int_cnt = 0;
    GPIO_writeDio(DIO_CAN_SS, 1);
    // GPIO_writeDio(DIO_CAN_RST, 1);

    res = tcan4550_reset();

    res = is_tcan4550_connected();
    if(res) {
        res = tcan4550_clear_spi_err() && res;
        tCanRegIntEn_t ie;
        ie.word = 0;
        res = tcan4550_configure_interrupt(&ie) && res;

        tCanRegIntFl_t dev_ir = {0};
        dev_ir.word = 0;
        res = tcan4550_read_interrupt(&dev_ir) && res;
        if(res) {
            if(1 == dev_ir.pwron) {
                res = tcan4550_clear_interrupt(&dev_ir);
            }
        }

        res = tcan4550_set_bit_rate(CAN_BAUD_RATE_DFLT) && res;

        tCanRegDataBitTime_t data_time = {0};
        data_time.word = 0;
        data_time.dtseg1 = 15;
        data_time.dtseg2 = 5;
        data_time.dbrp = 1;

        tCanRegGloFiltCfg_t gfc = {0};
        gfc.word = 0;
        gfc.rrfe = 1;
        gfc.rrfs = 1;
        gfc.anfe = 0;
        gfc.anfs = 0;

        tCanRegCCctrl_t CrtlReg = {0};
        CrtlReg.fdoe = 0; // CAN FD mode enable
        CrtlReg.brse = 0; // CAN FD Bit rate switch enable

        /* ************************************************************************
         * In the next configuration block, we will set the MCAN core up to have:
         *   - 1 SID filter element
         *   - 1 XID Filter element
         *   - 5 RX FIFO 0 elements
         *   - RX FIFO 0 supports data payloads up to 64 bytes
         *   - RX FIFO 1 and RX Buffer will not have any elements, but we still set their data payload sizes, even
         * though it's not required
         *   - No TX Event FIFOs
         *   - 2 Transmit buffers supporting up to 64 bytes of data payload
         */
        TCAN4550_MRAM_Config MramConfig = {0};
        // Standard ID number of elements, you MUST have a filter written to MRAM for each element defined
        MramConfig.sid_num_elements = 1;
        // Extended ID number of elements, you MUST have a filter written to MRAM for each element defined
        MramConfig.xid_num_elements = 1;
        MramConfig.rx0_num_elements = 5;                      // RX0 Number of elements
        MramConfig.rx0_element_size = MRAM_8_BYTE_DATA;       // RX0 data payload size
        MramConfig.rx1_num_elements = 0;                      // RX1 number of elements
        MramConfig.rx1_element_size = MRAM_8_BYTE_DATA;       // RX1 data payload size
        MramConfig.rx_buf_num_elements = 0;                   // RX buffer number of elements
        MramConfig.rx_buf_element_size = MRAM_64_BYTE_DATA;   // RX buffer data payload size
        MramConfig.tx_event_fifo_num_elements = 0;            // TX Event FIFO number of elements
        MramConfig.tx_buffer_num_elements = 2;                // TX buffer number of elements
        MramConfig.tx_buffer_element_size = MRAM_8_BYTE_DATA; // TX buffer data payload size

        res = tcan4550_protected_registers_unlock() && res;
        res = tcan4550_configure_cccr_register(&CrtlReg) && res;
        res = tcan4550_configure_global_filter(&gfc) && res;

        res = tcan4550_configure_data_timing_simple(&data_time) && res; // Setup CAN FD timing
        res = tcan4550_clear_mram() && res;

        res = tcan4550_mram_cfg(&MramConfig) && res;
#ifndef HAS_DEBUG
        res = tcan4550_protected_registers_lock() && res;
#endif
        tCanRegIntEn_t mcan_ie = {0};
        mcan_ie.word = 0;
        mcan_ie.rf0ne = 1;
        mcan_ie.tce = 1;

        res = tcan4550_configure_mcan_interrupt(&mcan_ie) && res;

        /* Setup filters, this filter will mark any message with ID 0x055 as a priority message */
        tCan4550SidFilter_t StdFiltId = {0};
        StdFiltId.sft = TCAN4550_SID_SFT_CLASSIC; // SFT: Standard filter type. Configured as a classic filter
        StdFiltId.sfec = TCAN4550_SID_SFEC_PRIORITYSTORERX0; // Standard filter element configuration, store it in RX
                                                             // fifo 0 as a priority message
        StdFiltId.sfid1 = 0x055;                             // SFID1 (Classic mode Filter)
        StdFiltId.sfid2 = 0x7FF;                             // SFID2 (Classic mode Mask)
        res = tcan4550_write_sid_filter(0, &StdFiltId);      // Write to the MRAM

        tCanRegModeOpPinCfg_t dev_cfg_reg = {0};
        dev_cfg_reg.word = 0;

        dev_cfg_reg.wake_config = 0;
        dev_cfg_reg.swe_dis = 0;
        dev_cfg_reg.wd_timer = 3;
        dev_cfg_reg.clk_ref = 1;
        dev_cfg_reg.mode_sel = 2;
        dev_cfg_reg.wd_bit_set = 1;
        dev_cfg_reg.device_reset = 0;
        dev_cfg_reg.wd_en = 0;
        dev_cfg_reg.nwkrq_config = 0;
        res = tcan4550_device_configure(&dev_cfg_reg) && res;

        // Set to normal mode, since configuration is done. This line turns on the transceiver
        res = tcan4550_set_mode(MODE_NORMAL) && res;

        // Resets all MCAN interrupts (does NOT include any SPIERR interrupts)
        res = tcan4550_write_reg(ADDR_MCAN_IR, 0xFFFFFFFF) && res;
    }
    return res;
}

bool tcan4550_deinit(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_WARNING(CAN, "deinit");
#endif
    res = tcan4550_set_mode(MODE_SLEEP) && res;
    return res;
}

static uint32_t tcan4550_calc_bit_rate(tCanRegBitTime_t reg) {
    uint32_t bit_rate = 0;
    float tq = 0.0f;
    float can_bit_period = 0.0f;

    tq = ((float)(reg.nbrp + 1U)) * (1.0f / ((float)CAN_XTAL_HZ));
    can_bit_period = tq * ((float)((reg.ntseg1 + 2U) + (reg.ntseg2 + 1U)));
    bit_rate = (uint32_t)(1.0f / can_bit_period);

    return bit_rate;
}

uint32_t tcan4550_get_bit_rate(void) {
    bool res = false;
    uint32_t bit_rate = 0;
    tCanRegBitTime_t reg = {0};
    res = tcan4550_read_reg(ADDR_MCAN_NBTP, &reg.word);
    if(res) {
        bit_rate = tcan4550_calc_bit_rate(reg);
    }
    return bit_rate;
}

bool tcan4550_set_bit_rate(uint32_t des_bit_rate) {
    bool res = false;
    uint32_t calc_bit_rate = 0;
    tCanRegBitTime_t reg = {0};
    reg.nbrp = 0;
    reg.ntseg1 = 30;
    reg.ntseg2 = 7;
    reg.nsjw = reg.ntseg2;
    uint32_t nearest_bit_rate = 0;
    uint32_t min_abs_diff = 0xFFFFFFFF;
    uint32_t cur_abs_diff = 0xFFFFFFFF;
    uint16_t bit_rate_prescaler = 0;
    for(bit_rate_prescaler = 0; bit_rate_prescaler <= 0x1FF; bit_rate_prescaler++) {
        reg.nbrp = bit_rate_prescaler;
        calc_bit_rate = tcan4550_calc_bit_rate(reg);
        if(calc_bit_rate == des_bit_rate) {
#ifdef HAS_LOG
            LOG_INFO(CAN, "bit rate %u", calc_bit_rate);
#endif
            res = true;
            break;
        }
        cur_abs_diff = abs(calc_bit_rate - des_bit_rate);
        if(cur_abs_diff < min_abs_diff) {
            min_abs_diff = cur_abs_diff;
            nearest_bit_rate = calc_bit_rate;
        }
    }
    if(res) {
        res = tcan4550_set_lock(false);
        if(res) {
            res = tcan4550_write_reg(ADDR_MCAN_NBTP, reg.word);
            res = tcan4550_set_lock(true) && res;
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(CAN, "Unreal bit rate %u %u", des_bit_rate, nearest_bit_rate);
#endif
    }
    return res;
}

static bool tcan4550_poll_can_interrupts(void) {
    bool res = false;
    uint32_t clear_bits = 0;
    tCanRegInt_t IntReg = {0};
    res = tcan4550_read_reg(ADDR_MCAN_IR, &IntReg.word);
    if(res) {
        clear_bits = IntReg.word;

        if(IntReg.rf0n) {
            IntReg.rf0n = 0;
#ifdef HAS_CLI
            LOG_PARN(CAN, "RxFIFO0NewMessage");
#endif
            TCAN4x5x_MCAN_RX_Header MsgHeader = {0}; // Initialize to 0 or you'll get garbage
            uint8_t num_bytes = 0; // Used since the ReadNextFIFO function will return how many bytes of data were read
            uint8_t dataPayload[64] = {0}; // Used to store the received data

            num_bytes = TCAN4x5x_MCAN_ReadNextFIFO(RXFIFO0, &MsgHeader,
                                                   dataPayload); // This will read the next element in the RX FIFO 0
            if(num_bytes) {
#ifdef HAS_LOG
                LOG_PARN(CAN, "RxID %u=0x%x", MsgHeader.ID, MsgHeader.ID);
#ifdef HAS_CAN_DEBUG
                print_mem(dataPayload, num_bytes, true, true, true, true);
#endif /*HAS_CAN_DEBUG*/
#endif /*HAS_LOG*/
                res = can_proc_payload(dataPayload, num_bytes);
                res = true;
            }
        }
        if(IntReg.rf0f) {
            IntReg.rf0f = 0;
#ifdef HAS_LOG
#endif
        }

        if(IntReg.ped) {
            IntReg.ped = 0;
#ifdef HAS_LOG
            LOG_ERROR(CAN, "Protocol Error in Data Phase");
#endif
            tCanRegProtStat_t ProtoState = {0};
            res = tcan4550_read_reg(ADDR_MCAN_PSR, &ProtoState.word);
#ifdef HAS_LOG
            if(res) {
                tcan4550_parse_reg_proto_state(ProtoState.word);
            }
#endif
        }

        if(IntReg.bo) {
            IntReg.bo = 0;
#ifdef HAS_LOG
            LOG_WARNING(CAN, "Bus_Off Status");
#endif
        }

        if(IntReg.ew) {
            IntReg.ew = 0;
#ifdef HAS_LOG
            LOG_WARNING(CAN, "Warning Status");
#endif
        }

        if(IntReg.ep) {
            IntReg.ep = 0;
#ifdef HAS_LOG
            LOG_ERROR(CAN, "Error Passive");
#endif
        }
        if(IntReg.tsw) {
            IntReg.tsw = 0;
#ifdef HAS_TCAN_DEBUG
            LOG_DEBUG(CAN, "Timestamp Wraparound");
#endif
        }
        if(IntReg.hpm) {
            IntReg.hpm = 0;
#ifdef HAS_LOG
            LOG_INFO(CAN, "High Priority Message");
#endif
        }
        if(IntReg.pea) {
            IntReg.pea = 0;
#ifdef HAS_LOG
            LOG_ERROR(CAN, "ProtocolErrorInArbitrationPhase");
#endif
            tCanRegProtStat_t ProtoState = {0};
            res = tcan4550_read_reg(ADDR_MCAN_PSR, &ProtoState.word);
#ifdef HAS_LOG
            if(res) {
                tcan4550_parse_reg_proto_state(ProtoState.word);
            }
#endif
        }
        if(IntReg.word) {
#ifdef HAS_LOG
            LOG_ERROR(CAN, "UnProcessed Interrupt 0x%08x", IntReg.word);
#endif
        }

        if(clear_bits) {
            res = tcan4550_write_reg(ADDR_MCAN_IR, clear_bits);
        }
    }

    return res;
}
#ifdef HAS_CAN_POLLING
static bool tcan4550_poll_dev_interrupts(void) {
    bool res = false;
    uint32_t clear_bits = 0;
    tCanRegIntFl_t reg = {0};
    res = tcan4550_read_reg(ADDR_IF, &reg.word);
    if(res) {
        clear_bits = reg.word;
        if(reg.vtwd) {
            reg.vtwd = 0;
#ifdef HAS_LOG
            LOG_WARNING(CAN, "Global Voltage, Temp or WDTO");
#endif
        }
        if(reg.m_can_int) {
            reg.m_can_int = 0;
#ifdef HAS_LOG
            LOG_DEBUG(CAN, "M_CAN global INT");
#endif
        }
        if(reg.spierr) {
            reg.spierr = 0;
#ifdef HAS_LOG
            LOG_WARNING(CAN, "SpiError");
#endif
            // TODO Explore SPI error
            tCanRegStatus_t stat_reg = {0};
            res = tcan4550_read_reg(ADDR_SPI_STATUS, &stat_reg.word);
#ifdef HAS_LOG
            if(res) {
                res = tcan4550_parse_reg_status(stat_reg.word);
            }
#endif
            res = tcan4550_clear_spi_err();
        }
        if(reg.canerr) {
            reg.canerr = 0;
#ifdef HAS_LOG
            LOG_DEBUG(CAN, "CANError");
#endif
        }
        if(reg.wkrq) {
            reg.wkrq = 0;
#ifdef HAS_LOG
            LOG_WARNING(CAN, "Wake Request");
#endif
        }
        if(reg.globalerr) {
            reg.globalerr = 0;
#ifdef HAS_LOG
            LOG_DEBUG(CAN, "Global Error (Any Fault)");
#endif
        }
        if(reg.candom) {
#ifdef HAS_LOG
            LOG_WARNING(CAN, "CAN Stuck Dominant");
#endif
        }
        if(reg.canslnt) {
            reg.canslnt = 0;
#ifdef HAS_LOG
            LOG_DEBUG(CAN, "CAN Silent");
#endif
        }
        if(reg.wkerr) {
            reg.wkerr = 0;
#ifdef HAS_LOG
            LOG_WARNING(CAN, "Wake Error");
#endif
        }
        if(reg.lwu) {
            reg.lwu = 0;
#ifdef HAS_LOG
            LOG_WARNING(CAN, "Local Wake Up");
#endif
        }
        if(reg.canint) {
            reg.canint = 0;
#ifdef HAS_LOG
            LOG_WARNING(CAN, "Can Bus Wake Up Interrupt");
#endif
        }
        if(reg.eccerr) {
            reg.eccerr = 0;
#ifdef HAS_LOG
            LOG_WARNING(CAN, "Uncorrectable ECC error detected");
#endif
        }
        if(reg.wdto) {
            reg.wdto = 0;
#ifdef HAS_LOG
            LOG_WARNING(CAN, "Watchdog Time Out");
#endif
        }
        if(reg.tsd) {
            reg.tsd = 0;
#ifdef HAS_LOG
            LOG_WARNING(CAN, "Thermal Shutdown ");
#endif
        }
        if(reg.pwron) {
            reg.pwron = 0;
#ifdef HAS_LOG
            LOG_WARNING(CAN, "Power ON");
#endif
        }
        if(reg.uvio) {
            reg.uvio = 0;
#ifdef HAS_LOG
            LOG_WARNING(CAN, "Under Voltage VIO");
#endif
        }
        if(reg.uvsup) {
            reg.uvsup = 0;
#ifdef HAS_LOG
            LOG_WARNING(CAN, "Under Voltage VSUP and UVCCOUT");
#endif
        }
        if(reg.sms) {
            reg.sms = 0;
#ifdef HAS_LOG
            LOG_WARNING(CAN, "Sleep Mode Status");
#endif
        }
        if(reg.canbusnom) {
            reg.canbusnom = 0;
#ifdef HAS_LOG
            LOG_WARNING(CAN, "CAN Bus normal");
#endif
        }

        if(reg.word) {
#ifdef HAS_LOG
            LOG_WARNING(CAN, "IntReg 0x%08x", reg.word);
#endif
        }

        if(clear_bits) {
            res = tcan4550_write_reg(ADDR_IF, clear_bits);
        }
    }

    return res;
}
#endif

bool tcan4550_poll_interrupts(void) {
    bool res = true;
#ifdef HAS_CAN_POLLING
    res = tcan4550_poll_dev_interrupts() && res;
#endif
    res = tcan4550_poll_can_interrupts() && res;
    return res;
}

bool tcan4550_proc(void) {
    bool res = false;
#ifdef HAS_CAN_POLLING
    static CanDevMode_t prev_mode = MODE_UNDEF;
#endif
    // CanPhy.cur.connected = is_tcan4550_connected();
    CanPhy.cur.connected = true;
    if(false == CanPhy.cur.connected) {
#ifdef HAS_LOG
        LOG_ERROR(CAN, "TCAN4550_SpiLinkLost");
#endif
        res = init_tcan();
    } else {
#ifdef HAS_CAN_POLLING
        tCanRegCCctrl_t ctrl_reg = {0};
        tCanRegProtStat_t proto_stat = {0};
        res = tcan4550_read_reg(ADDR_MCAN_PSR, &proto_stat.word);
        if(res) {
            CanPhy.cur.lec = (LastErrorCode_t)proto_stat.lec;
        }

        CanPhy.cur.lock = is_tcan4550_protected_reg_locked(&ctrl_reg);
        tCanRegModeOpPinCfg_t ModeOpPinCfg = {0};
        ModeOpPinCfg.word = 0;
        res = tcan4550_read_reg(ADDR_DEV_CONFIG, &ModeOpPinCfg.word);
        if(res) {
            if(ModeOpPinCfg.wd_en) {
                CanPhy.cur.wdt = true;
            } else {
                CanPhy.cur.wdt = false;
            }
        }
        CanPhy.cur.bit_rate = tcan4550_get_bit_rate();
        CanPhy.cur.mode = tcan4550_get_mode();
        if(prev_mode != CanPhy.cur.mode) {
#ifdef HAS_LOG
            LOG_INFO(CAN, "NewMode %s", can_mode2str(CanPhy.cur.mode));
#endif
        }
#endif

        res = tcan4550_poll_interrupts();
        uint8_t fifo_num = 0;
        uint8_t elements = 0;
        uint8_t frame = 0;
        uint8_t rx_payload[64] = {0};
        for(fifo_num = 0; fifo_num < RX_FIFO_CNT; fifo_num++) {
            elements = tcan4550_get_fifo_cnt(fifo_num);
            frame = 0;
            for(frame = 0; frame < elements; frame++) {
                TCAN4x5x_MCAN_RX_Header MsgHeader = {0};
                uint8_t rx_size = 0;
                rx_size = TCAN4x5x_MCAN_ReadNextFIFO((TCAN4x5x_MCAN_FIFO_Enum)fifo_num, &MsgHeader,
                                                     rx_payload); // This will read the next element in the RX FIFO 0
                if(rx_size) {
#ifdef HAS_LOG
                    LOG_PARN(CAN, "RxID %u=0x%x", MsgHeader.ID, MsgHeader.ID);
#ifdef HAS_CAN_DEBUG
                    print_mem(rx_payload, rx_size, true, true, true, true);
#endif
#endif
#ifdef LED_INDEX_BLUE
                    led_blink(&Led[LED_INDEX_BLUE], 600);
#endif
                    res = can_proc_payload(rx_payload, rx_size);
                }
            }
        }
#ifdef HAS_CAN_POLLING
        prev_mode = CanPhy.cur.mode;
#endif
    }

    return res;
}

uint8_t tcan4550_get_fifo_cnt(uint8_t fifo_num) {
    uint8_t size = 0;
    bool res = false;
    if(0 == fifo_num) {
        tCanRegFiFo0Stat_t fifo0 = {0};
        res = tcan4550_read_reg(ADDR_MCAN_RXF0S, &fifo0.word);
        if(res) {
            size = fifo0.f0fl;
        }
    } else if(0 == fifo_num) {
        tCanRegFiFo1Stat_t fifo1 = {0};
        res = tcan4550_read_reg(ADDR_MCAN_RXF1S, &fifo1.word);
        if(res) {
            size = fifo1.f1fl;
        }
    } else {
    }
    return size;
}
