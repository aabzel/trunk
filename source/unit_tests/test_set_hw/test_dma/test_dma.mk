    
    
    TEST_DMA_DIR = $(TEST_SET_HW_DIR)/test_dma
#@echo $(error TEST_DMA_DIR=$(TEST_DMA_DIR))
INCDIR += -I$(TEST_DMA_DIR)

OPT += -DHAS_TEST_DMA

SOURCES_C += $(TEST_DMA_DIR)/test_dma.c

