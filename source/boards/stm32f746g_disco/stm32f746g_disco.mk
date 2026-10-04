ifneq ($(STM32F746G_DISCO_MK_INC),Y)
    STM32F746G_DISCO_MK_INC=Y

    BOARD_CUSTOM_DIR = $(BOARD_DIR)/stm32f746g_disco

    # $(error BOARD_CUSTOM_DIR=$(BOARD_CUSTOM_DIR))
    MCAL_OPT += -DHAS_STM32F746G_DISCO

    MICROCONTROLLER=Y
    STM32F746G_DISCO=Y
    MCAL_OPT += -DHSE_VALUE=25000000

    INCDIR += -I$(BOARD_CUSTOM_DIR)

    SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/board_config.c
    SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/board_layout.c

    ifeq ($(BOARD_INFO),Y)
        include $(BOARD_CUSTOM_DIR)/board_custom/board_custom.mk
    endif

    ifeq ($(ADC),Y)
        MCAL_OPT += -DADC_REF_VOLTAGE=3.00f
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/adc_config.c
    endif

    ifeq ($(ADC_CHANNEL),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/adc_channel_config.c
    endif

    ifeq ($(GPIO_MAPPER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/gpio_mapper_config.c
    endif

    ifeq ($(BUTTON),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/button_config.c
    endif

    ifeq ($(CLI),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/cli_config.c
    endif

    ifeq ($(CAN),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/can_config.c
        #SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/can_mailbox_config.c
    endif

    ifeq ($(CRYP),Y)
        $(info Config Crypt)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/cryp_config.c
    endif

    ifeq ($(CROSS_DETECT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/cross_detect_config.c
    endif

    ifeq ($(DELTA_SIGMA),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/delta_sigma_config.c
    endif

    ifeq ($(EXT_INT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/ext_int_config.c
    endif

    ifeq ($(FREE_RTOS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/FreeRTOSConfig.c
    endif

    ifeq ($(GARLAND),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/garland_config.c
    endif

    ifeq ($(LITTLE_FS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/little_fs_config.c
    endif

    ifeq ($(HEALTH_MONITOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/board_monitor.c
    endif

    ifeq ($(GPIO),Y)
        $(info Config GPIO)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/gpio_config.c
    endif

    ifeq ($(I2C),Y)
        $(info Config I2C)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/i2c_config.c
    endif

    ifeq ($(ISO_TP),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/iso_tp_config.c
    endif

    ifeq ($(IQUEUE),Y)
        # $(info Config IQUEUE)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/iqueue_config.c
    endif

    ifeq ($(LED_MONO),Y)
        # $(error LED_MONO=$(LED_MONO))
        MCAL_OPT += -DHAS_LED_MONO
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/led_mono_config.c
    endif

    ifeq ($(LOAD_DETECT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/load_detect_config.c
    endif

    ifeq ($(INPUT_CAPTURE),Y)
        $(info Config InputCapture)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/input_capture_config.c
    endif

    ifeq ($(PID),Y)
        # $(info Config PID)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/pid_config.c
    endif

    ifeq ($(PINS),Y)
        $(info Config Pins)
        MCAL_OPT += -DHAS_PINS
    endif

    ifeq ($(POSTPONE_FUN),Y)
        # $(info Config POSTPONE_FUN)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/postpone_fun_config.c
    endif

    ifeq ($(PWM),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/pwm_config.c
    endif

    ifeq ($(RTC),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/rtc_config.c
    endif

    ifeq ($(SCHMITT_TRIGGER),Y)
        # $(error schmitt_trigger=$(schmitt_trigger))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/schmitt_trigger_config.c
    endif

    ifeq ($(SOFTWARE_TIMER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/sw_timer_config.c
    endif

    ifeq ($(SPI),Y)
        $(info Config SPI)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/spi_config.c
    endif

    ifeq ($(STORE_FS),Y)
        $(info Config STORE_FS)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/store_fs_config.c
    endif

    ifeq ($(SW_NVRAM),Y)
        $(info Config SwNvRam)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/sw_nvram_config.c
    endif

    ifeq ($(TBFP),Y)
        $(info Add config TBFP)
        MCAL_OPT += -DTBFP_MAX_PAYLOAD=350
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/tbfp_config.c
    endif

    ifeq ($(TIMER),Y)
        # $(error TIMER=$(TIMER))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/timer_config.c
    endif

    ifeq ($(RELAY),Y)
        # $(info Config RELAY)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/relay_config.c
    endif

    ifeq ($(STRING_READER),Y)
        # $(error STRING_READER=$(STRING_READER))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/string_reader_config.c
    endif

    ifeq ($(TIME),Y)
        # $(error TIME=$(TIME))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/time_config.c
    endif

    ifeq ($(LOG),Y)
        # $(error LOG=$(LOG))
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/log_config.c
    endif

    ifeq ($(UART),Y)
        # $(info Config UART)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/uart_config.c
    endif

    ifeq ($(UDS),Y)
        # $(info Config UDS)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/uds_config.c
    endif

    ifeq ($(MCAL_USB),Y)
        # $(info Config USB)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/usb_config.c
    endif

    ifeq ($(WM8994),Y)
        # $(info Config WM8994)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/wm8994_config.c
    endif

    ifeq ($(WRITER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CUSTOM_DIR)/writer_config.c
    endif

    #####
    ifeq ($(BOARD_SELECTED),Y)
        @echo $(error Board has been selected before)
    endif

    BOARD_SELECTED=Y
endif
