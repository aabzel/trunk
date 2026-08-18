#include "si4703_i2c.h"

#include "std_includes.h"
#include "si4703_mcal.h"
#include "time_mcal.h"
#include "array_diag.h"
#include "gpio_mcal.h"
#include "i2c_mcal.h"
#include "byte_utils.h"
#include "log.h"

uint8_t si4703_reg_addr_to_reg_index(const Si4703RegAddr_t reg_addr){
    uint8_t reg_index = reg_addr;
    const Si4703RegInfo_t* Info=Si4703GetRegInfo(reg_addr);
    if(Info) {
        reg_index = Info->reg_index;
    }
    LOG_PARN(SI4703,"Reg[0x%02x]->%u",reg_addr,reg_index);
    return reg_index;
}

bool si4703_i2c_read_reg(const uint8_t num, const Si4703RegAddr_t reg_addr, uint16_t* const reg_val) {
    bool res = false;
    Si4703Handle_t *Node = Si4703GetNode(num);
    if (Node) {
        res = i2c_mcal_read(Node->if_code.num, Node->i2c_addr, (uint8_t*) Node->RegRead, SI4703_REG_CNT*2);
        log_res(SI4703,res,"I2cReadAllReg");
        if(res) {
            res = false;
            log_level_t ll= log_level_get(SI4703) ;
            if(LOG_LEVEL_DEBUG==ll) {
                array_u16_print(Node->RegRead, SI4703_REG_CNT);
            }
            //memcpy(Node->RegWrite,Node->RegRead,SI4703_REG_CNT*2);

            uint8_t i = 0;
            for(i=0;i<SI4703_REG_CNT;i++){
                uint8_t k=si4703_reg_addr_to_reg_index(i);
                Node->RegWrite[i]=Node->RegRead[k];
            }

            uint8_t reg_index = si4703_reg_addr_to_reg_index(reg_addr);
            LOG_DEBUG(SI4703,"Get,Reg[0x%02x]=0x%04x",reg_addr,Node->RegRead[reg_index]);
            if(reg_val){
                *reg_val = reverse_byte_order_uint16(Node->RegRead[reg_index]);
                res = true;
            }
            //memcpy(reg_val,&Node->RegRead[reg_index],2);
        }
    }
    return res;
}

bool si4703_i2c_write_reg(const uint8_t num, const Si4703RegAddr_t reg_addr, const uint16_t reg_val) {
    bool res = false;
    LOG_DEBUG(SI4703,"Set,Reg[0x%02x]=0x%04x",reg_addr,reg_val);
    Si4703Handle_t *Node = Si4703GetNode(num);
    if (Node) {
        //uint8_t reg_index = si4703_reg_addr_to_reg_index(reg_addr);
//        Node->RegWrite[reg_index] = reverse_byte_order_uint16(reg_val); error
        Node->RegWrite[reg_addr] = reverse_byte_order_uint16(reg_val);
        res = i2c_mcal_write(Node->if_code.num,   Node->i2c_addr,  (uint8_t* )  &Node->RegWrite[SI4703_REG_POWERCFG], SI4703_REG_WRITE_CNT*2);
        log_res(SI4703,res,"I2cWriteAllReg");
    }
    return res;
}

bool si4700_i2c_read(uint8_t num, uint8_t * data, uint32_t size) {
    bool res = false;
    Si4703Handle_t *Node = Si4703GetNode(num);
    if (Node) {
        res = i2c_mcal_read(Node->if_code.num, Node->i2c_addr, (uint8_t*) data, size);
    }
    return res;
}

bool si4703_select_i2c_method_1_ll(Si4703Handle_t* Node) {
    bool res = true;
    res = gpio_logic_level_set(Node->PadSen, GPIO_LVL_HI);
    wait_ms(10);
    return res;
}

bool si4703_select_i2c_method_2_ll(Si4703Handle_t* Node) {
    bool res = true;
    res = gpio_logic_level_set(Node->PadGpio1, GPIO_LVL_HI);
    wait_ms(10);
    return res;
}

bool si4703_i2c_select_if(uint8_t num) {
    bool res = true;
    // All parameters applied on rising edge of RST.
    LOG_INFO(SI4703, "Select,I2C");
    Si4703Handle_t* Node=Si4703GetNode(num);
    if(Node){
        res = si4703_select_i2c_method_1_ll(Node);
        res = si4703_select_i2c_method_2_ll(Node);
    }
    return res;
}

#if 0

/* writes <len> registers from cache to radio at offset 0x02 */
bool si4700_i2c_write(uint8_t num, int len) {
    bool res = false;
    Si4703Handle_t* Node=Si4703GetNode(num);
    int i;
    unsigned char buf[32];
    unsigned char* ptr = buf;
    uint16_t data;

    for(i = 0; i < len; i++) {
        data = Node->cache[(i + SI4703_REG_POWERCFG) & 0xF];
        *ptr++ = (data >> 8) & 0xFF;
        *ptr++ = data & 0xFF;
    }
    res = i2c_mcal_write(Node->if_code.num, SI4703_I2C_ADDR, buf, len * 2);
    return res;
}


#endif
