#include "i2c_drv.h"

#include <stdbool.h>
#include <string.h>

#include "debug_info.h"
#include "hal_diag.h"
#include "i2c_types.h"
#include "log.h"
#include "at32f435_437.h"
#include "time_mcal.h"

static int8_t get_i2c_index(I2C_TypeDef* I2Cx) {
    int8_t num = -1;
#ifdef I2C1
    if(I2C1 == I2Cx) { /*APB1*/
        num = 1;
    }
#endif /*I2C1*/

#ifdef I2C2
    if(I2C2 == I2Cx) {
        num = 2;
    }
#endif /*I2C2*/

#ifdef I2C3
    if(I2C3 == I2Cx) {
        num = 3;
    }
#endif /*I2C2*/

    return num;
}

I2C_TypeDef* i2c_get_instance(uint8_t num) {
    I2C_TypeDef* I2Cx = NULL;
    switch(num) {
#ifdef I2C1
    case 1:
        I2Cx = I2C1;
        break;
#endif /*I2C1*/

#ifdef I2C2
    case 2:
        I2Cx = I2C2;
        break;
#endif /*I2C2*/

#ifdef I2C3
    case 3:
        I2Cx = I2C3;
        break;
#endif /*I2C3*/

    default:
        I2Cx = NULL;
        break;
    }
    return I2Cx;
}

bool i2c_init_ll(uint8_t num) {
    bool res = true;
    LOG_WARNING(I2C, "I2C%u Init ", num);
    I2C_TypeDef* I2Cx = NULL;
    I2cHandle_t* Node = I2cGetNode(num);
    const I2cConfig_t* Config = NULL;
    HAL_StatusTypeDef ret = HAL_ERROR;
    if(Node) {
        I2Cx = i2c_get_instance(num);
        if(I2Cx) {
            Config = I2cGetConfig(num);
            if(Config) {
                res = true;
            } else {
                LOG_ERROR(I2C, "ConfigErr");
                res = false;
            }
        } else {
            LOG_ERROR(I2C, "InstanceErr");
            res = false;
        }
    } else {
        LOG_ERROR(I2C, "HandleErr");
        res = false;
    }

    if(res) {
        Node->i2c_h.Instance = I2Cx;
        /*TODO add clock speed check*/
        Node->i2c_h.Init.ClockSpeed = Config->clock_speed;
        Node->i2c_h.Init.DutyCycle = I2C_DUTYCYCLE_2;
        Node->i2c_h.Init.OwnAddress1 = 0;
        Node->i2c_h.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
        Node->i2c_h.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
        Node->i2c_h.Init.OwnAddress2 = 0;
        Node->i2c_h.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
        Node->i2c_h.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

        ret = HAL_I2C_Init((I2C_HandleTypeDef*)&Node->i2c_h);
        if(HAL_OK == ret) {
            res = true;
            LOG_INFO(I2C, "%u Init " LOG_OK, num);
            Node->init_done = true;
        } else {
            LOG_ERROR(I2C, "%u Init" LOG_ER " %s", num, HalStatus2Str(ret));
            res = false;
        }
    } else {
        LOG_ERROR(I2C, "%u Conf " LOG_ER, num);
    }
    return res;
}

bool i2c_init(void) {
    bool res = false;
    uint8_t cnt = 0;
    LOG_WARNING(I2C, "Init");
#ifdef HAS_I2C1
    cnt += (uint8_t)i2c_init_ll(1);
#endif /*HAS_I2C1*/

#ifdef HAS_I2C2
    cnt += (uint8_t)i2c_init_ll(2);
#endif /*HAS_I2C2*/

#ifdef HAS_I2C3
    cnt += (uint8_t)i2c_init_ll(3);
#endif /*HAS_I2C3*/

    if(cnt) {
        res = true;
        LOG_INFO(I2C, "Init %u I2Cs", cnt);
    } else {
        res = false;
    }
    return res;
}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle) {

#ifdef HAS_I2C1
    if(I2C1 == i2cHandle->Instance) {
        __HAL_RCC_I2C1_CLK_ENABLE();

        HAL_NVIC_SetPriority(I2C1_EV_IRQn, 5, 5);
        HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);

        HAL_NVIC_SetPriority(I2C1_ER_IRQn, 5, 5);
        HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
    }
