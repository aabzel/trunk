ifneq ($(MCAL_X86_PRECONFIG_MK_INC),Y)
    MCAL_X86_PRECONFIG_MK_INC=Y
    # $(error MCAL_X86_PRECONFIG_MK_INC=$(MCAL_X86_PRECONFIG_MK_INC))

    MCAL_X86_DIR=$(MCAL_DIR)/mcal_x86x
    MICROCONTROLLER=Y

    ifeq ($(ADC),Y)
        include $(MCAL_X86_DIR)/adc/adc_preconfig.mk
    endif

    ifeq ($(CAN),Y) 
        include $(MCAL_X86_DIR)/can/can_preconfig.mk
    endif

    ifeq ($(CLOCK),Y)
        include $(MCAL_X86_DIR)/clock/clock_preconfig.mk
    endif

    ifeq ($(DMA),Y)
        include $(MCAL_X86_DIR)/dma/dma_preconfig.mk
    endif
    
    ifeq ($(FLASH),Y) 
        include $(MCAL_X86_DIR)/flash/flash_preconfig.mk
    endif

    ifeq ($(GPIO),Y) 
        include $(MCAL_X86_DIR)/gpio/gpio_preconfig.mk
    endif

    ifeq ($(I2C),Y) 
        include $(MCAL_X86_DIR)/i2c/i2c_preconfig.mk
    endif

    ifeq ($(NVS),Y) 
        include $(MCAL_X86_DIR)/nvs/nvs_preconfig.mk
    endif

    ifeq ($(RTC),Y)
        include $(MCAL_X86_DIR)/rtc/rtc_preconfig.mk
    endif

    ifeq ($(SPI),Y) 
        # $(error SPI=$(SPI))
        include $(MCAL_X86_DIR)/spi/spi_preconfig.mk
    endif
    
    ifeq ($(TIMER),Y)
        # $(error TIMER=[$(TIMER)])
        include $(MCAL_X86_DIR)/timer/timer_preconfig.mk
    endif

    ifeq ($(TRNG),Y)
        # $(error TRNG=[$(TRNG)])
        include $(MCAL_X86_DIR)/trng/trng_preconfig.mk
    endif

    ifeq ($(PWM),Y) 
        # $(error PWM=$(PWM))
        include $(MCAL_X86_DIR)/pwm/pwm_preconfig.mk
    endif

    ifeq ($(QSPI),Y)
        include $(MCAL_X86_DIR)/qspi/qspi_preconfig.mk
    endif

    ifeq ($(UART),Y) 
        # $(error UART=$(UART))
        include $(MCAL_X86_DIR)/uart/uart_preconfig.mk
    endif

    ifeq ($(WATCHDOG),Y) 
        # $(error WATCHDOG=$(WATCHDOG))
        include $(MCAL_X86_DIR)/watchdog/watchdog_preconfig.mk
    endif
endif