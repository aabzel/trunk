$(info SW_CONFIG_MK_INC=$(SW_CONFIG_MK_INC))
ifneq ($(SW_CONFIG_MK_INC),Y)
    SW_CONFIG_MK_INC=Y

    BOARD_CFG_DIR = $(BOARD_DIR)/sw_config
    INCDIR += -I$(BOARD_CFG_DIR)
    #@echo $(error BOARD_CFG_DIR=$(BOARD_CFG_DIR))

    OPT += -DHAS_SW_CONFIG


    ifeq ($(AUDIO),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/audio_config.c
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

    ifeq ($(DTMF),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dtmf_config.c
    endif

    ifeq ($(DISTANCE),Y)
        $(info Add config DISTANCE)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/distance_config.c
    endif

    ifeq ($(HEALTH_MONITOR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_monitor.c
    endif

    ifeq ($(LOAD_DETECT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/load_detect_config.c
    endif

    ifeq ($(SCHMITT_TRIGGER),Y)
        #@echo $(error schmitt_trigger=$(schmitt_trigger))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/schmitt_trigger_config.c
    endif

    ifeq ($(SOFTWARE_TIMER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sw_timer_config.c
    endif

    ifeq ($(TBFP),Y)
        $(info Add config TBFP)
        OPT += -DTBFP_MAX_PAYLOAD=350
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/tbfp_config.c
    endif

endif
