ifneq ($(NVS_MCAL_MK_INC),Y)
    NVS_MCAL_MK_INC=Y

    NVS_MCAL_DIR = $(MCAL_COMMON_DIR)/nvs
    #$(error NVS_MCAL_DIR=$(NVS_MCAL_DIR))

    INCDIR += -I$(NVS_MCAL_DIR)

    MCAL_OPT += -DHAS_NVS

    ifeq ($(NVS_PROC),Y)
        MCAL_OPT += -DHAS_NVS_PROC
    endif

    SOURCES_C += $(NVS_MCAL_DIR)/nvs_general.c

    ifeq ($(NVS_WRITE),Y)
        # $(error NVS_WRITE=$(NVS_WRITE))
        MCAL_OPT += -DHAS_NVS_WRITE
        SOURCES_C += $(NVS_MCAL_DIR)/nvs_write.c
    endif

    ifeq ($(NVS_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_NVS_INTERRUPTS
        SOURCES_C += $(NVS_MCAL_DIR)/nvs_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(NVS_DIAG),Y)
            MCAL_OPT += -DHAS_NVS_DIAG
            SOURCES_DIAG_C += $(NVS_MCAL_DIR)/nvs_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(NVS_COMMANDS),Y)
            MCAL_OPT += -DHAS_NVS_COMMANDS
            SOURCES_C += $(NVS_MCAL_DIR)/nvs_commands.c
        endif
    endif
endif
