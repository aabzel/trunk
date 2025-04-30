$(info SWD_COMMON_MCAL_MK_INC=$(SWD_COMMON_MCAL_MK_INC) )

ifneq ($(SWD_COMMON_MCAL_MK_INC),Y)
    SWD_COMMON_MCAL_MK_INC=Y

    SWD_MCAL_DIR = $(MCAL_COMMON_DIR)/swd
    #@echo $(error SWD_MCAL_DIR=$(SWD_MCAL_DIR))

    INCDIR += -I$(SWD_MCAL_DIR)
    OPT += -DHAS_SWD
    #OPT += -DHAS_SWD_PROC

    SOURCES_C += $(SWD_MCAL_DIR)/swd_general.c

    ifeq ($(SWD_DIAG),Y)
        SOURCES_C += $(SWD_MCAL_DIR)/swd_diag.c
    endif

    ifeq ($(SWD_COMMANDS),Y)
        OPT += -DHAS_SWD_COMMANDS
        SOURCES_C += $(SWD_MCAL_DIR)/swd_commands.c
    endif
endif



