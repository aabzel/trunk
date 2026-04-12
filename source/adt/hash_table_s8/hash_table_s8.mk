ifneq ($(HASH_TABLE_S8_MK_INC),Y)
    HASH_TABLE_S8_MK_INC=Y

    HASH_TABLE_S8_DIR = $(ADT_DIR)/hash_table_s8
    # $(error HASH_TABLE_S8_DIR=$(HASH_TABLE_S8_DIR))

    INCDIR += -I$(HASH_TABLE_S8_DIR)

    MCAL_OPT += -DHAS_HASH_TABLE_S8

    ifeq ($(HASH_TABLE_S8_PROC),Y)
        MCAL_OPT += -DHAS_HASH_TABLE_S8_PROC
    endif

    SOURCES_C += $(HASH_TABLE_S8_DIR)/hash_table_s8.c

    # must be outside
    SOURCES_C += $(HASH_TABLE_S8_DIR)/hash_table_s8_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(HASH_TABLE_S8_DIAG),Y)
            MCAL_OPT += -DHAS_HASH_TABLE_S8_DIAG
            SOURCES_C += $(HASH_TABLE_S8_DIR)/hash_table_s8_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(HASH_TABLE_S8_COMMANDS),Y)
            MCAL_OPT += -DHAS_HASH_TABLE_S8_COMMANDS
            SOURCES_C += $(HASH_TABLE_S8_DIR)/hash_table_s8_commands.c
        endif
    endif
endif
