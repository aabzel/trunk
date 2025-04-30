$(info LAP_TOP_X86_MK_INC=$(LAP_TOP_X86_MK_INC))
ifneq ($(LAP_TOP_X86_MK_INC),Y)
    LAP_TOP_X86_MK_INC=Y

    BOARD_CFG_DIR = $(BOARD_DIR)/x86
    #$(error BOARD_CFG_DIR=$(BOARD_CFG_DIR))

    OPT += -DHAS_X86
    OPT += -DHAS_PC

    INCDIR += -I$(BOARD_CFG_DIR)

    ifeq ($(BOARD_SELECTED),Y)
        @echo $(error Board has been selected before)
    endif

    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_config.c
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/board_monitor.c

    ifeq ($(GPIO),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gpio_config.c
    endif
    
    ifeq ($(BPSK),Y)
        $(info Add config BPSK)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/bpsk_config.c
    endif

    ifeq ($(CORRELATOR),Y)
        $(info Add config CORRELATOR)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/correlator_config.c
    endif
    
    ifeq ($(SCAN),Y)
        $(info Add config SCAN)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/scan_config.c
    endif
    
    ifeq ($(QUADRATURE_MIXER),Y)
        $(info Add config QUADRATURE_MIXER)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/quadrature_mixer_config.c
    endif

    ifeq ($(CLOCK_DIVIDER),Y)
        $(info Add config CLOCK_DIVIDER)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/clock_divider_config.c
    endif

    ifeq ($(DECIMATOR),Y)
        $(info Add config DECIMATOR)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/decimator_config.c
    endif

    ifeq ($(DELTA_SIGMA),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/delta_sigma_config.c
    endif

    ifeq ($(KALAH),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/kalah_config.c
    endif

    ifeq ($(SET_GAME),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/set_game_config.c
    endif

    ifeq ($(DTMF),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dtmf_config.c
    endif
    
    ifeq ($(DS_TWR),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/ds_twr_config.c
    endif

    ifeq ($(GPS),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gps_config.c
    endif
    
    ifeq ($(TOPO_SORT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/topo_sort_config.c
    endif
    

    ifeq ($(GPS_1BIT),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/gps_1bit_config.c
    endif

    ifeq ($(CLI),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cli_config.c
    endif



    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/mem_config.c

    ifeq ($(CRYP),Y)
        $(info Config Crypt)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/cryp_config.c
    endif

    ifeq ($(LOG),Y)
        $(info Config LOG)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/log_config.c
    endif

    ifeq ($(DASHBOARD),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/dashboard_config.c
    endif

    ifeq ($(DISPLAY),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/display_config.c
    endif

    ifeq ($(HISTOGRAM),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/histogram_config.c
    endif

    ifeq ($(IIR),Y)
        $(info Config IIR)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/iir_config.c
    endif

    ifeq ($(KEEPASS),Y)
        $(info Config KeePass)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/keepass_config.c
    endif

    ifeq ($(NOR_FLASH),Y)
        $(info Config SwNvRam)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/nor_flash_config.c
    endif

    ifeq ($(SET),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/set_config.c
    endif

    ifeq ($(STRING_READER),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/string_reader_config.c
    endif

    ifeq ($(SDR),Y)
        $(info Config Crypt)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/local_oscillator_config.c
    endif
    
    ifeq ($(SOCKET),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/socket_config.c
    endif

    ifeq ($(SONAR),Y)
        $(info Config SONAR)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sonar_config.c
    endif

    ifeq ($(SOUND_LOCALIZATION),Y)
        $(info Add config SOUND_LOCALIZATION)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sound_localization_config.c
    endif

    ifeq ($(SW_NOR_FLASH),Y)
        $(info Config SwNvRam)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sw_nor_flash_config.c
    endif

    ifeq ($(SCHMITT_TRIGGER),Y)
        #@echo $(error schmitt_trigger=$(schmitt_trigger))
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/schmitt_trigger_config.c
    endif

    ifeq ($(SPI),Y)
        $(info Config SPI)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/spi_config.c
    endif
    
    ifeq ($(SW_NVRAM),Y)
        $(info Config SwNvRam)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/sw_nvram_config.c
    endif

    ifeq ($(DECAWAVE),Y)
        $(info Add config DECAWAVE)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/decawave_proto_config.c
    endif
    
    ifeq ($(FIR),Y)
        $(info Add config FIR)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/fir_config.c
    endif

    ifeq ($(PHASE_DETECTOR),Y)
        $(info Add config PHASE DETECTOR)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/phase_detector_config.c
    endif

    ifeq ($(PID),Y)
        $(info Add config PID)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/pid_config.c
    endif
    
    ifeq ($(PLL_SIM),Y)
        $(info Add config PLL_SIM)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/pll_sim_config.c
    endif

    ifeq ($(RUNNING_LINE),Y)
        $(info Add config RUNNING_LINE)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/running_line_config.c
    endif

    ifeq ($(TIME),Y)
        $(info Add config TIME)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/time_config.c
    endif

    ifeq ($(WAV),Y)
        $(info Config WAV)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/wav_config.c
    endif
    
    ifeq ($(ISO_TP),Y)
        $(info Add config ISO_TP)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/iso_tp_config.c
    endif

    ifeq ($(TBFP),Y)
        $(info Add config TBFP)
        OPT += -DTBFP_MAX_PAYLOAD=512
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/tbfp_config.c
    endif

    ifeq ($(XML),Y)
        SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/xml_config.c
    endif

    BOARD_SELECTED=Y
endif