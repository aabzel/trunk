ifneq ($(COMPLEX_MK_INC),Y)
    COMPLEX_MK_INC=Y

    COMPLEX_DIR = $(COMPUTING_DIR)/complex
    #@echo $(error COMPLEX_DIR= $(COMPLEX_DIR))

    INCDIR += -I$(COMPLEX_DIR)

    SOURCES_C += $(COMPLEX_DIR)/complex_math.c

    OPT += -DHAS_COMPLEX

    FIFO_ARRAY=Y
    ifeq ($(DIAG),Y)
        ifeq ($(COMPLEX_DIAG),Y)
            OPT += -DHAS_COMPLEX_DIAG
            #@echo $(error COMPLEX_DIAG= $(COMPLEX_DIAG))
            SOURCES_C += $(COMPLEX_DIR)/complex_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(COMPLEX_COMMANDS),Y)
            SOURCES_C += $(COMPLEX_DIR)/complex_commands.c
        endif
    endif
    
endif