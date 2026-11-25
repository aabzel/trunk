ifneq ($(MCAL_MODULE_PRECONFIG_MK_INC),Y)
    MCAL_MODULE_PRECONFIG_MK_INC=Y
    # $(error MCAL_MODULE_PRECONFIG_MK_INC=$(MCAL_MODULE_PRECONFIG_MK_INC))

    MCAL_MODULE_DIR=$(MCAL_DIR)/mcal_module
    MICROCONTROLLER=Y

    ifeq ($(ADC),Y)
        include $(MCAL_MODULE_DIR)/adc/adc_preconfig.mk
    endif

    ifeq ($(CAN),Y) 
        include $(MCAL_MODULE_DIR)/can/can_preconfig.mk
    endif

    ifeq ($(CLOCK),Y)
        include $(MCAL_MODULE_DIR)/clock/clock_preconfig.mk
    endif

    ifeq ($(DMA),Y)
        include $(MCAL_MODULE_DIR)/dma/dma_preconfig.mk
    endif

    ifeq ($(EIM),Y)
        include $(MCAL_MODULE_DIR)/eim/eim_preconfig.mk
    endif

    ifeq ($(FLASH),Y) 
        include $(MCAL_MODULE_DIR)/flash/flash_preconfig.mk
    endif

    ifeq ($(GPIO),Y) 
        include $(MCAL_MODULE_DIR)/gpio/gpio_preconfig.mk
    endif

    ifeq ($(I2C),Y) 
        include $(MCAL_MODULE_DIR)/i2c/i2c_preconfig.mk
    endif

    ifeq ($(NVS),Y) 
        include $(MCAL_MODULE_DIR)/nvs/nvs_preconfig.mk
    endif

    ifeq ($(MAM),Y) 
        include $(MCAL_MODULE_DIR)/mam/mam_preconfig.mk
    endif
    
    ifeq ($(MPU),Y) 
        include $(MCAL_MODULE_DIR)/mpu/mpu_preconfig.mk
    endif

    ifeq ($(RTC),Y)
        include $(MCAL_MODULE_DIR)/rtc/rtc_preconfig.mk
    endif

    ifeq ($(SPI),Y) 
        # $(error SPI=$(SPI))
        include $(MCAL_MODULE_DIR)/spi/spi_preconfig.mk
    endif
    
    ifeq ($(TIMER),Y)
        # $(error TIMER=[$(TIMER)])
        include $(MCAL_MODULE_DIR)/timer/timer_preconfig.mk
    endif

    ifeq ($(PWM),Y) 
        # $(error PWM=$(PWM))
        include $(MCAL_MODULE_DIR)/pwm/pwm_preconfig.mk
    endif

    ifeq ($(QSPI),Y)
        include $(MCAL_MODULE_DIR)/qspi/qspi_preconfig.mk
    endif

    ifeq ($(UART),Y) 
        # $(error UART=$(UART))
        include $(MCAL_MODULE_DIR)/uart/uart_preconfig.mk
    endif

    ifeq ($(WATCHDOG),Y) 
        # $(error WATCHDOG=$(WATCHDOG))
        include $(MCAL_MODULE_DIR)/watchdog/watchdog_preconfig.mk
    endif
endif