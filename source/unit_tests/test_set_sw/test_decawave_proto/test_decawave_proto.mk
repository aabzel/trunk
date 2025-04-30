ifneq ($(TEST_DECAWAVE_MK_INC),Y)
    TEST_DECAWAVE_MK_INC=Y

    $(info Build  $(mkfile_path) )
    TEST_DECAWAVE_DIR = $(TEST_SET_SW_DIR)/test_decawave_proto
    #@echo $(error TEST_DECAWAVE_DIR= $(TEST_DECAWAVE_DIR))

    OPT += -DHAS_TEST_DECAWAVE
    OPT += -DHAS_TEST_SUIT_DECAWAVE
    OPT += -DHAS_TEST_SUIT_DECAWAVE_PROTO

    INCDIR += -I$(TEST_DECAWAVE_DIR)
    SOURCES_C += $(TEST_DECAWAVE_DIR)/test_decawave_proto.c
endif