$(info CIRCULAR_BUFFER_MK_INC=$(CIRCULAR_BUFFER_MK_INC) )

ifneq ($(CIRCULAR_BUFFER_MK_INC),Y)
    CIRCULAR_BUFFER_MK_INC=Y

    OPT += -DHAS_CIRCULAR_BUFFER
    CIRCULAR_BUFFER_DIR = $(ADT_DIR)/circular_buffer
    #@echo $(error CIRCULAR_BUFFER_DIR=[$(CIRCULAR_BUFFER_DIR)])

    INCDIR += -I$(CIRCULAR_BUFFER_DIR)

    SOURCES_C += $(CIRCULAR_BUFFER_DIR)/circular_buffer_index.c
    SOURCES_C += $(CIRCULAR_BUFFER_DIR)/circular_buffer_word.c

    ifeq ($(DIAG),Y)
        ifeq ($(CIRCULAR_BUFFER_DIAG),Y)
            OPT += -DHAS_CIRCULAR_BUFFER_DIAG
            SOURCES_C += $(CIRCULAR_BUFFER_DIR)/circular_buffer_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CIRCULAR_BUFFER_COMMANDS),Y)
            #@echo $(error CIRCULAR_BUFFER_COMMANDS=[$(CIRCULAR_BUFFER_COMMANDS)])
            OPT += -DHAS_CIRCULAR_BUFFER_COMMANDS
            SOURCES_C += $(CIRCULAR_BUFFER_DIR)/circular_buffer_commands.c
        endif
    endif
endif






