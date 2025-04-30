#include "i2c_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/kernel.h>

#include "i2c_config.h"
#include "i2c_custom_types.h"
#include "zephyr_diag.h"

#ifdef HAS_LOG
#include "log.h"
#endif /*HAS_LOG*/

#ifndef HAS_ZEPHYR
#error "+HAS_ZEPHYR"
#endif

/*
 * https://docs.zephyrproject.org/latest/hardware/peripherals/i2c.html
 * */

static const I2cInfo_t I2cInfo[] = {
#ifdef HAS_I2C0
    {
        .num = I2C_0,
        .dev = DEVICE_DT_GET(DT_NODELABEL(i2c0)),
        .valid = true,
    },
#endif

#ifdef HAS_I2C1
    {
        .num = I2C_1,
        .dev = DEVICE_DT_GET(DT_NODELABEL(i2c1)),
        .valid = true,
    },
#endif

#ifdef HAS_I2C2
    {
        .num = I2C_2,
        .dev = DEVICE_DT_GET(DT_NODELABEL(i2c2)),
        .valid = true,
    },
#endif

#ifdef HAS_I2C3
    {
        .num = I2C_3,
        .dev = DEVICE_DT_GET(DT_NODELABEL(i2c3)),
        .valid = true,
    }
#endif
};

static struct device* I2cNumToI2cDevPtr(I2cNum_t num) {
    struct device* Node = NULL;
    uint32_t cnt = ARRAY_SIZE(I2cInfo);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(I2cInfo[i].num == num) {
            Node = I2cInfo[i].dev;
            break;
        }
    }
    return Node;
}

static const I2cInfo_t* I2cGetInfo(I2cNum_t num) {
    const I2cInfo_t* Info = NULL;
    uint32_t cnt = ARRAY_SIZE(I2cInfo);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(I2cInfo[i].num == num) {
            Info = &I2cInfo[i];
            break;
        }
    }
    return Info;
}

static bool i2c_init_one(const GpioConfig_t* pinInstance) {
    bool res = false;
    return res;
}

bool i2c_init_ll(uint8_t num) {
    bool res = true;
    LOG_WARNING(I2C, "%u Init ", num);
    I2cHandle_t* Node = I2cGetNode(num);
    // const I2cConfig_t* I2cConfigNode = NULL;
    if(Node) {
        res = true;
    } else {
        LOG_ERROR(I2C, "HandleErr");
        res = false;
    }

    if(res) {
        /*Zephyr kernel will init I2C periphery*/
    } else {
        LOG_ERROR(I2C, "%u Conf " LOG_ER, num);
    }
    return res;
}

bool i2c_api_write(uint8_t num, uint8_t chip_addr, const uint8_t* const data, size_t size) {
    bool res = false;
    LOG_DEBUG(I2C, "I2C%u Write Chip:0x%x Len: %u", num, chip_addr, size);
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node && data && (0 < size)) {
        // uint32_t init_tx_cnt = Node->tx_cnt;
        Node->tx_int = false;
        struct device* I2cDev = I2cNumToI2cDevPtr((I2cNum_t)num);
        if(I2cDev) {
            int ret = i2c_write(I2cDev, (const uint8_t*)data, (uint32_t)size, (uint16_t)chip_addr);
            if(0 == ret) {
                res = true;
                LOG_DEBUG(I2C, "I2C%u WriteOk", num);
            } else {
                LOG_ERROR(I2C, "I2C%u WriteErr %d=%s", num, ret, ErrNo2Str(ret));
            }
        } else {
            LOG_ERROR(I2C, "I2C%u DevError", num);
        }
    } else {
        LOG_ERROR(I2C, "I2C%u NodeError", num);
    }
    return res;
}

bool i2c_write_wait(uint8_t num, uint8_t chip_addr, const uint8_t* const data, size_t size) {
    bool res = false;
    res = i2c_api_write(num, chip_addr, data, size);
    return res;
}

