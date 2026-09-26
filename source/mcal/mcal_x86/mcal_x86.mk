ifneq ($(MCAL_X86_DRV_MK_INC),Y)
    MCAL_X86_DRV_MK_INC=Y

    MCAL_X86_DIR = $(MCAL_DIR)/mcal_x86
    # $(error MCAL_X86_DIR=$(MCAL_X86_DIR))

    INCDIR += -I$(MCAL_X86_DIR)
 
    MCAL_X86=Y
    MCAL_OPT += -DHAS_MCAL_X86

    SOURCES_C += $(MCAL_X86_DIR)/x86x_misc.c
    ifeq ($(DIAG),Y)
        # $(error DIAG=$(DIAG))
        MCAL_OPT += -DHAS_HAL_DIAG
        SOURCES_C += $(MCAL_X86_DIR)/hal_diag.c
    endif

    ifeq ($(ADC),Y)   
        # $(error ADC=$(ADC))
        include $(MCAL_X86_DIR)/adc/adc.mk
    endif

    ifeq ($(CAN),Y)
        # $(error CAN=$(CAN))
        include $(MCAL_X86_DIR)/can/can.mk
    endif
    
    ifeq ($(CLOCK),Y)
        # $(error CLOCK=$(CLOCK)) 
        include $(MCAL_X86_DIR)/clock/clock.mk
    endif

    ifeq ($(CRYP_HW),Y)
        $(info Add Crypto Driver)
        # $(error CRYP=$(CRYP)) 
        include $(MCAL_X86_DIR)/cryp/cryp.mk
    endif

    ifeq ($(DAC),Y)
        # $(error DAC=$(DAC))
        include $(MCAL_X86_DIR)/dac/dac.mk
    endif
    
    ifeq ($(DMA),Y)
        # $(error DMA=$(DMA))
        include $(MCAL_X86_DIR)/dma/dma.mk
    endif

    ifeq ($(EXT_INT),Y)
        # $(error EXT_INT=$(EXT_INT))
        include $(MCAL_X86_DIR)/ext_int/ext_int.mk
    endif

    ifeq ($(FLASH),Y)
        # $(error FLASH=$(FLASH))
        include $(MCAL_X86_DIR)/flash/flash.mk
    endif

    ifeq ($(GPIO),Y)
        # $(error GPIO=$(GPIO))
        include $(MCAL_X86_DIR)/gpio/gpio.mk
    endif

    ifeq ($(I2C),Y)
        # $(error I2C=$(I2C))
        include $(MCAL_X86_DIR)/i2c/i2c.mk
    endif

    ifeq ($(I2C_FSM),Y)
        # $(error I2C=$(I2C))
        include $(MCAL_X86_DIR)/i2c_fsm/i2c_fsm.mk
    endif
    
    ifeq ($(INPUT_CAPTURE),Y)   
        # $(error INPUT_CAPTURE=$(INPUT_CAPTURE))
        include $(MCAL_X86_DIR)/input_capture/input_capture.mk
    endif

    ifeq ($(INTERRUPT),Y)
        # $(error INTERRUPT=$(INTERRUPT))
        # include $(MCAL_X86_DIR)/interrupt/interrupt.mk
    endif

    ifeq ($(IOMUX),Y)
        # $(error IOMUX=$(IOMUX))
        include $(MCAL_X86_DIR)/iomux/iomux.mk
    endif

    ifeq ($(MULTICORE),Y)
        # $(error MULTICORE=$(MULTICORE))
        include $(MCAL_X86_DIR)/multicore/multicore.mk
    endif

    ifeq ($(NVS),Y)
        # $(error NVS=$(NVS))
        include $(MCAL_X86_DIR)/nvs/nvs.mk
    endif

    ifeq ($(MCO),Y)
        # $(error SWD=$(SWD)) 
        include $(MCAL_X86_DIR)/mco/mco.mk
    endif
    
    ifeq ($(POWER),Y)
        include $(MCAL_X86_DIR)/power/power.mk
    endif

    ifeq ($(PWM),Y)
        # $(error PWM=$(PWM)) 
        include $(MCAL_X86_DIR)/pwm/pwm.mk
    endif

    ifeq ($(SPI),Y)
        # $(error SPI=$(SPI))
        include $(MCAL_X86_DIR)/spi/spi.mk
    endif

    ifeq ($(SYSTICK),Y)   
        # $(error SYSTICK=$(SYSTICK))
        include $(MCAL_X86_DIR)/systick/systick.mk
    endif

    ifeq ($(SWD),Y)
        # $(error SWD=$(SWD)) 
        include $(MCAL_X86_DIR)/swd/swd.mk
    endif
    
    ifeq ($(MAILBOX),Y)   
        # $(error MAILBOX=$(MAILBOX))
        include $(MCAL_X86_DIR)/mailbox/mailbox.mk
    endif

    ifeq ($(CLOCK_OUT),Y)
        # $(error CLOCK_OUT=$(CLOCK_OUT))
        include $(MCAL_X86_DIR)/clock_out/clock_out.mk
    endif

    ifeq ($(TRNG),Y)   
        # $(error TRNG=$(TRNG))
        include $(MCAL_X86_DIR)/trng/trng.mk
    endif
    
    ifeq ($(TIMER),Y)   
        # $(error TIMER=$(TIMER))
        include $(MCAL_X86_DIR)/timer/timer.mk
    endif

    ifeq ($(UART),Y) 
        # $(error UART=$(UART))
        include $(MCAL_X86_DIR)/uart/uart.mk
    endif
    
    ifeq ($(WATCHDOG),Y)
        # $(error WATCHDOG=$(WATCHDOG))
        include $(MCAL_X86_DIR)/watchdog/wdt.mk
    endif

endif
