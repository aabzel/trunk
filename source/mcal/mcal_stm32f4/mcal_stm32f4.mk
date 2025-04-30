ifneq ($(MCAL_STM32F4_DRV_MK_INC),Y)
    MCAL_STM32F4_DRV_MK_INC=Y

    MCAL_STM32F4_DIR = $(MCAL_DIR)/mcal_stm32f4
    #@echo $(error MCAL_STM32F4_DIR=$(MCAL_STM32F4_DIR))

    INCDIR += -I$(MCAL_STM32F4_DIR)
    #RCC=Y
    MCAL_STM32=Y
    STM32F4XX_HAL_DRIVER=Y

    ifeq ($(DIAG),Y)
        #@echo $(error DIAG=$(DIAG))
        OPT += -DHAS_HAL_DIAG
        SOURCES_C += $(MCAL_STM32F4_DIR)/hal_diag.c
    endif

    ifeq ($(HAL_MSP),Y)
        #@echo $(error HAL_MSP=$(HAL_MSP))
        SOURCES_C += $(MCAL_STM32F4_DIR)/stm32f4xx_hal_msp.c
    endif

    SOURCES_C += $(MCAL_STM32F4_DIR)/stm32f4xx_it.c
    SOURCES_C += $(MCAL_STM32F4_DIR)/hal_mcal.c

    ifeq ($(ADC),Y)   
        #@echo $(error ADC=$(ADC))
        include $(MCAL_STM32F4_DIR)/adc/adc.mk
    endif

    ifeq ($(CRYP_HW),Y)
        $(info Add Crypto Driver)
        #@echo $(error CRYP=$(CRYP)) 
        include $(MCAL_STM32F4_DIR)/cryp/cryp.mk
    endif
    
    ifeq ($(CLOCK),Y)  
        #@echo $(error CLOCK=$(CLOCK)) 
        include $(MCAL_STM32F4_DIR)/clocks/clocks.mk
    endif

    ifeq ($(DMA),Y)   
        #@echo $(error DMA=$(DMA))
        include $(MCAL_STM32F4_DIR)/dma/dma.mk
    endif

    ifeq ($(FLASH),Y)   
        #@echo $(error FLASH=$(FLASH))
        include $(MCAL_STM32F4_DIR)/flash/flash.mk
    endif

    ifeq ($(GPIO),Y) 
        #@echo $(error GPIO=$(GPIO))
        include $(MCAL_STM32F4_DIR)/gpio/gpio.mk
    endif

    ifeq ($(I2C),Y) 
        #@echo $(error I2C=$(I2C))
        include $(MCAL_STM32F4_DIR)/i2c/i2c.mk
    endif

    ifeq ($(I2S),Y) 
        #@echo $(error I2S=$(I2S))
        include $(MCAL_STM32F4_DIR)/i2s/i2s.mk
    endif

    ifeq ($(INTERRUPT),Y) 
        #@echo $(error INTERRUPT=$(INTERRUPT))
        include $(MCAL_STM32F4_DIR)/interrupt/interrupt.mk
    endif

    ifeq ($(IWDG),Y) 
        #@echo $(error IWDG=$(IWDG))
        include $(MCAL_STM32F4_DIR)/iwdg/iwdg.mk
    endif

    ifeq ($(NVS),Y)   
        #@echo $(error NVS=$(NVS))
        include $(MCAL_STM32F4_DIR)/nvs/nvs.mk
    endif

    ifeq ($(MCO),Y)
        #@echo $(error SWD=$(SWD)) 
        include $(MCAL_STM32F4_DIR)/mco/mco.mk
    endif

    ifeq ($(PWM),Y)
        #@echo $(error PWM=$(PWM)) 
        include $(MCAL_STM32F4_DIR)/pwm/pwm.mk
    endif

    ifeq ($(RTC),Y)
        #@echo $(error RTC=$(RTC))
        include $(MCAL_STM32F4_DIR)/rtc/rtc_internal.mk
    endif

    ifeq ($(SDIO),Y)
        #@echo $(error SDIO=$(SDIO)) 
        include $(MCAL_STM32F4_DIR)/sdio/sdio.mk
    endif

    ifeq ($(SPI),Y) 
        #@echo $(error SPI=$(SPI))
        include $(MCAL_STM32F4_DIR)/spi/spi.mk
    endif

    ifeq ($(SYSTICK),Y)   
        #@echo $(error SYSTICK=$(SYSTICK))
        include $(MCAL_STM32F4_DIR)/systick/systick.mk
    endif

    ifeq ($(SWD),Y)
        #@echo $(error SWD=$(SWD)) 
        include $(MCAL_STM32F4_DIR)/swd/swd.mk
    endif

    ifeq ($(TIMER),Y)   
        #@echo $(error TIMER=$(TIMER))
        include $(MCAL_STM32F4_DIR)/timer/timer.mk
    endif

    ifeq ($(UART),Y) 
        #@echo $(error UART=$(UART))
        include $(MCAL_STM32F4_DIR)/uart/uart.mk
    endif

    ifeq ($(USB),Y) 
        #@echo $(error USB=$(USB))
        include $(MCAL_STM32F4_DIR)/usb/usb.mk
    endif
endif
