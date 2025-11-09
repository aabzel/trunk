#include "lis3dh_i2c.h"

#include "log.h"
#include "array_diag.h"
#include "lis3dh_diag.h"
#ifdef HAS_I2C
#include "i2c_mcal.h"
#endif

bool lis3dh_i2c_reg_read_ll(Lis3dhHandle_t *Node, Lis3dhRegAddr_t addr, uint8_t *const byte) {
    bool res = false;
    uint8_t reg_byte = 0 ;
    uint8_t addr_val = (uint8_t) addr;
    LOG_DEBUG(LIS3DH, "Addr:0x%02x,AddrVal:0x%02x", addr, addr_val);
    res = i2c_api_read_mem(Node->i2c_num, Node->chip_addr, &addr_val, 1, (uint8_t*) &reg_byte, 1);
    if (res) {
        *byte = reg_byte;
        LOG_PARN(LIS3DH, "Read,Ok,CHIP:0x%x,REG:0x%02x,VAL:0x%02x", Node->chip_addr, addr,
                reg_byte);
    } else {
        LOG_ERROR(LIS3DH, "I2C%u,Read,Err,Reg:0x%02x=%s", Node->i2c_num, addr,
                Lis3dhRegAddrToName(addr));
    }
    return res;
}

bool lis3dh_i2c_reg_write_ll(Lis3dhHandle_t *Node, Lis3dhRegAddr_t addr, uint8_t byte) {
    bool res = false;
    uint8_t buff[2] = { addr, byte };
    res = i2c_api_write(Node->i2c_num, Node->chip_addr, buff, 2);
    if (res) {
        LOG_DEBUG(LIS3DH, "Write,Ok!Addr:0x%02x,Val:0x%s", addr, ArrayToStr(buff, 2));
    } else {
        LOG_ERROR(LIS3DH, "Write,Err,Addr:0x%02x=%s,Val:0x%04x", addr, Lis3dhRegAddrToName(addr),
                byte);
    }
    return res;
}

