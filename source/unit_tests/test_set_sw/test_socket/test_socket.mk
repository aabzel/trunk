ifneq ($(TEST_SOCKET_MK_INC),Y)
    TEST_SOCKET_MK_INC=Y

    $(info Build  $(mkfile_path))

    TEST_SOCKET_DIR = $(TEST_SET_SW_DIR)/test_socket
    #@echo $(error TEST_SOCKET_DIR= $(TEST_SOCKET_DIR))
    
    INCDIR += -I$(TEST_SOCKET_DIR)
    OPT += -DHAS_TEST_SUIT_SOCKET
    OPT += -DHAS_TEST_SOCKET
    
    SOURCES_C += $(TEST_SOCKET_DIR)/test_socket.c
endif