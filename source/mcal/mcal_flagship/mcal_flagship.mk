ifneq ($(MCAL_FLAGSHIP_DRV_MK_INC),Y)
    MCAL_FLAGSHIP_DRV_MK_INC=Y

    MCAL_FLAGSHIP_DIR = $(MCAL_DIR)/mcal_flagship
    # $(error MCAL_FLAGSHIP_DIR=$(MCAL_FLAGSHIP_DIR))

    INCDIR += -I$(MCAL_FLAGSHIP_DIR)
    #RCC=Y
    MCAL_FLAGSHIP=Y
    MCAL_OPT += -DHAS_MCAL_FLAGSHIP

    SOURCES_C += $(MCAL_FLAGSHIP_DIR)/mcal_flagship_misc.c
    
    ifeq ($(ACC),Y)       
        include $(MCAL_FLAGSHIP_DIR)/acc/acc.mk
    endif

    ifeq ($(ADC),Y)   
        # $(error ADC=$(ADC))
        include $(MCAL_FLAGSHIP_DIR)/adc/adc.mk
    endif
    
    ifeq ($(CAN),Y)
        # $(error CAN=$(CAN))
        include $(MCAL_FLAGSHIP_DIR)/can/can.mk
    endif
    
    ifeq ($(CLOCK),Y)
        # $(error CLOCK=$(CLOCK)) 
        include $(MCAL_FLAGSHIP_DIR)/clock/clock.mk
    endif

    ifeq ($(CLOCK_OUT),Y)
        # $(error CLOCK_OUT=$(CLOCK_OUT))
        include $(MCAL_FLAGSHIP_DIR)/clock_out/clock_out.mk
    endif

    ifeq ($(CRYP_HW),Y)
        $(info Add Crypto Driver)
        # $(error CRYP=$(CRYP)) 
        include $(MCAL_FLAGSHIP_DIR)/cryp/cryp.mk
    endif

    ifeq ($(DAC),Y)
        # $(error DAC=$(DAC))
        include $(MCAL_FLAGSHIP_DIR)/dac/dac.mk
    endif
    
    ifeq ($(DMA),Y)
        # $(error DMA=$(DMA))
        include $(MCAL_FLAGSHIP_DIR)/dma/dma.mk
    endif
    
    ifeq ($(DMA_CHANNEL),Y)
        # $(error DMA_CHANNEL=$(DMA_CHANNEL))
        include $(MCAL_FLAGSHIP_DIR)/dma_channel/dma_channel.mk
    endif
    
    ifeq ($(ERM),Y)   
        # $(error ERM=$(ERM))
        include $(MCAL_FLAGSHIP_DIR)/erm/erm.mk
    endif

    ifeq ($(EIM),Y)   
        # $(error EIM=$(EIM))
        include $(MCAL_FLAGSHIP_DIR)/eim/eim.mk
    endif

    ifeq ($(EXT_INT),Y)
        # $(error EXT_INT=$(EXT_INT))
        include $(MCAL_FLAGSHIP_DIR)/ext_int/ext_int.mk
    endif

    ifeq ($(FLASH),Y)
        # $(error FLASH=$(FLASH))
        include $(MCAL_FLAGSHIP_DIR)/flash/flash.mk
    endif

    ifeq ($(FCSMU),Y)
        # $(error FCSMU=$(FCSMU)) 
        include $(MCAL_FLAGSHIP_DIR)/fcsmu/fcsmu.mk
    endif

    ifeq ($(GPIO),Y)
        # $(error GPIO=$(GPIO))
        include $(MCAL_FLAGSHIP_DIR)/gpio/gpio.mk
    endif

    ifeq ($(I2C),Y)
        # $(error I2C=$(I2C))
        include $(MCAL_FLAGSHIP_DIR)/i2c/i2c.mk
    endif

    ifeq ($(I2C_FSM),Y)
        # $(error I2C=$(I2C))
        include $(MCAL_FLAGSHIP_DIR)/i2c_fsm/i2c_fsm.mk
    endif
    
    ifeq ($(INPUT_CAPTURE),Y)   
        # $(error INPUT_CAPTURE=$(INPUT_CAPTURE))
        include $(MCAL_FLAGSHIP_DIR)/input_capture/input_capture.mk
    endif

    ifeq ($(INTERRUPT),Y)
        # $(error INTERRUPT=$(INTERRUPT))
        include $(MCAL_FLAGSHIP_DIR)/interrupt/interrupt.mk
    endif

    ifeq ($(IOMUX),Y)
        # $(error IOMUX=$(IOMUX))
        include $(MCAL_FLAGSHIP_DIR)/iomux/iomux.mk
    endif

    ifeq ($(LOCKSTEP),Y)
        # $(error LOCKSTEP=$(LOCKSTEP))
        include $(MCAL_FLAGSHIP_DIR)/lockstep/lockstep.mk
    endif

    ifeq ($(MAM),Y)
        # $(error MAM=$(MAM)) 
        include $(MCAL_FLAGSHIP_DIR)/mam/mam.mk
    endif
    
    ifeq ($(MAILBOX),Y)   
        # $(error MAILBOX=$(MAILBOX))
        include $(MCAL_FLAGSHIP_DIR)/mailbox/mailbox.mk
    endif

    ifeq ($(MCO),Y)
        # $(error SWD=$(SWD)) 
        include $(MCAL_FLAGSHIP_DIR)/mco/mco.mk
    endif

    ifeq ($(MULTICORE),Y)
        # $(error MULTICORE=$(MULTICORE))
        include $(MCAL_FLAGSHIP_DIR)/multicore/multicore.mk
    endif

    ifeq ($(NVS),Y)
        # $(error NVS=$(NVS))
        include $(MCAL_FLAGSHIP_DIR)/nvs/nvs.mk
    endif

    ifeq ($(MPU),Y)
        # $(error MPU=$(MPU)) 
        include $(MCAL_FLAGSHIP_DIR)/mpu/mpu.mk
    endif
    
    
    ifeq ($(POWER),Y)
        include $(MCAL_FLAGSHIP_DIR)/power/power.mk
    endif

    ifeq ($(PWM),Y)
        # $(error PWM=$(PWM)) 
        include $(MCAL_FLAGSHIP_DIR)/pwm/pwm.mk
    endif

    ifeq ($(SPI),Y)
        # $(error SPI=$(SPI))
        include $(MCAL_FLAGSHIP_DIR)/spi/spi.mk
    endif

    ifeq ($(SYSTICK),Y)   
        # $(error SYSTICK=$(SYSTICK))
        include $(MCAL_FLAGSHIP_DIR)/systick/systick.mk
    endif

    ifeq ($(SWD),Y)
        # $(error SWD=$(SWD)) 
        include $(MCAL_FLAGSHIP_DIR)/swd/swd.mk
    endif

    ifeq ($(TIMER),Y)   
        # $(error TIMER=$(TIMER))
        include $(MCAL_FLAGSHIP_DIR)/timer/timer.mk
    endif

    ifeq ($(UART),Y) 
        # $(error UART=$(UART))
        include $(MCAL_FLAGSHIP_DIR)/uart/uart.mk
    endif
    
    ifeq ($(WATCHDOG),Y)
        # $(error WATCHDOG=$(WATCHDOG))
        include $(MCAL_FLAGSHIP_DIR)/watchdog/wdt.mk
    endif

endif
