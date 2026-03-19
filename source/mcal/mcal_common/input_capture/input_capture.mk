ifneq ($(INPUT_CAPTURE_GENERAL_DRV_MK_INC),Y)
    INPUT_CAPTURE_GENERAL_DRV_MK_INC=Y

    INPUT_CAPTURE_MCAL_DIR = $(MCAL_COMMON_DIR)/input_capture
    #@echo $(error INPUT_CAPTURE_MCAL_DIR=$(INPUT_CAPTURE_MCAL_DIR))

    INCDIR += -I$(INPUT_CAPTURE_MCAL_DIR)
    MCAL_OPT += -DHAS_INPUT_CAPTURE
    MCAL_OPT += -DHAS_INPUT_CAPTURE_INIT

    SOURCES_C += $(INPUT_CAPTURE_MCAL_DIR)/input_capture_general.c
    SOURCES_C += $(INPUT_CAPTURE_MCAL_DIR)/input_capture_isr.c

    ifeq ($(DIAG),Y)
        ifeq ($(INPUT_CAPTURE_DIAG),Y)
            #@echo $(error DIAG_INPUT_CAPTURE=$(DIAG_INPUT_CAPTURE))
            MCAL_OPT += -DHAS_INPUT_CAPTURE_DIAG
            SOURCES_C += $(INPUT_CAPTURE_MCAL_DIR)/input_capture_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(INPUT_CAPTURE_COMMANDS),Y)
            MCAL_OPT += -DHAS_INPUT_CAPTURE_COMMANDS
            SOURCES_C += $(INPUT_CAPTURE_MCAL_DIR)/input_capture_commands.c
        endif
    endif
endif
