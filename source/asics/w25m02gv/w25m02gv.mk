ifneq ($(W25M02GV_MK_INC),Y)
    W25M02GV_MK_INC=Y

    W25M02GV_DIR = $(ASICS_DIR)/w25m02gv
    #@echo $(error W25M02GV_DIR=$(W25M02GV_DIR))

    INCDIR += -I$(W25M02GV_DIR)

    OPT += -DHAS_W25M02GV
    OPT += -DHAS_W25M02GV_PROC

    SOURCES_C += $(W25M02GV_DIR)/w25m02gv.c

    ifeq ($(DIAG),Y)
        ifeq ($(W25M02GV_DIAG),Y)
            OPT += -DHAS_W25M02GV_DIAG
            SOURCES_C += $(W25M02GV_DIR)/w25m02gv_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(W25M02GV_COMMANDS),Y)
            OPT += -DHAS_W25M02GV_COMMANDS
            SOURCES_C += $(W25M02GV_DIR)/w25m02gv_commands.c
        endif
    endif
endif
