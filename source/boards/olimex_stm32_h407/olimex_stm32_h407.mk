$(info OLIMEX_H407_MK_INC=$(OLIMEX_H407_MK_INC))
ifneq ($(OLIMEX_H407_MK_INC),Y)
    OLIMEX_H407_MK_INC=Y

    BOARD_CFG_DIR = $(BOARD_DIR)/olimex_stm32_h407

    #@echo $(error BOARD_CFG_DIR=$(BOARD_CFG_DIR))

    OPT += -DHAS_OLIMEX_H407
    OPT += -DHSE_VALUE=12000000U

    MICROCONTROLLER=Y

    INCDIR += -I$(BOARD_CFG_DIR)

    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_config.c

    ifeq ($(GNSS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gnss_config.c
    endif

    ifeq ($(BUTTON),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/button_config.c
    endif

    ifeq ($(BH1750),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/bh1750_config.c
    endif

    ifeq ($(LTR390),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ltr390_config.c
    endif
    
    ifeq ($(CLI),Y)
        $(info Config Cli)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cli_config.c
    endif

    ifeq ($(CRYP),Y)
        $(info Config Crypt)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cryp_config.c
    endif

    ifeq ($(GPIO),Y)
        $(info Config GPIO)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gpio_config.c
    endif

    ifeq ($(DASHBOARD),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dashboard_config.c
    endif

    ifeq ($(LIGHT_NAVIGATOR),Y)
        SOURCES_CONFIGURATION_C += $(LIGHT_NAVIGATOR_DIR)/light_navigator_config.c
    endif

    ifeq ($(HEALTH_MONITOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_monitor.c
    endif

    ifeq ($(DS3231),Y)
        $(info + ds3231)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ds3231_config.c
    endif

    ifeq ($(FREE_RTOS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/FreeRTOSConfig.c
    endif

    ifeq ($(KEEPASS),Y)
        $(info Add config KEEPASS)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/keepass_config.c
    endif

    ifeq ($(LED_MONO),Y)
        #@echo $(error LED=$(LED))
        OPT += -DHAS_LED
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/led_mono_config.c
    endif

    ifeq ($(LOG),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/log_config.c
    endif

    ifeq ($(MIC2026),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/mic2026_config.c
    endif

    ifeq ($(NMEA),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/nmea_config.c
    endif
    
    ifeq ($(LIGHT_SENSOR),Y)
        $(info + LightSensorCfg)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/light_sensor_config.c
    endif

    ifeq ($(PINS),Y)
        $(info Config Pins)
        OPT += -DHAS_PINS
    endif

    ifeq ($(STRING_READER),Y)
        $(info + STRING_READER)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/string_reader_config.c
    endif

    ifeq ($(I2C),Y)
        OPT += -DHAS_I2C
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/i2c_config.c
    endif

    ifeq ($(RTOS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/rtos_task_config.c
    endif

    ifeq ($(SCHMITT_TRIGGER),Y)
        #@echo $(error schmitt_trigger=$(schmitt_trigger))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/schmitt_trigger_config.c
    endif

    ifeq ($(SPI),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/spi_config.c
    endif

    ifeq ($(SSD1306),Y)
        $(info Add config SSD1306)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ssd1306_config.c
    endif
    
    ifeq ($(SOFTWARE_TIMER),Y)
        $(info Config Software Timer)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sw_timer_config.c
    endif

    ifeq ($(TIME),Y)
        #@echo $(error TIME=$(TIME))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/time_config.c
    endif

    ifeq ($(TIMER),Y)
        #@echo $(error TIMER=$(TIMER))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/timer_config.c
    endif

    ifeq ($(UART),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/uart_config.c
    endif

    ifeq ($(UBLOX_NEO_6M),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ublox_neo_6m_config.c
    endif

    ifeq ($(USB),Y)
        #$(info Config USB)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/usb_config.c
    endif

    ifeq ($(I2S),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/i2s_config.c
    endif

    ifeq ($(DMA),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dma_config.c
    endif

    ifeq ($(BOARD_COMMANDS),Y)    
        OPT += -DHAS_BOARD_COMMANDS
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_commands.c
    endif
        
    ifeq ($(XML),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/xml_config.c
    endif

    ifeq ($(TBFP),Y)
        OPT += -DTBFP_MAX_PAYLOAD=20
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/tbfp_config.c
    endif

    ifeq ($(BOARD_SELECTED),Y)
        @echo $(error Board has been selected before)
    endif

    BOARD_SELECTED=Y
endif
