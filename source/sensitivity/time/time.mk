
ifneq ($(TIME_GENERAL_MK_INC),Y)
    TIME_GENERAL_MK_INC=Y

    TIME_GENERAL_DIR = $(SENSITIVITY_DIR)/time
    # $(error TIME_GENERAL_DIR= $(TIME_GENERAL_DIR))

    INCDIR += -I$(TIME_GENERAL_DIR)

    MCAL_OPT += -DHAS_TIME

    ifeq ($(TIME_PROC),Y)
        MCAL_OPT += -DHAS_TIME_PROC
    endif

    ifeq ($(TIME_EXT),Y)
        MCAL_OPT += -DHAS_TIME_EXT
    endif

    ifeq ($(DATE),Y)
        MCAL_OPT += -DHAS_DATE
    endif

    SOURCES_C += $(TIME_GENERAL_DIR)/time_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(TIME_DIAG),Y)
            MCAL_OPT += -DHAS_TIME_DIAG
            SOURCES_DIAG_C += $(TIME_GENERAL_DIR)/time_diag.c
        endif
    endif

    ifeq ($(TIMER),Y)
        SOURCES_C += $(TIME_GENERAL_DIR)/timer_utils.c
    endif

    SOURCES_C += $(TIME_GENERAL_DIR)/none_blocking_pause.c

    ifeq ($(CLI),Y)
        ifeq ($(TIME_COMMANDS),Y)
            MCAL_OPT += -DHAS_TIME_COMMANDS
            SOURCES_C += $(TIME_GENERAL_DIR)/time_commands.c
        endif
    endif
    
endif