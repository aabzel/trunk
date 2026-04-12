ifneq ($(HASH_TABLE_MK_INC),Y)
    HASH_TABLE_MK_INC=Y

    HASH_TABLE_DIR = $(ADT_DIR)/hash_table
    # $(error HASH_TABLE_DIR=$(HASH_TABLE_DIR))

    INCDIR += -I$(HASH_TABLE_DIR)

    MCAL_OPT += -DHAS_HASH_TABLE

    ifeq ($(HASH_TABLE_PROC),Y)
        MCAL_OPT += -DHAS_HASH_TABLE_PROC
    endif

    SOURCES_C += $(HASH_TABLE_DIR)/hash_table.c

    # must be outside
    SOURCES_C += $(HASH_TABLE_DIR)/hash_table_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(HASH_TABLE_DIAG),Y)
            MCAL_OPT += -DHAS_HASH_TABLE_DIAG
            SOURCES_C += $(HASH_TABLE_DIR)/hash_table_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(HASH_TABLE_COMMANDS),Y)
            MCAL_OPT += -DHAS_HASH_TABLE_COMMANDS
            SOURCES_C += $(HASH_TABLE_DIR)/hash_table_commands.c
        endif
    endif
endif
