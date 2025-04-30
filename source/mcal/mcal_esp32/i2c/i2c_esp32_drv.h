
#ifndef I2C_DRV_H
#define I2C_DRV_H

#include <stdbool.h>
#include <stdint.h>
#include <i2c.h>

#define I2C_MASTER_FREQ_HZ 100000
#define I2C_MASTER_TX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */
#define WRITE_BIT I2C_MASTER_WRITE              /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ                /*!< I2C master read */
#define ACK_CHECK_EN 0x1                        /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0                       /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                             /*!< I2C ack value */
#define NACK_VAL 0x1                            /*!< I2C nack value */


bool i2c_init(void);
bool i2c_read(uint8_t i2c_num, uint8_t i2c_addr, uint8_t* array, uint16_t array_len);
bool i2c_write(uint8_t i2c_num, uint8_t i2c_addr, uint8_t* array, uint16_t array_len);
bool i2c_scan(uint8_t i2c_num, uint8_t* array, uint16_t array_len, uint16_t* ic_cnt);
bool i2c_check_addr(uint8_t i2c_num, uint8_t i2c_addr);
bool i2c_send_signal(uint8_t signal);
bool i2c_wait_busy(void);
#endif /* I2C_DRV_H  */
