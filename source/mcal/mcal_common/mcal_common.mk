ifneq ($(MCAL_COMMON_MK_INC),Y)
    MCAL_COMMON_MK_INC=Y

    MCAL_COMMON_DIR = $(MCAL_DIR)/mcal_common
    # $(error MCAL_COMMON_DIR=$(MCAL_COMMON_DIR))

    INCDIR += -I$(MCAL_COMMON_DIR)

    OPT += -DHAS_MCAL
    OPT += -DHAS_MCAL_COMMANDS

    ifeq ($(DIAG),Y)
        SOURCES_C += $(MCAL_COMMON_DIR)/mcal_diag.c
    endif

    ifeq ($(ADC),Y)
        include $(MCAL_COMMON_DIR)/adc/adc.mk
    endif

    ifeq ($(CAN),Y)
        #@echo $(error CAN=$(CAN))
        include $(MCAL_COMMON_DIR)/can/can.mk
    endif

    ifeq ($(EEPROM),Y)
        #@echo $(error EEPROM=$(EEPROM))
        include $(MCAL_COMMON_DIR)/eeprom/eeprom.mk
    endif

    ifeq ($(CLOCK),Y)
        #@echo $(error CLOCK=$(CLOCK))
        include $(MCAL_COMMON_DIR)/clock/clock.mk
    endif

    ifeq ($(POWER),Y)
        #@echo $(error POWER=$(POWER))
        include $(MCAL_COMMON_DIR)/power/power.mk
    endif


    ifeq ($(DAC),Y)
        #@echo $(error DAC=$(DAC))
        include $(MCAL_COMMON_DIR)/dac/dac.mk
    endif
    
    ifeq ($(DMA),Y)
        include $(MCAL_COMMON_DIR)/dma/dma.mk
    endif

    ifeq ($(EXT_INT),Y)
        #@echo $(error EXT_INT=[$(EXT_INT)])
        include $(MCAL_COMMON_DIR)/ext_int/ext_int.mk
    endif

    ifeq ($(FLASH),Y) 
        #@echo $(error FLASH=[$(FLASH)])
        include $(MCAL_COMMON_DIR)/flash/flash.mk
    endif

    ifeq ($(GPIO),Y) 
        include $(MCAL_COMMON_DIR)/gpio/gpio.mk
    endif

    ifeq ($(INTERRUPT),Y) 
        include $(MCAL_COMMON_DIR)/interrupt/interrupt.mk
    endif

    ifeq ($(I2C),Y) 
        include $(MCAL_COMMON_DIR)/i2c/i2c.mk

        ifeq ($(I2C_FSM),Y) 
            include $(MCAL_COMMON_DIR)/i2c_fsm/i2c_fsm.mk
        endif
    endif

    ifeq ($(I2S),Y)
        #@echo $(error I2S=$(I2S))
        include $(MCAL_COMMON_DIR)/i2s/i2s.mk
    endif
    
    ifeq ($(I2S_FULL_DUPLEX),Y)
        #@echo $(error I2S_FULL_DUPLEX=$(I2S_FULL_DUPLEX))
        include $(MCAL_COMMON_DIR)/i2s_full_duplex/i2s_full_duplex.mk
    endif

    ifeq ($(INPUT_CAPTURE),Y)
        #@echo $(error INPUT_CAPTURE=$(INPUT_CAPTURE))
        include $(MCAL_COMMON_DIR)/input_capture/input_capture.mk
    endif

    ifeq ($(IOMUX),Y) 
        include $(MCAL_COMMON_DIR)/iomux/iomux.mk
    endif

    ifeq ($(NVS),Y) 
        include $(MCAL_COMMON_DIR)/nvs/nvs.mk
    endif

    ifeq ($(PDM),Y) 
        #@echo $(error PDM=$(PDM))
        include $(MCAL_COMMON_DIR)/pdm/pdm.mk
    endif

    ifeq ($(QSPI),Y)
        include $(MCAL_COMMON_DIR)/qspi/qspi.mk
    endif

    ifeq ($(RTC),Y)
        include $(MCAL_COMMON_DIR)/rtc/rtc.mk
    endif

    ifeq ($(PWM),Y) 
        #@echo $(error PWM=$(PWM))
        include $(MCAL_COMMON_DIR)/pwm/pwm.mk
    endif

    ifeq ($(SPIFI),Y)
        include $(MCAL_COMMON_DIR)/spifi/spifi.mk
    endif

    ifeq ($(SWD),Y)
        #@echo $(error SWD=$(SWD))
        include $(MCAL_COMMON_DIR)/swd/swd.mk
    endif

    ifeq ($(SDIO),Y) 
        #@echo $(error SDIO=$(SDIO))
        include $(MCAL_COMMON_DIR)/sdio/sdio.mk
    endif

    ifeq ($(SPI),Y) 
        #@echo $(error SPI=$(SPI))
        include $(MCAL_COMMON_DIR)/spi/spi.mk
    endif

    ifeq ($(TIMER),Y)
        #@echo $(error TIMER=[$(TIMER)])
        include $(MCAL_COMMON_DIR)/timer/timer.mk
    endif

    ifeq ($(UART),Y) 
        #@echo $(error UART=$(UART))
        include $(MCAL_COMMON_DIR)/uart/uart.mk
    endif

    ifeq ($(USB),Y)
        #@echo $(error USB=$(USB))
        include $(MCAL_COMMON_DIR)/usb/usb.mk
    endif

    ifeq ($(WATCHDOG),Y)
        include $(MCAL_COMMON_DIR)/watchdog/watchdog.mk
    endif
endif
