
ifneq ($(TEST_PLANETARIUM_MK_INC),Y)
    TEST_PLANETARIUM_MK_INC=Y
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path))

    TEST_PLANETARIUM_DIR = $(TEST_SET_SW_DIR)/test_planetarium
    #@echo $(error TEST_PLANETARIUM_DIR= $(TEST_PLANETARIUM_DIR))

    INCDIR += -I$(TEST_PLANETARIUM_DIR)
    OPT += -DHAS_TEST_SUIT_PLANETARIUM
    OPT += -DHAS_TEST_PLANETARIUM

    SOURCES_C += $(TEST_PLANETARIUM_DIR)/test_planetarium.c
endif