ifneq ($(MCAL_STM32F4_PRECONFIG_MK_INC),Y)
    MCAL_STM32F4_PRECONFIG_MK_INC=Y

    MCAL_STM32F4_DIR = $(MCAL_DIR)/mcal_stm32f4
    # $(error MCAL_STM32F4_DIR=$(MCAL_STM32F4_DIR))

    MCAL_STM32=Y
    HAL_MSP=Y
    #STM32F4XX_HAL_DRIVER=Y

    ifeq ($(ADC),Y)   
        include $(MCAL_STM32F4_DIR)/adc/adc_preconfig.mk
    endif

    ifeq ($(CAN),Y)  
        include $(MCAL_STM32F4_DIR)/can/can_preconfig.mk
    endif

    ifeq ($(CLOCK),Y)
        include $(MCAL_STM32F4_DIR)/clock/clock_preconfig.mk
    endif

    ifeq ($(CRYP_HW),Y)
        include $(MCAL_STM32F4_DIR)/cryp/cryp_preconfig.mk
    endif

    ifeq ($(EXT_INT),Y)
        include $(MCAL_STM32F4_DIR)/ext_int/ext_int_preconfig.mk
    endif
    
    ifeq ($(DMA),Y)   
        include $(MCAL_STM32F4_DIR)/dma/dma_preconfig.mk
    endif

    ifeq ($(FLASH),Y)   
        include $(MCAL_STM32F4_DIR)/flash/flash_preconfig.mk
    endif

    ifeq ($(GPIO),Y) 
        # $(error GPIO=$(GPIO))
        include $(MCAL_STM32F4_DIR)/gpio/gpio_preconfig.mk
    endif

    ifeq ($(I2C),Y) 
        # $(error I2C=$(I2C))
        include $(MCAL_STM32F4_DIR)/i2c/i2c_preconfig.mk
    endif

    ifeq ($(I2S),Y) 
        # $(error I2S=$(I2S))
        include $(MCAL_STM32F4_DIR)/i2s/i2s_preconfig.mk
    endif

    ifeq ($(INPUT_CAPTURE),Y)   
        # $(error INPUT_CAPTURE=$(INPUT_CAPTURE))
        include $(MCAL_STM32F4_DIR)/input_capture/input_capture_preconfig.mk
    endif

    ifeq ($(INTERRUPT),Y) 
        # $(error INTERRUPT=$(INTERRUPT))
        include $(MCAL_STM32F4_DIR)/interrupt/interrupt_preconfig.mk
    endif

    ifeq ($(IOMUX),Y)
        # $(error IOMUX=$(IOMUX))
        include $(MCAL_STM32F4_DIR)/iomux/iomux_preconfig.mk
    endif

    ifeq ($(WATCHDOG),Y) 
        # $(error WATCHDOG=$(WATCHDOG))
        include $(MCAL_STM32F4_DIR)/watchdog/watchdog_preconfig.mk
    endif

    ifeq ($(MPU),Y) 
        # $(error MPU=$(MPU))
        include $(MCAL_STM32F4_DIR)/mpu/mpu_preconfig.mk
    endif

    ifeq ($(NVS),Y)   
        # $(error NVS=$(NVS))
        include $(MCAL_STM32F4_DIR)/nvs/nvs_preconfig.mk
    endif

    ifeq ($(MCO),Y)
        # $(error SWD=$(SWD)) 
        include $(MCAL_STM32F4_DIR)/mco/mco_preconfig.mk
    endif

    ifeq ($(PWM),Y)
        # $(error PWM=$(PWM)) 
        include $(MCAL_STM32F4_DIR)/pwm/pwm_preconfig.mk
    endif

    ifeq ($(RTC),Y)
        # $(error RTC=$(RTC))
        include $(MCAL_STM32F4_DIR)/rtc/rtc_internal_preconfig.mk
    endif

    ifeq ($(SDIO),Y)
        # $(error SDIO=$(SDIO)) 
        include $(MCAL_STM32F4_DIR)/sdio/sdio_preconfig.mk
    endif

    ifeq ($(SPI),Y) 
        # $(error SPI=$(SPI))
        include $(MCAL_STM32F4_DIR)/spi/spi_preconfig.mk
    endif

    ifeq ($(SYSTICK),Y)   
        # $(error SYSTICK=$(SYSTICK))
        include $(MCAL_STM32F4_DIR)/systick/systick_preconfig.mk
    endif

    ifeq ($(SWD),Y)
        # $(error SWD=$(SWD)) 
        include $(MCAL_STM32F4_DIR)/swd/swd_preconfig.mk
    endif

    ifeq ($(TIMER),Y)   
        # $(error TIMER=$(TIMER))
        include $(MCAL_STM32F4_DIR)/timer/timer_preconfig.mk
    endif

    ifeq ($(UART),Y) 
        # $(error UART=$(UART))
        include $(MCAL_STM32F4_DIR)/uart/uart_preconfig.mk
    endif

    ifeq ($(USB),Y) 
        # $(error USB=$(USB))
        include $(MCAL_STM32F4_DIR)/usb/usb_preconfig.mk
    endif
endif
