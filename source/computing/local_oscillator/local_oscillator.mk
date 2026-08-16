ifneq ($(LOCAL_OSCILLATOR_MK_INC),Y)
    LOCAL_OSCILLATOR_MK_INC=Y

    LOCAL_OSCILLATOR_DIR = $(COMPUTING_DIR)/local_oscillator
    # $(error LOCAL_OSCILLATOR_DIR=$(LOCAL_OSCILLATOR_DIR))

    INCDIR += -I$(LOCAL_OSCILLATOR_DIR)

    MCAL_OPT += -DHAS_LOCAL_OSCILLATOR
    SOURCES_C += $(LOCAL_OSCILLATOR_DIR)/local_oscillator_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(LOCAL_OSCILLATOR_DIAG),Y)
            MCAL_OPT += -DHAS_LOCAL_OSCILLATOR_DIAG
            SOURCES_DIAG_C += $(LOCAL_OSCILLATOR_DIR)/local_oscillator_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(LOCAL_OSCILLATOR_COMMANDS),Y)
            MCAL_OPT += -DHAS_LOCAL_OSCILLATOR_COMMANDS
            SOURCES_C += $(LOCAL_OSCILLATOR_DIR)/local_oscillator_commands.c
        endif
    endif
endif
