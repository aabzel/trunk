
ifneq ($(TIME_GENERAL_MK_INC),Y)
    TIME_GENERAL_MK_INC=Y

    TIME_GENERAL_DIR = $(SENSITIVITY_DIR)/time
    # $(error TIME_GENERAL_DIR= $(TIME_GENERAL_DIR))

    INCDIR += -I$(TIME_GENERAL_DIR)

    OPT += -DHAS_TIME

    ifeq ($(TIME_PROC),Y)
        OPT += -DHAS_TIME_PROC
    endif

    ifeq ($(TIME_EXT),Y)
        OPT += -DHAS_TIME_EXT
        SOURCES_C += $(TIME_GENERAL_DIR)/none_blocking_pause.c
    endif


    ifeq ($(DATE),Y)
        OPT += -DHAS_DATE
    endif

    SOURCES_C += $(TIME_GENERAL_DIR)/time_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(TIME_DIAG),Y)
            OPT += -DHAS_TIME_DIAG
            SOURCES_C += $(TIME_GENERAL_DIR)/time_diag.c
        endif
    endif

    ifeq ($(TIMER),Y)
        SOURCES_C += $(TIME_GENERAL_DIR)/timer_utils.c
    endif


    ifeq ($(CLI),Y)
        ifeq ($(TIME_COMMANDS),Y)
            OPT += -DHAS_TIME_COMMANDS
            SOURCES_C += $(TIME_GENERAL_DIR)/time_commands.c
        endif
    endif
    
endif