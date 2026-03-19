ifneq ($(MAM_GENERAL_MK_INC),Y)
    MAM_GENERAL_MK_INC=Y

    MAM_GENERAL_DIR = $(MCAL_COMMON_DIR)/mam
    # $(error MAM_GENERAL_DIR=$(MAM_GENERAL_DIR))

    INCDIR += -I$(MAM_GENERAL_DIR)

    MCAL_OPT += -DHAS_MAM

    ifeq ($(MAM_PROC),Y)
        MCAL_OPT += -DHAS_MAM_PROC
    endif

    SOURCES_C += $(MAM_GENERAL_DIR)/mam_general.c

    ifeq ($(MAM_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_MAM_INTERRUPTS
        SOURCES_C += $(MAM_GENERAL_DIR)/mam_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(MAM_DIAG),Y)
            MCAL_OPT += -DHAS_MAM_DIAG
            SOURCES_C += $(MAM_GENERAL_DIR)/mam_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MAM_COMMANDS),Y)
            MCAL_OPT += -DHAS_MAM_COMMANDS
            SOURCES_C += $(MAM_GENERAL_DIR)/mam_commands.c
        endif
    endif
endif
