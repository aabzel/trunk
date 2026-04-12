
$(info WRITER_MK_INC=$(WRITER_MK_INC))

ifneq ($(WRITER_MK_INC),Y)
    WRITER_MK_INC=Y

    WRITER_DIR = $(LOG_DIR)/writer
    #$(error WRITER_DIR = $(WRITER_DIR))

    MCAL_OPT += -DHAS_WRITER

    INCDIR += -I$(WRITER_DIR)

    SOURCES_C += $(WRITER_DIR)/writer.c
    # SOURCES_C += $(WRITER_DIR)/writer_config.c

    ifeq ($(UART),Y)
        SOURCES_C += $(WRITER_DIR)/writer_uart.c
    endif

    ifeq ($(PC),Y)
        SOURCES_C += $(WRITER_DIR)/writer_stdout.c
    endif
    
    ifeq ($(DIAG),Y)
        ifeq ($(WRITER_DIAG),Y)
            # $(error WRITER_DIAG = $(WRITER_DIAG))
            MCAL_OPT += -DHAS_WRITER_DIAG
            SOURCES_C += $(WRITER_DIR)/writer_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(WRITER_COMMANDS),Y)
            # $(error WRITER_COMMANDS = $(WRITER_COMMANDS))
            MCAL_OPT += -DHAS_WRITER_COMMANDS
            SOURCES_C += $(WRITER_DIR)/writer_commands.c
        endif
    endif
endif
