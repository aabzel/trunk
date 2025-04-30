ifneq ($(MCAL_ARTERY_PRECONFIG_MK_INC),Y)
    MCAL_ARTERY_PRECONFIG_MK_INC=Y
    #@echo $(error MCAL_ARTERY_PRECONFIG_MK_INC=$(MCAL_ARTERY_PRECONFIG_MK_INC))

    MCAL_ARTERY_DIR=$(MCAL_DIR)/mcal_at32f4
    MICROCONTROLLER=Y

    ifeq ($(ADC),Y)
        include $(MCAL_ARTERY_DIR)/adc/adc_preconfig.mk
    endif

    ifeq ($(CLOCK),Y)
        include $(MCAL_ARTERY_DIR)/clock/clock_preconfig.mk
    endif

    ifeq ($(DMA),Y)
        include $(MCAL_ARTERY_DIR)/dma/dma_preconfig.mk
    endif

    ifeq ($(FLASH),Y) 
        include $(MCAL_ARTERY_DIR)/flash/flash_preconfig.mk
    endif

    ifeq ($(GPIO),Y) 
        include $(MCAL_ARTERY_DIR)/gpio/gpio_preconfig.mk
    endif
    
    ifeq ($(I2C),Y) 
        include $(MCAL_ARTERY_DIR)/i2c/i2c_preconfig.mk
    endif
    
    ifeq ($(I2S),Y) 
        #@echo $(error I2S=$(I2S))
        include $(MCAL_ARTERY_DIR)/i2s/i2s_preconfig.mk
    endif

    ifeq ($(NVS),Y) 
        include $(MCAL_ARTERY_DIR)/nvs/nvs_preconfig.mk
    endif

    ifeq ($(RTC),Y)
        include $(MCAL_ARTERY_DIR)/rtc/rtc_preconfig.mk
    endif

    ifeq ($(SDIO),Y) 
        #@echo $(error SDIO=$(SDIO))
        include $(MCAL_ARTERY_DIR)/sdio/sdio_preconfig.mk
    endif

    ifeq ($(SPI),Y) 
        #@echo $(error SPI=$(SPI))
        include $(MCAL_ARTERY_DIR)/spi/spi_preconfig.mk
    endif
    
    ifeq ($(TIMER),Y)
        #@echo $(error TIMER=[$(TIMER)])
        include $(MCAL_ARTERY_DIR)/timer/timer_preconfig.mk
    endif

    ifeq ($(PDM),Y) 
        #@echo $(error PDM=$(PDM))
        include $(MCAL_ARTERY_DIR)/pdm/pdm_preconfig.mk
    endif

    ifeq ($(PWM),Y) 
        #@echo $(error PWM=$(PWM))
        include $(MCAL_ARTERY_DIR)/pwm/pwm_preconfig.mk
    endif

    ifeq ($(QSPI),Y)
        include $(MCAL_ARTERY_DIR)/qspi/qspi_preconfig.mk
    endif

    ifeq ($(UART),Y) 
        #@echo $(error UART=$(UART))
        include $(MCAL_ARTERY_DIR)/uart/uart_preconfig.mk
    endif

    ifeq ($(USB),Y)
        include $(MCAL_ARTERY_DIR)/usb/usb_preconfig.mk
    endif
    
    ifeq ($(WATCHDOG),Y) 
        #@echo $(error WATCHDOG=$(WATCHDOG))
        include $(MCAL_ARTERY_DIR)/watchdog/watchdog_preconfig.mk
    endif
endif