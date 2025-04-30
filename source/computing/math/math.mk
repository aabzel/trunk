$(info MATH_MK_INC=$(MATH_MK_INC))

ifneq ($(MATH_MK_INC),Y)
    MATH_MK_INC=Y

    MATH_DIR = $(COMPUTING_DIR)/math
    #@echo $(error MATH_DIR=$(MATH_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))
    INCDIR += -I$(MATH_DIR)
    OPT +=-DHAS_MATH
    SOURCES_C += $(MATH_DIR)/utils_math.c

    ifeq ($(MATH_VECTOR),Y)
        OPT +=-DHAS_MATH_VECTOR
        OPT +=-DHAS_VECTOR_MATH
        SOURCES_C += $(MATH_DIR)/vector_math.c
    endif

    ifeq ($(MATH_VECTOR_DIAG),Y)
        OPT +=-DHAS_MATH_VECTOR_DIAG
        SOURCES_C += $(MATH_DIR)/vector_diag.c
    endif

    ifeq ($(MATH_COMMANDS),Y)
        OPT +=-DHAS_MATH_COMMANDS
        SOURCES_C += $(MATH_DIR)/math_commands.c
    endif
endif







