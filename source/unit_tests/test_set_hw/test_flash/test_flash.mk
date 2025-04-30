
TEST_FLASH_DIR = $(TEST_SET_HW_DIR)/test_flash
#@echo $(error TEST_FLASH_DIR=$(TEST_FLASH_DIR))
INCDIR += -I$(TEST_FLASH_DIR)

OPT += -DHAS_TEST_FLASH


    ifeq ($(TEST_FLASH_WRITE),Y)
        OPT += -DHAS_TEST_FLASH_WRITE
    endif

SOURCES_C += $(TEST_FLASH_DIR)/test_flash.c

