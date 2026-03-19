#include "i2c_fsm.h"

#include <string.h>

#include "i2c_fsm_custom.h"
#include "i2c_mcal.h"
#include "log.h"
#include "std_includes.h"
#include "time_mcal.h"

static bool i2c_fsm_proc_iteration(I2cHandle_t* const Node) {
    bool res = false;
#ifdef HAS_I2C_FSM_DIAG
    LOG_DEBUG(I2C_FSM, "I2C%u,%s", Node->num, I2cFsmNodeToStr(Node));
#endif
    switch(Node->fsm_state) {

    case I2C_FSM_STATE_IDLE:
        res = i2c_fsm_proc_frame_idle(Node);
        break;

    case I2C_FSM_STATE_WAIT_START1:
        res = i2c_fsm_proc_frame_wait_start1_done(Node);
        break;

    case I2C_FSM_STATE_WAIT_TX_7BIT_ADDR:
        res = i2c_fsm_proc_frame_wait_tx_7bitaddr_done(Node);
        break;

    case I2C_FSM_STATE_WAIT_TX_DATA:
        res = i2c_fsm_proc_frame_wait_tx_data_done(Node);
        break;

    case I2C_FSM_STATE_WAIT_START2:
        res = i2c_fsm_proc_frame_wait_start2_done(Node);
        break;

    case I2C_FSM_STATE_WAIT_TX_STOP:
        res = i2c_fsm_proc_frame_wait_stop_done(Node);
        break;

    case I2C_FSM_STATE_WAIT_TX_CHIP_READ_ADDR:
        res = i2c_fsm_proc_frame_wait_chip_read_addr_done(Node);
        break;

    case I2C_FSM_STATE_WAIT_READ_DATA:
        res = i2c_fsm_proc_frame_wait_read_data(Node);
        break;

    case I2C_FSM_STATE_WAIT_BUSY:
        res = i2c_fsm_proc_frame_wait_busy(Node);
        break;

    default: {
        LOG_ERROR(I2C_FSM, "I2C%u,UndefState:%u", Node->num, Node->fsm_state);
        res = false;
    } break;
    }

    if(I2C_FSM_INPUT_TIME_OUT == Node->fsm_input) {
        Node->loop = false;
    }

    return res;
}

static bool i2c_fsm_proc_in_timeout(I2cHandle_t* Node) {
    bool res = false;
    uint32_t cur_ms = time_get_ms32();
    uint32_t diff_ms = cur_ms - Node->start_ms;
    if(I2C_FSM_TIMEOUT_MS < diff_ms) {
        Node->fsm_input = I2C_FSM_INPUT_TIME_OUT;
        res = i2c_fsm_proc_timeout(Node);
        // break;
    }
    return res;
}

static bool i2c_fsm_proc_frame(I2cHandle_t* Node) {
    bool res = false;
    res = i2c_interrupts_disable_ll(Node);
    if(res) {
        Node->spin_cnt = 0;
        Node->loop = true;
        Node->fsm_state = I2C_FSM_STATE_IDLE;
        Node->start_ms = time_get_ms32();
        while(Node->loop) {
            res = i2c_fsm_proc_in_timeout(Node);
            res = i2c_fsm_input_get(Node);

            res = i2c_fsm_proc_iteration(Node);
            if(false == res) {
                LOG_DEBUG(I2C_FSM, "Iter:%u,Err", Node->spin_cnt);
            }
            Node->spin_cnt++;
        }
        LOG_NOTICE(I2C_FSM, "SpinCnt:%u ", Node->spin_cnt);
    } else {
        LOG_ERROR(I2C_FSM, "DisableIRQerr");
    }

    return res;
}

__attribute__((weak)) bool i2c_fsm_enable(I2cHandle_t* const Node) {
    bool res = false;
    return res;
}

