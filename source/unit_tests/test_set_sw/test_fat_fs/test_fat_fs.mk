ifneq ($(TEST_FAT_FS_MK_INC),Y)
    TEST_FAT_FS_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    TEST_FAT_FS_DIR = $(TEST_SET_SW_DIR)/test_fat_fs
    #@echo $(error TEST_FAT_FS_DIR= $(TEST_FAT_FS_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))
    OPT += -DHAS_TEST_SUIT_FAT_FS
    OPT += -DHAS_TEST_FAT_FS

    INCDIR += -I$(TEST_FAT_FS_DIR)
    SOURCES_C += $(TEST_FAT_FS_DIR)/test_fat_fs.c
endif