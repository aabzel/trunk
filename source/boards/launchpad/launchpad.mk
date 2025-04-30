$(info LAUNCHXL_CC26X2R1_MK_INC=$(LAUNCHXL_CC26X2R1_MK_INC))
ifneq ($(LAUNCHXL_CC26X2R1_MK_INC),Y)
    LAUNCHXL_CC26X2R1_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    #include $(WORKSPACE_LOC)/mcu/cc2652r1f/cc2652r1f.mk

    BOARD_CFG_DIR = $(BOARD_DIR)/launchpad
    #@echo $(error BOARD_CFG_DIR=$(BOARD_CFG_DIR))
    #@echo $(error CFLAGS=$(CFLAGS))
    OPT += -DHAS_LAUNCHXL_CC26X2R1

    MICROCONTROLLER=Y

    INCDIR += -I$(BOARD_CFG_DIR)

    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_config.c

    #@echo $(error HEALTH_MONITOR=$(HEALTH_MONITOR))
    ifeq ($(HEALTH_MONITOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_monitor.c
    endif

    ifeq ($(BUTTON),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/button_config.c
    endif

    ifeq ($(GPIO),Y)
        $(info Config GPIO)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gpio_config.c
    endif


    ifeq ($(XML),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/xml_config.c
    endif

    ifeq ($(PINS),Y)
        $(info Config Pins)
        OPT += -DHAS_PINS
    endif

    ifeq ($(SOFTWARE_TIMER),Y)
        $(info Config Software Timer)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sw_timer_config.c
    endif

    ifeq ($(FREE_RTOS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/FreeRTOSConfig.c
    endif

    ifeq ($(CLOCK),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/clock_config.c
    endif

    ifeq ($(CLI),Y)
        $(info Config Cli)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cli_config.c
    endif
    
    ifeq ($(CRYP),Y)
        $(info Config Crypt)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cryp_config.c
    endif

    ifeq ($(FLASH),Y)
        $(info Config Flash)
        #@echo $(error FLASH=$(FLASH))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/flash_config.c
    endif

    ifeq ($(FLASH_FS),Y)
        $(info Add config FlashFs)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/flash_fs_config.c
    endif

    ifeq ($(LED_MONO),Y)
        #@echo $(error LED=$(LED))
        OPT += -DHAS_LED
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/led_mono_config.c
    endif

    ifeq ($(KEEPASS),Y)
        $(info Add config KEEPASS)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/keepass_config.c
    endif

    ifeq ($(NVS),Y)
        $(info Add config NVS)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/nvs_config.c
    endif

    ifeq ($(PARAM),Y)
        $(info Config Param)
        #@echo $(error PARAM=$(PARAM))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/param_config.c
    endif

    ifeq ($(I2C),Y)
        OPT += -DHAS_I2C
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/i2c_config.c
    endif

    ifeq ($(SPI),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/spi_config.c
    endif

    ifeq ($(GENERIC),Y)
        ifeq ($(TIMER),Y)
            SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/timer_config.c
        endif
    endif

    ifeq ($(UART),Y)
        OPT += -DHAS_UART
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/uart_config.c
    endif

    ifeq ($(USB),Y)
        #$(info Config USB)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/usb_config.c
    endif

    ifeq ($(GENERIC),Y)
        OPT += -DHAS_UART
        ifeq ($(I2S),Y)
            OPT += -DHAS_I2S
            SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/i2s_config.c
        endif

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