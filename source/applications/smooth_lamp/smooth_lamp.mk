ifneq ($(SMOOTH_LAMP_MK_INC),Y)
    SMOOTH_LAMP_MK_INC=Y

    SMOOTH_LAMP_DIR = $(APPLICATIONS_DIR)/smooth_lamp
    # $(error SMOOTH_LAMP_DIR=$(SMOOTH_LAMP_DIR))

    INCDIR += -I$(SMOOTH_LAMP_DIR)

    MCAL_OPT += -DHAS_SMOOTH_LAMP

    MCAL_OPT += -DHAS_SMOOTH_LAMP_PROC

    SOURCES_C += $(SMOOTH_LAMP_DIR)/smooth_lamp.c

    ifeq ($(SMOOTH_LAMP_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_SMOOTH_LAMP_INTERRUPTS
        SOURCES_C += $(SMOOTH_LAMP_DIR)/smooth_lamp_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(SMOOTH_LAMP_DIAG),Y)
            MCAL_OPT += -DHAS_SMOOTH_LAMP_DIAG
            SOURCES_DIAG_C += $(SMOOTH_LAMP_DIR)/smooth_lamp_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SMOOTH_LAMP_COMMANDS),Y)
            MCAL_OPT += -DHAS_SMOOTH_LAMP_COMMANDS
            SOURCES_C += $(SMOOTH_LAMP_DIR)/smooth_lamp_commands.c
        endif
    endif
endif
