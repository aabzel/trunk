ifneq ($(BIT_FIFO_MK_INC),Y)
    BIT_FIFO_MK_INC=Y

    BIT_FIFO_DIR = $(ADT_DIR)/bit_fifo
    # $(error BIT_FIFO_DIR=$(BIT_FIFO_DIR))

    INCDIR += -I$(BIT_FIFO_DIR)

    MCAL_OPT += -DHAS_BIT_FIFO

    ifeq ($(BIT_FIFO_PROC),Y)
        MCAL_OPT += -DHAS_BIT_FIFO_PROC
    endif

    SOURCES_C += $(BIT_FIFO_DIR)/bit_fifo_mcal.c

    ifeq ($(BIT_FIFO_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_BIT_FIFO_INTERRUPTS
        SOURCES_C += $(BIT_FIFO_DIR)/bit_fifo_isr.c
    endif

    # must be outside
    SOURCES_CONFIGURATION_C += $(BIT_FIFO_DIR)/bit_fifo_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(BIT_FIFO_DIAG),Y)
            MCAL_OPT += -DHAS_BIT_FIFO_DIAG
            SOURCES_DIAG_C += $(BIT_FIFO_DIR)/bit_fifo_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BIT_FIFO_COMMANDS),Y)
            MCAL_OPT += -DHAS_BIT_FIFO_COMMANDS
            SOURCES_C += $(BIT_FIFO_DIR)/bit_fifo_commands.c
        endif
    endif
endif
