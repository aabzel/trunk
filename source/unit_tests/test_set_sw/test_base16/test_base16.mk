$(info TEST_BASE16_MK_INC=$(TEST_BASE16_MK_INC))

ifneq ($(TEST_BASE16_MK_INC),Y)
    TEST_BASE16_MK_INC=Y
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path))

    ifneq ($(BASE16),Y)
        @echo $(error +BASE16)
    endif

    TEST_BASE16_DIR = $(TEST_SET_SW_DIR)/test_base16
    #@echo $(error TEST_BASE16_DIR= $(TEST_BASE16_DIR))

    OPT += -DHAS_TEST_SUIT_BASE16
    OPT += -DHAS_TEST_BASE16

    INCDIR  += -I$(TEST_BASE16_DIR)

    SOURCES_C += $(TEST_BASE16_DIR)/test_base16.c
endif
