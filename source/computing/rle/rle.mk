$(info RLE_MK_INC=$(RLE_MK_INC))

ifneq ($(RLE_MK_INC),Y)
    RLE_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    RLE_DIR = $(COMPUTING_DIR)/rle
    #@echo $(error RLE_DIR = $(RLE_DIR))

    OPT += -DHAS_RLE
    INCDIR += -I$(RLE_DIR)

    SOURCES_C += $(RLE_DIR)/rle_encode.c
    SOURCES_C += $(RLE_DIR)/rle_decode.c

    ifeq ($(DIAG),Y)
        OPT += -DHAS_RLE_DIAG
        SOURCES_C += $(RLE_DIR)/rle_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(RLE_COMMANDS),Y)
            #@echo $(error RLE_COMMANDS = $(RLE_COMMANDS))
            OPT += -DHAS_RLE_COMMANDS
            SOURCES_C += $(RLE_DIR)/rle_commands.c
        endif
    endif
endif
