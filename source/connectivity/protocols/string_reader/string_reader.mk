$(info STRING_READER_DRV_MK_LOG=$(STRING_READER_DRV_MK_LOG))

ifneq ($(STRING_READER_DRV_MK_LOG),Y)
    STRING_READER_DRV_MK_LOG=Y
    STRING_READER_DRV_DIR = $(PROTOCOLS_DIR)/string_reader
    #@echo $(error READER_DRV_DIR= $(READER_DRV_DIR))
 
    $(info Build  READER driver)
 

    INCDIR += -I$(STRING_READER_DRV_DIR)

    READER=Y
    OPT += -DHAS_READER_CMD_HISTORY
    OPT += -DHAS_STRING_READER
    OPT += -DHAS_STRING_READER_PROC

    SOURCES_C += $(STRING_READER_DRV_DIR)/string_reader.c

    ifeq ($(STRING_READER_DIAG),Y)
        OPT += -DHAS_STRING_READER_DIAG
        SOURCES_C +=  $(STRING_READER_DRV_DIR)/string_reader_diag.c
    endif

    ifeq ($(STRING_READER_COMMANDS),Y)
        OPT += -DHAS_STRING_READER_COMMANDS
        #@echo $(error STRING_READER_COMMANDS= $(STRING_READER_COMMANDS))
        SOURCES_C +=  $(STRING_READER_DRV_DIR)/string_reader_commands.c
    endif
endif