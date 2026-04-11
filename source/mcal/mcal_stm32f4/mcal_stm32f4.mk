ifneq ($(MCAL_STM32F4_DRV_MK_INC),Y)
    MCAL_STM32F4_DRV_MK_INC=Y

    MCAL_CUSTOM_DIR = $(MCAL_DIR)/mcal_stm32f4
    # $(error MCAL_CUSTOM_DIR=$(MCAL_CUSTOM_DIR))

    INCDIR += -I$(MCAL_CUSTOM_DIR)
    #RCC=Y
    MCAL_STM32=Y
    #STM32F4XX_HAL_DRIVER=Y
    MCAL_OPT += -DHAS_MCAL_STM32

    ifeq ($(DIAG),Y)
        # $(error DIAG=$(DIAG))
        MCAL_OPT += -DHAS_HAL_DIAG
        SOURCES_DIAG_C += $(MCAL_CUSTOM_DIR)/hal_diag.c
    endif

    ifeq ($(HAL_MSP),Y)
        # $(error HAL_MSP=$(HAL_MSP))
        SOURCES_C += $(MCAL_CUSTOM_DIR)/stm32f4xx_hal_msp.c
    endif

    SOURCES_C += $(MCAL_CUSTOM_DIR)/stm32f4xx_it.c
    SOURCES_C += $(MCAL_CUSTOM_DIR)/hal_mcal.c

    ifeq ($(ADC),Y)   
        # $(error ADC=$(ADC))
        include $(MCAL_CUSTOM_DIR)/adc/adc.mk
    endif

    ifeq ($(CAN),Y) 
        # $(error STM32_CAN=$(STM32_CAN))
        include $(MCAL_CUSTOM_DIR)/can/can.mk
    endif

    ifeq ($(CRYP_HW),Y)
        $(info Add Crypto Driver)
        # $(error CRYP=$(CRYP)) 
        include $(MCAL_CUSTOM_DIR)/cryp/cryp.mk
    endif

    ifeq ($(CLOCK),Y)
        # $(error CLOCK=$(CLOCK)) 
        include $(MCAL_CUSTOM_DIR)/clock/clock.mk
    endif

    ifeq ($(CLOCK_OUT),Y)
        # $(error CLOCK_OUT=$(CLOCK_OUT)) 
        include $(MCAL_CUSTOM_DIR)/clock_out/clock_out.mk
    endif

    ifeq ($(DAC),Y)
        include $(MCAL_CUSTOM_DIR)/dac/dac.mk
    endif
    
    ifeq ($(DMA),Y)   
        # $(error DMA=$(DMA))
        include $(MCAL_CUSTOM_DIR)/dma/dma.mk
    endif

    ifeq ($(EXT_INT),Y)
        # $(error EXT_INT=$(EXT_INT))
        include $(MCAL_CUSTOM_DIR)/ext_int/ext_int.mk
    endif

    ifeq ($(FLASH),Y)   
        # $(error FLASH=$(FLASH))
        include $(MCAL_CUSTOM_DIR)/flash/flash.mk
    endif

    ifeq ($(GPIO),Y) 
        # $(error GPIO=$(GPIO))
        include $(MCAL_CUSTOM_DIR)/gpio/gpio.mk
    endif

    ifeq ($(I2C),Y) 
        # $(error I2C=$(I2C))
        include $(MCAL_CUSTOM_DIR)/i2c/i2c.mk
    endif
    
    ifeq ($(I2S),Y) 
        # $(error I2S=$(I2S))
        include $(MCAL_CUSTOM_DIR)/i2s/i2s.mk
    endif

    ifeq ($(INPUT_CAPTURE),Y)   
        # $(error INPUT_CAPTURE=$(INPUT_CAPTURE))
        include $(MCAL_CUSTOM_DIR)/input_capture/input_capture.mk
    endif

    ifeq ($(INTERRUPT),Y) 
        # $(error INTERRUPT=$(INTERRUPT))
        include $(MCAL_CUSTOM_DIR)/interrupt/interrupt.mk
    endif

    ifeq ($(IOMUX),Y)
        # $(error IOMUX=$(IOMUX))
        include $(MCAL_CUSTOM_DIR)/iomux/iomux.mk
    endif

    ifeq ($(MPU),Y) 
        # $(error MPU=$(MPU))
        include $(MCAL_CUSTOM_DIR)/mpu/mpu.mk
    endif

    ifeq ($(NVS),Y)   
        # $(error NVS=$(NVS))
        include $(MCAL_CUSTOM_DIR)/nvs/nvs.mk
    endif

    ifeq ($(PWM),Y)
        # $(error PWM=$(PWM)) 
        include $(MCAL_CUSTOM_DIR)/pwm/pwm.mk
    endif

    ifeq ($(RTC),Y)
        # $(error RTC=$(RTC))
        include $(MCAL_CUSTOM_DIR)/rtc/rtc_internal.mk
    endif

    ifeq ($(SDIO),Y)
        # $(error SDIO=$(SDIO)) 
        include $(MCAL_CUSTOM_DIR)/sdio/sdio.mk
    endif

    ifeq ($(SPI),Y) 
        # $(error SPI=$(SPI))
        include $(MCAL_CUSTOM_DIR)/spi/spi.mk
    endif

    ifeq ($(SYSTICK),Y)   
        # $(error SYSTICK=$(SYSTICK))
        include $(MCAL_CUSTOM_DIR)/systick/systick.mk
    endif

    ifeq ($(SWD),Y)
        # $(error SWD=$(SWD)) 
        include $(MCAL_CUSTOM_DIR)/swd/swd.mk
    endif

    ifeq ($(TIMER),Y)
        # $(error TIMER=$(TIMER))
        include $(MCAL_CUSTOM_DIR)/timer/timer.mk
    endif

    ifeq ($(UART),Y) 
        # $(error UART=$(UART))
        include $(MCAL_CUSTOM_DIR)/uart/uart.mk
    endif

    ifeq ($(STM32_USB),Y) 
        # $(error USB=$(USB))
        include $(MCAL_CUSTOM_DIR)/usb/usb.mk
    endif

    ifeq ($(WATCHDOG),Y) 
        # $(error WATCHDOG=$(WATCHDOG))
        include $(MCAL_CUSTOM_DIR)/watchdog/watchdog.mk
    endif
endif
