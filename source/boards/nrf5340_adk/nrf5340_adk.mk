$(info NRF5340_ADK_MK_INC=$(NRF5340_ADK_MK_INC))
ifneq ($(NRF5340_ADK_MK_INC),Y)
    NRF5340_ADK_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    $(info + Config for NRF5340-ADK)

    NRF5340=Y
    OPT += -DHAS_NRF5340
    BOARD_CFG_DIR = $(BOARD_DIR)/nrf5340_adk
    #include $(WORKSPACE_LOC)/mcu/nrf5340/nrf5340.mk
    #@echo $(error BOARD_CFG_DIR=$(BOARD_CFG_DIR))
    #@echo $(error CFLAGS=$(CFLAGS))
    OPT += -DHAS_NRF5340_ADK

    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_config.c
  
    INCDIR += -I$(BOARD_CFG_DIR)

    ifeq ($(AUDIO),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/audio_config.c
    endif

    ifeq ($(BUTTON),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/button_config.c
    endif

    ifeq ($(CROSS_DETECT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cross_detect_config.c
    endif
    ifeq ($(DTMF),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dtmf_config.c
    endif
    ifeq ($(DWM1000),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dwm1000_config.c
    endif

    ifeq ($(DWM3000),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dwm3000_config.c
    endif

    ifeq ($(CLI),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cli_config.c
    endif

    ifeq ($(GPIO),Y)
        $(info Config GPIO)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gpio_config.c
    endif

    ifeq ($(HEALTH_MONITOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_monitor.c
    endif

    ifeq ($(LED),Y)
        $(info Config LED)
        ifeq ($(LED_MONO),Y)
            $(info Config LED MONO)
            #@echo $(error LED_MONO=$(LED_MONO))
            OPT += -DHAS_LED_MONO
            SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/led_mono_config.c
        endif

        ifeq ($(LED_RGB),Y)
            $(info Config LED RGB)
            #@echo $(error LED_RGB=$(LED_RGB))
            OPT += -DHAS_LED_RGB
            SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/led_rgb_config.c
        endif
    endif

    ifeq ($(I2C),Y)
        OPT += -DHAS_I2C
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/i2c_config.c
    endif

    ifeq ($(I2S),Y)
        #@echo $(error I2S=$(I2S))
        OPT += -DHAS_I2S
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/i2s_config.c
    endif

    ifeq ($(LOAD_DETECT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/load_detect_config.c
    endif
    ifeq ($(PINS),Y)
        $(info Config Pins)
        OPT += -DHAS_PINS
    endif

    ifeq ($(PDM),Y)
        #@echo $(error PDM=$(PDM))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/pdm_config.c
    endif
    
    ifeq ($(PWM),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/pwm_config.c
    endif

    ifeq ($(RTC),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/rtc_config.c
    endif

    ifeq ($(SCHMITT_TRIGGER),Y)
        #@echo $(error schmitt_trigger=$(schmitt_trigger))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/schmitt_trigger_config.c
    endif
    
    ifeq ($(SOFTWARE_TIMER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sw_timer_config.c
    endif

    ifeq ($(SPI),Y)
        $(info + SPI config)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/spi_config.c
    endif

    ifeq ($(SD_CARD),Y)
        $(info + SD card config)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sd_card_config.c
    endif

    ifeq ($(TIMER),Y)
        #@echo $(error TIMER=$(TIMER))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/timer_config.c
    endif

    ifeq ($(UART),Y)
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
