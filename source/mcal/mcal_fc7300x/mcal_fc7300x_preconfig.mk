ifneq ($(MCAL_FC7300X_PRECONFIG_MK_INC),Y)
    MCAL_FC7300X_PRECONFIG_MK_INC=Y
    #@echo $(error MCAL_FC7300X_PRECONFIG_MK_INC=$(MCAL_FC7300X_PRECONFIG_MK_INC))

    MCAL_FC7300X_DIR=$(MCAL_DIR)/mcal_fc7300x
    MICROCONTROLLER=Y

    ifeq ($(ADC),Y)
        include $(MCAL_FC7300X_DIR)/adc/adc_preconfig.mk
    endif

    ifeq ($(CAN),Y) 
        include $(MCAL_FC7300X_DIR)/can/can_preconfig.mk
    endif

    ifeq ($(CLOCK),Y)
        include $(MCAL_FC7300X_DIR)/clock/clock_preconfig.mk
    endif

    ifeq ($(DMA),Y)
        include $(MCAL_FC7300X_DIR)/dma/dma_preconfig.mk
    endif
    
    ifeq ($(FLASH),Y) 
        include $(MCAL_FC7300X_DIR)/flash/flash_preconfig.mk
    endif

    ifeq ($(GPIO),Y) 
        include $(MCAL_FC7300X_DIR)/gpio/gpio_preconfig.mk
    endif

    ifeq ($(I2C),Y) 
        include $(MCAL_FC7300X_DIR)/i2c/i2c_preconfig.mk
    endif

    ifeq ($(NVS),Y) 
        include $(MCAL_FC7300X_DIR)/nvs/nvs_preconfig.mk
    endif

    ifeq ($(RTC),Y)
        include $(MCAL_FC7300X_DIR)/rtc/rtc_preconfig.mk
    endif

    ifeq ($(SPI),Y) 
        #@echo $(error SPI=$(SPI))
        include $(MCAL_FC7300X_DIR)/spi/spi_preconfig.mk
    endif
    
    ifeq ($(TIMER),Y)
        #@echo $(error TIMER=[$(TIMER)])
        include $(MCAL_FC7300X_DIR)/timer/timer_preconfig.mk
    endif

    ifeq ($(PWM),Y) 
        #@echo $(error PWM=$(PWM))
        include $(MCAL_FC7300X_DIR)/pwm/pwm_preconfig.mk
    endif

    ifeq ($(QSPI),Y)
        include $(MCAL_FC7300X_DIR)/qspi/qspi_preconfig.mk
    endif

    ifeq ($(UART),Y) 
        #@echo $(error UART=$(UART))
        include $(MCAL_FC7300X_DIR)/uart/uart_preconfig.mk
    endif

    ifeq ($(WATCHDOG),Y) 
        #@echo $(error WATCHDOG=$(WATCHDOG))
        include $(MCAL_FC7300X_DIR)/watchdog/watchdog_preconfig.mk
    endif
endif