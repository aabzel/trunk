ifneq ($(AES_TEST_CASE_MK_INC),Y)
    AES_TEST_CASE_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path))

    AES_TEST_CASES_DIR=$(TEST_SET_SW_DIR)/aes_test_utils
    #@echo $(error AES_TEST_CASES_DIR=$(AES_TEST_CASES_DIR))

    INCDIR += -I$(AES_TEST_CASES_DIR)
    OPT += -DHAS_AES_TEST_CASE

    SOURCES_C +=$(AES_TEST_CASES_DIR)/aes_test_case.c

endif