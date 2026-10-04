ifneq ($(NUCLEO_F401RE_MK_INC),Y)
    NUCLEO_F401RE_MK_INC=Y

    BOARD_CFG_DIR = $(BOARD_DIR)/nucleo_f401re

    # $(error BOARD_CFG_DIR=$(BOARD_CFG_DIR))
    MCAL_OPT += -DHAS_NUCLEO_F401RE

    MICROCONTROLLER=Y
    NUCLEO_F401RE=Y

    INCDIR += -I$(BOARD_CFG_DIR)

    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_config.c
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_layout.c

    ifeq ($(IR_RECEIVER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ir_receiver_config.c
    endif

    ifeq ($(GPIO_DAC),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gpio_dac_config.c
    endif

    ifeq ($(EXT_INT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ext_int_config.c
    endif

    ifeq ($(ADC),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/adc_config.c
    endif
    
    ifeq ($(BH1750),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/bh1750_config.c
    endif

    ifeq ($(BUTTON),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/button_config.c
    endif
    
    ifeq ($(BUZZER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/buzzer_config.c
    endif


    ifeq ($(CROSS_DETECT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cross_detect_config.c
    endif

    ifeq ($(CLI),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cli_config.c
    endif
    
    ifeq ($(CRYP),Y)
        $(info Config Crypt)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cryp_config.c
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

    ifeq ($(STORE_FS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/store_fs_config.c
    endif

    ifeq ($(DECAWAVE),Y)
        $(info Add config DECAWAVE)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/decawave_proto_config.c
    endif

    ifeq ($(DECADRIVER),Y)
        $(info + DECADRIVER)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/decadriver_config.c
    endif

    ifeq ($(DISK),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/disk_config.c
    endif
    
    ifeq ($(DWM1000),Y)
        $(info + DWM1000)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dwm1000_config.c
    endif

    ifeq ($(ESP_01),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/esp_01_config.c
    endif

    ifeq ($(FAT_FS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/fat_fs_config.c
    endif

    ifeq ($(FDA801),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_DIR)/fda801_config.c
    endif

    ifeq ($(FILE_MCAL),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/file_mcal_config.c
    endif

    ifeq ($(FREE_RTOS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/FreeRTOSConfig.c
    endif

    ifeq ($(GNSS),Y)
        $(info Config GNSS)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gnss_config.c
    endif
    
    ifeq ($(GPIO),Y)
        $(info Config GPIO)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gpio_config.c
    endif

    ifeq ($(HEALTH_MONITOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_monitor.c
    endif

    ifeq ($(I2C),Y)
        $(info Config I2C)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/i2c_config.c
    endif

    ifeq ($(I2S),Y)
        # $(error I2S=$(I2S))
        MCAL_OPT += -DHAS_I2S
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/i2s_config.c
    endif

    ifeq ($(KEEPASS),Y)
        $(info Add config KEEPASS)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/keepass_config.c
    endif

    ifeq ($(LED_MONO),Y)
        # $(error LED_MONO=$(LED_MONO))
        MCAL_OPT += -DHAS_LED_MONO
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/led_mono_config.c
    endif

    ifeq ($(LOG),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/log_config.c
    endif

    ifeq ($(LTR390),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ltr390_config.c
    endif

    ifeq ($(LIGHT_NAVIGATOR),Y)
        SOURCES_CONFIGURATION_C += $(LIGHT_NAVIGATOR_DIR)/light_navigator_config.c
    endif

    ifeq ($(LOAD_DETECT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/load_detect_config.c
    endif
    
    ifeq ($(LIGHT_SENSOR),Y)
        $(info + LightSensorCfg)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/light_sensor_config.c
    endif

    ifeq ($(NMEA),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/nmea_config.c
    endif

    ifeq ($(POSTPONE_FUN),Y)
        # $(info Config POSTPONE_FUN)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/postpone_fun_config.c
    endif
    
    ifeq ($(PHOTORESISTOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/photoresistor_config.c
    endif

    ifeq ($(STRING_READER),Y)
        $(info + STRING_READER)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/string_reader_config.c
    endif

    ifeq ($(TIME),Y)
        # $(error TIME=$(TIME))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/time_config.c
    endif
    
    ifeq ($(PIN),Y)
        MCAL_OPT += -DHAS_PIN
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/pin_config.c
    endif

    ifeq ($(PWM),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/pwm_config.c
    endif
    
    ifeq ($(RTC),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/rtc_config.c
    endif

    ifeq ($(SCHMITT_TRIGGER),Y)
        # $(error schmitt_trigger=$(schmitt_trigger))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/schmitt_trigger_config.c
    endif

    ifeq ($(SD_CARD),Y)
        $(info Config SD card)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sd_card_config.c
    endif

    ifeq ($(SI4703),Y)
        # $(error SI4703=$(SI4703))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/si4703_config.c
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

    ifeq ($(SW_UART),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sw_uart_config.c
    endif

    ifeq ($(SSD1306),Y)
        # $(error SSD1306=$(SSD1306))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ssd1306_config.c
    endif
    
    ifeq ($(TBFP),Y)
        $(info Add config TBFP)
        MCAL_OPT += -DTBFP_MAX_PAYLOAD=350
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/tbfp_config.c
    endif
    
    ifeq ($(TIMER),Y)
        # $(error TIMER=$(TIMER))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/timer_config.c
    endif

    ifeq ($(UBLOX_NEO_6M),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ublox_neo_6m_config.c
    endif

    ifeq ($(USB),Y)
        #$(info Config USB)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/usb_config.c
    endif

    ifeq ($(UART),Y)
        $(info Config UART)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/uart_config.c
    endif

    ifeq ($(XML),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/xml_config.c
    endif

    ifeq ($(W25Q16BV),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/w25q16bv_config.c
    endif
    
    ifeq ($(WRITER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/writer_config.c
    endif

    ifeq ($(WM8731),Y)
        # $(error WM8731=$(WM8731))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/wm8731_config.c
    endif

    #####
    ifeq ($(BOARD_SELECTED),Y)
        @echo $(error Board has been selected before)
    endif
    BOARD_SELECTED=Y
endif
