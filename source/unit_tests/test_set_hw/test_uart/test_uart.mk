    
    TEST_UART_DIR = $(TEST_SET_HW_DIR)/test_uart
#@echo $(error TEST_UART_DIR=$(TEST_UART_DIR))
INCDIR += -I$(TEST_UART_DIR)

OPT += -DHAS_TEST_UART

SOURCES_C += $(TEST_UART_DIR)/test_uart.c

