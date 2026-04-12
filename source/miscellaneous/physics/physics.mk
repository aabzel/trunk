ifneq ($(PHYSICS_GENERAL_MK_INC),Y)
    PHYSICS_GENERAL_MK_INC=Y

    PHYSICS_MCAL_DIR = $(MISCELLANEOUS_DIR)/physics
    # $(error PHYSICS_MCAL_DIR=$(PHYSICS_MCAL_DIR))

    INCDIR += -I$(PHYSICS_MCAL_DIR)
    MCAL_OPT += -DHAS_PHYSICS_UTILS
    MCAL_OPT += -DHAS_PHYSICS

    SOURCES_C += $(PHYSICS_MCAL_DIR)/physics_utils.c

    ifeq ($(DIAG),Y)
        ifeq ($(PHYSICS_DIAG),Y)
            MCAL_OPT += -DHAS_PHYSICS_DIAG
            SOURCES_C += $(PHYSICS_MCAL_DIR)/physics_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PHYSICS_COMMANDS),Y)
            # $(error PHYSICS_COMMANDS=$(PHYSICS_COMMANDS))
            $(info Add PHYSICS commands)
            MCAL_OPT += -DHAS_PHYSICS_COMMANDS
            SOURCES_C += $(PHYSICS_MCAL_DIR)/physics_commands.c
        endif
    endif
endif