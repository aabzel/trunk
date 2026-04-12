ifneq ($(MAX_HEAP_MK_INC),Y)
    MAX_HEAP_MK_INC=Y

    MAX_HEAP_DIR = $(ADT_DIR)/max_heap
    # $(error MAX_HEAP_DIR=$(MAX_HEAP_DIR))

    INCDIR += -I$(MAX_HEAP_DIR)

    MCAL_OPT += -DHAS_MAX_HEAP

    ifeq ($(MAX_HEAP_PROC),Y)
        MCAL_OPT += -DHAS_MAX_HEAP_PROC
    endif

    SOURCES_C += $(MAX_HEAP_DIR)/max_heap.c

    ifeq ($(MAX_HEAP_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_MAX_HEAP_INTERRUPTS
        SOURCES_C += $(MAX_HEAP_DIR)/max_heap_isr.c
    endif

    # must be outside
    SOURCES_C += $(MAX_HEAP_DIR)/max_heap_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(MAX_HEAP_DIAG),Y)
            MCAL_OPT += -DHAS_MAX_HEAP_DIAG
            SOURCES_C += $(MAX_HEAP_DIR)/max_heap_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MAX_HEAP_COMMANDS),Y)
            MCAL_OPT += -DHAS_MAX_HEAP_COMMANDS
            SOURCES_C += $(MAX_HEAP_DIR)/max_heap_commands.c
        endif
    endif
endif
