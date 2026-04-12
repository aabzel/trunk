$(info CIRCULAR_BUFFER_WORD_MK_INC=$(CIRCULAR_BUFFER_WORD_MK_INC) )
ifneq ($(CIRCULAR_BUFFER_WORD_MK_INC),Y)
    CIRCULAR_BUFFER_WORD_MK_INC=Y

    MCAL_OPT += -DHAS_CIRCULAR_BUFFER_WORD
    CIRCULAR_BUFFER_WORD_DIR = $(CIRCULAR_BUFFER_DIR)/word
    #  $(error CIRCULAR_BUFFER_WORD_DIR=[$(CIRCULAR_BUFFER_WORD_DIR)])

    INCDIR += -I$(CIRCULAR_BUFFER_WORD_DIR)

    SOURCES_C += $(CIRCULAR_BUFFER_WORD_DIR)/circular_buffer_word.c

    ifeq ($(DIAG),Y)
        ifeq ($(CIRCULAR_BUFFER_WORD_DIAG),Y)
            MCAL_OPT += -DHAS_CIRCULAR_BUFFER_WORD_DIAG
            SOURCES_C += $(CIRCULAR_BUFFER_WORD_DIR)/circular_buffer_word_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CIRCULAR_BUFFER_WORD_COMMANDS),Y)
            #  $(error CIRCULAR_BUFFER_WORD_COMMANDS=[$(CIRCULAR_BUFFER_WORD_COMMANDS)])
            MCAL_OPT += -DHAS_CIRCULAR_BUFFER_WORD_COMMANDS
            SOURCES_C += $(CIRCULAR_BUFFER_WORD_DIR)/circular_buffer_word_commands.c
        endif
    endif
endif






