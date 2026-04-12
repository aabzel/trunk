ifneq ($(UTILS_MK_INC),Y)
    UTILS_MK_INC=Y

    MISCELLANEOUS_DIR = $(WORKSPACE_LOC)/miscellaneous
    # $(error MISCELLANEOUS_DIR= $(MISCELLANEOUS_DIR))

    INCDIR += -I$(MISCELLANEOUS_DIR)
    MCAL_OPT += -DHAS_REPLACE_FORMATTER_CHARACTERS
    MCAL_OPT += -DHAS_BIT_SWAP
    MCAL_OPT += -DHAS_MISCELLANEOUS
    MCAL_OPT += -DHAS_MISC

    ifeq ($(BIT_UTILS),Y)
        include $(MISCELLANEOUS_DIR)/bit_utils/bit_utils.mk
    endif

    ifeq ($(UTILS_EXT),Y)
        include $(MISCELLANEOUS_DIR)/byte_misc/byte_misc.mk
    endif

    ifeq ($(DATA_UTILS_EXT),Y)
        # $(error DATA_UTILS_EXT=$(DATA_UTILS_EXT))
        MCAL_OPT += -DHAS_DATA_UTILS_EXT
    endif

    ifeq ($(DATA_MISC),Y)
        # $(error DATA_UTILS=$(DATA_UTILS))
        include $(MISCELLANEOUS_DIR)/data_misc/data_misc.mk
    endif

    ifeq ($(UTILS_EXT),Y)
        MCAL_OPT += -DHAS_UTILS_EXT
        # $(error UTILS_EXT=$(UTILS_EXT))
        SOURCES_C += $(MISCELLANEOUS_DIR)/helper.c
    endif

    ifeq ($(PHYSICS),Y)
        include $(MISCELLANEOUS_DIR)/physics/physics.mk
    endif

    ifeq ($(FLOAT),Y)
        include $(MISCELLANEOUS_DIR)/float_utils/float_utils.mk
    endif

    ifeq ($(TEST_FIRMWARE),Y)
        WRITE_ADDR=Y
    endif

    ifeq ($(STREAM),Y)
        # $(error LOG= $(LOG))
        SOURCES_C += $(MISCELLANEOUS_DIR)/debug_info.c
    endif

    #SOURCES_C += $(MISCELLANEOUS_DIR)/utils.c
endif
