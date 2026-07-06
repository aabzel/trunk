
$(info BUTTON_MK_INC=$(BUTTON_MK_INC))

ifneq ($(BUTTON_MK_INC),Y)
    BUTTON_MK_INC=Y

    BUTTON_DIR = $(SENSITIVITY_DIR)/button_fsm
    # $(error BUTTON_DIR=$(BUTTON_DIR))

    INCDIR += -I$(BUTTON_DIR)
    SOURCES_C += $(BUTTON_DIR)/button_mcal.c
    SOURCES_H += $(BUTTON_DIR)/button_mcal.h

    BUTTON=Y
    MCAL_OPT += -DHAS_BUTTON
    MCAL_OPT += -DHAS_BUTTON_PROC

    ifeq ($(BUTTON_DIAG),Y)
        MCAL_OPT += -DHAS_BUTTON_DIAG
        SOURCES_C += $(BUTTON_DIR)/button_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BUTTON_COMMANDS),Y)
            MCAL_OPT += -DHAS_BUTTON_COMMANDS
            SOURCES_C += $(BUTTON_DIR)/button_commands.c
        endif
    endif
endif