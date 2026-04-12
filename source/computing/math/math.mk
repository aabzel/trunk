$(info MATH_MK_INC=$(MATH_MK_INC))

ifneq ($(MATH_MK_INC),Y)
    MATH_MK_INC=Y

    MATH_DIR = $(COMPUTING_DIR)/math
    # $(error MATH_DIR=$(MATH_DIR))

    INCDIR += -I$(MATH_DIR)
    MCAL_OPT +=-DHAS_MATH
    SOURCES_C += $(MATH_DIR)/utils_math.c

    ifeq ($(DIAG),Y)
        SOURCES_C += $(MATH_DIR)/math_diag.c
    endif

    ifeq ($(MATH_VECTOR),Y)
        MCAL_OPT +=-DHAS_MATH_VECTOR
        MCAL_OPT +=-DHAS_VECTOR_MATH
        SOURCES_C += $(MATH_DIR)/vector_math.c
    endif

    ifeq ($(MATH_VECTOR_DIAG),Y)
        MCAL_OPT +=-DHAS_MATH_VECTOR_DIAG
        SOURCES_C += $(MATH_DIR)/vector_diag.c
    endif

    ifeq ($(MATH_COMMANDS),Y)
        # $(error MATH_DIR=$(MATH_DIR))
        MCAL_OPT +=-DHAS_MATH_COMMANDS
        SOURCES_C += $(MATH_DIR)/math_commands.c
    endif
endif







