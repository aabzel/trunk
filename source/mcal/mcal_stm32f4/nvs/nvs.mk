ifneq ($(NVS_CUSTOM_MK),Y)
    NVS_CUSTOM_MK=Y

    NVS_CUSTOM_DIR = $(MCAL_STM32F4_DIR)/nvs
    # $(error NVS_CUSTOM_DIR=$(NVS_CUSTOM_DIR))

    INCDIR += -I$(NVS_CUSTOM_DIR)
    MCAL_OPT += -DHAS_NVS_CUSTOM

    #SOURCES_C += $(NVS_CUSTOM_DIR)/nvs_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(NVS_DIAG),Y)
            $(info Add NVS Custom diag)
            MCAL_OPT += -DHAS_NVS_CUSTOM_DIAG
            SOURCES_C += $(NVS_CUSTOM_DIR)/nvs_custom_diag.c
        endif
    endif

    ifeq ($(NVS_WRITE),Y)
        $(info Add NVS write)
        # $(error NVS_WRITE=$(NVS_WRITE))
        MCAL_OPT += -DHAS_NVS_WRITE
    endif

    ifeq ($(CLI),Y)
        ifeq ($(NVS_COMMANDS),Y)
            $(info Add NVS commands)
            MCAL_OPT += -DHAS_NVS_CUSTOM_COMMANDS
            SOURCES_C += $(NVS_CUSTOM_DIR)/nvs_custom_commands.c
        endif
    endif
endif
