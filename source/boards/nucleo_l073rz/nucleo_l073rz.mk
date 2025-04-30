ifneq ($(NUCLEO_L073RZ_MK_INC),Y)
    NUCLEO_L073RZ_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    BOARD_CFG_DIR = $(BOARD_DIR)/nucleo_f401re

    #@echo $(error BOARD_CFG_DIR=$(BOARD_CFG_DIR))
    #@echo $(error CFLAGS=$(CFLAGS))DMA
    OPT += -DHAS_NUCLEO_L073RZ

    MICROCONTROLLER=Y

    INCDIR += -I$(BOARD_CFG_DIR)

    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_config.c
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_layout.c
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_monitor.c

    ifeq ($(ADC),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/adc_config.c
    endif

    ifeq ($(BH1750),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/bh1750_config.c
    endif

    ifeq ($(BUTTON),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/button_config.c
    endif

    ifeq ($(CLOCK),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/clock_config.c
    endif

    ifeq ($(CLI),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cli_config.c
    endif

    ifeq ($(DMA),Y)
        #@echo $(error DMA=$(DMA))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dma_config.c
    endif

    ifeq ($(DS3231),Y)
        $(info + ds3231)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ds3231_config.c
    endif

    ifeq ($(DW1000),Y)
        $(info + DW1000)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dw1000_config.c
    endif

    ifeq ($(FDA801),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_DIR)/fda801_config.c
    endif

    ifeq ($(LIGHT_SENSOR),Y)
        $(info + LightSensorCfg)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/light_sensor_config.c
    endif

    ifeq ($(FLASH),Y)
        $(info Config Flash)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/flash_config.c
    endif

    ifeq ($(FLASH_FS),Y)
        $(info Add config FlashFs)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/flash_fs_config.c
    endif

    ifeq ($(GPIO),Y)
        $(info Config GPIO)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gpio_config.c
    endif

    ifeq ($(I2C),Y)
        $(info Config I2C)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/i2c_config.c
    endif

    ifeq ($(I2S),Y)
        #@echo $(error I2S=$(I2S))
        OPT += -DHAS_I2S
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/i2s_config.c
    endif

    ifeq ($(LED_MONO),Y)
        #@echo $(error LED_MONO=$(LED_MONO))
        OPT += -DHAS_LED_MONO
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/led_mono_config.c
    endif

    ifeq ($(PHOTORESISTOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/photoresistor_config.c
    endif

    ifeq ($(NVS),Y)
        $(info Add config NVS)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/nvs_config.c
    endif

    ifeq ($(PARAM),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/param_config.c
    endif

    ifeq ($(PINS),Y)
        $(info Config Pins)
        OPT += -DHAS_PINS
    endif

    ifeq ($(SCHMITT_TRIGGER),Y)
        #@echo $(error schmitt_trigger=$(schmitt_trigger))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/schmitt_trigger_config.c
    endif

    ifeq ($(SD_CARD),Y)
        $(info Config SD card)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sd_card_config.c
    endif

    ifeq ($(SOFTWARE_TIMER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sw_timer_config.c
    endif

    ifeq ($(SPI),Y)
        $(info Config SPI)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/spi_config.c
    endif

    ifeq ($(SW_NVRAM),Y)
        $(info Config SwNvRam)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sw_nvram_config.c
    endif

    ifeq ($(TBFP),Y)
        $(info Add config TBFP)
        OPT += -DTBFP_MAX_PAYLOAD=350
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/tbfp_config.c
    endif

    ifeq ($(TIMER),Y)
        #@echo $(error TIMER=$(TIMER))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/timer_config.c
    endif

    ifeq ($(UART),Y)
        $(info Config UART)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/uart_config.c
    endif

    ifeq ($(WM8731),Y)
        #@echo $(error WM8731=$(WM8731))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/wm8731_config.c
    endif

    ifeq ($(BOARD_SELECTED),Y)
        @echo $(error Board has been selected before)
    endif
    BOARD_SELECTED=Y
endif