bool i2c_fsm_write_byte(uint8_t num, uint8_t chip_base_addr, uint8_t addr, uint8_t reg_val) {
    bool res = false;
    LOG_DEBUG(I2C_FSM, "I2C%u,Write,Chip:0x%02x,RegAddr:0x%02x,Byte:0x%02x", num, chip_base_addr, addr, reg_val);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->spot_chip = false;
        uint8_t buff[2] = {0};
        buff[0] = addr;
        buff[1] = reg_val;

        Node->TxData = buff;
        Node->TxDataSize = 2;
        Node->tx_index = 0;

        Node->RxData = NULL;
        Node->RxDataSize = 0;
        Node->rx_index = 0;

        Node->slave_addr = chip_base_addr;
        Node->fsm_operation = I2C_FSM_OPERATION_WRITE;
        Node->fsm_input = I2C_FSM_INPUT_NONE;

        Node->fsm_input_exist = true;

        res = i2c_fsm_proc_frame(Node);
    }

    return res;
}

bool i2c_fsm_read_mem(uint8_t num, uint8_t chip_base_addr, uint8_t* const addr, size_t addr_size, uint8_t* const data,
                      size_t size) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
    }

    return res;
}

bool i2c_fsm_write_word(uint8_t num, uint8_t chip_base_addr, const uint16_t word) {
    bool res = false;
    LOG_DEBUG(I2C_FSM, "I2C%u,WriteWord,Chip:0x%02x,Word:0x%04x", num, chip_base_addr, word);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->spot_chip = false;

        Node->TxData = (uint8_t*)&word;
        Node->TxDataSize = 2;
        Node->tx_index = 0;

        Node->RxData = NULL;
        Node->RxDataSize = 0;
        Node->rx_index = 0;

        Node->slave_addr = chip_base_addr;
        Node->fsm_operation = I2C_FSM_OPERATION_WRITE;
        Node->fsm_input = I2C_FSM_INPUT_NONE;
        Node->fsm_input_exist = true;

        res = i2c_fsm_proc_frame(Node);
    }

    return res;
}

// see Figure 11-5 Transfer sequence of I2C master transmitter
bool i2c_fsm_read_word(uint8_t num, uint8_t chip_base_addr, uint8_t word_addr, uint16_t* const word) {
    bool res = false;
    LOG_DEBUG(I2C_FSM, "I2C%u,Read,Chip:0x%02x,WordAddr:0x%02x", num, chip_base_addr, word_addr);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        static uint8_t tx_data = 0;
        tx_data = word_addr;
        Node->TxData = &tx_data;
        Node->TxDataSize = 1;
        Node->tx_index = 0;
        Node->spot_chip = false;
        Node->RxData = (uint8_t*)word;
        Node->RxDataSize = 2;
        Node->rx_index = 0;

        res = i2c_clear_events(Node);
        Node->slave_addr = chip_base_addr;
        Node->fsm_operation = I2C_FSM_OPERATION_READ_MEM;
        Node->fsm_input = I2C_FSM_INPUT_NONE;
        Node->fsm_input_exist = true;

        res = i2c_fsm_proc_frame(Node);

        uint16_t read_word = 0;
        memcpy(&read_word, Node->RxData, 2);
        LOG_DEBUG(I2C_FSM, "I2C%u,RxWord:0x%04x", num, read_word);
    }

    return res;
}

bool i2c_fsm_wait_busy(I2cHandle_t* Node) {
    bool res = false;
    Node->start_ms = time_get_ms32();
    Node->loop = true;
    Node->fsm_input = I2C_FSM_INPUT_NONE;
    Node->fsm_state = I2C_FSM_STATE_WAIT_BUSY;
    Node->spin_cnt = 0;
    res = i2c_fsm_enable(Node);
    while(Node->loop) {
        res = i2c_fsm_input_get(Node);
        res = i2c_fsm_proc_iteration(Node);

        res = i2c_fsm_proc_in_timeout(Node);

        if(I2C_FSM_STATE_IDLE == Node->fsm_state) {
            Node->loop = false;
            res = true;
        }
        Node->spin_cnt++;
    }
    return res;
}

bool i2c_fsm_check_addr(uint8_t num, uint8_t i2c_addr) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->spot_chip = false;
        Node->RxData = NULL;
        Node->RxDataSize = 0;
        Node->TxData = NULL;
        Node->TxDataSize = 0;

        Node->slave_addr = i2c_addr;
        Node->fsm_operation = I2C_FSM_OPERATION_CHECK_ADDR;
        Node->fsm_input = I2C_FSM_INPUT_GENERATE_START;
        Node->fsm_input_exist = true;

        res = i2c_fsm_proc_frame(Node);
        res = Node->spot_chip;
    }
    return res;
}

