
ifneq ($(TEST_MODULATOR_MK_INC),Y)
    TEST_MODULATOR_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    
    TEST_MODULATOR_DIR = $(TEST_SET_SW_DIR)/test_modulator
    #@echo $(error TEST_MODULATOR_DIR= $(TEST_MODULATOR_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))

    OPT += -DHAS_TEST_SUIT_MODULATOR
    OPT += -DHAS_TEST_MODULATOR

    INCDIR  += -I$(TEST_MODULATOR_DIR)

    SOURCES_C += $(TEST_MODULATOR_DIR)/test_modulator.c


endif