#endif /*HAS_I2C1*/

#ifdef HAS_I2C2
    if(I2C2 == i2cHandle->Instance) {
        __HAL_RCC_I2C2_CLK_ENABLE();

        HAL_NVIC_SetPriority(I2C2_EV_IRQn, 5, 5);
        HAL_NVIC_EnableIRQ(I2C2_EV_IRQn);

        HAL_NVIC_SetPriority(I2C2_ER_IRQn, 5, 5);
        HAL_NVIC_EnableIRQ(I2C2_ER_IRQn);
    }
#endif /*HAS_I2C2*/

#ifdef HAS_I2C3
    if(I2C3 == i2cHandle->Instance) {
        __HAL_RCC_I2C3_CLK_ENABLE();

        HAL_NVIC_SetPriority(I2C3_EV_IRQn, 5, 5);
        HAL_NVIC_EnableIRQ(I2C3_EV_IRQn);

        HAL_NVIC_SetPriority(I2C3_ER_IRQn, 5, 5);
        HAL_NVIC_EnableIRQ(I2C3_ER_IRQn);
    }
#endif /*HAS_I2C3*/
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle) {
#ifdef HAS_I2C1
    if(I2C1 == i2cHandle->Instance) {
        __HAL_RCC_I2C1_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
        HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
    }
#endif

#ifdef HAS_I2C2
    if(I2C2 == i2cHandle->Instance) {
        __HAL_RCC_I2C2_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(I2C2_EV_IRQn);
        HAL_NVIC_DisableIRQ(I2C2_ER_IRQn);
    }
#endif

#ifdef HAS_I2C3
    if(I2C3 == i2cHandle->Instance) {
        __HAL_RCC_I2C3_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(I2C3_EV_IRQn);
        HAL_NVIC_DisableIRQ(I2C3_ER_IRQn);
    }
#endif
}

bool i2c_api_write(uint8_t num, uint8_t chip_addr, const uint8_t* const array, size_t size) {
    bool res = false;
    uint8_t i2c_addr = chip_addr;
    i2c_addr = i2c_compose_write_address(chip_addr);
    LOG_DEBUG(I2C, "%u Write Chip:0x%x Len: %u", num, i2c_addr, size);
    HAL_StatusTypeDef ret;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node && array && (0 < size)) {
        uint32_t init_tx_cnt = Node->tx_cnt;
        Node->tx_int = false;
        ret = HAL_I2C_Master_Transmit_IT((I2C_HandleTypeDef*)&Node->i2c_h, (uint16_t)i2c_addr, array, size);
        if(HAL_OK == ret) {
            res = true;
            uint32_t cnt = 0;
            while(init_tx_cnt == Node->tx_cnt) {
                cnt++;
                if(0x0027ffff < cnt) {
                    res = false;
                    break;
                }
            }
        } else {
            res = false;
            LOG_ERROR(I2C, "I2C%u TxErr %u=%s", num, ret, HalStatus2Str(ret));
            i2c_init_ll(num);
        }
    }
    return res;
}

bool i2c_api_write_reg(uint8_t num, uint8_t chip_addr, uint8_t addr, uint8_t reg_val) {
    bool res = false;
    LOG_DEBUG(I2C, "%u WriteReg ChipID 0x%02x RegAddr:0x%02X Val:0x%02X", num, chip_addr, addr, reg_val);
    uint8_t frame[2] = {addr, reg_val};
    res = i2c_api_write(num, chip_addr, &frame[0], 2);
    return res;
}

