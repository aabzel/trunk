ifneq ($(ACC_MK_INC),Y)
    ACC_MK_INC=Y

    ACC_DIR = $(MCAL_COMMON_DIR)/acc
    # $(error ACC_DIR=$(ACC_DIR))

    INCDIR += -I$(ACC_DIR)

    MCAL_OPT += -DHAS_ACC

    ifeq ($(ACC_PROC),Y)
        MCAL_OPT += -DHAS_ACC_PROC
    endif

    SOURCES_C += $(ACC_DIR)/acc_general.c


    # must be outside
    SOURCES_C += $(ACC_DIR)/acc_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(ACC_DIAG),Y)
            MCAL_OPT += -DHAS_ACC_DIAG
            SOURCES_C += $(ACC_DIR)/acc_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ACC_COMMANDS),Y)
            MCAL_OPT += -DHAS_ACC_COMMANDS
            SOURCES_C += $(ACC_DIR)/acc_commands.c
        endif
    endif
endif
