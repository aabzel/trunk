$(info TEST_BT1026_MK_INC=$(TEST_BT1026_MK_INC))

ifneq ($(TEST_BT1026_MK_INC),Y)
    TEST_BT1026_MK_INC=Y
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path))

    ifneq ($(BT1026),Y)
        @echo $(error +BT1026)
    endif

    TEST_BT1026_DIR = $(TEST_SET_SW_DIR)/test_bt1026
    #@echo $(error TEST_BT1026_DIR= $(TEST_BT1026_DIR))

    OPT += -DHAS_TEST_SUIT_BT1026
    INCDIR  += -I$(TEST_BT1026_DIR)

    SOURCES_C += $(TEST_BT1026_DIR)/test_bt1026.c
endif