bool i2c_api_read(uint8_t num, uint8_t chip_addr, uint8_t* array, uint32_t size) {
    bool res = false;
    uint8_t i2c_addr = chip_addr;
    i2c_addr = i2c_compose_read_address(chip_addr);
    LOG_DEBUG(I2C, "%u Read Chip:0x%x Len: %u", num, i2c_addr, size);
    HAL_StatusTypeDef ret;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->rx_int = false;
        ret = HAL_I2C_Master_Receive_IT(&Node->i2c_h, (uint16_t)i2c_addr, array, (uint16_t)size);
        if(HAL_OK == ret) {
            res = true;

            uint32_t diff = 0;
            res = I2cWaitRxDoneTimeOut(Node,3000, &diff);

            if(res) {
                LOG_DEBUG(I2C, "I2C%u ReadOk", num);
            } else {
                LOG_ERROR(I2C, "I2C%u ReadTimeOut", num);
            }

        } else {
            LOG_ERROR(I2C, "I2C%u, RxErr %u=%s", num, ret, HalStatus2Str(ret));
            i2c_init_ll(num);
        }
    }else {
        LOG_ERROR(I2C, "Node" LOG_ER);
    }
    return res;
}

bool i2c_send_signal(uint8_t num, I2cSignal_t signal) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        switch(signal) {
        case I2C_START:
            /* Generate Start */
            SET_BIT(Node->i2c_h.Instance->CR1, I2C_CR1_START);
            res = true;
            break;
        case I2C_STOP:
            /* Generate Stop */
            SET_BIT(Node->i2c_h.Instance->CR1, I2C_CR1_STOP);
            res = true;
            break;
        default:
            res = false;
            break;
        }
    } else {
        LOG_ERROR(I2C, "Node" LOG_ER);
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
    uint8_t i2c_addr = chip_addr;
    i2c_addr = i2c_compose_read_address(chip_addr);
    LOG_DEBUG(I2C, "I2C%u Read, Chip 0x%x, Reg 0x%x", num, chip_addr, addr);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        // uint32_t init_rx_cnt = Node->rx_cnt;
        HAL_StatusTypeDef ret = 0;
        Node->rx_int = false;
        ret = HAL_I2C_Mem_Read_IT(&Node->i2c_h, (uint16_t)i2c_addr, addr, 1, value, 1);
        if(HAL_OK == ret) {

            res = true;
            uint32_t cnt = 0;
            while(false == Node->rx_int) {
                cnt++;
                if(0x001FFFFF < cnt) {
                    res = false;
                    break;
                }
            }
            if(res) {
                LOG_DEBUG(I2C, "I2C%u MemReadOk", num);
            }

        } else {
            LOG_ERROR(I2C, "I2C%u RegReadErr %s, RegAddr:0x%04x", num, HalStatus2Str(ret), (uint16_t)addr);
            i2c_init_ll(num);
            res = false;
        }
    }
    return res;
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef* hi2c) {
    int8_t num;
    num = get_i2c_index(hi2c->Instance);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->tx_cnt++;
        Node->tx_cpl_cnt++;
        Node->tx_int = true;
    }
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef* hi2c) {
    int8_t num = 0;
    num = get_i2c_index(hi2c->Instance);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->rx_cnt++;
        Node->rx_int = true;
    }
}

/**
 * @brief  Memory Rx Transfer completed callback.
 * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
 *                the configuration information for the specified I2C.
 * @retval None
 */
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef* hi2c) {
    /* Prevent unused argument(s) compilation warning */
    int8_t num = 0;
    num = get_i2c_index(hi2c->Instance);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->rx_cnt++;
        Node->rx_int = true;
    }

    /* NOTE : This function should not be modified, when the callback is needed,
              the HAL_I2C_MemRxCpltCallback could be implemented in the user file
     */
}

#ifdef HAS_I2C_SLAVE
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef* hi2c) {
    int8_t num;
    num = get_i2c_index(hi2c->Instance);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
    }
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef* hi2c) {
    int8_t num;
    num = get_i2c_index(hi2c->Instance);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
    }
}
#endif /*HAS_I2C_SLAVE*/

void HAL_I2C_AddrCallback(I2C_HandleTypeDef* hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode) {
    int8_t num;
    num = get_i2c_index(hi2c->Instance);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
    }
}

