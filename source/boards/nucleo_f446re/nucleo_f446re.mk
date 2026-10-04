ifneq ($(NUCLEO_F446RE_MK_INC),Y)
    NUCLEO_F446RE_MK_INC=Y

    BOARD_CFG_DIR = $(BOARD_DIR)/nucleo_f446re

    # $(error BOARD_CFG_DIR=$(BOARD_CFG_DIR))
    # $(error CFLAGS=$(CFLAGS))
    MCAL_OPT += -DHAS_NUCLEO_F446RE

    NUCLEO_F446RE=Y
    MICROCONTROLLER=Y
    STM32F446RE=Y

    INCDIR += -I$(BOARD_CFG_DIR)

    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_layout.c

    ifeq ($(ADC),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/adc_config.c
    endif

    ifeq ($(DS_TWR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ds_twr_config.c
    endif

    ifeq ($(DDS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dds_config.c
    endif

    ifeq ($(ADC_CHANNEL),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/adc_channel_config.c
    endif

    ifeq ($(EXT_INT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ext_int_config.c
    endif

    ifeq ($(GNSS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gnss_config.c
    endif

    ifeq ($(BH1750),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/bh1750_config.c
    endif

    ifeq ($(BT1026),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/bt1026_config.c
    endif

    ifeq ($(BUTTON),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/button_config.c
    endif

    ifeq ($(BOARD_COMMANDS),Y)
        MCAL_OPT += -DHAS_BOARD_COMMANDS
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_commands.c
    endif

    ifeq ($(CAN),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/can_config.c
        #SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/can_mailbox_config.c
    endif

    ifeq ($(CRYP),Y)
        $(info Config Crypt)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cryp_config.c
    endif
    
    ifeq ($(CLOCK),Y)
        #SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/clock_config.c
    endif

    ifeq ($(CROSS_DETECT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/cross_detect_config.c
    endif
    
    ifeq ($(GARLAND),Y)
        # $(error GARLAND=$(GARLAND))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/garland_config.c
    endif
    
    ifeq ($(CLI),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cli_config.c
    endif

    ifeq ($(LIGHT_NAVIGATOR),Y)
        SOURCES_CONFIGURATION_C += $(LIGHT_NAVIGATOR_DIR)/light_navigator_config.c
    endif
    
 
    ifeq ($(DASHBOARD),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dashboard_config.c
    endif

    ifeq ($(DELTA_SIGMA),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/delta_sigma_config.c
    endif
    
    ifeq ($(BUZZER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/buzzer_config.c
    endif
    
    ifeq ($(DS3231),Y)
        $(info + ds3231)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ds3231_config.c
    endif

    ifeq ($(FAT_FS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/fat_fs_config.c
    endif
    
    ifeq ($(DW1000),Y)
        $(info + DW1000)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dw1000_config.c
    endif

    ifeq ($(FREE_RTOS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/FreeRTOSConfig.c
    endif
    
    ifeq ($(DECADRIVER),Y)
        $(info + DECADRIVER)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/decadriver_config.c
    endif

    ifeq ($(ISO_TP),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/iso_tp_config.c
    endif

    ifeq ($(DWM1000),Y)
        $(info + DWM1000)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dwm1000_config.c
    endif

    ifeq ($(LITTLE_FS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/little_fs_config.c
    endif


    ifeq ($(IQUEUE),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/iqueue_config.c
    endif
    
    ifeq ($(DECAWAVE),Y)
        $(info Add config DECAWAVE)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/decawave_proto_config.c
    endif

    ifeq ($(IIR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/iir_config.c
    endif
    
    ifeq ($(FDA801),Y)
        # $(error FDA801=$(FDA801))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/fda801_config.c
    endif
    
    ifeq ($(BPSK),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/bpsk_config.c
    endif
    
    ifeq ($(GM67),Y)
        $(info Add config GM67)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gm67_config.c
    endif

    ifeq ($(DECIMATOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/decimator_config.c
    endif
    
    ifeq ($(MAX9860),Y)
        $(info Add config MAX9860)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/max9860_config.c
    endif

    ifeq ($(QUAD_MIX_4FS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/quad_mix_4fs_config.c
    endif
    
    ifeq ($(FLASH),Y)
        $(info Config Flash)
        #SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/flash_config.c
    endif

    ifeq ($(KEEPASS),Y)
        $(info Add config KEEPASS)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/keepass_config.c
    endif
    
    ifeq ($(FLASH_FS),Y)
        $(info Add config FlashFs)
        #SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/flash_fs_config.c
    endif

    ifeq ($(LTR390),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ltr390_config.c
    endif

    ifeq ($(STRING_READER),Y)
        $(info Add config STRING_READER)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/string_reader_config.c
    endif

    ifeq ($(GPIO),Y)
        $(info Config GPIO)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_config.c
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gpio_config.c
    endif

    ifeq ($(LOG),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/log_config.c
    endif
    
    ifeq ($(HEALTH_MONITOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_monitor.c
    endif

    ifeq ($(I2C),Y)
        $(info Config I2C)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/i2c_config.c
    endif

    ifeq ($(DISK),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/disk_config.c
    endif

    ifeq ($(NMEA),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/nmea_config.c
    endif

    ifeq ($(I2S),Y)
        # $(error I2S=$(I2S))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/i2s_config.c
    endif

    ifeq ($(LED_MONO),Y)
        # $(error LED_MONO=$(LED_MONO))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/led_mono_config.c
    endif

    ifeq ($(LIGHT_SENSOR),Y)
        $(info + LightSensorCfg)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/light_sensor_config.c
    endif

    ifeq ($(LOAD_DETECT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/load_detect_config.c
    endif

    ifeq ($(NOR_FLASH),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/nor_flash_config.c
    endif

    ifeq ($(INPUT_CAPTURE),Y)
        $(info Config InputCapture)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/input_capture_config.c
    endif
    
    ifeq ($(POSTPONE_FUN),Y)
        # $(info Config POSTPONE_FUN)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/postpone_fun_config.c
    endif
    
    ifeq ($(PHOTORESISTOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/photoresistor_config.c
    endif

    ifeq ($(PID),Y)
        # $(info Config PID)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/pid_config.c
    endif

    ifeq ($(PARAM),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/param_config.c
    endif

    ifeq ($(LASER_SIGHT),Y)
        # $(info Config LASER_SIGHT)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/laser_sight_config.c
    endif
    
    ifeq ($(PINS),Y)
        $(info Config Pins)
        MCAL_OPT += -DHAS_PINS
    endif

    ifeq ($(RUNNING_LINE),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/running_line_config.c
    endif

    ifeq ($(PWM),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/pwm_config.c
    endif

    ifeq ($(SSD1306),Y)
        $(info Add config SSD1306)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ssd1306_config.c
    endif

    ifeq ($(SCHMITT_TRIGGER),Y)
        # $(error schmitt_trigger=$(schmitt_trigger))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/schmitt_trigger_config.c
    endif

    ifeq ($(SD_CARD),Y)
        $(info Config SD card)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sd_card_config.c
    endif

    ifeq ($(SLIDING_INTEGRAL),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sliding_integral_config.c
    endif


    ifeq ($(SET_GAME),Y)
        $(info Config SET_GAME)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/set_game_config.c
    endif
    
    ifeq ($(SOFTWARE_TIMER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sw_timer_config.c
    endif

    ifeq ($(SPI),Y)
        $(info Config SPI)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/spi_config.c
    endif

    ifeq ($(STORE_FS),Y)
        $(info Config STORE_FS)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/store_fs_config.c
    endif
    
    ifeq ($(SW_NVRAM),Y)
        $(info Config SwNvRam)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sw_nvram_config.c
    endif
    
    ifeq ($(TBFP),Y)
        $(info Add config TBFP)
        MCAL_OPT += -DTBFP_MAX_PAYLOAD=350
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/tbfp_config.c
    endif

    ifeq ($(TIME),Y)
        $(info Config Time)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/time_config.c
    endif

    ifeq ($(TIMER),Y)
        # $(error TIMER=$(TIMER))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/timer_config.c
    endif

    ifeq ($(UART),Y)
        $(info Config UART)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/uart_config.c
    endif

    ifeq ($(UBLOX_NEO_6M),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ublox_neo_6m_config.c
    endif

    ifeq ($(WRITER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/writer_config.c
    endif

    ifeq ($(UDS),Y)
        # $(info Config UDS)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/uds_config.c
    endif
    
    ifeq ($(ESP_01),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/esp_01_config.c
    endif
    
    ifeq ($(RTC),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/rtc_config.c
    endif

    ifeq ($(XML),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/xml_config.c
    endif

    ifeq ($(PWM_PHASE_DEMO),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/pwm_phase_demo_config.c
    endif

    ifeq ($(WM8731),Y)
        # $(error WM8731=$(WM8731))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/wm8731_config.c
    endif

    ifeq ($(W25Q16BV),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/w25q16bv_config.c
    endif

    #####
    ifeq ($(BOARD_SELECTED),Y)
        @echo $(error Board has been selected before)
    endif
    BOARD_SELECTED=Y
endif
