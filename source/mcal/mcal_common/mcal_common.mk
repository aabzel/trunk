ifneq ($(MCAL_COMMON_MK_INC),Y)
    MCAL_COMMON_MK_INC=Y

    MCAL_COMMON_DIR = $(MCAL_DIR)/mcal_common
    # $(error MCAL_COMMON_DIR=$(MCAL_COMMON_DIR))

    INCDIR += -I$(MCAL_COMMON_DIR)

    MCAL_OPT += -DHAS_MCAL
    MCAL_OPT += -DHAS_MCAL_COMMANDS

    ifeq ($(DIAG),Y)
        SOURCES_C += $(MCAL_COMMON_DIR)/mcal_diag.c
    endif

    ifeq ($(ACC),Y)
        include $(MCAL_COMMON_DIR)/acc/acc.mk
    endif

    ifeq ($(ADC),Y)
        include $(MCAL_COMMON_DIR)/adc/adc.mk
    endif

    ifeq ($(LOCKSTEP),Y)
        #  $(error LOCKSTEP=$(LOCKSTEP))
        include $(MCAL_COMMON_DIR)/lockstep/lockstep.mk
    endif
    
    ifeq ($(MULTICORE),Y)
        #  $(error MULTICORE=$(MULTICORE))
        include $(MCAL_COMMON_DIR)/multicore/multicore.mk
    endif

    ifeq ($(MAILBOX),Y)
        include $(MCAL_COMMON_DIR)/mailbox/mailbox.mk
    endif

    ifeq ($(CLOCK_OUT),Y)
        #  $(error CLOCK_OUT=$(CLOCK_OUT))
        include $(MCAL_COMMON_DIR)/clock_out/clock_out.mk
    endif

    ifeq ($(CAN),Y)
        #  $(error CAN=$(CAN))
        include $(MCAL_COMMON_DIR)/can/can.mk
    endif

    ifeq ($(EIM),Y)
        #  $(error EIM=$(EIM))
        include $(MCAL_COMMON_DIR)/eim/eim.mk
    endif

    ifeq ($(ERM),Y)
        #  $(error ERM=$(ERM))
        include $(MCAL_COMMON_DIR)/erm/erm.mk
    endif

    ifeq ($(EEPROM),Y)
        #  $(error EEPROM=$(EEPROM))
        include $(MCAL_COMMON_DIR)/eeprom/eeprom.mk
    endif

    ifeq ($(CLOCK),Y)
        #  $(error CLOCK=$(CLOCK))
        include $(MCAL_COMMON_DIR)/clock/clock.mk
    endif

    ifeq ($(POWER),Y)
        #  $(error POWER=$(POWER))
        include $(MCAL_COMMON_DIR)/power/power.mk
    endif

    ifeq ($(PIN),Y)
        #  $(error PIN=$(PIN))
        include $(MCAL_COMMON_DIR)/pin/pin.mk
    endif

    ifeq ($(DAC),Y)
        #  $(error DAC=$(DAC))
        include $(MCAL_COMMON_DIR)/dac/dac.mk
    endif
    
    ifeq ($(DMA),Y)
        include $(MCAL_COMMON_DIR)/dma/dma.mk
    endif

    ifeq ($(DMA_CHANNEL),Y)
        include $(MCAL_COMMON_DIR)/dma_channel/dma_channel.mk
    endif

    ifeq ($(EXT_INT),Y)
        #  $(error EXT_INT=[$(EXT_INT)])
        include $(MCAL_COMMON_DIR)/ext_int/ext_int.mk
    endif

    ifeq ($(FCSMU),Y) 
        #  $(error FCSMU=[$(FCSMU)])
        include $(MCAL_COMMON_DIR)/fcsmu/fcsmu.mk
    endif

    ifeq ($(FLASH),Y) 
        #  $(error FLASH=[$(FLASH)])
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
        #  $(error I2S=$(I2S))
        include $(MCAL_COMMON_DIR)/i2s/i2s.mk
    endif
    
    ifeq ($(I2S_FULL_DUPLEX),Y)
        #  $(error I2S_FULL_DUPLEX=$(I2S_FULL_DUPLEX))
        include $(MCAL_COMMON_DIR)/i2s_full_duplex/i2s_full_duplex.mk
    endif

    ifeq ($(INPUT_CAPTURE),Y)
        #  $(error INPUT_CAPTURE=$(INPUT_CAPTURE))
        include $(MCAL_COMMON_DIR)/input_capture/input_capture.mk
    endif

    ifeq ($(IOMUX),Y) 
        include $(MCAL_COMMON_DIR)/iomux/iomux.mk
    endif

    ifeq ($(NVS),Y) 
        include $(MCAL_COMMON_DIR)/nvs/nvs.mk
    endif

    ifeq ($(MAM),Y)
        #MAM Matrix Access Monitor
        include $(MCAL_COMMON_DIR)/mam/mam.mk
    endif

    ifeq ($(MPU),Y) 
        include $(MCAL_COMMON_DIR)/mpu/mpu.mk
    endif

    ifeq ($(PDM),Y) 
        #  $(error PDM=$(PDM))
        include $(MCAL_COMMON_DIR)/pdm/pdm.mk
    endif

    ifeq ($(RTC),Y)
        include $(MCAL_COMMON_DIR)/rtc/rtc.mk
    endif

    ifeq ($(PWM),Y) 
        #  $(error PWM=$(PWM))
        include $(MCAL_COMMON_DIR)/pwm/pwm.mk
    endif

    ifeq ($(QSPI),Y)
        include $(MCAL_COMMON_DIR)/qspi/qspi.mk
    endif

    ifeq ($(SPIFI),Y)
        include $(MCAL_COMMON_DIR)/spifi/spifi.mk
    endif

    ifeq ($(SWD),Y)
        #  $(error SWD=$(SWD))
        include $(MCAL_COMMON_DIR)/swd/swd.mk
    endif

    ifeq ($(SDIO),Y) 
        #  $(error SDIO=$(SDIO))
        include $(MCAL_COMMON_DIR)/sdio/sdio.mk
    endif

    ifeq ($(SPI),Y) 
        #  $(error SPI=$(SPI))
        include $(MCAL_COMMON_DIR)/spi/spi.mk
    endif

    ifeq ($(TRNG),Y) 
        #  $(error TRNG=[$(TRNG)])
        include $(MCAL_COMMON_DIR)/trng/trng.mk
    endif

    ifeq ($(TIMER),Y)
        #  $(error TIMER=[$(TIMER)])
        include $(MCAL_COMMON_DIR)/timer/timer.mk
    endif

    ifeq ($(UART),Y) 
        #  $(error UART=$(UART))
        include $(MCAL_COMMON_DIR)/uart/uart.mk
    endif

    ifeq ($(TRG),Y)
        # True random generator
        include $(MCAL_COMMON_DIR)/trg/trg.mk
    endif

    ifeq ($(MCAL_USB),Y)
        #  $(error USB=$(USB))
        include $(MCAL_COMMON_DIR)/usb/usb.mk
    endif

    ifeq ($(WATCHDOG),Y)
        include $(MCAL_COMMON_DIR)/watchdog/watchdog.mk
    endif
endif
