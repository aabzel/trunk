$(info DUMMY_BOARD_MK_INC=$(DUMMY_BOARD_MK_INC))
ifneq ($(DUMMY_BOARD_MK_INC),Y)
    DUMMY_BOARD_MK_INC=Y

    BOARD_CUSTOM_DIR = $(BOARD_DIR)/dummy_board

    #@echo $(error BOARD_CUSTOM_DIR=$(BOARD_CUSTOM_DIR))
    MCAL_OPT += -DHAS_DUMMY_BOARD

    MICROCONTROLLER=Y
    INCDIR += -I$(BOARD_CUSTOM_DIR)

    ifeq ($(CONFIG_CAM),Y)
        include $(BOARD_CUSTOM_DIR)/config_cam/config_cam.mk
    endif

    SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/board_config.c

    ifeq ($(ACCELEROMETER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/accelerometer_config.c
    endif

    ifeq ($(AT24C02),Y)
        #@echo $(error AT24C02=$(AT24C02))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/at24cxx_config.c
    endif

    ifeq ($(ADC),Y)
        #@echo $(error ADC=$(ADC))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/adc_config.c
    endif

    ifeq ($(STORE_FS),Y)
        #@echo $(error STORE_FS=$(STORE_FS))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/store_fs_config.c
    endif

    ifeq ($(BLACK_BOX),Y)
        $(info Config BLACK_BOX)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/black_box_config.c
    endif
    
    ifeq ($(BOARD_INFO),Y)
        include $(BOARD_CUSTOM_DIR)/board_custom/board_custom.mk
    endif

    ifeq ($(BUTTON),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/button_config.c
    endif

    ifeq ($(CAN),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/can_config.c
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/can_mailbox_config.c
    endif

    ifeq ($(CLI),Y)
        $(info Config Cli)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/cli_config.c
    endif
    
    ifeq ($(CRYP),Y)
        $(info Config Crypt)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/cryp_config.c
    endif

    ifeq ($(CROSS_DETECT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cross_detect_config.c
    endif

    ifeq ($(DELTA_SIGMA),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/delta_sigma_config.c
    endif
    
    ifeq ($(EXT_INT),Y)
        $(info Config EXT_INT)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/ext_int_config.c
    endif

    ifeq ($(FREE_RTOS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/FreeRTOSConfig.c
    endif

    ifeq ($(FIR),Y)
        $(info Config FIR)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/fir_config.c
    endif

    ifeq ($(FIR_INT),Y)
        $(info Config FIR_INT)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/fir_int_config.c
    endif

    
    ifeq ($(GPIO),Y)
        $(info Config GPIO)
        SOURCES_THIRD_PARTY_C += $(BOARD_CUSTOM_DIR)/gpio_config.c
    endif

    ifeq ($(HEALTH_MONITOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/board_monitor.c
    endif

    ifeq ($(LITTLE_FS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/little_fs_config.c
    endif
    
    ifeq ($(LED_MONO),Y)
        #@echo $(error LED=$(LED))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/led_mono_config.c
    endif

    ifeq ($(LED_RGB),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/led_rgb_config.c
    endif

    ifeq ($(LOG),Y)
        $(info Config LOG)
        #$(error LOG=$(LOG))
        SOURCES_THIRD_PARTY_C += $(BOARD_CUSTOM_DIR)/log_config.c
    endif

    ifeq ($(I2C),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/i2c_config.c
    endif

    ifeq ($(ISO_TP),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/iso_tp_config.c
    endif
    
    ifeq ($(LIS3DH),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/lis3dh_config.c
    endif
    
    ifeq ($(PID),Y)
        #$(info Config PID)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/pid_config.c
    endif

    ifeq ($(POSTPONE_FUN),Y)
        #$(info Config POSTPONE_FUN)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/postpone_fun_config.c
    endif

    ifeq ($(PWM),Y)
        $(info Config PWM)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/pwm_config.c
    endif

    ifeq ($(LOAD_DETECT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/load_detect_config.c
    endif

    ifeq ($(INPUT_CAPTURE),Y)
        $(info Config InputCapture)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/input_capture_config.c
    endif

    ifeq ($(PINS),Y)
        $(info Config Pins)
        MCAL_OPT += -DHAS_PINS
    endif
    
    ifeq ($(PWM_DAC),Y)
        $(info Config PWM_DAC)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/pwm_dac_config.c
    endif
    
    
    ifeq ($(RTC),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/rtc_config.c
    endif
    
    ifeq ($(SCHMITT_TRIGGER),Y)
        #@echo $(error schmitt_trigger=$(schmitt_trigger))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/schmitt_trigger_config.c
    endif

    ifeq ($(SCRIPT),Y)
        #@echo $(error SCRIPT=$(SCRIPT))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/script_config.c
    endif

    ifeq ($(SOFTWARE_TIMER),Y)
        $(info Config Software Timer)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/sw_timer_config.c
    endif
    
    ifeq ($(STRING_READER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/string_reader_config.c
    endif

    ifeq ($(SD_CARD),Y)
        $(info Config SD_CARD)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sd_card_config.c
    endif
    
    ifeq ($(SPI),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/spi_config.c
    endif

    ifeq ($(TIME),Y)
        #@echo $(error TIME=$(TIME))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/time_config.c
    endif

    ifeq ($(TIMER),Y)
        #@echo $(error TIMER=$(TIMER))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/timer_config.c
    endif

    ifeq ($(UART),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/uart_config.c
    endif

    ifeq ($(UDS),Y)
        #$(info Config UDS)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/uds_config.c
    endif

    ifeq ($(TBFP),Y)
        $(info Add config TBFP)
        MCAL_OPT += -DTBFP_MAX_PAYLOAD=350
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/tbfp_config.c
    endif

    ifeq ($(WRITER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/writer_config.c
    endif


    #####
    ifeq ($(BOARD_SELECTED),Y)
        @echo $(error Board has been selected before)
    endif
    BOARD_SELECTED=Y
endif
