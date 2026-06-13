ifneq ($(ENCODER_LAMP_MK_INC),Y)
    ENCODER_LAMP_MK_INC=Y

    ENCODER_LAMP_DIR = $(APPLICATIONS_DIR)/encoder_lamp
    # $(error ENCODER_LAMP_DIR=$(ENCODER_LAMP_DIR))

    INCDIR += -I$(ENCODER_LAMP_DIR)

    MCAL_OPT += -DHAS_ENCODER_LAMP

    ifeq ($(ENCODER_LAMP_PROC),Y)
        MCAL_OPT += -DHAS_ENCODER_LAMP_PROC
    endif

    SOURCES_C += $(ENCODER_LAMP_DIR)/encoder_lamp_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(ENCODER_LAMP_DIAG),Y)
            MCAL_OPT += -DHAS_ENCODER_LAMP_DIAG
            SOURCES_DIAG_C += $(ENCODER_LAMP_DIR)/encoder_lamp_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ENCODER_LAMP_COMMANDS),Y)
            MCAL_OPT += -DHAS_ENCODER_LAMP_COMMANDS
            SOURCES_C += $(ENCODER_LAMP_DIR)/encoder_lamp_commands.c
        endif
    endif
endif
