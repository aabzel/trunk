$(info RATIONAL_NUM_MK_INC=$(RATIONAL_NUM_MK_INC))

ifneq ($(RATIONAL_NUM_MK_INC),Y)
    RATIONAL_NUM_MK_INC=Y

    RATIONAL_NUM_DIR = $(COMPUTING_DIR)/rational_num
    # $(error RATIONAL_NUM_DIR=$(RATIONAL_NUM_DIR))

    INCDIR += -I$(RATIONAL_NUM_DIR)
    MCAL_OPT +=-DHAS_RATIONAL_NUM

    SOURCES_C += $(RATIONAL_NUM_DIR)/rational_num.c

    ifeq ($(RATIONAL_NUM_DIAG),Y)
        MCAL_OPT +=-DHAS_RATIONAL_NUM_DIAG
        SOURCES_C += $(RATIONAL_NUM_DIR)/rational_num_diag.c
    endif

    ifeq ($(RATIONAL_NUM_COMMANDS),Y)
        MCAL_OPT +=-DHAS_RATIONAL_NUM_COMMANDS
        SOURCES_C += $(RATIONAL_NUM_DIR)/rational_num_commands.c
    endif
endif







