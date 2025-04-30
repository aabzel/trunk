$(info TEST_LC3_MK_INC=$(TEST_LC3_MK_INC))

ifneq ($(TEST_LC3_MK_INC),Y)
    TEST_LC3_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    ifneq ($(LC3),Y)
        @echo $(error +LC3)
    endif

    TEST_LC3_DIR = $(TEST_SET_SW_DIR)/test_lc3

    INCDIR += -I$(TEST_LC3_DIR)

    OPT += -DHAS_TEST_SUIT_LC3

    SOURCES_C += $(TEST_LC3_DIR)/test_lc3.c
endif
