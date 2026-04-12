
ifneq ($(AT32F435_437_FIRMWARE_LIBRARY_EN_V2_1_5_MK_LOC),Y) 
    AT32F435_437_FIRMWARE_LIBRARY_EN_V2_1_5_MK_LOC=Y

    HAL_AT32_DIR = $(THIRD_PARTY_DIR)/AT32F435_437_Firmware_Library_EN_V2.1.5
    HAL_AT32_SOURCES_THIRD_PARTY_C = $(HAL_AT32_DIR)/libraries/drivers/src

    #@echo $(error HAL_AT32_DIR=$(HAL_AT32_DIR))
    INCDIR += -I$(HAL_AT32_DIR)
    INCDIR += -I$(HAL_AT32_DIR)/libraries
    INCDIR += -I$(HAL_AT32_DIR)/libraries/cmsis
    INCDIR += -I$(HAL_AT32_DIR)/libraries/cmsis/cm4
    INCDIR += -I$(HAL_AT32_DIR)/libraries/cmsis/cm4/core_support

    INCDIR += -I$(HAL_AT32_DIR)/libraries/drivers
    INCDIR += -I$(HAL_AT32_DIR)/libraries/drivers/inc

    MCAL_OPT += -DHAS_AT32F43X_FIRMWARE_LIB
    MCAL_OPT += -DMISC_MODULE_ENABLED
    
    SOURCES_THIRD_PARTY_C += $(HAL_AT32_SOURCES_THIRD_PARTY_C)/at32f435_437_misc.c

    ifeq ($(ADC),Y)
        $(info Add At ADC)
        MCAL_OPT += -DADC_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(HAL_AT32_SOURCES_THIRD_PARTY_C)/at32f435_437_adc.c
    endif

    ifeq ($(CLOCK),Y)
        #@echo $(error CLOCK=$(CLOCK))
        MCAL_OPT += -DCRM_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(HAL_AT32_SOURCES_THIRD_PARTY_C)/at32f435_437_crm.c
    endif

    ifeq ($(GPIO),Y)
        $(info Add GPIO)
        MCAL_OPT += -DGPIO_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(HAL_AT32_SOURCES_THIRD_PARTY_C)/at32f435_437_gpio.c
    endif

    ifeq ($(CAN),Y) 
        $(info Add At CAN)
        MCAL_OPT += -DCAN_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(HAL_AT32_SOURCES_THIRD_PARTY_C)/at32f435_437_can.c
    endif

    ifeq ($(DAC),Y)
        $(info Add At DAC)
        MCAL_OPT += -DDAC_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(HAL_AT32_SOURCES_THIRD_PARTY_C)/at32f435_437_dac.c
    endif

    ifeq ($(DMA),Y)
        $(info Add At DMA)
        MCAL_OPT += -DDMA_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(HAL_AT32_SOURCES_THIRD_PARTY_C)/at32f435_437_dma.c
    endif
    
    ifeq ($(FLASH),Y)
        #@echo $(error FLASH=$(FLASH))
        $(info Add At FLASH)
        MCAL_OPT += -DFLASH_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(HAL_AT32_SOURCES_THIRD_PARTY_C)/at32f435_437_flash.c
    endif

    EXINT=Y
    ifeq ($(EXINT),Y)
        $(info Add EXINT)
        MCAL_OPT += -DEXINT_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(HAL_AT32_SOURCES_THIRD_PARTY_C)/at32f435_437_exint.c
    endif

    SCFG=Y
    ifeq ($(SCFG),Y)
        $(info Add SCFG)
        MCAL_OPT += -DSCFG_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(HAL_AT32_SOURCES_THIRD_PARTY_C)/at32f435_437_scfg.c
    endif

    ifeq ($(I2C),Y)
        $(info Add At I2C)
        MCAL_OPT += -DI2C_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(HAL_AT32_SOURCES_THIRD_PARTY_C)/at32f435_437_i2c.c
    endif

    ifeq ($(I2S),Y) 
        #$(info Add At I2S)
    endif

    ifeq ($(SPI),Y)
        $(info Add At SPI)
        MCAL_OPT += -DSPI_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(HAL_AT32_SOURCES_THIRD_PARTY_C)/at32f435_437_spi.c
    endif

    ifeq ($(TIMER),Y) 
        $(info Add Artery TIMER HAL)
        MCAL_OPT += -DTMR_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(HAL_AT32_SOURCES_THIRD_PARTY_C)/at32f435_437_tmr.c
    endif

    ifeq ($(PDM),Y) 
        #$(info Add At PDM)
    endif

    ifeq ($(POWER),Y) 
        $(info Add At POWER)
        MCAL_OPT += -DPWC_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(HAL_AT32_SOURCES_THIRD_PARTY_C)/at32f435_437_pwc.c
    endif

    ifeq ($(PWM),Y)
    endif
    
    ifeq ($(UART),Y) 
        $(info Add At UART)
        MCAL_OPT += -DUSART_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(HAL_AT32_SOURCES_THIRD_PARTY_C)/at32f435_437_usart.c
    endif

    ifeq ($(WATCHDOG),Y) 
        $(info Add At WATCHDOG)
        MCAL_OPT += -DWDT_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(HAL_AT32_SOURCES_THIRD_PARTY_C)/at32f435_437_wdt.c
    endif

    ifeq ($(NVS),Y) 
        $(info Add At NVS)
    endif

    ifeq ($(RTC),Y) 
    endif

    ifeq ($(QSPI),Y) 
    endif

    include $(HAL_AT32_DIR)/middlewares/middlewares.mk
endif