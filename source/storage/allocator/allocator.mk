
ifneq ($(ALLOCATOR_MK_INC),Y)
    ALLOCATOR_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    ALLOCATOR_DIR = $(STORAGE_DIR)/allocator
    #@echo $(error ALLOCATOR_DIR = $(ALLOCATOR_DIR))
    INCDIR += -I$(ALLOCATOR_DIR)

    OPT += -DHAS_HEAP
    OPT += -DHAS_ALLOCATOR

    SOURCES_C += $(ALLOCATOR_DIR)/heap_allocator.c
    ifeq ($(CLI),Y)
        #@echo $(error CLI=$(CLI))
        ifeq ($(ALLOCATOR_COMMANDS),Y)
            #@echo $(error ALLOCATOR_COMMANDS = $(ALLOCATOR_COMMANDS))
            OPT += -DHAS_HEAP_COMMANDS
            SOURCES_C += $(ALLOCATOR_DIR)/allocator_commands.c
        endif
    endif

    ifeq ($(GARBAGE_COLLECTOR),Y)
        include $(STORAGE_DIR)/allocator/garbage_collector/garbage_collector.mk
    endif
endif