void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef* hi2c) {
    int8_t num;
    num = get_i2c_index(hi2c->Instance);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
    }
}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef* hi2c) {
    int8_t num;
    num = get_i2c_index(hi2c->Instance);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->tx_cnt++;
        Node->tx_cpl_cnt++;
        Node->tx_int = true;
    }
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef* hi2c) {
    int8_t num;
    num = get_i2c_index(hi2c->Instance);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->error_cnt++;
    }
}

void HAL_I2C_AbortCpltCallback(I2C_HandleTypeDef* hi2c) {
    int8_t num;
    num = get_i2c_index(hi2c->Instance);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
    }
}

static bool i2c_master_check_addr(I2C_HandleTypeDef* hi2c, uint16_t DevAddress) {
    bool res = false;
    /* Init tickstart for timeout management*/
    uint32_t tickstart = HAL_GetTick();

    if(HAL_I2C_STATE_READY == hi2c->State) {
        /* Wait until BUSY flag is reset */
        if(HAL_OK == I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, 25, tickstart)) {
            /* Process Locked */
            __HAL_LOCK(hi2c);

            /* Check if the I2C is already enabled */
            if((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE) {
                /* Enable I2C peripheral */
                __HAL_I2C_ENABLE(hi2c);
            }

            /* Disable Pos */
            CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

            hi2c->State = HAL_I2C_STATE_BUSY_TX;
            hi2c->Mode = HAL_I2C_MODE_MASTER;
            hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

            /* Prepare transfer parameters */
            hi2c->pBuffPtr = NULL;
            hi2c->XferCount = 0;
            hi2c->XferSize = hi2c->XferCount;
            hi2c->XferOptions = 0xFFFF0000U;

            /* Send Slave Address */
            if(HAL_OK == I2C_MasterRequestWrite(hi2c, DevAddress, 1000, tickstart)) {
                /* Clear ADDR flag */
                __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

                /* Generate Stop */
                SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

                hi2c->State = HAL_I2C_STATE_READY;
                hi2c->Mode = HAL_I2C_MODE_NONE;

                /* Process Unlocked */
                __HAL_UNLOCK(hi2c);
                res = true;
            }
        }
    }

    return res;
}

bool i2c_check_addr(uint8_t num, uint8_t i2c_addr) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        res = i2c_master_check_addr(&Node->i2c_h, i2c_addr);
    }
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

bool i2c_api_read_mem(uint8_t num, uint8_t chip_addr, uint8_t* const addr, size_t addr_size, uint8_t* const data,
                      size_t size) {
    bool res = false;
    uint8_t i2c_addr = chip_addr;
    i2c_addr = i2c_compose_read_address(chip_addr);
    LOG_DEBUG(I2C, "I2C%u ReadMem,Chip:0x%x,Reg:0x%02x=0x%04x,AdrSize:%u Byte,DataToRx:%u Byte", num, chip_addr, *addr,
              (uint16_t)*addr, addr_size, size);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        // uint32_t init_rx_cnt = Node->rx_cnt;
        HAL_StatusTypeDef ret = 0;
        Node->rx_int = false;
        uint16_t addr_u16 = RegAddr2Word(addr, addr_size);
        ret = HAL_I2C_Mem_Read_IT(&Node->i2c_h, (uint16_t)i2c_addr, addr_u16, addr_size, data, size);
        if(HAL_OK == ret) {
            res = true;
            uint32_t diff = 0;
            uint32_t start = time_get_ms32();
            while(1) {
                uint32_t cur = time_get_ms32();
                diff = cur - start;
                if(3000 < diff) {
                    res = false;
                    break;
                }

                if(Node->rx_int) {
                    break;
                    res = true;
                }
            }
            if(res) {
                LOG_DEBUG(I2C, "I2C%u MemReadOk,waited:%ums", num,diff);
            } else {
                LOG_ERROR(I2C, "I2C%u MemReadTimeOut", num);
            }
        } else {
            LOG_ERROR(I2C, "I2C%u MemReadErr %u=%s", num, ret, HalStatus2Str(ret));
            i2c_init_ll(num);
            res = false;
        }
    } else {
        LOG_ERROR(I2C, "I2C%u NodeErr", num);
    }
    return res;
}
