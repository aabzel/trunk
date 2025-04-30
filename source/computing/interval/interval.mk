$(info INTERVAL_MK_INC=$(INTERVAL_MK_INC))

ifneq ($(INTERVAL_MK_INC),Y)
    INTERVAL_MK_INC=Y

    INTERVAL_DIR = $(COMPUTING_DIR)/interval
    #@echo $(error INTERVAL_DIR = $(INTERVAL_DIR))

    OPT += -DHAS_INTERVAL
    INCDIR += -I$(INTERVAL_DIR)

    SOURCES_C += $(INTERVAL_DIR)/interval.c

    ifeq ($(INTERVAL_DIAG),Y)
        SOURCES_C += $(INTERVAL_DIR)/interval_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(INTERVAL_COMMANDS),Y)
            #@echo $(error INTERVAL_COMMANDS = $(INTERVAL_COMMANDS))
            OPT += -DHAS_INTERVAL_COMMANDS
            SOURCES_C += $(INTERVAL_DIR)/interval_commands.c
        endif
    endif
endif
