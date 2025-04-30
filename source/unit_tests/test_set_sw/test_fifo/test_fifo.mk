
    
TEST_FIFO_DIR = $(TEST_SET_SW_DIR)/test_fifo
#@echo $(error TEST_FIFO_DIR= $(TEST_FIFO_DIR))
#@echo $(error CFLAGS= $(CFLAGS))

INCDIR += -I$(TEST_FIFO_DIR)

OPT += -DHAS_TEST_SUIT_FIFO

SOURCES_C += $(TEST_FIFO_DIR)/test_fifo_array.c
SOURCES_C += $(TEST_FIFO_DIR)/test_fifo_char.c
SOURCES_C += $(TEST_FIFO_DIR)/test_fifo_indexer.c
