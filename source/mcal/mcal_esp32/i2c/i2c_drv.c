
#include "i2c_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <i2c.h>

#include "log.h"
#include "bit_utils.h"
#include "sys_config.h"


i2c_config_t I2cConf[I2C_COUNT] = {{
    .mode = I2C_MODE_MASTER,
    .sda_io_num = DIO_I2C_SDA,
    .scl_io_num = DIO_I2C_SCK,
    .sda_pullup_en = GPIO_PULLUP_ENABLE,
    .scl_pullup_en = GPIO_PULLUP_ENABLE,
    .master.clk_speed = I2C_MASTER_FREQ_HZ,
    // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
},
{
       .mode = I2C_MODE_MASTER,
       .sda_io_num = DIO_I2C_SDA,
       .scl_io_num = DIO_I2C_SCK,
       .sda_pullup_en = GPIO_PULLUP_ENABLE,
       .scl_pullup_en = GPIO_PULLUP_ENABLE,
       .master.clk_speed = I2C_MASTER_FREQ_HZ,
       // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
}
};

static bool i2c_init_one(uint8_t i2c_num) {
    bool res = false;
    esp_err_t ret;
    ret = i2c_param_config(i2c_num, &I2cConf[i2c_num] );
    if(ESP_OK==ret){
         res= true;
    }else{
       res = false;
    }
    if(res){
        ret= i2c_driver_install(i2c_num, I2cConf[i2c_num].mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
        if(ESP_OK==ret){
            res= true;
        }else{
            res = false;
        }
   }
    return res;
}

bool i2c_init(void) {
    bool res = true;
#ifdef HAS_I2C0
    res=i2c_init_one(0)&&res;
#endif
#ifdef HAS_I2C1
    res=i2c_init_one(1)&&res;
#endif
    return res;
}

bool i2c_write(uint8_t i2c_num, uint8_t i2c_addr, uint8_t* array, uint16_t array_len) {
    bool res = false;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    if(cmd){
        esp_err_t ret;
        ret = i2c_master_start(cmd);
        if(ESP_OK ==ret){

        }else{
            LOG_ERROR(I2C, "StartErr");
        }

        ret =i2c_master_write_byte(cmd, (i2c_addr << 1) | WRITE_BIT, ACK_CHECK_EN);
        if(ESP_OK ==ret){
        }else{
            LOG_ERROR(I2C, "AddrWrErr");
        }
        ret = i2c_master_write(cmd, array, array_len, ACK_CHECK_EN);
        if(ESP_OK ==ret){
        }else{
            LOG_ERROR(I2C, "DataWrErr");
        }
        ret = i2c_master_stop(cmd);
        if(ESP_OK ==ret){
        }else{
            LOG_ERROR(I2C, "StopErr");
        }
        ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
        if(ESP_OK ==ret){
        }else{
            LOG_ERROR(I2C, "BeginErr");
        }
        i2c_cmd_link_delete(cmd);
        res = true;
    }else{
        LOG_ERROR(I2C, "CmdWrLinkErr");
    }
    return res;
}

bool i2c_read(uint8_t i2c_num, uint8_t i2c_addr, uint8_t* array, uint16_t array_len) {
    bool res = false;
   // if (array_len == 0) {
   //     return ESP_OK;
   // }
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    if(cmd){
        esp_err_t ret;
        ret = i2c_master_start(cmd);
        if(ESP_OK ==ret){
        }else{
            LOG_ERROR(I2C, "StartErr");
        }
        ret = i2c_master_write_byte(cmd, (i2c_addr << 1) | READ_BIT, ACK_CHECK_EN);
        if(ESP_OK ==ret){
        }else{
            LOG_ERROR(I2C, "WrAddrErr");
        }



        if (1<array_len ) {
            ret=i2c_master_read(cmd, array, array_len-1, ACK_VAL);
            if(ESP_OK ==ret){
            }else{
                LOG_ERROR(I2C, "ReadDataErr");
            }
        }
        ret = i2c_master_read_byte(cmd, array + array_len - 1, NACK_VAL);
        if(ESP_OK ==ret){
        }else{
           LOG_ERROR(I2C, "ReadTailErr");
        }

        ret = i2c_master_stop(cmd);
        if(ESP_OK ==ret){
        }else{
            LOG_ERROR(I2C, "StopErr");
        }
        ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
        if(ESP_OK ==ret){
        }else{
            LOG_ERROR(I2C, "CmdErr");
        }

        i2c_cmd_link_delete(cmd);
        res = true;
    }else{
        LOG_ERROR(I2C, "CmdReadLinkErr");
    }
    return res;
}

bool i2c_wait_busy(void) {
    bool res = true;

    return res;
}

bool i2c_check_addr(uint8_t i2c_num, uint8_t i2c_addr) {
    bool res = false;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    if(cmd){
         esp_err_t ret;
         ret=i2c_master_start(cmd);
         ret=i2c_master_write_byte(cmd, (i2c_addr << 1) | WRITE_BIT, ACK_CHECK_EN);
         ret=i2c_master_stop(cmd);
         ret = i2c_master_cmd_begin(i2c_num, cmd, 50 / portTICK_RATE_MS);
         i2c_cmd_link_delete(cmd);
         if (ESP_OK==ret ) {
             res = true;
         } else if (ESP_ERR_TIMEOUT==ret ) {
             res = false;
         } else {
             res = false;
         }
    }
    return res;
}

bool i2c_send_signal(uint8_t signal) {
    bool res = false;
    return res;
}


bool i2c_scan(uint8_t i2c_num, uint8_t* array, uint16_t array_len, uint16_t* ic_cnt) {
    uint8_t address;
    bool out_res=false;
    bool res=false;
    uint16_t cnt=0;
    printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\r\n");
    for (int i = 0; i < 128; i += 16) {
        printf("%02x: ", i);
        for (int j = 0; j < 16; j++) {
            fflush(stdout);
            address = i + j;
            res=i2c_check_addr(i2c_num,   address );
            if(true==res){
                out_res = true;
                printf("%02x ", address);
                     if(cnt<array_len){
                         array[cnt]=address;
                     }
                     cnt++;
            }else{
                printf("UU ");
            }

        }
        printf("\r\n");
    }
    if(ic_cnt){
        *ic_cnt=cnt;
    }
    return out_res;
}
