$(info TEST_SDIO_MK_INC=$(TEST_SDIO_MK_INC))
ifneq ($(TEST_SDIO_MK_INC),Y)
    TEST_SDIO_MK_INC=Y


    TEST_SDIO_DIR = $(TEST_SET_HW_DIR)/test_sdio
    #@echo $(error TEST_SDIO_DIR=$(TEST_SDIO_DIR))

    INCDIR += -I$(TEST_SDIO_DIR)
    OPT += -DHAS_TEST_SDIO
    SOURCES_C += $(TEST_SDIO_DIR)/test_sdio.c
endif