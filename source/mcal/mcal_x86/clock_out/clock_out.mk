$(info CLOCK_OUT_CUSTOM_DRV_MK_INC=  $(CLOCK_OUT_CUSTOM_DRV_MK_INC) )
ifneq ($(CLOCK_OUT_CUSTOM_DRV_MK_INC),Y)
    CLOCK_OUT_CUSTOM_DRV_MK_INC=Y

    CLOCK_OUT_CUSTOM_DIR = $(MCAL_X86_DIR)/clock_out

    INCDIR += -I$(CLOCK_OUT_CUSTOM_DIR)
    MCAL_OPT += -DHAS_CLOCK_OUT_CUSTOM

    # $(error CLOCK_OUT_CUSTOM_DIR=$(CLOCK_OUT_CUSTOM_DIR))
    SOURCES_C += $(CLOCK_OUT_CUSTOM_DIR)/clock_out_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(CLOCK_OUT_DIAG),Y)
            MCAL_OPT += -DHAS_CLOCK_OUT_CUSTOM_DIAG
            SOURCES_C += $(CLOCK_OUT_CUSTOM_DIR)/clock_out_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CLOCK_OUT_COMMANDS),Y)
            #@echo $(error CLOCK_OUT_COMMANDS=$(CLOCK_OUT_COMMANDS))
            MCAL_OPT += -DHAS_CLOCK_OUT_CUSTOM_COMMANDS
            SOURCES_C += $(CLOCK_OUT_CUSTOM_DIR)/clock_out_custom_commands.c
        endif
    endif
endif