bool i2c_fsm_read_byte(uint8_t num, uint8_t chip_base_addr, uint8_t addr, uint8_t* value) {
    bool res = false;
    LOG_DEBUG(I2C_FSM, "I2C%u,Read,Chip:0x%02x,Reg:0x%02x", num, chip_base_addr, addr);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->spot_chip = false;
        Node->RxData = value;
        Node->RxDataSize = 1;
        Node->rx_index = 0;
        Node->TxData = &addr;
        Node->TxDataSize = 1;
        Node->tx_index = 0;

        Node->slave_addr = chip_base_addr;
        Node->fsm_operation = I2C_FSM_OPERATION_READ_MEM;
        Node->fsm_input = I2C_FSM_INPUT_NONE;

        Node->fsm_input_exist = true;

        res = i2c_fsm_proc_frame(Node);
        res = Node->spot_chip;
    }

    return res;
}

bool i2c_fsm_init_one(uint8_t num) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        res = i2c_fsm_init_one_ll(Node);
    }
    return res;
}

bool i2c_fsm_write_byte_verify(uint8_t num, uint8_t chip_base_addr, uint8_t reg_addr, uint8_t set_value) {
    bool res = false;
    res = i2c_fsm_write_byte(num, chip_base_addr, reg_addr, set_value);
    if(res) {
        res = false;
        uint8_t get_value = 0;
        res = i2c_fsm_read_byte(num, chip_base_addr, reg_addr, &get_value);
        if(res) {
            res = false;
            if(get_value == set_value) {
                res = true;
            }
        }
    }

    return res;
}

bool i2c_fsm_read(uint8_t num, uint8_t chip_base_addr, uint8_t* data, uint32_t size) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->fsm_operation = I2C_FSM_OPERATION_RAED;
        Node->RxData = data;
        Node->RxDataSize = size;
        Node->TxData = NULL;
        Node->TxDataSize = 0;

        Node->slave_addr = chip_base_addr;
        Node->fsm_input = I2C_FSM_INPUT_GENERATE_START;

        res = i2c_fsm_proc_frame(Node);
    }

    return res;
}

bool i2c_fsm_write(uint8_t num, uint8_t chip_base_addr, const uint8_t* const array, size_t size) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->fsm_operation = I2C_FSM_OPERATION_WRITE;
        Node->TxData = array;
        Node->TxDataSize = size;
        Node->RxData = NULL;
        Node->RxDataSize = 0;

        Node->slave_addr = chip_base_addr;
        Node->fsm_input = I2C_FSM_INPUT_GENERATE_START;

        res = i2c_fsm_proc_frame(Node);
    }

    return res;
}

// Start and stop
static bool i2c_fsm_empty_ll(I2cHandle_t* Node) {
    bool res = false;
    if(Node) {
        Node->spot_chip = false;
        Node->RxData = NULL;
        Node->RxDataSize = 0;
        Node->TxData = NULL;
        Node->TxDataSize = 0;

        Node->slave_addr = 0;
        Node->fsm_operation = I2C_FSM_OPERATION_EMPTY;
        Node->fsm_input = I2C_FSM_INPUT_GENERATE_START;
        Node->fsm_input_exist = true;

        res = i2c_fsm_proc_frame(Node);
    }
    return res;
}

bool i2c_fsm_empty(uint8_t num) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        res = i2c_fsm_empty_ll(Node);
    }
    return res;
}

bool i2c_fsm_init_one_ll(I2cHandle_t* Node) {
    bool res = false;
    if(Node) {
        LOG_WARNING(I2C_FSM, "I2C_FSM_%u,Init", Node->num);
        Node->slave_addr = 0;
        Node->fsm_operation = I2C_FSM_OPERATION_NOP;
        Node->fsm_state = I2C_FSM_STATE_IDLE;
        Node->fsm_input = I2C_FSM_INPUT_NONE;
        Node->fsm_input_cnt = 0;
        Node->TxDataSize = 0;
        Node->RxDataSize = 0;
        Node->RxData = 0;
        Node->TxData = 0;
        res = true;
    } else {
        LOG_ERROR(I2C_FSM, "No,Node");
    }

    return res;
}
