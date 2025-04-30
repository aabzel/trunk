$(info MINI_M4_MK_INC=$(MINI_M4_MK_INC))

ifneq ($(MINI_M4_MK_INC),Y)
    MINI_M4_MK_INC=Y
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    BOARD_CFG_DIR = $(BOARD_DIR)/mini_m4
    #@echo $(error BOARD_CFG_DIR=$(BOARD_CFG_DIR))

    ifneq ($(STM32F415RG),Y)
        @echo $(error mini-m4 board needs STM32F415RG)
    endif

    MICROCONTROLLER=Y
    MINI_M4=Y
    OPT += -DHAS_MINI_M4

    INCDIR += -I$(BOARD_CFG_DIR)

    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_config.c

    ifeq ($(GPIO),Y)
        $(info Config GPIO)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gpio_config.c
    endif

    ifeq ($(KEEPASS),Y)
        $(info Config KEEPASS)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/keepass_config.c
    endif

    ifeq ($(SPI),Y)
        $(info Config SPI)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/spi_config.c
    endif

    ifeq ($(SD_CARD),Y)
        $(info Config SD_CARD)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sd_card_config.c
    endif

    ifeq ($(HEALTH_MONITOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_monitor.c
    endif

    #include $(WORKSPACE_LOC)/mcu/stm32f415rg/stm32f415rg.mk
    #include $(WORKSPACE_LOC)/stm32.mk

    ifeq ($(PINS),Y)
        $(info Config Pins)
        OPT += -DHAS_PINS
    endif

    ifeq ($(SOFTWARE_TIMER),Y)
        $(info Config Software Timer)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sw_timer_config.c
    endif

    ifeq ($(CLOCK),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/clock_config.c
    endif

    ifeq ($(CRYP),Y)
        $(info Config Crypt)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cryp_config.c
    endif

    ifeq ($(FLASH),Y)
        $(info Config Flash)
        #@echo $(error FLASH=$(FLASH))
        ifeq ($(GENERIC_MONOLITHIC),Y)
            OPT += -DHAS_GENERIC_MONOLITHIC
            SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/flash_config_monolithic.c
        else
            SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/flash_config.c
        endif
    endif



    ifeq ($(LED),Y)
        $(info Config LED)
        ifeq ($(LED_MONO),Y)
            $(info Config LED MONO)
            #@echo $(error LED_MONO=$(LED_MONO))
            OPT += -DHAS_LED_MONO
            SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/led_mono_config.c
        endif
    endif





    ifeq ($(SDIO),Y)
        $(info Config SDIO)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sdio_config.c
    endif

    ifeq ($(GENERIC),Y)
        ifeq ($(TIMER),Y)
            #@echo $(error TIMER=$(TIMER))
            OPT += -DHAS_TIMER
            OPT += -DHAS_TIMER1
            OPT += -DHAS_TIMER2
            OPT += -DHAS_TIMER3
            OPT += -DHAS_TIMER5
            SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/timer_config.c
        endif
    endif

    ifeq ($(UART),Y)
        $(info Config UART)
        OPT += -DHAS_UART1
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/uart_config.c
    endif

    ifeq ($(USB),Y)
        #$(info Config USB)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/usb_config.c
    endif

    ifeq ($(GENERIC),Y)
        OPT += -DHAS_DMA1
        OPT += -DHAS_DMA2
        #DMA is needed for UART
        ifeq ($(DMA),Y)
            OPT += -DHAS_DMA
            SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dma_config.c
        endif
    endif

    ifeq ($(BOARD_SELECTED),Y)
        @echo $(error Board has been selected before)
    endif

    BOARD_SELECTED=Y
endif