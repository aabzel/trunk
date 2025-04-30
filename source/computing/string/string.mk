$(info STRINGS_MK_INC=$(STRINGS_MK_INC))

ifneq ($(STRINGS_MK_INC),Y)
    STRINGS_MK_INC=Y

    STRING_UTILS_DIR = $(COMPUTING_DIR)/string
    #@echo $(error STRING_UTILS_DIR=$(STRING_UTILS_DIR))
    INCDIR += -I$(STRING_UTILS_DIR)
    OPT += -DHAS_STRING

    ifeq ($(STRING_PARSER),Y)
        OPT += -DHAS_PARSE_8BIT_TYPES
        OPT += -DHAS_PARSE_16BIT_TYPES
        OPT += -DHAS_PARSE_32BIT_TYPES
        OPT += -DHAS_PARSE_64BIT_TYPES
        OPT += -DHAS_STRING_PARSER
        #@echo $(error STRING_PARSER= $(STRING_PARSER))
        SOURCES_C += $(STRING_UTILS_DIR)/convert.c
    endif

    ifeq ($(NUM_DIAG),Y)
        OPT += -DHAS_NUM_DIAG
        SOURCES_C += $(STRING_UTILS_DIR)/num_to_str.c
    endif

    ifeq ($(STRING_PARSER_DIAG),Y)
        OPT += -DHAS_STRING_PARSER_DIAG
        SOURCES_C += $(STRING_UTILS_DIR)/convert_diag.c
    endif

    SOURCES_C += $(STRING_UTILS_DIR)/str_utils.c

    ifeq ($(STR2_DOUBLE),Y)
        #@echo $(error STR2_DOUBLE=$(STR2_DOUBLE))
        OPT += -DHAS_STR2_DOUBLE
    endif
    
    ifeq ($(DOUBLE_TO_STR),Y)
        #@echo $(error DOUBLE_TO_STR=$(DOUBLE_TO_STR))
        OPT += -DHAS_DOUBLE_TO_STR
    endif

    ifeq ($(BIN_2_STR),Y)
        #@echo $(error BIN_2_STR=$(BIN_2_STR))
        OPT += -DHAS_BIN_2_STR
    endif

    ifeq ($(STR2_MONTH),Y)
        OPT += -DHAS_STR2_MONTH
    endif

    ifeq ($(STR2_FLOAT),Y)
        OPT += -DHAS_STR2_FLOAT
    endif

    ifeq ($(X86_64),Y)
        #@echo $(error stop)
        SOURCES_C += $(STRING_UTILS_DIR)/str_utils_ex.c
    endif
endif