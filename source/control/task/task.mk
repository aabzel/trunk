ifneq ($(SCHEDULER_DRV_MK_INC),Y)
    SCHEDULER_DRV_MK_INC=Y

    SCHEDULER_DIR = $(CONTROL_DIR)/task
    # $(error SCHEDULER_DIR=$(SCHEDULER_DIR))
    INCDIR += -I$(SCHEDULER_DIR)

    OPT += -DHAS_TASK
    OPT += -DHAS_SCHEDULER

    SOURCES_C += $(SCHEDULER_DIR)/task_info.c
    SOURCES_C += $(SCHEDULER_DIR)/task_config.c

    ifeq ($(TASK_DIAG),Y)
        OPT += -DHAS_TASK_DIAG
        SOURCES_C += $(SCHEDULER_DIR)/task_diag.c
    endif

    ifeq ($(CLI),Y)
        #@echo $(error TASK_COMMANDS=$(TASK_COMMANDS))
        ifeq ($(TASK_COMMANDS),Y)
            OPT += -DHAS_TASK_COMMANDS
            SOURCES_C += $(SCHEDULER_DIR)/task_commands.c
        endif
    endif
endif
