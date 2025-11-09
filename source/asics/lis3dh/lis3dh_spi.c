#include "lis3dh_spi.h"

#include "log.h"
#include "gpio_mcal.h"
#include "none_blocking_pause.h"
#include "array_diag.h"

#ifdef HAS_LIS3DH_DIAG
#include "lis3dh_diag.h"
#endif

#ifdef HAS_SPI
#include "spi_mcal.h"
#endif

static uint8_t spi_extract_byte(uint8_t *const rx_array){
    uint8_t rx_byte = 0xFF;
    if(0xFF!=rx_array[0]){
        rx_byte= rx_array[0];
    }else{
        if(0xFF!=rx_array[1]){
            rx_byte= rx_array[1];
        }else{
            rx_byte = 0xFF;
        }
    }
    return rx_byte;
}

bool lis3dh_spi_reg_read_ll(Lis3dhHandle_t *Node, Lis3dhRegAddr_t reg_addr, uint8_t *const rx_byte) {
    bool res = false;
    //uint8_t addr_val = (uint8_t)addr;
    if(Node){
        LOG_DEBUG(LIS3DH, "Addr:0x%02x", reg_addr);
        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_LOW);
       // wait_ms(1);
        Lis3dhSpiHeader_t Header = { 0 };
        Header.register_address = reg_addr;
        Header.rw = LIS3DH_SPI_READ;
        Header.ms = LIS3DH_MS_ADDR_STATIC;

        static uint8_t tx_array[2]= {0};
        tx_array[0] = Header.byte;
        tx_array[1] = 0; // OK?
        //tx_array[1] = 0xFF; // error
        static uint8_t rx_array[2]= {0};
        res = spi_api_write_read(Node->spi_num, tx_array, rx_array, 2);
        if(res) {
            if(rx_byte) {
                rx_byte[0] = spi_extract_byte(rx_array);
                //rx_byte[0] = rx_array[1];
            }
            LOG_DEBUG(LIS3DH, "WreadRead,Ok,SPI%u,REG:0x%02x,VAL:0x%02x", Node->spi_num, reg_addr,
                     rx_array[1]);
        } else {
#ifdef HAS_LIS3DH_DIAG
            LOG_ERROR(LIS3DH, "SPI%u,WreadRead,Err,Reg:0x%02x=%s", Node->spi_num, reg_addr,
                      Lis3dhRegAddrToName(reg_addr));
#endif
        }
      //  wait_ms(1);
        gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_HI);
    }
    return res;
}

bool lis3dh_spi_reg_write_ll(Lis3dhHandle_t *Node, Lis3dhRegAddr_t addr, uint8_t byte) {
    bool res = false;
    gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_LOW);
    wait_us(500);

    Lis3dhSpiHeader_t Header = { 0 };
    Header.byte = 0;
    Header.register_address = addr;
    Header.rw = LIS3DH_SPI_WRITE;
    Header.ms = LIS3DH_MS_ADDR_STATIC;
    static uint8_t TxBuff[2] = { 0 };
    TxBuff[0] = Header.byte;
    TxBuff[1] = byte;
    res = spi_api_write(Node->spi_num, TxBuff, 2);
    if (res) {
        LOG_DEBUG(LIS3DH, "SPI%u,Write,Ok!Addr:0x%02x,Val:0x%s", Node->spi_num, addr,
                ArrayToStr(TxBuff, 2));
    } else {
#ifdef HAS_LIS3DH_DIAG
        LOG_ERROR(LIS3DH, "SPI%u,Write,Err,Addr:0x%02x=%s,Val:0x%04x", Node->spi_num, addr,
                Lis3dhRegAddrToName(addr), byte);
#endif
    }
    wait_us(500);
    gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_HI);
    return res;
}

