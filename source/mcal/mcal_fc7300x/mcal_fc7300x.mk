ifneq ($(MCAL_FC7300X_DRV_MK_INC),Y)
    MCAL_FC7300X_DRV_MK_INC=Y

    MCAL_FC7300X_DIR = $(MCAL_DIR)/mcal_fc7300x
    #@echo $(error MCAL_FC7300X_DIR=$(MCAL_FC7300X_DIR))

    INCDIR += -I$(MCAL_FC7300X_DIR)
    #RCC=Y
    MCAL_FC7300X=Y
    MCAL_OPT += -DHAS_MCAL_FC7300X

    ifeq ($(DIAG),Y)
        #@echo $(error DIAG=$(DIAG))
        MCAL_OPT += -DHAS_HAL_DIAG
        SOURCES_C += $(MCAL_FC7300X_DIR)/hal_diag.c
    endif

    SOURCES_C += $(MCAL_FC7300X_DIR)/fc7300x_int.c
    SOURCES_C += $(MCAL_FC7300X_DIR)/fc7300x_misc.c
    #SOURCES_C += $(MCAL_FC7300X_DIR)/sys.c

    ifeq ($(ADC),Y)   
        #@echo $(error ADC=$(ADC))
        include $(MCAL_FC7300X_DIR)/adc/adc.mk
    endif

    ifeq ($(CAN),Y)
        #@echo $(error CAN=$(CAN))
        include $(MCAL_FC7300X_DIR)/can/can.mk
    endif
    
    ifeq ($(CLOCK),Y)
        #@echo $(error CLOCK=$(CLOCK)) 
        include $(MCAL_FC7300X_DIR)/clock/clock.mk
    endif

    ifeq ($(CRYP_HW),Y)
        $(info Add Crypto Driver)
        #@echo $(error CRYP=$(CRYP)) 
        include $(MCAL_FC7300X_DIR)/cryp/cryp.mk
    endif

    ifeq ($(DAC),Y)
        #@echo $(error DAC=$(DAC))
        include $(MCAL_FC7300X_DIR)/dac/dac.mk
    endif
    
    ifeq ($(DMA),Y)
        #@echo $(error DMA=$(DMA))
        include $(MCAL_FC7300X_DIR)/dma/dma.mk
    endif

    ifeq ($(EXT_INT),Y)
        #@echo $(error EXT_INT=$(EXT_INT))
        include $(MCAL_FC7300X_DIR)/ext_int/ext_int.mk
    endif

    ifeq ($(FLASH),Y)
        #@echo $(error FLASH=$(FLASH))
        include $(MCAL_FC7300X_DIR)/flash/flash.mk
    endif

    ifeq ($(GPIO),Y)
        #@echo $(error GPIO=$(GPIO))
        include $(MCAL_FC7300X_DIR)/gpio/gpio.mk
    endif

    ifeq ($(I2C),Y)
        #@echo $(error I2C=$(I2C))
        include $(MCAL_FC7300X_DIR)/i2c/i2c.mk
    endif

    ifeq ($(I2C_FSM),Y)
        #@echo $(error I2C=$(I2C))
        include $(MCAL_FC7300X_DIR)/i2c_fsm/i2c_fsm.mk
    endif
    
    ifeq ($(INPUT_CAPTURE),Y)   
        #@echo $(error INPUT_CAPTURE=$(INPUT_CAPTURE))
        include $(MCAL_FC7300X_DIR)/input_capture/input_capture.mk
    endif

    ifeq ($(INTERRUPT),Y)
        #@echo $(error INTERRUPT=$(INTERRUPT))
        include $(MCAL_FC7300X_DIR)/interrupt/interrupt.mk
    endif

    ifeq ($(IOMUX),Y)
        #@echo $(error IOMUX=$(IOMUX))
        include $(MCAL_FC7300X_DIR)/iomux/iomux.mk
    endif

    ifeq ($(MULTICORE),Y)
        #@echo $(error MULTICORE=$(MULTICORE))
        include $(MCAL_FC7300X_DIR)/multicore/multicore.mk
    endif

    ifeq ($(NVS),Y)
        #@echo $(error NVS=$(NVS))
        include $(MCAL_FC7300X_DIR)/nvs/nvs.mk
    endif

    ifeq ($(MCO),Y)
        #@echo $(error SWD=$(SWD)) 
        include $(MCAL_FC7300X_DIR)/mco/mco.mk
    endif
    
    ifeq ($(POWER),Y)
        include $(MCAL_FC7300X_DIR)/power/power.mk
    endif

    ifeq ($(PWM),Y)
        #@echo $(error PWM=$(PWM)) 
        include $(MCAL_FC7300X_DIR)/pwm/pwm.mk
    endif

    ifeq ($(SPI),Y)
        #@echo $(error SPI=$(SPI))
        include $(MCAL_FC7300X_DIR)/spi/spi.mk
    endif

    ifeq ($(SYSTICK),Y)   
        #@echo $(error SYSTICK=$(SYSTICK))
        include $(MCAL_FC7300X_DIR)/systick/systick.mk
    endif

    ifeq ($(SWD),Y)
        #@echo $(error SWD=$(SWD)) 
        include $(MCAL_FC7300X_DIR)/swd/swd.mk
    endif
    
    ifeq ($(MAILBOX),Y)   
        #@echo $(error MAILBOX=$(MAILBOX))
        include $(MCAL_FC7300X_DIR)/mailbox/mailbox.mk
    endif

    ifeq ($(CLOCK_OUT),Y)
        #@echo $(error CLOCK_OUT=$(CLOCK_OUT))
        include $(MCAL_FC7300X_DIR)/clock_out/clock_out.mk
    endif

    ifeq ($(TIMER),Y)   
        #@echo $(error TIMER=$(TIMER))
        include $(MCAL_FC7300X_DIR)/timer/timer.mk
    endif

    ifeq ($(UART),Y) 
        #@echo $(error UART=$(UART))
        include $(MCAL_FC7300X_DIR)/uart/uart.mk
    endif
    
    ifeq ($(WATCHDOG),Y)
        #@echo $(error WATCHDOG=$(WATCHDOG))
        include $(MCAL_FC7300X_DIR)/watchdog/wdt.mk
    endif

endif
