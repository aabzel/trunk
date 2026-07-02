$(info DEV_E_BOX_STM32FXX_M_V3_0_MK_INC=$(DEV_E_BOX_STM32FXX_M_V3_0_MK_INC))
ifneq ($(DEV_E_BOX_STM32FXX_M_V3_0_MK_INC),Y)
    DEV_E_BOX_STM32FXX_M_V3_0_MK_INC=Y

    BOARD_CUSTOM_DIR = $(BOARD_DIR)/dev_e_box_stm32Fxx_m_v3_0
    #  $(error BOARD_CUSTOM_DIR=$(BOARD_CUSTOM_DIR))

    MCAL_OPT += -DHAS_DEV_E_BOX_STM32FXX_M_V3_0

    MCAL_OPT += -DHSE_VALUE=8000000U
    
    MICROCONTROLLER=Y

    INCDIR += -I$(BOARD_CUSTOM_DIR)

    SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/board_config.c

    ifeq ($(LOG),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/log_config.c
    endif

    ifeq ($(DDS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/dds_config.c
    endif

    ifeq ($(BUZZER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/buzzer_config.c
    endif

    ifeq ($(GNSS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/gnss_config.c
    endif

    # must be outside
    ifeq ($(DEMAGNETIZER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/demagnetizer_config.c
    endif

    ifeq ($(DISK),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/disk_config.c
    endif

    ifeq ($(BUTTON),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/button_config.c
    endif

    ifeq ($(BOARD_COMMANDS),Y)    
        MCAL_OPT += -DHAS_BOARD_COMMANDS
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/board_commands.c
    endif

    ifeq ($(BH1750),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/bh1750_config.c
    endif

    ifeq ($(FREE_RTOS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/FreeRTOSConfig.c
    endif

    ifeq ($(FILE_MCAL),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/file_mcal_config.c
    endif

    ifeq ($(GPIO),Y)
        $(info Config GPIO)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/gpio_config.c
    endif

    ifeq ($(DASHBOARD),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/dashboard_config.c
    endif

    ifeq ($(LIGHT_NAVIGATOR),Y)
        SOURCES_CONFIGURATION_C += $(LIGHT_NAVIGATOR_DIR)/light_navigator_config.c
    endif

    ifeq ($(ESP_01),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/esp_01_config.c
    endif

    ifeq ($(HEALTH_MONITOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/board_monitor.c
    endif

    ifeq ($(PINS),Y)
        $(info Config Pins)
        MCAL_OPT += -DHAS_PINS
    endif

    ifeq ($(FAT_FS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/fat_fs_config.c
    endif

    ifeq ($(DS3231),Y)
        $(info + ds3231)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/ds3231_config.c
    endif

    ifeq ($(GAME_PAD_PS2),Y)
        #  $(error GAME_PAD_PS2=$(GAME_PAD_PS2))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/game_pad_ps2_config.c
    endif

    ifeq ($(SOFTWARE_TIMER),Y)
        $(info Config Software Timer)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/sw_timer_config.c
    endif

    ifeq ($(LTR390),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/ltr390_config.c
    endif

    ifeq ($(CLI),Y)
        $(info Config Cli)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/cli_config.c
    endif

    ifeq ($(CRYP),Y)
        $(info Config Crypt)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/cryp_config.c
    endif

    ifeq ($(EXT_INT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/ext_int_config.c
    endif

    ifeq ($(PWM),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/pwm_config.c
    endif

    ifeq ($(WM8731),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/wm8731_config.c
    endif

    ifeq ($(RC_CAR),Y)
        #  $(error RC_CAR=$(RC_CAR))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/rc_car_config.c
    endif

    ifeq ($(NMEA),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/nmea_config.c
    endif
    
    ifeq ($(LIGHT_SENSOR),Y)
        $(info + LightSensorCfg)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/light_sensor_config.c
    endif
    
    ifeq ($(LED_MONO),Y)
        #  $(error LED=$(LED))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/led_mono_config.c
    endif

    ifeq ($(LED_MONO_PWM),Y)
        #  $(error LED_MONO_PWM=$(LED_MONO_PWM))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/led_mono_pwm_config.c
    endif

    ifeq ($(KEEPASS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/keepass_config.c
    endif

    ifeq ($(I2C),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/i2c_config.c
    endif

    ifeq ($(SSD1306),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/ssd1306_config.c
    endif

    ifeq ($(DRV8870),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/drv8870_config.c
    endif

    ifeq ($(IR_RECEIVER),Y)
        #  $(error IR_RECEIVER=$(IR_RECEIVER))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/ir_receiver_config.c
    endif

    ifeq ($(SMOOTH_LAMP),Y)
        #  $(error SMOOTH_LAMP=$(SMOOTH_LAMP))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/smooth_lamp_config.c
    endif

    ifeq ($(SCHMITT_TRIGGER),Y)
        #  $(error schmitt_trigger=$(schmitt_trigger))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/schmitt_trigger_config.c
    endif

    ifeq ($(SPI),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/spi_config.c
    endif
    
    ifeq ($(RTC),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/rtc_config.c
    endif    
    
    ifeq ($(STRING_READER),Y)
        $(info + STRING_READER)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/string_reader_config.c
    endif

    ifeq ($(TIME),Y)
        #  $(error TIME=$(TIME))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/time_config.c
    endif

    ifeq ($(TIMER),Y)
        #  $(error TIMER=$(TIMER))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/timer_config.c
    endif

    ifeq ($(UART),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/uart_config.c
    endif

    ifeq ($(UBLOX_NEO_6M),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/ublox_neo_6m_config.c
    endif

    ifeq ($(USB),Y)
        #$(info Config USB)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/usb_config.c
    endif

    ifeq ($(WRITER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/writer_config.c
    endif

    ifeq ($(I2S),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/i2s_config.c
    endif

    ifeq ($(DMA),Y)
        MCAL_OPT += -DHAS_DMA
        #SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/dma_config.c
    endif

    ifeq ($(XML),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/xml_config.c
    endif

    ifeq ($(TBFP),Y)
        MCAL_OPT += -DTBFP_MAX_PAYLOAD=20
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/tbfp_config.c
    endif

    ifeq ($(WAV),Y)
        $(info Config GPIO)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/wav_config.c
    endif

    ifeq ($(W25Q16BV),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/w25q16bv_config.c
    endif

    #####
    ifeq ($(BOARD_SELECTED),Y)
        @echo $(error Board has been selected before)
    endif

    BOARD_SELECTED=Y
endif
