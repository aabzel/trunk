ifneq ($(UNIT_TEST_MK_INC),Y)
    UNIT_TEST_MK_INC=Y


    UNIT_TESTS_DIR=$(WORKSPACE_LOC)/unit_tests
    #@echo $(error UNIT_TESTS_DIR=$(UNIT_TESTS_DIR))

    INCDIR += -I$(UNIT_TESTS_DIR)
    OPT += -DHAS_UNIT_TEST
    OPT += -DHAS_TEST

    ifneq ($(UNIT_TEST),Y)
        @echo $(error Add UNIT_TEST)
    endif

    SOURCES_C +=$(UNIT_TESTS_DIR)/print_buffer.c
    SOURCES_C +=$(UNIT_TESTS_DIR)/test_config.c
    SOURCES_C +=$(UNIT_TESTS_DIR)/unit_test.c
    SOURCES_C +=$(UNIT_TESTS_DIR)/unit_test_run.c

    ifeq ($(CLI),Y)
        ifeq ($(UNIT_TEST_COMMANDS),Y)
            #@echo $(error UNIT_TEST_COMMANDS=$(UNIT_TEST_COMMANDS))
            OPT += -DHAS_UNIT_TEST_COMMANDS
            SOURCES_C += $(UNIT_TESTS_DIR)/unit_test_commands.c
        endif
    endif

    ifeq ($(TEST_SW),Y)
        #@echo $(error TEST_SW=$(TEST_SW))
        OPT += -DHAS_SW_TESTS
        include $(UNIT_TESTS_DIR)/test_set_sw/test_set_sw.mk
    endif

    ifeq ($(TEST_HW),Y)
        #@echo $(error TEST_HW=$(TEST_HW))
        OPT += -DHAS_HW_TESTS
        include $(UNIT_TESTS_DIR)/test_set_hw/test_set_hw.mk
    endif
endif