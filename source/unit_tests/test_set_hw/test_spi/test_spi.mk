    
    TEST_SPI_DIR = $(TEST_SET_HW_DIR)/test_spi

    #@echo $(error TEST_SPI_DIR=$(TEST_SPI_DIR))
    INCDIR += -I$(TEST_SPI_DIR)

    OPT += -DHAS_TEST_SPI
    
    SOURCES_C += $(TEST_SPI_DIR)/test_spi.c
