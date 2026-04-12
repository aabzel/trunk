ifneq ($(SCHEDULER_DRV_MK_INC),Y)
    SCHEDULER_DRV_MK_INC=Y

    SCHEDULER_DIR = $(CONTROL_DIR)/scheduler
    # $(error SCHEDULER_DIR=$(SCHEDULER_DIR))
    INCDIR += -I$(SCHEDULER_DIR)

    MCAL_OPT += -DHAS_SCHEDULER

    ifeq ($(SCHEDULER_EXT),Y)
        MCAL_OPT += -DHAS_SCHEDULER_EXT
    endif

    SOURCES_C += $(SCHEDULER_DIR)/scheduler_mcal.c

    ifeq ($(SCHEDULER_DIAG),Y)
        MCAL_OPT += -DHAS_SCHEDULER_DIAG
        SOURCES_C += $(SCHEDULER_DIR)/scheduler_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SCHEDULER_COMMANDS),Y)
            # $(error SCHEDULER_COMMANDS=$(SCHEDULER_COMMANDS))
            MCAL_OPT += -DHAS_SCHEDULER_COMMANDS
            SOURCES_C += $(SCHEDULER_DIR)/scheduler_commands.c
        endif
    endif
endif
