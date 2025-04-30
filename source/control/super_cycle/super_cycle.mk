$(info SUPER_CYCLE_MK_INC=$(SUPER_CYCLE_MK_INC))

ifneq ($(SUPER_CYCLE_MK_INC),Y)
    SUPER_CYCLE_MK_INC=Y

    $(info Add Super Cycle)

    SUPER_CYCLE_DIR = $(CONTROL_DIR)/super_cycle
    #@echo $(error SUPER_CYCLE_DIR = $(SUPER_CYCLE_DIR))

    OPT += -DHAS_SUPER_CYCLE
    INCDIR += -I$(SUPER_CYCLE_DIR)

    SOURCES_C += $(SUPER_CYCLE_DIR)/super_cycle.c
    SOURCES_C += $(SUPER_CYCLE_DIR)/super_cycle_config.c

    ifeq ($(SUPER_CYCLE_DIAG),Y)
        $(info Add Super Cycle Diag)
        OPT += -DHAS_SUPER_CYCLE_DIAG
        SOURCES_C += $(SUPER_CYCLE_DIR)/super_cycle_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SUPER_CYCLE_COMMANDS),Y)
            $(info Add Super Cycle Commands)
            OPT += -DHAS_SUPER_CYCLE_COMMANDS
            #@echo $(error SUPER_CYCLE_COMMANDS = $(SUPER_CYCLE_COMMANDS))
            SOURCES_C += $(SUPER_CYCLE_DIR)/super_cycle_commands.c
        endif
    endif
endif
