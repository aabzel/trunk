#include "si4703_spi.h"

#include "gpio_mcal.h"
#include "si4703_mcal.h"
#include "std_includes.h"
#include "spi_mcal.h"
#include "log.h"
#include "timer_utils.h"

bool si4703_spi_select_if(uint8_t num) {
    bool res = true;
    LOG_INFO(SI4703, "Select,SPI");
    Si4703Handle_t *Node = Si4703GetNode(num);
    if (Node) {
        res = gpio_logic_level_set(Node->PadReset, GPIO_LVL_LOW);
        wait_ms(10);
        res = gpio_logic_level_set(Node->PadSen, GPIO_LVL_LOW);
        res = gpio_logic_level_set(Node->PadGpio1, GPIO_LVL_LOW);
        // res = gpio_logic_level_set(Node->PadGpio3, GPIO_LVL_HI);
        wait_ms(10);
        res = si4703_reset(num);
    }
    return res;
}

static bool si4703_compose_addr(uint8_t reg_addr, Si4703SpiAddressRead_t* const AddressRead) {
    bool res = false;
    if (AddressRead) {
        BitField8_t Field8;
        Field8.byte = reg_addr;
        AddressRead->address0 = Field8.bit0;
        AddressRead->address1 = Field8.bit1;
        AddressRead->address2 = Field8.bit2;
        AddressRead->address3 = Field8.bit3;
        AddressRead->address4 = 0;
        AddressRead->address5 = 1;
        AddressRead->address6 = 1;
        AddressRead->address7 = 0;
        res = true;
    }
    return res;
}

bool si4703_spi_read_reg(const uint8_t num, const Si4703RegAddr_t reg_addr, uint16_t* const reg_val) {
    bool res = false;
    Si4703Handle_t *Node = Si4703GetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->PadSen, GPIO_LVL_LOW);

        Si4703SpiAddressRead_t AddressRead = {0};
        si4703_compose_addr(reg_addr, &AddressRead);
        AddressRead.RW = Si4703_SPI_READ;
        res = spi_write_byte(Node->if_code.num, AddressRead.byte[1]);

        res = spi_mcal_read_word(Node->if_code.num, reg_val);

        gpio_logic_level_set(Node->PadSen, GPIO_LVL_HI);
        wait_ms(10);
    }
    return res;
}

bool si4703_spi_write_reg(const uint8_t num, const Si4703RegAddr_t reg_addr, const uint16_t reg_val) {
    bool res = false;
    LOG_DEBUG(SI4703, "WriteReg:0x%02x,Val:0x%04x", reg_addr, reg_val);
    Si4703Handle_t *Node = Si4703GetNode(num);
    if(Node) {
        gpio_logic_level_set(Node->PadSen, GPIO_LVL_LOW);

        BitField8_t Field8;
        Field8.byte = reg_addr;

        Si4703SpiFrameWrite_t FrameWrite;
        FrameWrite.address_bit0=Field8.bit0;
        FrameWrite.address_bit1=Field8.bit1;
        FrameWrite.address_bit2=Field8.bit2;
        FrameWrite.address_bit3=Field8.bit3;
        FrameWrite.write_bit = Si4703_SPI_WRITE;
        FrameWrite.address_bit4=0;
        FrameWrite.address_bit5=1;
        FrameWrite.address_bit6=1;
        FrameWrite.address_bit7=0;

        FrameWrite.data_word = reg_val;
        FrameWrite.res = 0;

        res = spi_write_dword(Node->if_code.num, FrameWrite.dword);

        gpio_logic_level_set(Node->PadSen, GPIO_LVL_HI);
        wait_ms(10);
    }
    return res;
}

bool si4700_spi_read(uint8_t num, uint8_t* const data , const uint8_t size) {
    bool res = false;
    Si4703Handle_t* Node = Si4703GetNode(num);
    if(Node){
        res = true;
    }
    return res;
}

bool si4700_spi_write(uint8_t num, const uint8_t* const data , const uint8_t size) {
    bool res = false;
    Si4703Handle_t* Node=Si4703GetNode(num);
    if(Node){
        res = true;
    }
    return res;
}



