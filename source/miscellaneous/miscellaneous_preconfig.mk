ifneq ($(UTILS_PRECONFIG_INC),Y)
    UTILS_PRECONFIG_INC=Y

    MISCELLANEOUS_DIR = $(WORKSPACE_LOC)/miscellaneous
    #@echo $(error MISCELLANEOUS_DIR= $(MISCELLANEOUS_DIR))

    ifeq ($(BIT_UTILS),Y)
        include $(MISCELLANEOUS_DIR)/bit_utils/bit_utils_preconfig.mk
    endif

    ifeq ($(FLOAT),Y)
        include $(MISCELLANEOUS_DIR)/float_utils/float_utils_preconfig.mk
    endif

endif
