ifneq ($(TEST_PHYSICS_MK),Y)
    TEST_PHYSICS_MK=Y
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    TEST_PHYSICS_DIR = $(TEST_SET_SW_DIR)/test_physics
    #@echo $(error TEST_PHYSICS_DIR= $(TEST_PHYSICS_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))
    $(info Add Utils Test)
    INCDIR += -I$(TEST_PHYSICS_DIR)

    OPT += -DHAS_TEST_SUIT_PHYSICS
    OPT += -DHAS_TEST_PHYSICS

    SOURCES_C += $(TEST_PHYSICS_DIR)/test_physics.c



endif