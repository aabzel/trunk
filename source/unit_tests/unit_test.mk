ifneq ($(UNIT_TEST_MK_INC),Y)
    UNIT_TEST_MK_INC=Y

    UNIT_TESTS_DIR=$(WORKSPACE_LOC)/unit_tests
    # $(error UNIT_TESTS_DIR=$(UNIT_TESTS_DIR))

    INCDIR += -I$(UNIT_TESTS_DIR)
    MCAL_OPT += -DHAS_UNIT_TEST
    MCAL_OPT += -DHAS_TEST

    ifneq ($(UNIT_TEST),Y)
        @echo $(error Add UNIT_TEST)
    endif

    SOURCES_C +=$(UNIT_TESTS_DIR)/print_buffer.c
    SOURCES_C +=$(UNIT_TESTS_DIR)/test_config.c
    SOURCES_C +=$(UNIT_TESTS_DIR)/unit_test.c

    ifeq ($(DIAG),Y)
        ifeq ($(UNIT_TEST_DIAG),Y)
            # $(error UNIT_TEST_DIAG=$(UNIT_TEST_DIAG))
            MCAL_OPT += -DHAS_UNIT_TEST_DIAG
            SOURCES_DIAG_C +=$(UNIT_TESTS_DIR)/unit_test_diag.c
        endif
    endif
    
    ifeq ($(CLI),Y)
        ifeq ($(UNIT_TEST_COMMANDS),Y)
            # $(error UNIT_TEST_COMMANDS=$(UNIT_TEST_COMMANDS))
            MCAL_OPT += -DHAS_UNIT_TEST_COMMANDS
            SOURCES_C += $(UNIT_TESTS_DIR)/unit_test_commands.c
        endif
    endif

    ifeq ($(TEST_SW),Y)
        # $(error TEST_SW=$(TEST_SW))
        MCAL_OPT += -DHAS_SW_TESTS
        include $(UNIT_TESTS_DIR)/test_set_sw/test_set_sw.mk
    endif

    ifeq ($(TEST_HW),Y)
        # $(error TEST_HW=$(TEST_HW))
        MCAL_OPT += -DHAS_HW_TESTS
        include $(UNIT_TESTS_DIR)/test_set_hw/test_set_hw.mk
    endif
endif