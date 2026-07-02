#include "spi_custom_diag.h"

#include "spi_mcal.h"
#include "mcal_types.h"
#include "diag_inc.h"
#include "clock_diag.h"

const Reg32_t SpiRegs[] = {
    {.num=1, .name="SPI_CR1",     .offset=0x0,  .size=2, .access=ACCESS_READ_WRITE, .valid=true,},
    {.num=2, .name="SPI_CR2",     .offset=0x4,  .size=2, .access=ACCESS_READ_WRITE, .valid=true,},
    {.num=3, .name="SPI_SR",      .offset=0x8,  .size=2, .access=ACCESS_READ_ONLY,  .valid=true,},
    {.num=4, .name="SPI_DR",      .offset=0xC,  .size=2, .access=ACCESS_READ_WRITE, .valid=true,},
    {.num=5, .name="SPI_CRCPR",   .offset=0x10, .size=2, .access=ACCESS_READ_WRITE, .valid=true,},
    {.num=6, .name="SPI_RXCRCR",  .offset=0x14, .size=2, .access=ACCESS_READ_ONLY,  .valid=true,},
    {.num=7, .name="SPI_TXCRCR",  .offset=0x18, .size=2, .access=ACCESS_READ_ONLY,  .valid=true,},
    {.num=8, .name="SPI_I2SCFGR", .offset=0x1C, .size=2, .access=ACCESS_READ_WRITE, .valid=true,},
    {.num=9, .name="SPI_I2SPR",   .offset=0x20, .size=2, .access=ACCESS_READ_WRITE, .valid=true,},
};

uint32_t spi_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(SpiRegs);
    return cnt;
}

const char* SpiInfoToStr(const SpiInfo_t* const Info) {
    memset(text, 0, sizeof(text));
    strcpy(text, "");
    if(Info) {
        sprintf(text, "SPI%u,", Info->num);
        snprintf(text, sizeof(text), "%sSPIx:0x%p,", text, Info->SPIx);
        snprintf(text, sizeof(text), "%seClock:%s,", text, ClockBusToStr(Info->clock_bus));
        snprintf(text, sizeof(text), "%sIrq:%d,", text, Info->irq_n);
        //snprintf(text, sizeof(text), "%sEnd:0x%p,", text, Info->TansferEndNotification);
        //snprintf(text, sizeof(text), "%sStart:0x%p,", text, Info->TansferStartNotification);
        //snprintf(text, sizeof(text), "%sInts:%u,", text, Info->e_instance);
        //snprintf(text, sizeof(text), "%sReg:0x%p,", text, Info->Regs);
#ifdef HAS_SPI_DMA
        //snprintf(text, sizeof(text), "%seDmaTx:%u,", text, Info->dma_trigger_src_tx);
        //snprintf(text, sizeof(text), "%seDmaRx:%u,", text, Info->dma_trigger_src_rx);
#endif
    }
    return text;
}

static char* update_csv_line(char * temp,
                             uint32_t size,
                             const uint32_t mask,
                             const uint32_t error,
                             char *token){
    if(mask==(mask&error)){
        snprintf(temp, size, "%s%s,", text, token);
    }
    return temp;
}

const char* SpiErrToStr(const uint32_t error){
    memset(text, 0, sizeof(text));
    strcpy(text, "");

    update_csv_line(text, sizeof(text), HAL_SPI_ERROR_CRC, error, "CRC");
#if 0
    if(HAL_SPI_ERROR_CRC==(HAL_SPI_ERROR_CRC&error)){
        snprintf(text, sizeof(text), "%sCRC,", text);
    }
#endif
    if(HAL_SPI_ERROR_MODF==(HAL_SPI_ERROR_MODF&error)){
        snprintf(text, sizeof(text), "%sMODF,", text);
    }

    if(HAL_SPI_ERROR_OVR==(HAL_SPI_ERROR_OVR&error)){
        snprintf(text, sizeof(text), "%sOVR,", text);
    }

    if(HAL_SPI_ERROR_FRE==(HAL_SPI_ERROR_FRE&error)){
        snprintf(text, sizeof(text), "%sFRE,", text);
    }

    if(HAL_SPI_ERROR_DMA==(HAL_SPI_ERROR_DMA&error)){
        snprintf(text, sizeof(text), "%sDMA,", text);
    }

    if(HAL_SPI_ERROR_FLAG==(HAL_SPI_ERROR_FLAG&error)){
        snprintf(text, sizeof(text), "%sFLAG,", text);
    }

    if(HAL_SPI_ERROR_ABORT==(HAL_SPI_ERROR_ABORT&error)){
        snprintf(text, sizeof(text), "%sABORT,", text);
    }

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
    if(USE_HAL_SPI_REGISTER_CALLBACKS==(USE_HAL_SPI_REGISTER_CALLBACKS&error)){
        snprintf(text, sizeof(text), "%sCallBack,", text);
    }
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */

    return text;
}


