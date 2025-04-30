$(info BLACK_BOX_MK_LOG=$(BLACK_BOX_MK_LOG))

ifneq ($(BLACK_BOX_MK_LOG),Y)
    BLACK_BOX_DRV_MK_LOG=Y

    BLACK_BOX_DRV_DIR = $(STORAGE_DIR)/black_box
    #@echo $(error BLACK_BOX_DRV_DIR= $(BLACK_BOX_DRV_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))

    INCDIR += -I$(BLACK_BOX_DRV_DIR)

    BLACK_BOX=Y
    OPT += -DHAS_BLACK_BOX
    OPT += -DHAS_BLACK_BOX_PROC

    SOURCES_C += $(BLACK_BOX_DRV_DIR)/black_box.c

    ifeq ($(DIAG),Y)
        OPT += -DHAS_BLACK_BOX_DIAG
        SOURCES_C += $(BLACK_BOX_DRV_DIR)/black_box_diag.c
    endif

    ifeq ($(BLACK_BOX_COMMANDS),Y)
        OPT += -DHAS_BLACK_BOX_COMMANDS
        #@echo $(error BLACK_BOX_COMMANDS= $(BLACK_BOX_COMMANDS))
        SOURCES_C +=  $(BLACK_BOX_DRV_DIR)/black_box_commands.c
    endif
endif