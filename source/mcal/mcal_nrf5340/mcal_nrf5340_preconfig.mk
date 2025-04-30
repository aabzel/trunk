ifneq ($(MCAL_NRF5340_PRECONFIG_MK_INC),Y)
    MCAL_NRF5340_PRECONFIG_MK_INC=Y

    MCAL_NRF5340_DIR = $(MCAL_DIR)/mcal_nrf5340

    NRF5340=Y
    
    ifeq ($(ADC),Y)
        include $(MCAL_NRF5340_DIR)/adc/adc_preconfig.mk
    endif

    ifeq ($(FLASH),Y)
        include $(MCAL_NRF5340_DIR)/flash/flash_preconfig.mk
    endif

    ifeq ($(GPIO),Y)
        include $(MCAL_NRF5340_DIR)/gpio/gpio_preconfig.mk
    endif

    ifeq ($(CLOCK),Y)
        include $(MCAL_NRF5340_DIR)/clock/clock_preconfig.mk
    endif

    ifeq ($(TIMER),Y)
        include $(MCAL_NRF5340_DIR)/timer/timer_preconfig.mk
    endif

    ifeq ($(I2S),Y)
        include $(MCAL_NRF5340_DIR)/i2s/i2s_preconfig.mk
    endif

    ifeq ($(I2C),Y)
        include $(MCAL_NRF5340_DIR)/i2c/i2c_preconfig.mk
    endif

    ifeq ($(IPC),Y)
        include $(MCAL_NRF5340_DIR)/ipc/ipc_preconfig.mk
    endif

    ifeq ($(NVS),Y)
        include $(MCAL_NRF5340_DIR)/nvs/nvs_preconfig.mk
    endif

    ifeq ($(PDM),Y)
        include $(MCAL_NRF5340_DIR)/pdm/pdm_preconfig.mk
    endif

    ifeq ($(PWM),Y)
        include $(MCAL_NRF5340_DIR)/pwm/pwm_preconfig.mk
    endif

    ifeq ($(RTC),Y)
        include $(MCAL_NRF5340_DIR)/rtc/rtc_preconfig.mk
    endif

    ifeq ($(QSPI),Y)
        include $(MCAL_NRF5340_DIR)/qspi/qspi_preconfig.mk
    endif

    ifeq ($(SPI),Y)
        include $(MCAL_NRF5340_DIR)/spi/spi_preconfig.mk
    endif

    ifeq ($(SYSTICK),Y)
        include $(MCAL_NRF5340_DIR)/systick/systick_preconfig.mk
    endif

    include $(MCAL_NRF5340_DIR)/cores/nrf_cores_preconfig.mk

    ifeq ($(UART),Y)
        include $(MCAL_NRF5340_DIR)/uart/uart_preconfig.mk
    endif

    ifeq ($(USB),Y) 
        include $(MCAL_NRF5340_DIR)/usb/usb_preconfig.mk
    endif
endif


