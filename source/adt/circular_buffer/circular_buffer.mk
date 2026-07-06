$(info CIRCULAR_BUFFER_MK_INC=$(CIRCULAR_BUFFER_MK_INC) )

ifneq ($(CIRCULAR_BUFFER_MK_INC),Y)
    CIRCULAR_BUFFER_MK_INC=Y

    MCAL_OPT += -DHAS_CIRCULAR_BUFFER
    CIRCULAR_BUFFER_DIR = $(ADT_DIR)/circular_buffer
    #  $(error CIRCULAR_BUFFER_DIR=[$(CIRCULAR_BUFFER_DIR)])

    INCDIR += -I$(CIRCULAR_BUFFER_DIR)

    SOURCES_C += $(CIRCULAR_BUFFER_DIR)/circular_buffer_index.c

    include $(CIRCULAR_BUFFER_DIR)/float/circular_buffer_float.mk
    include $(CIRCULAR_BUFFER_DIR)/dword/circular_buffer_dword.mk
    include $(CIRCULAR_BUFFER_DIR)/word/circular_buffer_word.mk

    ifeq ($(DIAG),Y)
        ifeq ($(CIRCULAR_BUFFER_DIAG),Y)
            MCAL_OPT += -DHAS_CIRCULAR_BUFFER_DIAG
            SOURCES_C += $(CIRCULAR_BUFFER_DIR)/circular_buffer_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CIRCULAR_BUFFER_COMMANDS),Y)
            #  $(error CIRCULAR_BUFFER_COMMANDS=[$(CIRCULAR_BUFFER_COMMANDS)])
            MCAL_OPT += -DHAS_CIRCULAR_BUFFER_COMMANDS
            SOURCES_C += $(CIRCULAR_BUFFER_DIR)/circular_buffer_commands.c
        endif
    endif
endif






