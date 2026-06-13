$(info JZ_F407VET6_MK_INC=$(JZ_F407VET6_MK_INC))
ifneq ($(JZ_F407VET6_MK_INC),Y)
    JZ_F407VET6_MK_INC=Y

    BOARD_CFG_DIR = $(BOARD_DIR)/jz_f407vet6

    # $(error BOARD_CFG_DIR=$(BOARD_CFG_DIR))

    MCAL_OPT += -DHAS_JZ_F407VET6
    MCAL_OPT += -DHSE_VALUE=25000000U

    ifeq ($(BOARD_PROC),Y)
        MCAL_OPT += -DHAS_BOARD_PROC
    endif

    MICROCONTROLLER=Y

    INCDIR += -I$(BOARD_CFG_DIR)

    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_config.c

    ifeq ($(ADC),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/adc_config.c
    endif

    ifeq ($(ADC_CHANNEL),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/adc_channel_config.c
    endif

    ifeq ($(BPSK),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/bpsk_config.c
    endif

    ifeq ($(BPSK_4FS),Y)
        #$(error BPSK_4FS=$(BPSK_4FS))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/bpsk_4fs_config.c
    endif

    ifeq ($(BUZZER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/buzzer_config.c
    endif

    ifeq ($(DDS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dds_config.c
    endif

    ifeq ($(EXT_INT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ext_int_config.c
    endif

    ifeq ($(DASHBOARD),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dashboard_config.c
    endif
    
    ifeq ($(GNSS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gnss_config.c
    endif

    ifeq ($(BH1750),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/bh1750_config.c
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

    ifeq ($(CLI),Y)
        $(info Config Cli)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cli_config.c
    endif

    ifeq ($(CRYP),Y)
        $(info Config Crypt)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cryp_config.c
    endif

    ifeq ($(ESP_01),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/esp_01_config.c
    endif

    ifeq ($(GPIO),Y)
        $(info Config GPIO)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gpio_config.c
    endif

    ifeq ($(GARLAND),Y)
        # $(error GARLAND=$(GARLAND))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/garland_config.c
    endif

    ifeq ($(DRV8870),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/drv8870_config.c
    endif

    ifeq ($(DS3231),Y)
        $(info + ds3231)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ds3231_config.c
    endif

    ifeq ($(FAT_FS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/fat_fs_config.c
    endif

    ifeq ($(FREE_RTOS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/FreeRTOSConfig.c
    endif
    
    ifeq ($(I2C),Y)
        MCAL_OPT += -DHAS_I2C
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/i2c_config.c
    endif

    ifeq ($(ISO_TP),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/iso_tp_config.c
    endif

    ifeq ($(IQUEUE),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/iqueue_config.c
    endif

    ifeq ($(IIR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/iir_config.c
    endif

    ifeq ($(DECIMATOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/decimator_config.c
    endif

    ifeq ($(QUAD_MIX_4FS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/quad_mix_4fs_config.c
    endif

    ifeq ($(KEEPASS),Y)
        $(info Add config KEEPASS)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/keepass_config.c
    endif

    ifeq ($(LIGHT_NAVIGATOR),Y)
        SOURCES_CONFIGURATION_C += $(LIGHT_NAVIGATOR_DIR)/light_navigator_config.c
    endif

    ifeq ($(HEALTH_MONITOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_monitor.c
    endif

    ifeq ($(LTR390),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ltr390_config.c
    endif

    ifeq ($(LED_MONO),Y)
        #$(error LED_MONO=$(LED_MONO))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/led_mono_config.c
    endif

    ifeq ($(LOG),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/log_config.c
    endif

    ifeq ($(DISK),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/disk_config.c
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
        MCAL_OPT += -DHAS_PINS
    endif

    ifeq ($(ENCODER_LAMP),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/encoder_lamp_config.c
    endif

    ifeq ($(POSTPONE_FUN),Y)
        # $(info Config POSTPONE_FUN)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/postpone_fun_config.c
    endif

    ifeq ($(LASER_SIGHT),Y)
        # $(info Config LASER_SIGHT)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/laser_sight_config.c
    endif

    ifeq ($(STRING_READER),Y)
        $(info + STRING_READER)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/string_reader_config.c
    endif

    ifeq ($(PWM),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/pwm_config.c
    endif

    ifeq ($(IR_RECEIVER),Y)
        # $(error IR_RECEIVER=$(IR_RECEIVER))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ir_receiver_config.c
    endif

    ifeq ($(PID),Y)
        # $(error PID=$(PID))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/pid_config.c
    endif

    ifeq ($(RTOS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/rtos_task_config.c
    endif

    ifeq ($(SCHMITT_TRIGGER),Y)
        # $(error schmitt_trigger=$(schmitt_trigger))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/schmitt_trigger_config.c
    endif

    ifeq ($(SMOOTH_LAMP),Y)
        # $(error SMOOTH_LAMP=$(SMOOTH_LAMP))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/smooth_lamp_config.c
    endif

    ifeq ($(SLIDING_INTEGRAL),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sliding_integral_config.c
    endif

    ifeq ($(SPI),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/spi_config.c
    endif

    ifeq ($(SW_NVRAM),Y)
        $(info Config SwNvRam)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/sw_nvram_config.c
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
        # $(error TIME=$(TIME))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/time_config.c
    endif

    ifeq ($(TIMER),Y)
        # $(error TIMER=$(TIMER))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/timer_config.c
    endif

    ifeq ($(UART),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/uart_config.c
    endif

    ifeq ($(UBLOX_NEO_6M),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ublox_neo_6m_config.c
    endif

    ifeq ($(MCAL_USB),Y)
        #$(info Config USB)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/usb_config.c
    endif


    ifeq ($(I2S),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/i2s_config.c
    endif

    ifeq ($(UDS),Y)
        # $(info Config UDS)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/uds_config.c
    endif
        
    ifeq ($(RTC),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/rtc_config.c
    endif        

    ifeq ($(DELTA_SIGMA),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/delta_sigma_config.c
    endif

    ifeq ($(XML),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/xml_config.c
    endif

    ifeq ($(PWM_PHASE_DEMO),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/pwm_phase_demo_config.c
    endif

    ifeq ($(STORE_FS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/store_fs_config.c
    endif

    ifeq ($(TBFP),Y)
        MCAL_OPT += -DTBFP_MAX_PAYLOAD=20
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/tbfp_config.c
    endif
    
    ifeq ($(WRITER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/writer_config.c
    endif

    ifeq ($(W25Q16BV),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/w25q16bv_config.c
    endif

    ifeq ($(BOARD_SELECTED),Y)
        @echo $(error Board has been selected before)
    endif

    BOARD_SELECTED=Y
endif
