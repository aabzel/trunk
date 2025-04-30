ifneq ($(TEST_DDS_MK),Y)
    TEST_DDS_MK=Y

    TEST_DDS_DIR = $(TEST_SET_SW_DIR)/test_dds
    #@echo $(error TEST_DDS_DIR= $(TEST_DDS_DIR))
    $(info + DDS Test)
    INCDIR += -I$(TEST_DDS_DIR)

    OPT += -DHAS_TEST_SUIT_DDS
    OPT += -DHAS_TEST_DDS

    SOURCES_C += $(TEST_DDS_DIR)/test_dds.c

endif