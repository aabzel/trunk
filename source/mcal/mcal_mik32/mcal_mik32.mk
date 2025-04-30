ifneq ($(MCAL_MIK32_DRV_MK_INC),Y)
    MCAL_MIK32_DRV_MK_INC=Y

    MCAL_MIK32_DIR = $(MCAL_DIR)/mcal_mik32
    # $(error MCAL_MIK32_DIR=$(MCAL_MIK32_DIR))

    INCDIR += -I$(MCAL_MIK32_DIR)
    MCAL_MIK32=Y
    OPT += -DHAS_MIK32

    ifeq ($(DIAG),Y)
        #@echo $(error DIAG=$(DIAG))
        OPT += -DHAS_HAL_DIAG
        SOURCES_C += $(MCAL_MIK32_DIR)/hal_diag.c
    endif


    SOURCES_C += $(MCAL_MIK32_DIR)/mik32_it.c
    SOURCES_C += $(MCAL_MIK32_DIR)/hal_mcal.c

    ifeq ($(BOOT_MANAGER),Y)   
        include $(MCAL_MIK32_DIR)/boot_manager/boot_manager.mk
    endif
       
    ifeq ($(ADC),Y)   
        #@echo $(error ADC=$(ADC))
        include $(MCAL_MIK32_DIR)/adc/adc.mk
    endif

    ifeq ($(CRYP_HW),Y)
        $(info Add Crypto Driver)
        #@echo $(error CRYP=$(CRYP)) 
        include $(MCAL_MIK32_DIR)/cryp/cryp.mk
    endif

    ifeq ($(CLOCK),Y)  
        #@echo $(error CLOCK=$(CLOCK)) 
        include $(MCAL_MIK32_DIR)/clock/clock.mk
    endif

    ifeq ($(DMA),Y)   
        #@echo $(error DMA=$(DMA))
        include $(MCAL_MIK32_DIR)/dma/dma.mk
    endif

    ifeq ($(FLASH),Y)   
        #@echo $(error FLASH=$(FLASH))
        include $(MCAL_MIK32_DIR)/flash/flash.mk
    endif

    ifeq ($(EEPROM),Y)   
        #@echo $(error EEPROM=$(EEPROM))
        include $(MCAL_MIK32_DIR)/eeprom/eeprom.mk
    endif
    
    ifeq ($(GPIO),Y) 
        #@echo $(error GPIO=$(GPIO))
        include $(MCAL_MIK32_DIR)/gpio/gpio.mk
    endif

    ifeq ($(I2C),Y) 
        #@echo $(error I2C=$(I2C))
        include $(MCAL_MIK32_DIR)/i2c/i2c.mk
    endif

    ifeq ($(INTERRUPT),Y) 
        #@echo $(error INTERRUPT=$(INTERRUPT))
        include $(MCAL_MIK32_DIR)/interrupt/interrupt.mk
    endif

    ifeq ($(NVS),Y)
        #@echo $(error NVS=$(NVS))
        include $(MCAL_MIK32_DIR)/nvs/nvs.mk
    endif

    ifeq ($(MCO),Y)
        #@echo $(error SWD=$(SWD)) 
        include $(MCAL_MIK32_DIR)/mco/mco.mk
    endif

    ifeq ($(PWM),Y)
        #@echo $(error PWM=$(PWM)) 
        include $(MCAL_MIK32_DIR)/pwm/pwm.mk
    endif

    ifeq ($(RTC),Y)
        #@echo $(error RTC=$(RTC))
        include $(MCAL_MIK32_DIR)/rtc/rtc_internal.mk
    endif

    ifeq ($(SPI),Y) 
        #@echo $(error SPI=$(SPI))
        include $(MCAL_MIK32_DIR)/spi/spi.mk
    endif

    ifeq ($(SPIFI),Y) 
        #@echo $(error SPI=$(SPI))
        include $(MCAL_MIK32_DIR)/spifi/spifi.mk
    endif

    ifeq ($(TIMER),Y)   
        #@echo $(error TIMER=$(TIMER))
        include $(MCAL_MIK32_DIR)/timer/timer.mk
    endif

    ifeq ($(UART),Y) 
        # $(error UART=$(UART))
        include $(MCAL_MIK32_DIR)/uart/uart.mk
    endif

    ifeq ($(WATCHDOG),Y) 
        #@echo $(error WATCHDOG=$(WATCHDOG))
        include $(MCAL_MIK32_DIR)/watchdog/watchdog.mk
    endif
endif
