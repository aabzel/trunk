ifneq ($(BIN_HEAP_MK_INC),Y)
    BIN_HEAP_MK_INC=Y

    BIN_HEAP_DIR = $(ADT_DIR)/bin_heap
    # $(error BIN_HEAP_DIR=$(BIN_HEAP_DIR))

    INCDIR += -I$(BIN_HEAP_DIR)

    MCAL_OPT += -DHAS_BIN_HEAP

    ifeq ($(BIN_HEAP_PROC),Y)
        MCAL_OPT += -DHAS_BIN_HEAP_PROC
    endif

    SOURCES_C += $(BIN_HEAP_DIR)/bin_heap.c

    ifeq ($(DIAG),Y)
        ifeq ($(BIN_HEAP_DIAG),Y)
            MCAL_OPT += -DHAS_BIN_HEAP_DIAG
            SOURCES_C += $(BIN_HEAP_DIR)/bin_heap_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BIN_HEAP_COMMANDS),Y)
            MCAL_OPT += -DHAS_BIN_HEAP_COMMANDS
            SOURCES_C += $(BIN_HEAP_DIR)/bin_heap_commands.c
        endif
    endif
endif
