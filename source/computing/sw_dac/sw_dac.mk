$(info SW_DAC_MK_INC=$(SW_DAC_MK_INC))
ifneq ($(SW_DAC_MK_INC),Y)
    SW_DAC_MK_INC=Y
    $(info Add SW DAC)

    SW_DAC=Y

    SW_DAC_DIR = $(COMPUTING_DIR)/sw_dac
    INCDIR += -I$(SW_DAC_DIR)
    OPT += -DHAS_SW_DAC

    ifeq ($(SW_DAC_STATIC_SAMPLES),Y)
        OPT += -DHAS_SW_DAC_STATIC_SAMPLES
    endif

    ifeq ($(DYNAMIC_SAMPLES),Y)
        OPT += -DHAS_DYNAMIC_SAMPLES
    endif

    ifeq ($(REAL_SAMPLE_ARRAY),Y)
        OPT += -DHAS_REAL_SAMPLE_ARRAY
    endif

    SOURCES_C += $(SW_DAC_DIR)/sw_dac_config.c
    SOURCES_C += $(SW_DAC_DIR)/sw_dac_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(SW_DAC_DIAG),Y)
            #@echo $(error SW_DAC_DIAG=$(SW_DAC_DIAG))
            $(info Add SW DAC)
            OPT += -DHAS_SW_DAC_DIAG
            SOURCES_C += $(SW_DAC_DIR)/sw_dac_diag.c
        endif
    endif

    #@echo $(error SW_DAC_DIR=$(SW_DAC_DIR))

    ifeq ($(CLI),Y)
        ifeq ($(SW_DAC_COMMANDS),Y)
            $(info Add SW DAC Commands)
            OPT += -DHAS_SW_DAC_COMMANDS
            SOURCES_C += $(SW_DAC_DIR)/sw_dac_commands.c
        endif
    endif

endif
