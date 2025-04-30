ifneq ($(MCAL_NRF5340_DRV_MK_INC),Y)
    MCAL_NRF5340_DRV_MK_INC=Y

    MCAL_NRF5340_DIR = $(MCAL_DIR)/mcal_nrf5340
    #@echo $(error MCAL_NRF5340_DIR=$(MCAL_NRF5340_DIR))
    INCDIR += -I$(MCAL_NRF5340_DIR)
    OPT += -DHAS_MCAL_NRF5340
    OPT += -DHAS_NRF

    #OPT += -DNRFX_CUSTOM_ERROR_CODES
    SOURCES_C += $(MCAL_NRF5340_DIR)/nrfx_it.c
    ifeq ($(DIAG),Y)
        SOURCES_C += $(MCAL_NRF5340_DIR)/hal_nrfx_diag.c
    endif

    ifeq ($(ADC),Y)
        #@echo $(error ADC=$(ADC)) 
        include $(MCAL_NRF5340_DIR)/adc/adc.mk
    endif

    ifeq ($(FLASH),Y)
        #@echo $(error FLASH=$(FLASH)) 
        include $(MCAL_NRF5340_DIR)/flash/flash.mk
    endif

    ifeq ($(GPIO),Y)
        include $(MCAL_NRF5340_DIR)/gpio/gpio.mk
    endif

    ifeq ($(CLOCK),Y)
        #@echo $(error CLOCK=$(CLOCK)) 
        include $(MCAL_NRF5340_DIR)/clock/clock.mk
    endif

    ifeq ($(TIMER),Y)
        #@echo $(error TIMER=$(TIMER)) 
        include $(MCAL_NRF5340_DIR)/timer/timer.mk
    endif

    ifeq ($(I2S),Y)
        #@echo $(error I2S=$(I2S)) 
        include $(MCAL_NRF5340_DIR)/i2s/i2s.mk
    endif

    ifeq ($(I2C),Y)
        #@echo $(error I2C=$(I2C)) 
        include $(MCAL_NRF5340_DIR)/i2c/i2c.mk
    endif

    ifeq ($(IPC),Y)
        #@echo $(error IPC=$(IPC)) 
        include $(MCAL_NRF5340_DIR)/ipc/ipc.mk
    endif

    ifeq ($(NVS),Y)
        #@echo $(error NVS=$(NVS)) 
        include $(MCAL_NRF5340_DIR)/nvs/nvs.mk
    endif

    ifeq ($(PDM),Y)
        include $(MCAL_NRF5340_DIR)/pdm/pdm.mk
    endif

    ifeq ($(PWM),Y)
        #@echo $(error PWM=$(PWM)) 
        include $(MCAL_NRF5340_DIR)/pwm/pwm.mk
    endif

    ifeq ($(RTC),Y)
        #@echo $(error RTC=$(RTC)) 
        include $(MCAL_NRF5340_DIR)/rtc/rtc.mk
    endif

    ifeq ($(QSPI),Y)
        include $(MCAL_NRF5340_DIR)/qspi/qspi.mk
    endif

    ifeq ($(SPI),Y)
        #@echo $(error SPI=$(SPI)) 
        include $(MCAL_NRF5340_DIR)/spi/spi.mk
    endif

    ifeq ($(SYSTICK),Y)
        include $(MCAL_NRF5340_DIR)/systick/systick.mk
    endif

    include $(MCAL_NRF5340_DIR)/cores/nrf_cores.mk

    ifeq ($(UART),Y)
        #@echo $(error UART=$(UART)) 
        include $(MCAL_NRF5340_DIR)/uart/uart.mk
    endif

    ifeq ($(USB),Y) 
        #@echo $(error USB=$(USB)) 
        include $(MCAL_NRF5340_DIR)/usb/usb.mk
    endif
endif
