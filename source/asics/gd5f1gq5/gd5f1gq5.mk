ifneq ($(GD5F1GQ5_MK_INC),Y)
    GD5F1GQ5_MK_INC=Y

    GD5F1GQ5_DIR = $(ASICS_DIR)/gd5f1gq5
    # $(error GD5F1GQ5_DIR=$(GD5F1GQ5_DIR))

    INCDIR += -I$(GD5F1GQ5_DIR)

    MCAL_OPT += -DHAS_GD5F1GQ5
    MCAL_OPT += -DHAS_GD5F1GQ5_PROC

    SOURCES_C += $(GD5F1GQ5_DIR)/gd5f1gq5_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(GD5F1GQ5_DIAG),Y)
            MCAL_OPT += -DHAS_GD5F1GQ5_DIAG
            SOURCES_DIAG_C += $(GD5F1GQ5_DIR)/gd5f1gq5_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(GD5F1GQ5_COMMANDS),Y)
            MCAL_OPT += -DHAS_GD5F1GQ5_COMMANDS
            SOURCES_C += $(GD5F1GQ5_DIR)/gd5f1gq5_commands.c
        endif
    endif
endif
