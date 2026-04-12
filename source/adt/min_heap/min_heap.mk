ifneq ($(MIN_HEAP_MK_INC),Y)
    MIN_HEAP_MK_INC=Y

    MIN_HEAP_DIR = $(ADT_DIR)/min_heap
    # $(error MIN_HEAP_DIR=$(MIN_HEAP_DIR))

    INCDIR += -I$(MIN_HEAP_DIR)

    MCAL_OPT += -DHAS_MIN_HEAP

    ifeq ($(MIN_HEAP_PROC),Y)
        MCAL_OPT += -DHAS_MIN_HEAP_PROC
    endif

    SOURCES_C += $(MIN_HEAP_DIR)/min_heap.c

    ifeq ($(MIN_HEAP_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_MIN_HEAP_INTERRUPTS
        SOURCES_C += $(MIN_HEAP_DIR)/min_heap_isr.c
    endif

    # must be outside
    SOURCES_C += $(MIN_HEAP_DIR)/min_heap_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(MIN_HEAP_DIAG),Y)
            MCAL_OPT += -DHAS_MIN_HEAP_DIAG
            SOURCES_C += $(MIN_HEAP_DIR)/min_heap_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MIN_HEAP_COMMANDS),Y)
            MCAL_OPT += -DHAS_MIN_HEAP_COMMANDS
            SOURCES_C += $(MIN_HEAP_DIR)/min_heap_commands.c
        endif
    endif
endif