bool i2c_api_read(uint8_t num, uint8_t chip_addr, uint8_t* const data, size_t size) {
    bool res = false;
    if(data) {
        struct device* I2cDev = I2cNumToI2cDevPtr((I2cNum_t)num);
        if(I2cDev) {
            int ret = i2c_read(I2cDev, data, (uint32_t)size, (uint16_t)chip_addr);
            if(0 == ret) {
                res = true;
            } else {
                LOG_ERROR(I2C, "%u ReadErr %d=%s", num, ret, ErrNo2Str(ret));
            }
        } else {
            LOG_ERROR(I2C, "%u DevErr", num);
        }
    }
    return res;
}

bool i2c_api_write_reg(uint8_t num, uint8_t dev_addr, uint8_t reg_addr, uint8_t value) {
    bool res = false;
    LOG_DEBUG(I2C, "I2C%u Write ChipAddr: 0x%x Reg[0x%x]=0x%x", num, dev_addr, reg_addr, value);
    struct device* I2cDev = I2cNumToI2cDevPtr((I2cNum_t)num);
    if(I2cDev) {
        int ret = i2c_reg_write_byte(I2cDev, (uint16_t)dev_addr, reg_addr, value);
        if(0 == ret) {
            LOG_DEBUG(I2C, "I2C%u WriteOk", num);
            res = true;
        } else {
            LOG_ERROR(I2C, "%u Chip 0x%02x WriteReg 0x%02x err %d=%s ", num, dev_addr, reg_addr, ret, ErrNo2Str(ret));
        }
    } else {
        LOG_ERROR(I2C, "%u DevErr", num);
    }
    return res;
}

bool i2c_api_read_byte(uint8_t num, uint8_t dev_addr, uint8_t reg_addr, uint8_t* value) {
    bool res = false;
    if(value) {
        struct device* I2cDev = I2cNumToI2cDevPtr((I2cNum_t)num);
        if(I2cDev) {
            int ret = i2c_reg_read_byte(I2cDev, dev_addr, reg_addr, value);
            if(0 == ret) {
                res = true;
            } else {
                LOG_ERROR(I2C, "%u ReadErr %d=%s", num, ret, ErrNo2Str(ret));
            }
        } else {
            LOG_ERROR(I2C, "%u DevErr", num);
        }
    }
    return res;
}

bool i2c_api_read_mem(uint8_t num, uint8_t chip_addr, uint8_t* const addr, size_t addr_size, uint8_t* const read_buf,
                      size_t size) {
    bool res = false;
    LOG_DEBUG(I2C, "ReadMem I2C%u, Chip:0x%x,AddrSize:%u,DataSize:%u", num, chip_addr, addr_size, size);
    struct device* I2cDev = I2cNumToI2cDevPtr((I2cNum_t)num);
    if(I2cDev) {
        int ret = 0;
        ret = i2c_write_read(I2cDev, (uint16_t)chip_addr, (void*)addr, addr_size, (void*)read_buf, size);
        if(0 == ret) {
            res = true;
        } else {
            LOG_ERROR(I2C, "I2C%u WriteReadErr %d=%s", num, ret, ErrNo2Str(ret));
        }
    } else {
        LOG_ERROR(I2C, "I2C%u DevErr", num);
    }

    return res;
}

bool i2c_check_addr(uint8_t num, uint8_t chip_addr) {
    bool res = false;
    uint8_t data[2];
    set_log_level(I2C, LOG_LEVEL_CRITICAL);
    res = i2c_api_read(num, chip_addr, data, 1);
    set_log_level(I2C, LOG_LEVEL_INFO);
    return res;
}

bool i2c_send_signal(uint8_t num, I2cSignal_t signal) {
    bool res = false;
    /*Zephyr API does not allow to send I2C signals
      https://docs.zephyrproject.org/3.1.0/hardware/peripherals/i2c.html
     */
    return res;
}

bool i2c_init(void) {
    bool res = true;
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

    if(cnt) {
        LOG_INFO(I2C, "Init %u I2Cs", cnt);
        res = true;
    } else {
        res = false;
    }

    return res;
}
