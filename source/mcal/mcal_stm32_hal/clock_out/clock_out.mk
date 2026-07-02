$(info CLOCK_OUT_CUSTOM_MK_INC=  $(CLOCK_OUT_CUSTOM_MK_INC) )
ifneq ($(CLOCK_OUT_CUSTOM_MK_INC),Y)
    CLOCK_OUT_CUSTOM_MK_INC=Y

    CLOCK_OUT_CUSTOM_DIR = $(MCAL_CUSTOM_DIR)/clock_out
    # $(error CLOCK_OUT_CUSTOM_DIR=$(CLOCK_OUT_CUSTOM_DIR))

    INCDIR += -I$(CLOCK_OUT_CUSTOM_DIR)
    MCAL_OPT += -DHAS_CLOCK_OUT_CUSTOM

    ifeq ($(MCO1),Y)
        MCAL_OPT += -DHAS_MCO1
    endif

    ifeq ($(MCO2),Y)
        MCAL_OPT += -DHAS_MCO2
    endif

    MCAL_OPT += -DHAS_MCO
    MCAL_OPT += -DHAS_CLOCK_OUT_CUSTOM
    SOURCES_C += $(CLOCK_OUT_CUSTOM_DIR)/clock_out_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(CLOCK_OUT_DIAG),Y)
            MCAL_OPT += -DHAS_CLOCK_OUT_CUSTOM_DIAG
            SOURCES_C += $(CLOCK_OUT_CUSTOM_DIR)/clock_out_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CLOCK_OUT_COMMANDS),Y)
            # $(error CLOCK_OUT_COMMANDS=$(CLOCK_OUT_COMMANDS))
            MCAL_OPT += -DHAS_CLOCK_OUT_CUSTOM_COMMANDS
            SOURCES_C += $(CLOCK_OUT_CUSTOM_DIR)/clock_out_custom_commands.c
        endif
    endif
endif