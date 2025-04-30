#include "i2c_mcal.h"

#include "stm32f4xx_hal.h"
#include "i2c_custom_diag.h"

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef* hi2c) {
    int8_t num;
    num = get_i2c_index(hi2c->Instance);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->tx_cnt++;
        Node->tx_cpl_cnt++;
        Node->tx_int = true;
        Node->tx_done = true;
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
        Node->tx_done = true;
    }
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef* hi2c) {
    int8_t num = 0;
    num = get_i2c_index(hi2c->Instance);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->rx_cnt++;
        Node->rx_int = true;
        Node->rx_done = true;
    }
}

/*
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
        Node->rx_done = true;
    }
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

void HAL_I2C_AbortCpltCallback(I2C_HandleTypeDef* hi2c) {
    int8_t num;
    num = get_i2c_index(hi2c->Instance);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
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
