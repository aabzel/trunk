ifneq ($(INPUT_CAPTURE_CUSTOM_DRV_MK_INC),Y)
    INPUT_CAPTURE_CUSTOM_DRV_MK_INC=Y

    INPUT_CAPTURE_CUSTOM_DIR = $(MCAL_AT32F4_DIR)/input_capture
    #@echo $(error INPUT_CAPTURE_CUSTOM_DIR=$(INPUT_CAPTURE_CUSTOM_DIR))

    INCDIR += -I$(INPUT_CAPTURE_CUSTOM_DIR)
    MCAL_OPT += -DHAS_INPUT_CAPTURE

    SOURCES_C += $(INPUT_CAPTURE_CUSTOM_DIR)/input_capture_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(INPUT_CAPTURE_DIAG),Y)
            MCAL_OPT += -DHAS_INPUT_CAPTURE_CUSTOM_DIAG
            SOURCES_C += $(INPUT_CAPTURE_CUSTOM_DIR)/input_capture_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(INPUT_CAPTURE_COMMANDS),Y)
            MCAL_OPT += -DHAS_INPUT_CAPTURE_CUSTOM_COMMANDS
            SOURCES_C += $(INPUT_CAPTURE_CUSTOM_DIR)/input_capture_custom_commands.c
        endif
    endif
endif
