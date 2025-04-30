ifneq ($(MCAL_COMMON_PRECONFIG_MK_INC),Y)
    MCAL_COMMON_PRECONFIG_MK_INC=Y
    #@echo $(error MCAL_COMMON_PRECONFIG_MK_INC=$(MCAL_COMMON_PRECONFIG_MK_INC))

    MCAL_COMMON_DIR = $(MCAL_DIR)/mcal_common
    MICROCONTROLLER=Y
    
    ifeq ($(TIMER),Y)
        #@echo $(error TIMER=[$(TIMER)])
        include $(MCAL_COMMON_DIR)/timer/timer_preconfig.mk
    endif

    #ifeq ($(CLOCK),Y)
    #    include $(MCAL_COMMON_DIR)/clock/clock_preconfig.mk
    #endif

    ifeq ($(ADC),Y)
        include $(MCAL_COMMON_DIR)/adc/adc_preconfig.mk
    endif

    ifeq ($(DMA),Y)
        include $(MCAL_COMMON_DIR)/dma/dma_preconfig.mk
    endif

    ifeq ($(EEPROM),Y)
        include $(MCAL_COMMON_DIR)/eeprom/eeprom_preconfig.mk
    endif

    ifeq ($(FLASH),Y) 
        include $(MCAL_COMMON_DIR)/flash/flash_preconfig.mk
    endif

    ifeq ($(GPIO),Y) 
        include $(MCAL_COMMON_DIR)/gpio/gpio_preconfig.mk
    endif
    
    ifeq ($(I2C),Y) 
        include $(MCAL_COMMON_DIR)/i2c/i2c_preconfig.mk
    endif
    
    ifeq ($(I2S),Y) 
        #@echo $(error I2S=$(I2S))
        include $(MCAL_COMMON_DIR)/i2s/i2s_preconfig.mk
    endif

    ifeq ($(NVS),Y) 
        include $(MCAL_COMMON_DIR)/nvs/nvs_preconfig.mk
    endif

    ifeq ($(RTC),Y)
        include $(MCAL_COMMON_DIR)/rtc/rtc_preconfig.mk
    endif

    ifeq ($(QSPI),Y)
        include $(MCAL_COMMON_DIR)/qspi/qspi_preconfig.mk
    endif

    ifeq ($(SDIO),Y) 
        #@echo $(error SDIO=$(SDIO))
        include $(MCAL_COMMON_DIR)/sdio/sdio_preconfig.mk
    endif

    ifeq ($(SPI),Y) 
        #@echo $(error SPI=$(SPI))
        include $(MCAL_COMMON_DIR)/spi/spi_preconfig.mk
    endif

    ifeq ($(PDM),Y) 
        #@echo $(error PDM=$(PDM))
        include $(MCAL_COMMON_DIR)/pdm/pdm_preconfig.mk
    endif

    ifeq ($(PWM),Y) 
        #@echo $(error PWM=$(PWM))
        include $(MCAL_COMMON_DIR)/pwm/pwm_preconfig.mk
    endif

    ifeq ($(UART),Y) 
        #@echo $(error UART=$(UART))
        include $(MCAL_COMMON_DIR)/uart/uart_preconfig.mk
    endif
    
    ifeq ($(USB),Y)
        include $(MCAL_COMMON_DIR)/usb/usb_preconfig.mk
    endif

    ifeq ($(WATCHDOG),Y) 
        #@echo $(error WATCHDOG=$(WATCHDOG))
        include $(MCAL_COMMON_DIR)/watchdog/watchdog_preconfig.mk
    endif

endif