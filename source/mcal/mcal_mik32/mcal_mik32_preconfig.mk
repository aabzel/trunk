ifneq ($(MCAL_MIK32_PRECONF_MK_INC),Y)
    MCAL_MIK32_PRECONF_MK_INC=Y

    MCAL_MIK32_DIR = $(MCAL_DIR)/mcal_mik32
    # $(error MCAL_MIK32_DIR=$(MCAL_MIK32_DIR))


    include $(MCAL_MIK32_DIR)/boot_manager/boot_manager.mk
    
    ifeq ($(ADC),Y)   
        include $(MCAL_MIK32_DIR)/adc/adc_preconfig.mk
    endif

    ifeq ($(CRYP_HW),Y)
        include $(MCAL_MIK32_DIR)/cryp/cryp_preconfig.mk
    endif

    ifeq ($(CLOCK),Y)  
        include $(MCAL_MIK32_DIR)/clock/clock_preconfig.mk
    endif

    ifeq ($(DMA),Y)   
        include $(MCAL_MIK32_DIR)/dma/dma_preconfig.mk
    endif

    ifeq ($(FLASH),Y)   
        include $(MCAL_MIK32_DIR)/flash/flash_preconfig.mk
    endif

    ifeq ($(EEPROM),Y)   
        include $(MCAL_MIK32_DIR)/eeprom/eeprom_preconfig.mk
    endif
    
    ifeq ($(GPIO),Y) 
        include $(MCAL_MIK32_DIR)/gpio/gpio_preconfig.mk
    endif

    ifeq ($(I2C),Y) 
        include $(MCAL_MIK32_DIR)/i2c/i2c_preconfig.mk
    endif

    ifeq ($(INTERRUPT),Y) 
        include $(MCAL_MIK32_DIR)/interrupt/interrupt_preconfig.mk
    endif

    ifeq ($(IWDG),Y) 
        include $(MCAL_MIK32_DIR)/iwdg/iwdg_preconfig.mk
    endif

    ifeq ($(NVS),Y)   
        include $(MCAL_MIK32_DIR)/nvs/nvs_preconfig.mk
    endif


    ifeq ($(PWM),Y)
        include $(MCAL_MIK32_DIR)/pwm/pwm_preconfig.mk
    endif

    ifeq ($(RTC),Y)
        include $(MCAL_MIK32_DIR)/rtc/rtc_internal_preconfig.mk
    endif

    ifeq ($(SPI),Y) 
        include $(MCAL_MIK32_DIR)/spi/spi_preconfig.mk
    endif

    ifeq ($(SPIFI),Y) 
        include $(MCAL_MIK32_DIR)/spifi/spifi_preconfig.mk
    endif

    ifeq ($(TIMER),Y)   
        include $(MCAL_MIK32_DIR)/timer/timer_preconfig.mk
    endif

    ifeq ($(UART),Y) 
        include $(MCAL_MIK32_DIR)/uart/uart_preconfig.mk
    endif
endif
