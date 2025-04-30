$(info TEST_PDM_MK_INC=$(TEST_PDM_MK_INC))
ifneq ($(TEST_PDM_MK_INC),Y)
    TEST_PDM_MK_INC=Y

    $(info + pdm tests)
    TEST_PDM_DIR = $(TEST_SET_HW_DIR)/test_pdm

    #@echo $(error TEST_PDM_DIR=$(TEST_PDM_DIR))
    INCDIR += -I$(TEST_PDM_DIR)

    OPT += -DHAS_TEST_PDM
    OPT += -DHAS_TEST_SUIT_PDM

    SOURCES_C += $(TEST_PDM_DIR)/test_pdm.c
endif