ifneq ($(END_OF_BLOCK_MK_INC),Y)
    END_OF_BLOCK_MK_INC=Y

    END_OF_BLOCK_DIR = $(APPLICATIONS_DIR)/end_of_block
    #@ echo $(error END_OF_BLOCK_DIR = $(END_OF_BLOCK_DIR))
    OPT += -DHAS_END_OF_BLOCK

    INCDIR += -I$(END_OF_BLOCK_DIR)

    SOURCES_C += $(END_OF_BLOCK_DIR)/end_of_block.c
    SOURCES_C += $(END_OF_BLOCK_DIR)/end_of_block_config.c

    ifeq ($(DIAG),Y)
        SOURCES_C += $(END_OF_BLOCK_DIR)/end_of_block_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(END_OF_BLOCK_COMMANDS),Y)
            OPT += -DHAS_END_OF_BLOCK_COMMANDS
            SOURCES_C += $(END_OF_BLOCK_DIR)/end_of_block_commands.c
        endif
    endif
endif


