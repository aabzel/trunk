#include "i2c_database.h"

#include "data_utils.h"
#include "i2c_types.h"

static const I2cRecord_t I2cRecord[] = {
    {
        .name = "AXP192",
        .chip_addr = 0x34,
    },
    {
        .name = "AD2425WCCSZ",
        .chip_addr_read = 0x68,
        .chip_addr_write = 0x69,
    },
    {
        .name = "BQ34210IPWRQ1",
        .chip_addr_read = 0xAB,
        .chip_addr_write = 0xAA,
    },
    {
        .name = "bq25125",
        .chip_addr = 0x6a,
        .chip_addr_read = 0xD4,
    },
    {
        .name = "24AA512",
        .chip_addr = 0x50,
    },
    {
        .name = "BH1750",
        .chip_addr = 0x23,
    }, /*TODO*/
    {
        .name = "BH1750",
        .chip_addr = 0x5C,
    },
    {
        .name = "LSM6DSOXTR",
    },
    {
        .name = "NAU8814",
        .chip_addr = 0x1A,
        .chip_addr_read = 0x35,
        .chip_addr_write = 0x34,
    },
    {
        .name = "SI4703",
        .chip_addr = 0x10,
        .chip_addr_read = 0x20,
        .chip_addr_write = 0x21,
    },
    {
        .name = "Si4737",
        .chip_addr = 0x63,
        .chip_addr_read = 0xC6,
        .chip_addr_write = 0xC7,
    },
    {
        .name = "MAX9860",
        .chip_addr_read = 0x20,
        .chip_addr_write = 0x21,
    },
    {
        .name = "WM8731",
        .chip_addr = 0x1a,
        .chip_addr_read = 0x35,
        .chip_addr_write = 0x34,
    },
    {
        .chip_addr = 0x6c,
        .name = "Fda801",
    },
    {
        .chip_addr = 0x6d,
        .name = "Fda801",
    },
    {
        .chip_addr = 0x6e,
        .name = "Fda801",
    },
    {
        .chip_addr = 0x6f,
        .name = "Fda801",
    },

    {
        .chip_addr = 0x68,
        .name = "AD2421WCCSZ",
    },
    {
        .chip_addr = 0x39,
        .name = "ADAU1361CPZ",
    },
    {
        .chip_addr = 0x38,
        .name = "ADAU1452WBCPZ",
    },
    {
        .chip_addr = 0x62,
        .name = "PCA9632TK",
    },
    {
        .chip_addr = 0x40,
        .name = "INA233AIDGSR",
    },
};

uint32_t i2c_get_databse_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(I2cRecord);
    return cnt;
}

const char* I2cGetChipName(uint8_t chip_addr) {
    const char* name = "?";
    uint32_t i = 0;
    uint32_t cnt = i2c_get_databse_cnt();
    for(i = 0; i < cnt; i++) {
        if(I2cRecord[i].chip_addr == chip_addr) {
            name = I2cRecord[i].name;
            break;
        }
    }
    return name;
}
