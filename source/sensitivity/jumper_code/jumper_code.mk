ifneq ($(JUMPER_CODE_MK_INC),Y)
    JUMPER_CODE_MK_INC=Y

    JUMPER_CODE_DIR = $(SENSITIVITY_DIR)/jumper_code
    # $(error JUMPER_CODE_DIR=$(JUMPER_CODE_DIR))

    INCDIR += -I$(JUMPER_CODE_DIR)

    MCAL_OPT += -DHAS_JUMPER_CODE

    ifeq ($(JUMPER_CODE_PROC),Y)
        MCAL_OPT += -DHAS_JUMPER_CODE_PROC
    endif

    SOURCES_C += $(JUMPER_CODE_DIR)/jumper_code_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(JUMPER_CODE_DIAG),Y)
            MCAL_OPT += -DHAS_JUMPER_CODE_DIAG
            SOURCES_DIAG_C += $(JUMPER_CODE_DIR)/jumper_code_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(JUMPER_CODE_COMMANDS),Y)
            MCAL_OPT += -DHAS_JUMPER_CODE_COMMANDS
            SOURCES_C += $(JUMPER_CODE_DIR)/jumper_code_commands.c
        endif
    endif
endif
