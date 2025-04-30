$(info NRF5340_DK_MK_INC=$(NRF5340_DK_MK_INC))
ifneq ($(NRF5340_DK_MK_INC),Y)
    NRF5340_DK_MK_INC=Y

    BOARD_CFG_DIR = $(BOARD_DIR)/nrf5340_dk
    INCDIR += -I$(BOARD_CFG_DIR)
    #@echo $(error BOARD_CFG_DIR=$(BOARD_CFG_DIR))

    NRF5340=Y
    MICROCONTROLLER=Y
    INTERFACES=Y
    NRF5340_DK=Y

    OPT += -DHAS_NRF5340_DK

    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_config.c

    ifeq ($(ADC),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/adc_config.c
    endif

    ifeq ($(AUDIO),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/audio_config.c
    endif

    ifeq ($(AT24C02),Y)
        #@echo $(error AT24C02=$(AT24C02))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/at24cxx_config.c
    endif

    ifeq ($(BLE_SPEAKER_CFG),Y)
        OPT += -DHAS_BLE_SPEAKER_CFG
    endif

    ifeq ($(BT_BLE_UWB_TAG_CFG),Y)
        OPT += -DHAS_BT_BLE_UWB_TAG_CFG
    endif

    ifeq ($(BT1026),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/bt1026_config.c
    endif

    ifeq ($(BUTTON),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/button_config.c
    endif

    ifeq ($(CLI),Y)
        $(info Config CLI)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cli_config.c
    endif

    ifeq ($(CROSS_DETECT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cross_detect_config.c
    endif

    ifeq ($(DASHBOARD),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dashboard_config.c
    endif

    ifeq ($(DS_TWR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ds_twr_config.c
    endif

    ifeq ($(DS3231),Y)
        $(info + ds3231)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ds3231_config.c
    endif

    ifeq ($(DTMF),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dtmf_config.c
    endif

    ifeq ($(DW1000),Y)
        $(info + DW1000)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dw1000_config.c
    endif

    ifeq ($(DECAWAVE),Y)
        $(info Add config DECAWAVE)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/decawave_proto_config.c
    endif

    ifeq ($(DECADRIVER),Y)
        $(info + DECADRIVER)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/decadriver_config.c
    endif

    ifeq ($(DISTANCE),Y)
        $(info Add config DISTANCE)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/distance_config.c
    endif

    ifeq ($(DWM1000),Y)
        $(info + DWM1000)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dwm1000_config.c
    endif

    ifeq ($(DWM3000),Y)
        $(info + DWM3000)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dwm3000_config.c
    endif

    ifeq ($(FDA801),Y)
        #@echo $(error FDA801=$(FDA801))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/fda801_config.c
    endif

    ifeq ($(GPIO),Y)
        $(info Config GPIO)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gpio_config.c
    endif

    ifeq ($(HEALTH_MONITOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_monitor.c
    endif

    ifeq ($(I2C),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/i2c_config.c
    endif

    ifeq ($(I2S),Y)
        #@echo $(error I2S=$(I2S))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/i2s_config.c
    endif

    ifeq ($(LED_MONO),Y)
        #@echo $(error LED_MONO=$(LED_MONO))
        OPT += -DHAS_LED_MONO
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/led_mono_config.c
    endif

    ifeq ($(LIGHT_SENSOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/light_sensor_config.c
    endif

    ifeq ($(LOAD_DETECT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/load_detect_config.c
    endif

    ifeq ($(MAX98357),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/max98357_config.c
    endif

    ifeq ($(MAX9860),Y)
        #@echo $(error MAX9860=$(MAX9860))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/max9860_config.c
    endif

    ifeq ($(MX25R6435F),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/mx25r6435f_config.c
    endif

    ifeq ($(NOR_FLASH),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/nor_flash_config.c
    endif

    ifeq ($(PINS),Y)
        $(info Config Pins)
        OPT += -DHAS_PINS
    endif

    ifeq ($(PWM),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/pwm_config.c
    endif

    ifeq ($(PDM),Y)
        #@echo $(error PDM=$(PDM))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/pdm_config.c
    endif

    ifeq ($(QSPI),Y)
        $(info Config QSPI)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/qspi_config.c
    endif

    ifeq ($(RTC),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/rtc_config.c
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

    ifeq ($(SSD1306),Y)
        #@echo $(error SSD1306=$(SSD1306))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ssd1306_config.c
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

    #####
    ifeq ($(BOARD_SELECTED),Y)
        @echo $(error Board has been selected before)
    endif

    BOARD_SELECTED=Y
endif
