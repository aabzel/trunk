$(info BH1750_MK_INC=$(BH1750_MK_INC) )
ifneq ($(BH1750_MK_INC),Y)
    BH1750_MK_INC=Y
    BH1750_DIR = $(ASICS_DIR)/bh1750
    #@echo $(error BH1750_DIR=$(BH1750_DIR))
    $(info + BH1750)

    INCDIR += -I$(BH1750_DIR)
    MCAL_OPT += -DHAS_BH1750
    MCAL_OPT += -DHAS_BH1750_PROC

    I2C=Y
    MCAL_OPT += -DHAS_I2C

    SOURCES_C += $(BH1750_DIR)/bh1750_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(BH1750_DIAG),Y)
            $(info Add BH1750_DIAG)
            MCAL_OPT += -DHAS_BH1750_DIAG
            SOURCES_C += $(BH1750_DIR)/bh1750_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BH1750_COMMANDS),Y)
            #@echo $(error BH1750_COMMANDS=$(BH1750_COMMANDS))
            $(info Add BH1750_COMMANDS)
            MCAL_OPT += -DHAS_BH1750_COMMANDS
            SOURCES_C += $(BH1750_DIR)/bh1750_commands.c
        endif
    endif
endif
