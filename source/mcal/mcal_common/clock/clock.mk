
ifneq ($(CLOCKS_GENERAL_MK_INC),Y)
    CLOCKS_GENERAL_MK_INC=Y

    CLOCK_MCAL_DIR = $(MCAL_COMMON_DIR)/clock
    # $(error CLOCK_MCAL_DIR=$(CLOCK_MCAL_DIR))

    INCDIR += -I$(CLOCK_MCAL_DIR)
    OPT += -DHAS_CLOCK
    #CLOCK_DIAG=Y

    SOURCES_C += $(CLOCK_MCAL_DIR)/clock_general.c

    ifeq ($(CLOCK_EXT),Y)
        OPT += -DHAS_CLOCK_EXT
    endif

    ifeq ($(START_PAUSE),Y)
        OPT += -DHAS_START_PAUSE
    endif

    ifeq ($(CLOCK_RUN_TIME_CTRL),Y)
        OPT += -DHAS_CLOCK_RUN_TIME_CTRL
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(CLOCK_DIAG),Y)
            #@echo $(error CLOCK_DIAG=$(CLOCK_DIAG))
            OPT += -DHAS_CLOCK_DIAG
            SOURCES_C += $(CLOCK_MCAL_DIR)/clock_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CLOCK_COMMANDS),Y)
            $(info Add Clock commands)
            OPT += -DHAS_CLOCK_COMMANDS
            SOURCES_C += $(CLOCK_MCAL_DIR)/clock_commands.c
        endif
    endif
endif
