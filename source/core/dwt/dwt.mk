ifneq ($(DWT_MK_INC),Y)
    DWT_MK_INC=Y

    DWT_DIR = $(CORE_DIR)/dwt
    # $(error DWT_DIR=$(DWT_DIR))

    INCDIR += -I$(DWT_DIR)

    MCAL_OPT += -DHAS_DWT

    MCAL_OPT += -DHAS_DWT_PROC
    #ifeq ($(DWT_PROC),Y)
    #endif

    SOURCES_C += $(DWT_DIR)/dwt_mcal.c

    # must be outside
    SOURCES_CONFIGURATION_C += $(DWT_DIR)/dwt_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(DWT_DIAG),Y)
            MCAL_OPT += -DHAS_DWT_DIAG
            SOURCES_DIAG_C += $(DWT_DIR)/dwt_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DWT_COMMANDS),Y)
            MCAL_OPT += -DHAS_DWT_COMMANDS
            SOURCES_C += $(DWT_DIR)/dwt_commands.c
        endif
    endif
endif
