$(info TEST_BASE64_MK_INC=$(TEST_BASE64_MK_INC))

ifneq ($(TEST_BASE64_MK_INC),Y)
    TEST_BASE64_MK_INC=Y
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path))

    ifneq ($(BASE64),Y)
        @echo $(error +BASE64)
    endif

    TEST_BASE64_DIR = $(TEST_SET_SW_DIR)/test_base64
    #@echo $(error TEST_BASE64_DIR= $(TEST_BASE64_DIR))

    OPT += -DHAS_TEST_SUIT_BASE64
    INCDIR  += -I$(TEST_BASE64_DIR)

    SOURCES_C += $(TEST_BASE64_DIR)/test_base64.c
endif
