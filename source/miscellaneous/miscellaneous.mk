ifneq ($(UTILS_MK_INC),Y)
    UTILS_MK_INC=Y

    MISCELLANEOUS_DIR = $(WORKSPACE_LOC)/miscellaneous
    #@echo $(error MISCELLANEOUS_DIR= $(MISCELLANEOUS_DIR))

    INCDIR += -I$(MISCELLANEOUS_DIR)
    OPT += -DHAS_REPLACE_FORMATTER_CHARACTERS
    OPT += -DHAS_BIT_SWAP
    OPT += -DHAS_MISCELLANEOUS

    ifeq ($(DATA_UTILS_EXT),Y)
        OPT += -DHAS_DATA_UTILS_EXT
    endif

    ifeq ($(DATA_UTILS),Y)
        OPT += -DHAS_DATA_UTILS
        #$(error DATA_UTILS=$(DATA_UTILS))
        SOURCES_C += $(MISCELLANEOUS_DIR)/data_utils.c
    endif

    ifeq ($(BIT_UTILS),Y)
        include $(MISCELLANEOUS_DIR)/bit_utils/bit_utils.mk
    endif

    ifeq ($(UTILS_EXT),Y)
        OPT += -DHAS_UTILS_EXT
        #$(error UTILS_EXT=$(UTILS_EXT))
 
        SOURCES_C += $(MISCELLANEOUS_DIR)/byte_utils.c
        SOURCES_C += $(MISCELLANEOUS_DIR)/helper.c
        SOURCES_C += $(MISCELLANEOUS_DIR)/physics_utils.c
    endif

    ifeq ($(FLOAT),Y)
		include $(MISCELLANEOUS_DIR)/float_utils/float_utils.mk
    endif

    ifeq ($(TEST_FIRMWARE),Y)
        WRITE_ADDR=Y
    endif

    ifeq ($(STREAM),Y)
        #@echo $(error LOG= $(LOG))
        SOURCES_C += $(MISCELLANEOUS_DIR)/debug_info.c
    endif

    #SOURCES_C += $(MISCELLANEOUS_DIR)/utils.c
endif
