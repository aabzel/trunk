
ifneq ($(GARBAGE_COLLECTOR_MK_INC),Y)
    GARBAGE_COLLECTOR_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    GARBAGE_COLLECTOR_DIR = $(WORKSPACE_LOC)components/allocator/garbage_collector
    #@echo $(error GARBAGE_COLLECTOR_DIR = $(GARBAGE_COLLECTOR_DIR))

    OPT += -DHAS_GARBAGE_COLLECTOR
    INCDIR += -I$(GARBAGE_COLLECTOR_DIR)

    SOURCES_C += $(GARBAGE_COLLECTOR_DIR)/garbage_collector.c
    ifeq ($(CLI),Y)
        ifeq ($(GARBAGE_COLLECTOR_COMMANDS),Y)
            #@echo $(error GARBAGE_COLLECTOR_COMMANDS = $(GARBAGE_COLLECTOR_COMMANDS))
            OPT += -DHAS_GARBAGE_COLLECTOR_COMMANDS
            SOURCES_C += $(GARBAGE_COLLECTOR_DIR)/garbage_collector_commands.c
        endif
    endif
endif
